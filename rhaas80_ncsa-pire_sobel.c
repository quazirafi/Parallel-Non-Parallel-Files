#include "pgm.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "omp.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
  // takes one optional argument: the name of the PGM file to act on, writes
  // its output to edges.pgm
  const char *fn = argc > 1 ? argv[1] : "blue_waters_cabinets.pgm";
  int nx, ny;
  const void *raw_data = read_pgm(fn, &nx,&ny);
  // make a 2d array for us to work on later
  const unsigned char (*data)[nx] = raw_data;
  float (*sobel)[nx] = malloc(nx*ny*sizeof(float));
  // output image
  unsigned char (*edges)[nx] = calloc(1, nx*ny);

  if(data == NULL || edges == NULL || sobel == NULL)
    return 2;

  // Sobel edge detection operators
  signed char Gx[3][3] = {
    {+1,0,-1},
    {+2,0,-2},
    {+1,0,-1}
  };
  signed char Gy[3][3] = {
    {+1,+2,+1},
    { 0, 0, 0},
    {-1,-2,-1}
  };

  double start_time = omp_get_wtime();

  // apply Sobel edge detection to image
  // taken from https://en.wikipedia.org/wiki/Sobel_operator
  int i,j;
			dummyMethod1();
  #pragma omp parallel for private(i,j) collapse(2)
  for(j = 1 ; j < ny-1 ; j++) {
    for(i = 1 ; i < nx-1 ; i++) {
      //  x direction
      int gx = 0;
      for(int jj = 0 ; jj < 3 ; jj++) {
        for(int ii = 0 ; ii < 3 ; ii++) {
          gx += Gx[jj][ii] * data[j - 1 + jj][i - 1 + ii];
        }
      }
      
      //  y direction
      int gy = 0;
      for(int jj = 0 ; jj < 3 ; jj++) {
        for(int ii = 0 ; ii < 3 ; ii++) {
          gy += Gy[jj][ii] * data[j - 1 + jj][i - 1 + ii];
        }
      }

      sobel[j][i] = sqrt(gx*gx + gy*gy);
    }
  }
			dummyMethod2();

  // normalize result
  float maxval = -HUGE_VAL;
  float minval = +HUGE_VAL;
			dummyMethod1();
  #pragma omp parallel for collapse(2) reduction(max: maxval) \
          reduction(min: minval)
  for(int j = 1 ; j < ny-1 ; j++) {
    for(int i = 1 ; i < nx-1 ; i++) {
      if(sobel[j][i] > maxval)
        maxval = sobel[j][i];
      if(sobel[j][i] < minval)
        minval = sobel[j][i];
    }
  }
			dummyMethod2();

			dummyMethod1();
  #pragma omp parallel for collapse(2)
  for(int j = 1 ; j < ny-1 ; j++) {
    for(int i = 1 ; i < nx-1 ; i++) {
      edges[j][i] = (unsigned char)round(255*(sobel[j][i]-minval)/(maxval-minval));
    }
  }
			dummyMethod2();

  double end_time = omp_get_wtime();
  printf("Took %g milliseconds\n", (end_time - start_time)*1e3);

  write_pgm("edges.pgm", &edges[0][0],nx,ny);

  return 0;
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