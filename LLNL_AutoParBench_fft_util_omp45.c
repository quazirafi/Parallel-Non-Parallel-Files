#include <complex.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "mytypes.h"
#include "pf3d_fft.h"
#include "util.h"
#include "runparm.h"
#include "pf3dbench.h"

#define dns(a,b,c) dns[CELTNDX3(a,b,c)]
#define grd(a,b,c) grd[CELTNDX(a,b,c)]


void fft_norm_omp45(rcomplex *grd, int numx, int numy, int numz, int lenFFTx, int lenFFTy)
{
  real fac;

  fac = 1.0 / (lenFFTx * lenFFTy);
#pragma omp target teams num_teams(num_teams) is_device_ptr(grd) map(to:numx,numy,numz,fac)
  {
    int ix, iy, iz;

    /* NOTE - FFT normalization is performed only after the FFT result
       is back in the pF3D array with guard zones.
    */
dummyMethod1();
#pragma omp distribute parallel for collapse(3)
    for(iz= 0; iz < numz; iz++) {
      for(iy= 0; iy < numy; iy++) {
        for(ix= 0; ix < numx; ix++) {
          /* grd(ix,iy,iz) *= fac; */
          grd[ ((iz*(nyl+1))+iy)*(nxl+1)+ix ] *= fac;
        }
      }
    }
dummyMethod2();
  }
}

void guard2dense_omp45(rcomplex *grd, rcomplex *dns, int nxl, int nyl, int nzl)
{
#pragma omp target teams num_teams(num_teams) is_device_ptr(grd, dns)
  {
    int ix, iy, iz;

    /* grd must have guard zones like t0 and other light waves.
       dns has no guard zones.
       NOTE - this function is always called for arrays where
       the x-index varies fastest (i.e. normal pF3D order).
       Array dimensions are the normal nxl-by-nyl-by-nzl. */
							dummyMethod1();
#pragma omp distribute parallel for collapse(3)
    for(iz= 0; iz < nzl; iz++) {
      for(iy= 0; iy < nyl; iy++) {
        for(ix= 0; ix < nxl; ix++) {
          dns(ix,iy,iz)= grd(ix,iy,iz);
        }
      }
    }
							dummyMethod2();
  }
}

void dense2guard_omp45(rcomplex *dns, rcomplex *grd, int nxl, int nyl, int nzl)
{
#pragma omp target teams num_teams(num_teams) is_device_ptr(grd, dns)
  {
    int ix, iy, iz;

    /* grd must have guard zones like t0 and other light waves.
       dns has no guard zones.
       NOTE - this function is always called for arrays where
       the x-index varies fastest (i.e. normal pF3D order).
       Array dimensions are the normal nxl-by-nyl-by-nzl. */
							dummyMethod1();
  #pragma omp distribute parallel for collapse(3)
    for(iz= 0; iz < nzl; iz++) {
      for(iy= 0; iy < nyl; iy++) {
        for(ix= 0; ix < nxl; ix++) {
          grd(ix,iy,iz)= dns(ix,iy,iz);
        }
      }
    }
							dummyMethod2();
  }
}

void dense2dbl_omp45(rcomplex *dns, dcomplex *dbl, int num_i, int num_j,
               int num_k)
{
  /* dns and dbl have no guard zones. dbl is definitely
     "complex double". dns is usually "complex float" but sometimes
     is "complex double".
     WARNING - this function might operate on nxl-by-nyl-by-nzl arrays,
     nxfull-by-nrows-by-nzl arrays, or nyfull-by-ncols-by-nzl arrays.
     Because the array is dense, compute the length and treat as 1D. */
#pragma omp target teams num_teams(num_teams) is_device_ptr(dbl, dns)
  {
    long i, nvals;

    nvals= num_i*(long)num_j*num_k;
  
							dummyMethod1();
  #pragma omp distribute parallel for
    for(i= 0; i < nvals; i++) {
      dbl[i]= dns[i];
    }
							dummyMethod2();
  }
}

void dbl2dense_omp45(dcomplex *dbl, rcomplex *dns, int num_i, int num_j,
               int num_k)
{
  /* dns and dbl have no guard zones. dbl is definitely
     "complex double". dns is usually "complex float" but sometimes
     is "complex double".
     WARNING - this function might operate on nxl-by-nyl-by-nzl arrays,
     nxfull-by-nrows-by-nzl arrays, or nyfull-by-ncols-by-nzl arrays.
     Because the array is dense, compute the length and treat as 1D. */
#pragma omp target teams num_teams(num_teams) is_device_ptr(dbl, dns)
  {
    long i, nvals;

    nvals= num_i*(long)num_j*num_k;

							dummyMethod1();
  #pragma omp distribute parallel for
    for(i= 0; i < nvals; i++) {
      dns[i]= dbl[i];
    }
							dummyMethod2();
  }
}


void trans_to_omp45(rcomplex *ibuf, rcomplex *obuf, int numx, int numy, int numz)
{
#pragma omp target teams num_teams(num_teams) is_device_ptr(ibuf, obuf)
  {
    int i, j, k;

    /* transpose from row-major to column-major */
							dummyMethod1();
#pragma omp distribute parallel for collapse(3)
    for(k=0; k<numz; k++) {
      for(i=0; i<numx; i++) {
        for(j=0; j<numy; j++) {
          obuf[j+i*numy+k*numx*numy]= ibuf[i+j*numx+k*numx*numy];
        }
      }
    }
							dummyMethod2();
  }
}

void trans_from_omp45(rcomplex *ibuf, rcomplex *obuf, int numx, int numy, int numz)
{
#pragma omp target teams num_teams(num_teams) is_device_ptr(ibuf, obuf)
  {
    int i, j, k;

    /* transpose back from obuf to ecolumn-major to row-major */
							dummyMethod1();
#pragma omp distribute parallel for collapse(3)
    for(k=0; k<numz; k++) {
      for(j=0; j<numy; j++) {
        for(i=0; i<numx; i++) {
          obuf[i+j*numx+k*numx*numy] = ibuf[j+i*numy+k*numx*numy];
        }
      }
    }
							dummyMethod2();
  }
}

void rows_to_omp45(rcomplex *ibuf, rcomplex *obuf, int chunksize, int nrows,
                   int numP)
{
#pragma omp target teams num_teams(num_teams) map(to:chunksize) is_device_ptr(ibuf, obuf)
  {
    int ip, i, j, iz;
    long bufoff, rowoff;
  
    /*
     * Copy from ibuf to obuf. ibuf is nxl by nrows by mp_p
     * obuf is nx by nrows
     */
							dummyMethod1();
#pragma omp distribute parallel for collapse(3)
    for(iz= 0; iz < nzl; iz++) {
      for(ip= 0; ip < numP; ip++) {
        for (j=0; j<nrows; j++) {
          bufoff= j*nxl+ip*chunksize+iz*nxl*nyl;
          rowoff= j*nxfull+ip*nxl+iz*nxl*nyl;
          for (i=0; i<nxl; i++) {
            obuf[i+rowoff] = ibuf[i+bufoff];
          }
        }
      }
    }
							dummyMethod2();
  }
}

void rows_from_omp45(rcomplex *ibuf, rcomplex *obuf, int chunksize, int nrows,
               int numP)
{
#pragma omp target teams num_teams(num_teams) map(to:chunksize) is_device_ptr(ibuf, obuf)
  {
    int ip, i, j, iz;
    long bufoff, rowoff;

    /*
     * Copy from ibuf to obuf. ibuf is nxfull by nrows
     * obuf is nxl by nrows by mp_p
     */
							dummyMethod1();
#pragma omp distribute parallel for collapse(3)
    for(iz= 0; iz < nzl; iz++) {
      for(ip= 0; ip < numP; ip++) {
        for (j=0; j<nrows; j++) {
          bufoff= j*nxl+ip*chunksize+iz*nxl*nyl;
          rowoff= j*nxfull+ip*nxl+iz*nxl*nyl;
          for (i=0; i<nxl; i++) {
            obuf[i+bufoff] = ibuf[i+rowoff];
          }
        }
      }
    }
							dummyMethod2();
  }
}

void cols_to_omp45(rcomplex *ibuf, rcomplex *obuf, int chunksize, int ncols,
               int numQ)
{
#pragma omp target teams num_teams(num_teams) map(to:chunksize) is_device_ptr(ibuf, obuf)
  {
    int iq, i, j, iz;
    long bufoff, coloff;

    /*
     * Copy from ibuf to obuf. ibuf is nyl by ncols by mp_q
     * obuf is nyfull by ncols
     */
							dummyMethod1();
#pragma omp distribute parallel for collapse(3)
    for(iz= 0; iz < nzl; iz++) {
      for(iq= 0; iq < numQ; iq++) {
        for (i=0; i<ncols; i++) {
          bufoff= i*nyl+iq*chunksize+iz*nxl*nyl;
          coloff= i*nyfull+iq*nyl+iz*nxl*nyl;
          for (j=0; j<nyl; j++) {
            obuf[j+coloff] = ibuf[j+bufoff];
          }
        }
      }
    }
							dummyMethod2();
  }
}

void cols_from_omp45(rcomplex *ibuf, rcomplex *obuf, int chunksize, int ncols,
               int numQ)
{

#pragma omp target teams num_teams(num_teams) map(to:chunksize) is_device_ptr(ibuf, obuf)
  {
    int iq, i, j, iz;
    long bufoff, coloff;

    /*
     * Copy from ibuf to obuf. ibuf is nyfull by ncols
     * obuf is nyl by ncols by mp_q
     */
							dummyMethod1();
#pragma omp distribute parallel for collapse(3)
    for(iz= 0; iz < nzl; iz++) {
      for(iq= 0; iq < numQ; iq++) {
        for (i=0; i<ncols; i++) {
          bufoff= i*nyl+iq*chunksize+iz*nxl*nyl;
          coloff= i*nyfull+iq*nyl+iz*nxl*nyl;
          for (j=0; j<nyl; j++) {
            obuf[j+bufoff] = ibuf[j+coloff];
          }
        }
      }
    }
							dummyMethod2();
  }
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