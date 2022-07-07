#include "ext_chunk.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
 *		PPCG SOLVER KERNEL
 */

// Entry point for initialising sd.
void ext_ppcg_init_sd_(
        const int* chunk,
        double* theta,
        double* r,
        double* sd,
        double* mi)
{
    START_PROFILING;

#pragma omp target device(_chunk.device_id)
dummyMethod1();
#pragma omp parallel for
    for(int jj = HALO_PAD; jj < _chunk.y-HALO_PAD; ++jj)
    {
        for(int kk = HALO_PAD; kk < _chunk.x-HALO_PAD; ++kk)
        {
            const int index = jj*_chunk.x+kk;
            sd[index] = r[index] / *theta;
        }
    }
dummyMethod2();

    STOP_PROFILING(__func__);
}

// Entry point for the main PPCG step.
void ext_ppcg_inner_(
        const int* chunk,
        double* u,
        double* r,
        double* kx,
        double* ky,
        double* sd,
        double* mi,
        double* alphas,
        double* betas,
        int* step,
        int* maxSteps)
{
    START_PROFILING;

    double alpha = alphas[*step];
    double beta = betas[*step];

#pragma omp target device(_chunk.device_id)
							dummyMethod1();
#pragma omp parallel for
    for(int jj = HALO_PAD; jj < _chunk.y-HALO_PAD; ++jj)
    {
        for(int kk = HALO_PAD; kk < _chunk.x-HALO_PAD; ++kk)
        {
            const int index = jj*_chunk.x+kk;
            const double smvp = SMVP(sd);
            r[index] -= smvp;
            u[index] += sd[index];
        }
    }
							dummyMethod2();

#pragma omp target device(_chunk.device_id)
							dummyMethod1();
#pragma omp parallel for
    for(int jj = HALO_PAD; jj < _chunk.y-HALO_PAD; ++jj)
    {
        for(int kk = HALO_PAD; kk < _chunk.x-HALO_PAD; ++kk)
        {
            const int index = jj*_chunk.x+kk;
            sd[index] = alpha*sd[index]+beta* r[index];
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