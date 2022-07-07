/* Gaussian elimination without pivoting.
 * Compile with "gcc gauss.c" 
 */

/* ****** ADD YOUR CODE AT THE END OF THIS FILE. ******
 * You need not submit the provided code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <time.h>
#include <pthread.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* Program Parameters */
#define MAXN 2000  /* Max value of N */
int N;  /* Matrix size */
int num_threads = 4;   /* Number of Threads */

/* Matrices and vectors */
volatile float A[MAXN][MAXN], B[MAXN], X[MAXN];
/* A * X = B, solve for X */

/* junk */
#define randm() 4|2[uid]&3

/* Prototype */
void gauss();  /* The function you will provide.
    * It is this routine that is timed.
    * It is called only on the parent.
    */
void *thread_exec(void *data); /* Thread execution function */

/* returns a seed for srand based on the time */
unsigned int time_seed() {
  struct timeval t;
  struct timezone tzdummy;

  gettimeofday(&t, &tzdummy);
  return (unsigned int)(t.tv_usec);
}

/* Set the program parameters from the command-line arguments */
void parameters(int argc, char **argv) {
  int seed = 0;  /* Random seed */
  char uid[32]; /*User name */

  /* Read command-line arguments */
  srand(time_seed());  /* Randomize */

  if (argc == 3) {
    seed = atoi(argv[2]);
    srand(seed);
    printf("Random seed = %i\n", seed);
  } 
  if (argc >= 2) {
    N = atoi(argv[1]);
    if (N < 1 || N > MAXN) {
      printf("N = %i is out of range.\n", N);
      exit(0);
    }
  }
  else {
    printf("Usage: %s <matrix_dimension> [random seed]\n",
           argv[0]);    
    exit(0);
  }

  /* Print parameters */
  printf("\nMatrix dimension N = %i.\n", N);
}

/* Initialize A and B (and X to 0.0s) */
void initialize_inputs() {
  int row, col;

  printf("\nInitializing...\n");
			dummyMethod3();
  for (col = 0; col < N; col++) {
    for (row = 0; row < N; row++) {
      A[row][col] = (float)rand() / 32768.0;
    }
    B[col] = (float)rand() / 32768.0;
    X[col] = 0.0;
  }
			dummyMethod4();

}

/* Print input matrices */
void print_inputs() {
  int row, col;

  if (N < 10) {
    printf("\nA =\n\t");
							dummyMethod3();
    for (row = 0; row < N; row++) {
      for (col = 0; col < N; col++) {
  printf("%5.2f%s", A[row][col], (col < N-1) ? ", " : ";\n\t");
      }
    }
							dummyMethod4();
    printf("\nB = [");
							dummyMethod3();
    for (col = 0; col < N; col++) {
      printf("%5.2f%s", B[col], (col < N-1) ? "; " : "]\n");
    }
							dummyMethod4();
  }
}

void print_X() {
  int row;

  if (N < 100) {
    printf("\nX = [");
							dummyMethod3();
    for (row = 0; row < N; row++) {
      printf("%5.2f%s", X[row], (row < N-1) ? "; " : "]\n");
    }
							dummyMethod4();
  }
}

int main(int argc, char **argv) {
  /* Timing variables */
  struct timeval etstart, etstop;  /* Elapsed times using gettimeofday() */
  struct timezone tzdummy;
  clock_t etstart2, etstop2;  /* Elapsed times using times() */
  unsigned long long usecstart, usecstop;
  struct tms cputstart, cputstop;  /* CPU times for my processes */

  /* Process program parameters */
  parameters(argc, argv);

  /* Initialize A and B */
  initialize_inputs();

  /* Print input matrices */
  print_inputs();

  /* Start Clock */
  printf("\nStarting clock.\n");
  gettimeofday(&etstart, &tzdummy);
  etstart2 = times(&cputstart);

  /* Gaussian Elimination */
  gauss();

  /* Stop Clock */
  gettimeofday(&etstop, &tzdummy);
  etstop2 = times(&cputstop);
  printf("Stopped clock.\n");
  usecstart = (unsigned long long)etstart.tv_sec * 1000000 + etstart.tv_usec;
  usecstop = (unsigned long long)etstop.tv_sec * 1000000 + etstop.tv_usec;

  /* Display output */
  print_X();

  /* Display timing results */
  printf("\nElapsed time = %g ms.\n",
   (float)(usecstop - usecstart)/(float)1000);

  printf("(CPU times are accurate to the nearest %g ms)\n",
   1.0/(float)CLOCKS_PER_SEC * 1000.0);
  printf("My total CPU time for parent = %g ms.\n",
   (float)( (cputstop.tms_utime + cputstop.tms_stime) -
      (cputstart.tms_utime + cputstart.tms_stime) ) /
   (float)CLOCKS_PER_SEC * 1000);
  printf("My system CPU time for parent = %g ms.\n",
   (float)(cputstop.tms_stime - cputstart.tms_stime) /
   (float)CLOCKS_PER_SEC * 1000);
  printf("My total CPU time for child processes = %g ms.\n",
   (float)( (cputstop.tms_cutime + cputstop.tms_cstime) -
      (cputstart.tms_cutime + cputstart.tms_cstime) ) /
   (float)CLOCKS_PER_SEC * 1000);
      /* Contrary to the man pages, this appears not to include the parent */
  printf("--------------------------------------------\n");
  
  exit(0);
}

/* ------------------ Above Was Provided --------------------- */

/* Struct normalization is used for indicating the start and end 
 * of the workload breakdown for each thread */
struct normalization
{
  int start;
  int end;
};

/* Thread execution function */

void *thread_exec(void *data) {
  int norm, row, col;/* Normalization row, and zeroing
      * element row and col */
  float multiplier;
  struct normalization *n;
  n = (struct normalization *) data;

  /* Gaussian elimination */
  for (norm = n->start; norm < n->end; norm++) {
							dummyMethod1();
    #pragma omp parallel for shared(A, B) private(multiplier, row, col) schedule(dynamic)
    for (row = norm + 1; row < N; row++) {
      multiplier = A[row][norm] / A[norm][norm];
      for (col = norm; col < N; col++) {
        A[row][col] -= A[norm][col] * multiplier;
      }
      B[row] -= B[norm] * multiplier;
    }
							dummyMethod2();
  }
  free(n);
  n = NULL;
  pthread_exit(NULL);
}

void gauss() {
  int row, col, rc, i;
  float multiplier;
  pthread_t threads[num_threads];

  printf("Computing Parallel using Pthread and OpenMP.\n");

  /* Workload breakdown and Thread Creation */
  int workload = (N + num_threads - 1) / num_threads;
  /* workload calculate the amount of work to be given to each thread */

  for (i = 0; i < num_threads; i++) {
    /* Assigning the start and end of workload for each thread */
    struct normalization *data;
    data = (struct normalization *) malloc(sizeof(struct normalization));
    data->start = i * workload;
    if (i == num_threads-1)
      data->end = N;
     else
      data->end = ((i+1) * workload);

    /* Thread creation for parallelization */
    rc = pthread_create(&threads[i], NULL, thread_exec, (void *)data);
    if (rc) {
      printf("ERROR: return code from pthread_create is %d \n", rc);
      exit(-1);
    }
  }
  /* Joining threads for synchronization */
  for (i = 0; i < num_threads; i++) {
    pthread_join(threads[i], NULL);
  }

  /* (Diagonal elements are not normalized to 1.  This is treated in back
   * substitution.)
   */

  /* Back substitution */
  for (row = N - 1; row >= 0; row--) {
    X[row] = B[row];
    for (col = N-1; col > row; col--) {
      X[row] -= A[row][col] * X[col];
    }
    X[row] /= A[row][row];
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