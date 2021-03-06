#include <math.h>    // (in path known to compiler)			needed by exp
#include "omp.h"
#include <stdbool.h> // (in path known to compiler)			needed by true/false
#include <stdio.h>   // (in path known to compiler)			needed by printf
#include <stdlib.h>  // (in path known to compiler)			needed by malloc
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <malloc.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]);

#define fp double

#define NUMBER_PAR_PER_BOX                                                     \
  100 // keep this low to allow more blocks that share shared memory to run
      // concurrently, code does not work for larger than 110, more speedup can
      // be achieved with larger number and no shared memory used

#define NUMBER_THREADS                                                         \
  128 // this should be roughly equal to NUMBER_PAR_PER_BOX for best performance

#define DOT(A, B) ((A.x) * (B.x) + (A.y) * (B.y) + (A.z) * (B.z)) // STABLE

typedef struct {
  fp x, y, z;

} THREE_VECTOR;

typedef struct {
  fp v, x, y, z;

} FOUR_VECTOR;

typedef struct nei_str {

  // neighbor box
  int x, y, z;
  int number;
  long offset;

} nei_str;

typedef struct box_str {

  // home box
  int x, y, z;
  int number;
  long offset;

  // neighbor boxes
  int nn;
  nei_str nei[26];

} box_str;

typedef struct par_str {

  fp alpha;

} par_str;

typedef struct dim_str {

  // input arguments
  int cur_arg;
  int arch_arg;
  int cores_arg;
  int boxes1d_arg;

  // system memory
  long number_boxes;
  long box_mem;
  long space_elem;
  long space_mem;
  long space_mem2;

} dim_str;

// #include "./util/timer/timer.h"			// (in path specified
// here)
#ifdef __cplusplus
extern "C" {
#endif

// Returns the current system time in microseconds
long long get_time() {
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return (tv.tv_sec * 1000000) + tv.tv_usec;
}

#ifdef __cplusplus
}
#endif

// #include "./util/num/num.h"				// (in path specified
// here)
#ifdef __cplusplus
extern "C" {
#endif

int isInteger(char *str) {

  if (*str == '\0') {
    return 0;
  }

			dummyMethod3();
  for (; *str != '\0'; str++) {
    if (*str < 48 ||
        *str >
            57) { // digit characters (need to include . if checking for float)
      return 0;
    }
  }
			dummyMethod4();

  return 1;
}

#ifdef __cplusplus
}
#endif

// #include "./kernel/kernel_cpu.h"				// (in library
// path specified here)
#ifdef __cplusplus
extern "C" {
#endif

void kernel_cpu(par_str par, dim_str dim, box_str *box, FOUR_VECTOR *rv, fp *qv,
                FOUR_VECTOR *fv) {

  // timer
  long long time0;

  time0 = get_time();

  // timer
  long long time1;
  long long time2;
  long long time3;
  long long time4;

  // parameters
  fp alpha;
  fp a2;

  // counters
  int i, j, k, l;

  // home box
  long first_i;
  FOUR_VECTOR *rA;
  FOUR_VECTOR *fA;

  // neighbor box
  int pointer;
  long first_j;
  FOUR_VECTOR *rB;
  fp *qB;

  // common
  fp r2;
  fp u2;
  fp fs;
  fp vij;
  fp fxij, fyij, fzij;
  THREE_VECTOR d;

  time1 = get_time();

  omp_set_num_threads(dim.cores_arg);

  time2 = get_time();

  alpha = par.alpha;
  a2 = 2.0 * alpha * alpha;

  time3 = get_time();

  //======================================================================================================================================================150
  //	PROCESS INTERACTIONS
  //======================================================================================================================================================150

			dummyMethod1();
#pragma omp parallel for private(i, j, k) private(first_i, rA, fA) private(    \
    pointer, first_j, rB, qB) private(r2, u2, fs, vij, fxij, fyij, fzij, d)
  for (l = 0; l < dim.number_boxes; l = l + 1) {

    first_i = box[l].offset; // offset to common arrays

    rA = &rv[first_i];
    fA = &fv[first_i];

    for (k = 0; k < (1 + box[l].nn); k++) {

      if (k == 0) {
        pointer = l; // set first box to be processed to home box
      } else {
        pointer =
            box[l].nei[k - 1].number; // remaining boxes are neighbor boxes
      }

      first_j = box[pointer].offset;

      rB = &rv[first_j];
      qB = &qv[first_j];

      for (i = 0; i < NUMBER_PAR_PER_BOX; i = i + 1) {

        // do for the # of particles in current (home or neighbor) box
        for (j = 0; j < NUMBER_PAR_PER_BOX; j = j + 1) {

          // // coefficients
          r2 = rA[i].v + rB[j].v - DOT(rA[i], rB[j]);
          u2 = a2 * r2;
          vij = exp(-u2);
          fs = 2. * vij;
          d.x = rA[i].x - rB[j].x;
          d.y = rA[i].y - rB[j].y;
          d.z = rA[i].z - rB[j].z;
          fxij = fs * d.x;
          fyij = fs * d.y;
          fzij = fs * d.z;

          // forces
          fA[i].v += qB[j] * vij;
          fA[i].x += qB[j] * fxij;
          fA[i].y += qB[j] * fyij;
          fA[i].z += qB[j] * fzij;

        } // for j

      } // for i

    } // for k

  } // for l
			dummyMethod2();

  time4 = get_time();

  printf("Time spent in different stages of CPU/MCPU KERNEL:\n");

  printf("%15.12f s, %15.12f % : CPU/MCPU: VARIABLES\n",
         (float)(time1 - time0) / 1000000,
         (float)(time1 - time0) / (float)(time4 - time0) * 100);
  printf("%15.12f s, %15.12f % : MCPU: SET DEVICE\n",
         (float)(time2 - time1) / 1000000,
         (float)(time2 - time1) / (float)(time4 - time0) * 100);
  printf("%15.12f s, %15.12f % : CPU/MCPU: INPUTS\n",
         (float)(time3 - time2) / 1000000,
         (float)(time3 - time2) / (float)(time4 - time0) * 100);
  printf("%15.12f s, %15.12f % : CPU/MCPU: KERNEL\n",
         (float)(time4 - time3) / 1000000,
         (float)(time4 - time3) / (float)(time4 - time0) * 100);

  printf("Total time:\n");
  printf("%.12f s\n", (float)(time4 - time0) / 1000000);

} // main

#ifdef __cplusplus
}
#endif

int main(int argc, char *argv[]) {

  // timer
  long long time0;

  time0 = get_time();

  // timer
  long long time1;
  long long time2;
  long long time3;
  long long time4;
  long long time5;
  long long time6;
  long long time7;

  // counters
  int i, j, k, l, m, n;

  // system memory
  par_str par_cpu;
  dim_str dim_cpu;
  box_str *box_cpu;
  FOUR_VECTOR *rv_cpu;
  fp *qv_cpu;
  FOUR_VECTOR *fv_cpu;
  int nh;

  time1 = get_time();

  // assing default values
  dim_cpu.cores_arg = 1;
  dim_cpu.boxes1d_arg = 1;

  // go through arguments
			dummyMethod3();
  for (dim_cpu.cur_arg = 1; dim_cpu.cur_arg < argc; dim_cpu.cur_arg++) {
    // check if -cores
    if (strcmp(argv[dim_cpu.cur_arg], "-cores") == 0) {
      // check if value provided
      if (argc >= dim_cpu.cur_arg + 1) {
        // check if value is a number
        if (isInteger(argv[dim_cpu.cur_arg + 1]) == 1) {
          dim_cpu.cores_arg = atoi(argv[dim_cpu.cur_arg + 1]);
          if (dim_cpu.cores_arg < 0) {
            printf("ERROR: Wrong value to -cores parameter, cannot be <=0\n");
            return 0;
          }
          dim_cpu.cur_arg = dim_cpu.cur_arg + 1;
        }
        // value is not a number
        else {
          printf("ERROR: Value to -cores parameter in not a number\n");
          return 0;
        }
      }
      // value not provided
      else {
        printf("ERROR: Missing value to -cores parameter\n");
        return 0;
      }
    }
    // check if -boxes1d
    else if (strcmp(argv[dim_cpu.cur_arg], "-boxes1d") == 0) {
      // check if value provided
      if (argc >= dim_cpu.cur_arg + 1) {
        // check if value is a number
        if (isInteger(argv[dim_cpu.cur_arg + 1]) == 1) {
          dim_cpu.boxes1d_arg = atoi(argv[dim_cpu.cur_arg + 1]);
          if (dim_cpu.boxes1d_arg < 0) {
            printf("ERROR: Wrong value to -boxes1d parameter, cannot be <=0\n");
            return 0;
          }
          dim_cpu.cur_arg = dim_cpu.cur_arg + 1;
        }
        // value is not a number
        else {
          printf("ERROR: Value to -boxes1d parameter in not a number\n");
          return 0;
        }
      }
      // value not provided
      else {
        printf("ERROR: Missing value to -boxes1d parameter\n");
        return 0;
      }
    }
    // unknown
    else {
      printf("ERROR: Unknown parameter\n");
      return 0;
    }
  }
			dummyMethod4();

  // Print configuration
  printf("Configuration used: cores = %d, boxes1d = %d\n", dim_cpu.cores_arg,
         dim_cpu.boxes1d_arg);

  time2 = get_time();

  par_cpu.alpha = 0.5;

  time3 = get_time();

  // total number of boxes
  dim_cpu.number_boxes =
      dim_cpu.boxes1d_arg * dim_cpu.boxes1d_arg * dim_cpu.boxes1d_arg;

  // how many particles space has in each direction
  dim_cpu.space_elem = dim_cpu.number_boxes * NUMBER_PAR_PER_BOX;
  dim_cpu.space_mem = dim_cpu.space_elem * sizeof(FOUR_VECTOR);
  dim_cpu.space_mem2 = dim_cpu.space_elem * sizeof(fp);

  // box array
  dim_cpu.box_mem = dim_cpu.number_boxes * sizeof(box_str);

  time4 = get_time();

  // allocate boxes
  box_cpu = (box_str *)malloc(dim_cpu.box_mem);

  // initialize number of home boxes
  nh = 0;

  // home boxes in z direction
			dummyMethod3();
  for (i = 0; i < dim_cpu.boxes1d_arg; i++) {
    // home boxes in y direction
    for (j = 0; j < dim_cpu.boxes1d_arg; j++) {
      // home boxes in x direction
      for (k = 0; k < dim_cpu.boxes1d_arg; k++) {

        // current home box
        box_cpu[nh].x = k;
        box_cpu[nh].y = j;
        box_cpu[nh].z = i;
        box_cpu[nh].number = nh;
        box_cpu[nh].offset = nh * NUMBER_PAR_PER_BOX;

        // initialize number of neighbor boxes
        box_cpu[nh].nn = 0;

        // neighbor boxes in z direction
        for (l = -1; l < 2; l++) {
          // neighbor boxes in y direction
          for (m = -1; m < 2; m++) {
            // neighbor boxes in x direction
            for (n = -1; n < 2; n++) {

              // check if (this neighbor exists) and (it is not the same as home
              // box)
              if ((((i + l) >= 0 && (j + m) >= 0 && (k + n) >= 0) == true &&
                   ((i + l) < dim_cpu.boxes1d_arg &&
                    (j + m) < dim_cpu.boxes1d_arg &&
                    (k + n) < dim_cpu.boxes1d_arg) == true) &&
                  (l == 0 && m == 0 && n == 0) == false) {

                // current neighbor box
                box_cpu[nh].nei[box_cpu[nh].nn].x = (k + n);
                box_cpu[nh].nei[box_cpu[nh].nn].y = (j + m);
                box_cpu[nh].nei[box_cpu[nh].nn].z = (i + l);
                box_cpu[nh].nei[box_cpu[nh].nn].number =
                    (box_cpu[nh].nei[box_cpu[nh].nn].z * dim_cpu.boxes1d_arg *
                     dim_cpu.boxes1d_arg) +
                    (box_cpu[nh].nei[box_cpu[nh].nn].y * dim_cpu.boxes1d_arg) +
                    box_cpu[nh].nei[box_cpu[nh].nn].x;
                box_cpu[nh].nei[box_cpu[nh].nn].offset =
                    box_cpu[nh].nei[box_cpu[nh].nn].number * NUMBER_PAR_PER_BOX;

                // increment neighbor box
                box_cpu[nh].nn = box_cpu[nh].nn + 1;
              }

            } // neighbor boxes in x direction
          }   // neighbor boxes in y direction
        }     // neighbor boxes in z direction

        // increment home box
        nh = nh + 1;

      } // home boxes in x direction
    }   // home boxes in y direction
  }     // home boxes in z direction
			dummyMethod4();

  // random generator seed set to random value - time in this case
  srand(time(NULL));

  // input (distances)
  rv_cpu = (FOUR_VECTOR *)malloc(dim_cpu.space_mem);
			dummyMethod3();
  for (i = 0; i < dim_cpu.space_elem; i = i + 1) {
    rv_cpu[i].v =
        (rand() % 10 + 1) / 10.0; // get a number in the range 0.1 - 1.0
    rv_cpu[i].x =
        (rand() % 10 + 1) / 10.0; // get a number in the range 0.1 - 1.0
    rv_cpu[i].y =
        (rand() % 10 + 1) / 10.0; // get a number in the range 0.1 - 1.0
    rv_cpu[i].z =
        (rand() % 10 + 1) / 10.0; // get a number in the range 0.1 - 1.0
  }
			dummyMethod4();

  // input (charge)
  qv_cpu = (fp *)malloc(dim_cpu.space_mem2);
			dummyMethod3();
  for (i = 0; i < dim_cpu.space_elem; i = i + 1) {
    qv_cpu[i] = (rand() % 10 + 1) / 10.0; // get a number in the range 0.1 - 1.0
  }
			dummyMethod4();

  // output (forces)
  fv_cpu = (FOUR_VECTOR *)malloc(dim_cpu.space_mem);
			dummyMethod3();
  for (i = 0; i < dim_cpu.space_elem; i = i + 1) {
    fv_cpu[i].v = 0; // set to 0, because kernels keeps adding to initial value
    fv_cpu[i].x = 0; // set to 0, because kernels keeps adding to initial value
    fv_cpu[i].y = 0; // set to 0, because kernels keeps adding to initial value
    fv_cpu[i].z = 0; // set to 0, because kernels keeps adding to initial value
  }
			dummyMethod4();

  time5 = get_time();

  kernel_cpu(par_cpu, dim_cpu, box_cpu, rv_cpu, qv_cpu, fv_cpu);

  // wfr 20191219 ????????????????????????
  fp tmpfp = fv_cpu[0].v;

  time6 = get_time();

  // dump results
#ifdef OUTPUT
  FILE *fptr;
  fptr = fopen("result.txt", "w");
  for (i = 0; i < dim_cpu.space_elem; i = i + 1) {
    fprintf(fptr, "%f, %f, %f, %f\n", fv_cpu[i].v, fv_cpu[i].x, fv_cpu[i].y,
            fv_cpu[i].z);
  }
  fclose(fptr);
#endif

  free(rv_cpu);
  free(qv_cpu);
  free(fv_cpu);
  free(box_cpu);

  time7 = get_time();

  //======================================================================================================================================================150
  //	DISPLAY TIMING
  //======================================================================================================================================================150

  // printf("Time spent in different stages of the application:\n");

  // printf("%15.12f s, %15.12f % : VARIABLES\n",
  // (float) (time1-time0) / 1000000, (float) (time1-time0) / (float)
  // (time7-time0) * 100); printf("%15.12f s, %15.12f % : INPUT ARGUMENTS\n",
  // (float) (time2-time1) / 1000000, (float) (time2-time1) / (float)
  // (time7-time0) * 100); printf("%15.12f s, %15.12f % : INPUTS\n",
  // (float) (time3-time2) / 1000000, (float) (time3-time2) / (float)
  // (time7-time0) * 100); printf("%15.12f s, %15.12f % : dim_cpu\n",
  // (float) (time4-time3) / 1000000, (float) (time4-time3) / (float)
  // (time7-time0) * 100); printf("%15.12f s, %15.12f % : SYS MEM: ALO\n",
  // (float) (time5-time4) / 1000000, (float) (time5-time4) / (float)
  // (time7-time0) * 100);

  // printf("%15.12f s, %15.12f % : KERNEL: COMPUTE\n",
  // (float) (time6-time5) / 1000000, (float) (time6-time5) / (float)
  // (time7-time0) * 100);

  // printf("%15.12f s, %15.12f % : SYS MEM: FRE\n",
  // (float) (time7-time6) / 1000000, (float) (time7-time6) / (float)
  // (time7-time0) * 100);

  // printf("Total time:\n");
  // printf("%.12f s\n",
  // (float) (time7-time0) / 1000000);

  //======================================================================================================================================================150
  //	RETURN
  //======================================================================================================================================================150

  return 0.0; // always returns 0.0
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