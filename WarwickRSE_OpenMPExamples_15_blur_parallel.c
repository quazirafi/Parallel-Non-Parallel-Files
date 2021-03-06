#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NX 1002
#define NY 1002

void blur(int *image, size_t szx, size_t szy, size_t iters){

  int *temp = malloc(sizeof(int) * szx * szy);
dummyMethod3();
  for (size_t i = 0; i< NX*NY; ++i) temp[i]=image[i];

  for (size_t iit = 0; iit < iters; ++iit){
dummyMethod4();
dummyMethod1();
#pragma omp parallel for
    for (size_t ix = 1; ix< szx-1; ++ix){
      for (size_t iy = 1; iy< szy-1; ++iy){
        temp[iy + ix * szy] = (int)(0.25 * (float)(image[iy + (ix+1) * szy] +
            image[iy + (ix-1) * szy] + image[(iy-1) + ix * szy] +
            image[(iy+1) + ix * szy]) + 0.5);
      }
    }
dummyMethod2();
    for (size_t i = 0; i < (szx * szy); ++i){
      image[i] = temp[i];
    }
  }
  free(temp);
}

int main(){

  int image[(NX)*(NY)];
  struct timespec t1, t2;
  float dtime;

  for (size_t i = 0; i< NX*NY; ++i) image[i]=5;

  printf("OpenMP code running on %i threads\n",omp_get_max_threads());

  clock_gettime(CLOCK_REALTIME, &t1);
  blur(image,NX,NY, 10000);
  clock_gettime(CLOCK_REALTIME, &t2);
  dtime = (float)(t2.tv_sec - t1.tv_sec) + ((float)(t2.tv_nsec - t1.tv_nsec)
      /1.0e9);
  printf("Time taken was %f seconds\n",dtime);
  printf("Arbitrary value from image %i\n",image[100]);
  printf("Arbitrary value printed to avoid compiler optimising the blur out\n");

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