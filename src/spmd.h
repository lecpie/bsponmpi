#ifndef BSPONMPI_SPMD_H
#define BSPONMPI_SPMD_H

#include <mpi.h>

#include "dllexport.h"

namespace bsplib {

class DLL_LOCAL Spmd {
public:

    explicit Spmd( int nprocs ); // Collective
    ~Spmd();  // Collective

    bool ended() { return m_ended; }
    bool active() { return m_active; }
    int pid() const { return m_pid; }
    int nprocs() const { return m_nprocs; }
    double time() const { return MPI_Wtime() - m_time; }

    int normal_sync(); // return non-zero on error
    int end_sync();   // return non-zero on error

    MPI_Comm comm() const { return m_comm; }

private:
    MPI_Comm m_comm;
    bool m_ended;
    bool m_active;
    double m_time;
    int m_pid;
    int m_nprocs;
};

}

#endif
