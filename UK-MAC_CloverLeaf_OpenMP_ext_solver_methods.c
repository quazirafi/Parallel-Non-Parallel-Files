#include "ext_chunk.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
 *		SHARED SOLVER METHODS
 */

// Entry point to copy U.
void ext_solver_copy_u_(
        const int* chunk,
        double* u0,
        double* u)
{
    START_PROFILING;

#pragma omp target device(_chunk.device_id)
dummyMethod1();
#pragma omp parallel for
    for(int jj = HALO_PAD; jj < _chunk.y-HALO_PAD; ++jj)
    {
        for(int kk = HALO_PAD; kk < _chunk.x-HALO_PAD; ++kk)
        {
            int index = jj*_chunk.x+kk;
            u0[index] = u[index];	
        }
    }
dummyMethod2();

    STOP_PROFILING(__func__);
}

// Entry point for calculating residual.
void ext_calculate_residual_(
        const int* chunk,
        double* u,
        double* u0,
        double* r,
        double* kx,
        double* ky)
{
    START_PROFILING;

#pragma omp target device(_chunk.device_id)
							dummyMethod1();
#pragma omp parallel for
    for(int jj = HALO_PAD; jj < _chunk.y-HALO_PAD; ++jj)
    {
        for(int kk = HALO_PAD; kk < _chunk.x-HALO_PAD; ++kk)
        {
            int index = jj*_chunk.x+kk;
            const double smvp = SMVP(u);
            r[index] = u0[index] - smvp;
        }
    }
							dummyMethod2();

    STOP_PROFILING(__func__);
}

// Entry point for calculating 2norm.
void ext_calculate_2norm_(
        const int* chunk,
        double* buffer,
        double* norm)
{
    START_PROFILING;

    double normTemp = 0.0;
#pragma omp target device(_chunk.device_id)
							dummyMethod1();
#pragma omp parallel for reduction(+:normTemp)
    for(int jj = HALO_PAD; jj < _chunk.y-HALO_PAD; ++jj)
    {
        for(int kk = HALO_PAD; kk < _chunk.x-HALO_PAD; ++kk)
        {
            int index = jj*_chunk.x+kk;
            normTemp += buffer[index]*buffer[index];			
        }
    }
							dummyMethod2();

    *norm = normTemp;

    STOP_PROFILING(__func__);
}

// Entry point for finalising solution.
void ext_solver_finalise_(
        const int* chunk,
        double* energy,
        double* density,
        double* u)
{
    START_PROFILING;

#pragma omp target device(_chunk.device_id)
							dummyMethod1();
#pragma omp parallel for
    for(int jj = HALO_PAD; jj < _chunk.y-HALO_PAD; ++jj)
    {
        for(int kk = HALO_PAD; kk < _chunk.x-HALO_PAD; ++kk)
        {
            int index = jj*_chunk.x+kk;
            energy[index] = u[index]/density[index];
        }
    }
							dummyMethod2();

    STOP_PROFILING(__func__);
}
int dummyMethod1(){
    return 0;
}
int dummyMethod2(){
    return 0;
}
int dummyMethod3(){
    return 0;
}
int dummyMethod4(){
    return 0;
}