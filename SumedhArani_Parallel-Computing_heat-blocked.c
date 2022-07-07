#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include "heat-blocked.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void heatBlocked(double* A0, double* Anext, int nx, int ny, int nz,
                  int tx, int ty, int tz, int timesteps)
{
	double h = A0[0];
  double *temp_ptr;
  int t, i, ii, j, jj, k;
  omp_set_num_threads(8);

  for (t = 0; t < timesteps; t++) {
    for (jj = 1; jj < ny-1; jj+=ty) {
dummyMethod1();
    	#pragma omp parallel for collapse(2) private(ii,k,i,j) schedule(static)
    	for (ii = 1; ii < nx - 1; ii+=tx) {
				for (k = 1; k < nz - 1; k++) {
dummyMethod2();
  				for (j = jj; j < MIN(jj+ty,ny - 1); j++) {
				    for (i = ii; i < MIN(ii+tx,nx - 1); i++) {
				      Anext[Index3D (nx, ny, i, j, k)] = 
								A0[Index3D (nx, ny, i, j, k + 1)] +
								A0[Index3D (nx, ny, i, j, k - 1)] +
								A0[Index3D (nx, ny, i, j + 1, k)] +
								A0[Index3D (nx, ny, i, j - 1, k)] +
								A0[Index3D (nx, ny, i + 1, j, k)] +
								A0[Index3D (nx, ny, i - 1, j, k)]
								- 6.0 * A0[Index3D (nx, ny, i, j, k)] / (h*h);
	    			}
	  			}
				}
      }
    }
    temp_ptr = A0;
    A0 = Anext;
    Anext = temp_ptr;
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