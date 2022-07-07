#include "ext_chunk.h"
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
 *		CONJUGATE GRADIENT SOLVER KERNEL
 */

// Entry point for CG initialisation.
void ext_cg_solver_init_(
        const int* chunk,
        double* density,
        double* energy,
        double* u,
        double* p,
        double* r,
        double* mi,
        double* w,
        double* z,
        double* kx,
        double* ky,
        const int* coefficient,
        const int* preconditioner,
        double* dt,
        double* rx,
        double* ry,
        double* rro)
{
    if(*coefficient < CONDUCTIVITY && *coefficient < RECIP_CONDUCTIVITY)
    {
        panic(__LINE__, __FILE__, "Coefficient %d is not valid.\n", *coefficient);
    }

    START_PROFILING;
#pragma omp target device(_chunk.device_id)
							dummyMethod1();
#pragma omp parallel for
    for(int jj = 0; jj < _chunk.y; ++jj)
    {
        for(int kk = 0; kk < _chunk.x; ++kk)
        {
            const int index = jj*_chunk.x+kk;
            p[index] = 0.0;
            r[index] = 0.0;
            u[index] = energy[index]*density[index];
        }
    }
							dummyMethod2();

#pragma omp target device(_chunk.device_id)
							dummyMethod1();
#pragma omp parallel for
    for(int jj = 1; jj < _chunk.y-1; ++jj)
    {
        for(int kk = 1; kk < _chunk.x-1; ++kk)
        {
            const int index = jj*_chunk.x+kk;
            w[index] = (*coefficient == CONDUCTIVITY) ? density[index] : 1.0/density[index];
        }
    }
							dummyMethod2();

#pragma omp target device(_chunk.device_id)
							dummyMethod1();
#pragma omp parallel for
    for(int jj = HALO_PAD; jj < _chunk.y-1; ++jj)
    {
        for(int kk = HALO_PAD; kk < _chunk.x-1; ++kk)
        {
            const int index = jj*_chunk.x+kk;
            kx[index] = *rx*(w[index-1]+w[index])/(2.0*w[index-1]*w[index]);
            ky[index] = *ry*(w[index-_chunk.x]+w[index])/(2.0*w[index-_chunk.x]*w[index]);
        }
    }
							dummyMethod2();

    double rroTemp = 0.0;

#pragma omp target device(_chunk.device_id)
							dummyMethod1();
#pragma omp parallel for reduction(+:rroTemp)
    for(int jj = HALO_PAD; jj < _chunk.y-HALO_PAD; ++jj)
    {
        for(int kk = HALO_PAD; kk < _chunk.x-HALO_PAD; ++kk)
        {
            const int index = jj*_chunk.x+kk;
            const double smvp = SMVP(u);
            w[index] = smvp;
            r[index] = u[index]-w[index];
            p[index] = r[index];
            rroTemp += r[index]*p[index];
        }
    }
							dummyMethod2();

    *rro = rroTemp;

    STOP_PROFILING(__func__);
}

// Entry point for calculating w
void ext_cg_calc_w_(
        const int* chunk,
        double* p,
        double* w,
        double* kx,
        double* ky,
        double* pw)
{
    double pwTemp = 0.0;

    START_PROFILING;

#pragma omp target device(_chunk.device_id)
							dummyMethod1();
#pragma omp parallel for reduction(+:pwTemp)
    for(int jj = HALO_PAD; jj < _chunk.y-HALO_PAD; ++jj)
    {
        for(int kk = HALO_PAD; kk < _chunk.x-HALO_PAD; ++kk)
        {
            const int index = jj*_chunk.x+kk;
            const double smvp = SMVP(p);
            w[index] = smvp;
            pwTemp += w[index]*p[index];
        }
    }
							dummyMethod2();

    *pw = pwTemp;

    STOP_PROFILING(__func__);
}

// Entry point for calculating ur
void ext_cg_calc_ur_(
        const int* chunk,
        double* u,
        double* p,
        double* r,
        double* mi,
        double* w,
        double* z,
        const double* alpha,
        double* rrn)
{
    double rrnTemp = 0.0;

    START_PROFILING;
#pragma omp target device(_chunk.device_id)
							dummyMethod1();
#pragma omp parallel for reduction(+:rrnTemp)
    for(int jj = HALO_PAD; jj < _chunk.y-HALO_PAD; ++jj)
    {
        for(int kk = HALO_PAD; kk < _chunk.x-HALO_PAD; ++kk)
        {
            const int index = jj*_chunk.x+kk;

            u[index] += *alpha*p[index];
            r[index] -= *alpha*w[index];
            rrnTemp += r[index]*r[index];
        }
    }
							dummyMethod2();

    *rrn = rrnTemp;
    STOP_PROFILING(__func__);
}

// Entry point for calculating p
void ext_cg_calc_p_(
        const int* chunk,
        double* p,
        double* r,
        double* z,
        const double* beta)
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
            p[index] = *beta*p[index] + r[index];
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