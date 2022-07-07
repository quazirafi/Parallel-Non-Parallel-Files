/**
 * Program to scale and project data into 2D and find a centroid
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
  struct to hold arrays attributes
  it is an Structure of Arrays
*/
struct SoA{
  float* x;
  float* y;
  float* z;
  float* mass;
};

// Place phaseballs uniformly in a box, with mass equal to the manhattan distance
int place_uniformly(int sx, int ex, int sy, int ey, int sz, int ez, struct SoA* soa){
  // current phaseball
  int counter = 0;
  // number of phaseballs
  int number_of_phaseballs = (ex-sx+1)*(ey-sy+1)*(ez-sy+1);
  // allocate memeory for the arrays
  soa->x = (float *) malloc(number_of_phaseballs * sizeof(float));
  soa->y = (float *) malloc(number_of_phaseballs * sizeof(float));
  soa->z = (float *) malloc(number_of_phaseballs * sizeof(float));
  soa->mass = (float *) malloc(number_of_phaseballs * sizeof(float));

			dummyMethod3();
  for(int i=sx; i<=ex; i++) {
        for(int j=sy; j<=ey; j++) {
            for(int k=sz; k<=ez; k++) {
                soa->x[counter] = i;
                soa->y[counter] = j;
                soa->z[counter] = k;
                soa->mass[counter] = fabs(i)+fabs(j)+fabs(k);
                counter ++;
            }
        }
    }
			dummyMethod4();
  return number_of_phaseballs;
}

void post_process(struct SoA* soa, float* cx, float* cy, int* length) {
    double mass_sum=0.0;
    double wx=0.0;
    double wy=0.0;

    // uasge of REDUCTION pattern
							dummyMethod1();
    #pragma omp parallel for reduction(+:mass_sum,wx,wy)
    for(int i=0; i<*length; i++){
      mass_sum += soa->mass[i];
      wx += soa->x[i] * soa->mass[i];
      wy += soa->y[i] * soa->mass[i];
    }
							dummyMethod2();

    *cx = wx/mass_sum;
    *cy = wy/mass_sum;

    return;
}

int main(int argc, char** argv) {
    // struct of arrays to store attributes
    struct SoA soa;
    // Set the initial configuration and get the number of phaseballs
    int length_of_arr = place_uniformly(-1000,1000,-100,100,-100,100,&soa);
    // Generate output
    float cx,cy;
    struct timespec start_time;
    struct timespec end_time;
    clock_gettime(CLOCK_MONOTONIC,&start_time);
    post_process(&soa, &cx, &cy, &length_of_arr);
    clock_gettime(CLOCK_MONOTONIC,&end_time);
    long msec = (end_time.tv_sec - start_time.tv_sec)*1000 + (end_time.tv_nsec - start_time.tv_nsec)/1000000;

    // Print output
    printf("Centroid at: %f,%f\n",cx,cy);
    printf("found in %dms\n",msec);

    return EXIT_SUCCESS;
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