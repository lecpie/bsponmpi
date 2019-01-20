#ifndef BSPONMPI_RDMA_H
#define BSPONMPI_RDMA_H

#include "a2a.h"
#include "unbuf.h"
#include "uintserialize.h"
#include "dllexport.h"

#ifdef HAS_CXX11_UNORDERED_MAP
#include <unordered_map>
#else
#include <tr1/unordered_map>
#endif

#include <mpi.h>

namespace bsplib {

class DLL_LOCAL Rdma { 
public:
        struct Memslot {
        void * addr;
        size_t size;
    };
    typedef size_t MemslotID;

    Rdma( MPI_Comm comm , size_t max_msg_size  )
        : m_first_exchange( comm, max_msg_size )
        , m_second_exchange( comm, max_msg_size )
        , m_pid(m_first_exchange.pid())
        , m_nprocs(m_first_exchange.nprocs())
        , m_register()
        , m_used_slots()
        , m_free_slots()
        , m_send_actions( m_nprocs )
        , m_recv_actions( m_nprocs )
        , m_unbuf( max_msg_size, comm )
        , m_send_push_pop_comm_buf()
        , m_recv_push_pop_comm_buf()
    {}

    void push_reg( void * addr, size_t size );
    void pop_reg( MemslotID slot );

    static MemslotID no_slot() { return MemslotID(-1); }
    static MemslotID null_slot() { return MemslotID(-2); }

    MemslotID lookup_reg( const void * addr ) const
    {   
        if (addr == NULL ) return null_slot();

        Reg::const_iterator i = m_register.find( const_cast<void*>(addr) );
        if (i != m_register.end())
            return i->second.back();
        return no_slot(); 
    }

    bool was_just_pushed( const void * addr ) const 
    { return m_send_push_pop_comm_buf.was_pushed( const_cast<void*>(addr) ); }

    const Memslot & slot( int pid, MemslotID slot ) const
    { return m_used_slots[ slot * m_nprocs + pid ]; }

    void put( const void * src, int dst_pid, MemslotID dst_slot, size_t dst_offset,
            size_t size );

    void hpput( const void * src, int dst_pid, MemslotID dst_slot, size_t dst_offset,
            size_t size );

    void get( int src_pid, MemslotID src_slot, size_t src_offset, void * dst,
            size_t size );

    void hpget( int src_pid, MemslotID src_slot, size_t src_offset, void * dst,
            size_t size );

    void sync( );

private:
#ifdef HAS_CXX11_UNORDERED_MAP
    typedef std::unordered_map< void * , std::list< MemslotID > > Reg;
#else
    typedef std::tr1::unordered_map< void *, std::list< MemslotID > > Reg;
#endif
    A2A m_first_exchange;
    A2A m_second_exchange;
    int m_pid, m_nprocs;
    Reg m_register;
    std::vector< Memslot > m_used_slots;
    std::vector< MemslotID > m_free_slots;

    struct Action { 
        enum Kind { GET, HPPUT, HPGET } kind; 
        int target_pid, src_pid, dst_pid, tag;
        size_t src_addr, dst_addr;
        size_t size;
    };

    struct ActionBuf {
        ActionBuf( int nprocs )
            : m_actions()
            , m_counts( nprocs )
            , m_get_buffer_offset( nprocs )
        {}

        std::vector< Action > m_actions;
        std::vector< size_t > m_counts;
        std::vector< size_t > m_get_buffer_offset;

        void push_back( const Action & action )
        {   
            m_actions.push_back( action );
            m_counts[ action.target_pid ] += 1;
        }

        void set_get_buffer_offset( A2A & buf ) 
        {
            for ( int p = 0; p < buf.nprocs(); ++p ) 
                m_get_buffer_offset[ p ] = buf.send_size( p );
        }

        void serialize( A2A & a2a );
        void deserialize( A2A & a2a );
        void execute( Rdma & rdma );
      
        void clear() 
        {
            m_actions.clear();
            std::fill( m_counts.begin(), m_counts.end(), 0);
            std::fill( m_get_buffer_offset.begin(), m_get_buffer_offset.end(), 0);
        }
    };

    ActionBuf m_send_actions;
    ActionBuf m_recv_actions;
        

    /// Unbuffered communications
    Unbuf m_unbuf;
    
    // Comm structure to exchange push & pop of registers 
    struct PushPopCommBuf {
        std::vector< Memslot >   m_pushed_slots;
        std::vector< MemslotID > m_popped_slots;
        
        void clear()
        { m_pushed_slots.clear(); m_popped_slots.clear(); }

        void serialize( A2A & a2a );
        void deserialize( A2A & a2a );
        void execute( Rdma & rdma );

        bool was_pushed( void * ptr ) const; // for error messages
    };
    PushPopCommBuf m_send_push_pop_comm_buf;
    PushPopCommBuf m_recv_push_pop_comm_buf;

    void write_gets();
    void write_puts();

};

}

#endif
