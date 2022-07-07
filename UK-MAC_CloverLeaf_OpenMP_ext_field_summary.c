#include "ext_chunk.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
 * 		FIELD SUMMARY KERNEL
 * 		Calculates aggregates of values in field.
 */	

#pragma omp declare target

// Entry point for field summary method.
void ext_field_summary_kernel_(
        const int* chunk,
        double* volume,
        double* density,
        double* energy0,
        double* u,
        double* volOut,
        double* massOut,
        double* ieOut,
        double* tempOut)
{
    double vol = 0.0;
    double ie = 0.0;
    double temp = 0.0;
    double mass = 0.0;

							dummyMethod1();
#pragma omp parallel for reduction(+:vol,ie,temp,mass)
    for(int jj = HALO_PAD; jj < _chunk.y-HALO_PAD; ++jj)
    {
        for(int kk = HALO_PAD; kk < _chunk.x-HALO_PAD; ++kk)
        {
            int index = jj*_chunk.x+kk;
            double cellVol = volume[index];
            double cellMass = cellVol*density[index];
            vol += cellVol;
            mass += cellMass;
            ie += cellMass*energy0[index];
            temp += cellMass*u[index];
        }
    }
							dummyMethod2();

    *volOut = vol;
    *ieOut = ie;
    *tempOut = temp;
    *massOut = mass;
}

#pragma omp end declare target
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