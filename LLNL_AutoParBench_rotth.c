/*
 * rotth.c
 *
 * does rotation of complex array tvar through real angle thetb
 * Input array does NOT have guard cells, so it uses CELTNDX2
 * and CELTNDX3 index macros.
 *
 */

#ifdef _OPENMP
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#endif

#include <stdio.h>

#include "light.h"
#include "pf3dbench.h"
#include "util.h"

#include "runparm.h"
#include "pf3dbenchvars.h"

#define tvar2D(a,b)    tvar[CELTNDX2(a,b)]
#define thetb2D(a,b)   thetb[CELTNDX2(a,b)]
#define tvar3D(a,b,c)  tvar[CELTNDX3(a,b,c)]
#define thetb3D(a,b,c) thetb[CELTNDX3(a,b,c)]
#define IREAL 1
void rotth_z_merge(rcomplex * restrict tvar, real * restrict thetb, int izlo, int izhi)
{
    int  ix, iy, iz;

    /* Collapsing all three loops may be a bad idea on CPUs with SIMD units
       because that could prevent SIMD instruction generation. */
#ifdef _OPENMP
    /* #pragma omp parallel for COLLAPSE(2) */
							dummyMethod1();
#pragma omp parallel for COLLAPSE(2) private(ix, iy, iz)
#endif
    for(iz= izlo; iz <= izhi; iz++) {
      for (iy=0; iy<nyl; iy++) {
#pragma omp simd 
	for (ix=0; ix<nxl; ix++) {
          tvar3D(ix,iy,iz)= tvar3D(ix,iy,iz)*(COS(thetb3D(ix,iy,iz))+SIN(thetb3D(ix,iy,iz)) );
	}
      }
    }
							dummyMethod2();
}

void rotth_z_merge3(rcomplex * restrict tvar, real * restrict thetb, int izlo, int izhi)
{
    int  ix, iy, iz;

    /* Collapsing all three loops may be a bad idea on CPUs with SIMD units
       because that could prevent SIMD instruction generation. */
#ifdef _OPENMP
							dummyMethod1();
#pragma omp parallel for simd COLLAPSE(3)
#endif
    for(iz= izlo; iz <= izhi; iz++) {
      for (iy=0; iy<nyl; iy++) {
	for (ix=0; ix<nxl; ix++) {
          tvar3D(ix,iy,iz)= tvar3D(ix,iy,iz)*(COS(thetb3D(ix,iy,iz))+IREAL*SIN(thetb3D(ix,iy,iz)) );
	}
      }
    }
							dummyMethod2();
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