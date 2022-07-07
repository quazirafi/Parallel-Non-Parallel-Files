#include "stdio.h" // printf
#include "stdlib.h" // malloc and rand for instance. Rand not thread safe!
#include "time.h"   // time(0) to get random seed
#include "math.h"  // sine and cosine
#include "omp.h"
#include <string.h>
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define DIM 2
#define MAX_PARTICLES 500
#define G 6.67408e-11
#define CYCLES 100
#define DELTA_T 0.05

typedef double vect_t[DIM];

void computeForcesSimple(vect_t* pos, double* masses, vect_t* forces);
void computeForcesReduced(vect_t* pos, double* masses, vect_t* forces);
void initParticles(vect_t* pos, vect_t* vel, double* masses);
void move_particles(vect_t* pos, vect_t* vel, double* masses, vect_t* forces);
double mysecond();

int main(void) {

  vect_t* pos = (vect_t*) malloc (MAX_PARTICLES*sizeof(vect_t));
  vect_t* vel = (vect_t*) malloc (MAX_PARTICLES*sizeof(vect_t));
  vect_t* forces = (vect_t*) malloc (MAX_PARTICLES*sizeof(vect_t));
  double* masses = (double*) malloc (MAX_PARTICLES*sizeof(double));
  double t1, t2;

  initParticles(pos, vel, masses);
  //computeForces(pos, masses, forces);

  t1 = mysecond();

			dummyMethod3();
  for(int step = 0; step <= CYCLES/DELTA_T ; step++) {
    forces = memset(forces, 0, MAX_PARTICLES*sizeof(vect_t));
    //computeForcesSimple(pos, masses, forces);
    computeForcesReduced(pos, masses, forces);
    move_particles(pos, vel, masses, forces);
  }
			dummyMethod4();

  t2 = mysecond();

  printf("Algorithm run time: %f s\n", t2-t1);

  /*for(int q = 0; q < MAX_PARTICLES; q++) {
    printf("Particle%d -> X: %f, Y: %f, VelX: %f, VelY: %f\n", q+1, pos[q][1], pos[q][2], vel[q][0], vel[q][1]);
  }*/
}

void move_particles(vect_t* pos, vect_t* vel, double* masses, vect_t* forces) {
			dummyMethod3();
  for(int q = 0; q < MAX_PARTICLES; q++) {
    pos[q][1] += DELTA_T*vel[q][1]; 
    pos[q][2] += DELTA_T*vel[q][2]; 
    vel[q][1] += DELTA_T/masses[q]*forces[q][1]; 
    vel[q][2] += DELTA_T/masses[q]*forces[q][2];
  }
			dummyMethod4();
}

void computeForcesSimple(vect_t* pos, double* masses, vect_t* forces) {
			dummyMethod1();
  #pragma omp parallel for collapse(2)
  for(int q = 0; q < MAX_PARTICLES; q++) {
    for(int k = 0; k < MAX_PARTICLES; k++) {
      if(k == q) {
        continue;
      }
      double x_diff = pos[q][0] - pos[k][0];
      double y_diff = pos[q][1] - pos[k][1];

      double dist = sqrt(x_diff*x_diff + y_diff*y_diff);
      double dist_cubed = dist*dist*dist;

      forces[q][0] -= G*masses[q]*masses[k]/dist_cubed * x_diff;
      forces[q][1] -= G*masses[q]*masses[k]/dist_cubed * y_diff;
    }
  }
			dummyMethod2();
}

void computeForcesReduced(vect_t* pos, double* masses, vect_t* forces) {
			dummyMethod1();
  #pragma omp parallel for
  for(int q = 0; q < MAX_PARTICLES; q++) {
    for(int k=q+1; k < MAX_PARTICLES; k++) {
      vect_t force_qk;

      double x_diff = pos[q][0] - pos[k][0];
      double y_diff = pos[q][1] - pos[k][1];

      double dist = sqrt(x_diff*x_diff + y_diff*y_diff);
      double dist_cubed = dist*dist*dist;

      force_qk[0] = G*masses[q]*masses[k]/dist_cubed * x_diff;
      force_qk[1] = G*masses[q]*masses[k]/dist_cubed * y_diff;
      
      forces[q][0] += force_qk[0];
      forces[q][1] += force_qk[1];
      forces[k][0] -= force_qk[0];
      forces[k][1] -= force_qk[1];
    }
  }
			dummyMethod2();
}
  
void initParticles(vect_t* pos, vect_t* vel, double* masses) {
			dummyMethod3();
  for(int q = 0; q < MAX_PARTICLES; q++) {
    pos[q][0] = (rand() / (double)(RAND_MAX)) * 2 - 1;
		pos[q][1] = (rand() / (double)(RAND_MAX)) * 2 - 1;

		vel[q][0] = (rand() / (double)(RAND_MAX)) * 2 - 1;
		vel[q][1] = (rand() / (double)(RAND_MAX)) * 2 - 1;
		
		masses[q] = fabs((rand() / (double)(RAND_MAX)) * 2 - 1);
  }
			dummyMethod4();
}

// function with timer                                                             
double mysecond(){
  struct timeval tp;
  struct timezone tzp;
  int i;

  i = gettimeofday(&tp,&tzp);
  return ( (double) tp.tv_sec + (double) tp.tv_usec * 1.e-6 );
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