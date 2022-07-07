#include <stdio.h>
#include <stdlib.h>
#include "heat.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void heat(double* A0, double* Anext, int nx, int ny, int nz, int timesteps)
{
	double fac = A0[0];
  double *temp_ptr;
  int i, j, k, t;
  for (t = 0; t < timesteps; t++) 
  {
dummyMethod1();
    #pragma omp parallel for
    for (k = 1; k < nz - 1; k++) 
    {
      for (j = 1; j < ny - 1; j++)
      {
      	for (i = 1; i < nx - 1; i++) 
        {
          Anext[Index3D (nx, ny, i, j, k)] = 
            A0[Index3D (nx, ny, i, j, k + 1)] +
            A0[Index3D (nx, ny, i, j, k - 1)] +
            A0[Index3D (nx, ny, i, j + 1, k)] +
            A0[Index3D (nx, ny, i, j - 1, k)] +
            A0[Index3D (nx, ny, i + 1, j, k)] +
            A0[Index3D (nx, ny, i - 1, j, k)]
            - 6.0 * A0[Index3D (nx, ny, i, j, k)] / (fac*fac);
      	}
      }
    }
dummyMethod2();
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