#include "spmd.h"

#include <assert.h>

namespace bsplib { 

Spmd :: Spmd( int nprocs ) 
{
    int mpi_init;
    int world_pid = -1;
    
    MPI_Initialized(&mpi_init);
    assert( mpi_init );
    MPI_Bcast( &nprocs, 1, MPI_INT, 0, MPI_COMM_WORLD );

    MPI_Comm_rank( MPI_COMM_WORLD, & world_pid );
    m_closed = false;
    m_active = world_pid < nprocs;
    MPI_Comm_split( MPI_COMM_WORLD, m_active, world_pid, &m_comm );

    MPI_Comm_size( m_comm, &m_nprocs );
    MPI_Comm_rank( m_comm, &m_pid );

#ifdef HAS_CLOCK_GETTIME
    clock_gettime( CLOCK_MONOTONIC, &m_time );
#else
    m_time = MPI_Wtime();
#endif
}

Spmd :: ~Spmd() {
    assert( m_closed );
    assert( m_comm == MPI_COMM_NULL );
}

int Spmd :: end_sync() {
    int end = 1, total_end = 0;
    MPI_Allreduce( &end, &total_end, 1, MPI_INT, MPI_SUM, m_comm );
    
    if (total_end != m_nprocs)
        return 1;

    return 0;
}

void Spmd :: close() {
    // wait for inactive & active processes to synchronize
    MPI_Barrier( MPI_COMM_WORLD );
    m_closed = true;

    MPI_Comm_free( &m_comm );
    m_comm = MPI_COMM_NULL;

    MPI_Finalize();
}

int Spmd :: normal_sync() {
    int end = 0, total_end = 0;
    MPI_Allreduce( &end, &total_end, 1, MPI_INT, MPI_SUM, m_comm );
    
    if (total_end != 0 )
        return 1;

    return 0;
}

}

