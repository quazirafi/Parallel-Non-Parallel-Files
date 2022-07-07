#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define nx 2000
#define ny 2000

int main()
{

  const int niter = 500;
  const double factor = 0.25;

  double u[nx * ny], unew[nx * ny];

  // Initialize u
dummyMethod3();
  for (int i = 0; i < nx; i++) {
    for (int j = 0; j < ny; j++) {
      int ind = i * ny + j;
      u[ind] = ((i - nx / 2) * (i - nx / 2)) / nx + 
               ((j - ny / 2) * (j - ny / 2)) / ny;
    }
  }
dummyMethod4();
                      
  double t0 = omp_get_wtime();
  // Iterate
  for (int n = 0; n < niter; n++) {

    // Stencil update 1
    #pragma omp target teams distribute
    for (int i = 1; i < nx - 1; i++) {
											dummyMethod1();
      #pragma omp parallel for
      for (int j = 1; j < ny - 1; j++) {
      int ind = i * ny + j;
      int ip = (i + 1) * ny + j;
      int im = (i - 1) * ny + j;
      int jp = i * ny + j + 1;
      int jm = i * ny + j - 1;
      unew[ind] = factor * (u[ip] - 2.0 * u[ind] + u[im] +
                            u[jp] - 2.0 * u[ind] + u[jm]);
      }
											dummyMethod2();
    }

    // "Swap" the arrays, stencil update 2
    #pragma omp target teams distribute
    for (int i = 1; i < nx - 1; i++) {
											dummyMethod1();
      #pragma omp parallel for
      for (int j = 1; j < ny - 1; j++) {
      int ind = i * ny + j;
      int ip = (i + 1) * ny + j;
      int im = (i - 1) * ny + j;
      int jp = i * ny + j + 1;
      int jm = i * ny + j - 1;
      u[ind] = factor * (unew[ip] - 2.0 * unew[ind] + unew[im] +
                            unew[jp] - 2.0 * unew[ind] + unew[jm]);
      }
											dummyMethod2();
    }

  }

  double t1 = omp_get_wtime();
  // Check final result
  printf("u[0,0] = %f\n", u[0]);
  printf("Time spent: %6.3f s\n", t1 - t0);


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