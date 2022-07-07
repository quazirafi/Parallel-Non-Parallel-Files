/* This file is only for reference. It might not be compiled successfully,
 * because m_set_procs(), m_get_numprocs() might not be supported. Please
 * write your own parallel version (Pthread, OpenMP, or MPI verion). For
 * instance, you should use pthread_create() and pthread_join() to
 * write a Pthread version, and use MPI initilization and communication
 * functions to write a MPI version.
 * If the compiler reports ulocks.h and task.h header files are missing,
 * just remove those two lines which include these two header files.
 * These two header files are not necessary.
 * Yong Chen (yong.chen@ttu.edu), 2011.
 */

/* Gaussian elimination without pivoting.
 * Compile with "cc -mp -O2 gauss.c"
 */

/* ****** ADD YOUR CODE AT THE END OF THIS FILE. ******
 * You need not submit the provided code.
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <limits.h>
#include <time.h>
#include <unistd.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* Program Parameters */
#define MAXN 2000  /* Max value of N */
static int N;  /* Matrix size */
static int procs;  /* Number of processors to use */
/* Matrices and vectors */
double  **A, **B,**C;
/* A * X = B, solve for X */
/* junk */
#define randm() 4|2[uid]&3
/* Prototype */
/* returns a seed for srand based on the time */
unsigned int time_seed() {
    struct timeval t;
    struct timezone tzdummy;

    gettimeofday(&t, &tzdummy);
    return (unsigned int)(t.tv_usec);
}

/* Set the program parameters from the command-line arguments */
void parameters(int argc, char **argv) {
    int submit = 0;  /* = 1 if submission parameters should be used */
    int seed = 0;  /* Random seed */
    int L_cuserid;
    char uid[L_cuserid+2];
   
    /* Read command-line arguments */
    srand(time_seed());  /* Randomize */
    if (argc != 2) {
        if ( argc == 2 && !strcmp(argv[1], "submit") ) {
            /* Use submission parameters */
	printf("Inside Submission:");
            submit = 1;
            N = 4;
            printf("\nSubmission run.\ni");
            srand(rand());
        }
        else {
            if (argc == 3) {
                seed = atoi(argv[2]);
                srand(seed);
                printf("Random seed = %i\n", seed);
            }
            else {
                printf("Usage: %s <matrix_dimension> [random seed]\n",argv[0]);
                printf("%s submit\n", argv[0]);
                exit(0);
            }
        }
    }
    /* Interpret command-line args */
    if (!submit) {
        N = atoi(argv[1]);
        if (N < 1 || N > MAXN) {
            printf("N = %i is out of range.\n", N);
            exit(0);
        }
      /*  if (procs < 1) {
            printf("Warning: Invalid number of processors = %i.  Using 1.\n", procs);
            procs = 1;
        }
        if (procs >100) {
            printf("Warning: %i processors requested; only %i available.\n",
                   procs,100);
            procs = 100;
        }*/
    }  
    /* Print parameters */
    printf("\nMatrix dimension N = %i.\n", N);
    //printf("Number of processors = %i.\n", procs);

    /* Set number of processors */
   
}

/* Initialize A and B (and X to 0.0s) */
void initialize_inputs() {
    int row, col;

    printf("\nInitializing...\n");
							dummyMethod3();
    for (col = 0; col < N; col++) {
        for (row = 0; row < N; row++) {
            A[row][col] = ceil(rand() / 32768.0);
        }

    }
							dummyMethod4();
	dummyMethod3();
	for (col = 0; col < N; col++) {
        for (row = 0; row < N; row++) {
            B[row][col] = ceil(rand() / 32768.0);
        }

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
                printf("%.1lf%s", A[row][col], (col < N-1) ? ", " : ";\n\t");
            }
        }
															dummyMethod4();
       printf("\nB=\n\t");
													dummyMethod3();
       for(row=0;row<N;row++)
       {
        for(col=0;col<N;col++)
         {
           printf("%.1lf%s",B[row][col],(col < N-1)?",":";\n\t");
         }    
       }
													dummyMethod4();
    }
}
void print_outputs()
{
int row,col;
if(N<10)
{
printf("\nC=\n\t");
dummyMethod3();
for(row=0;row<N;row++)
{
for(col=0;col<N;col++)
{
printf("%.1lf%s",C[row][col],(col < N-1)?",":";\n\t");
}
}
dummyMethod4();
}
}

void main(int argc, char **argv) {
    /* Timing variables */
    struct timeval etstart, etstop;  /* Elapsed times using gettimeofday() */
    struct timezone tzdummy;
    clock_t etstart2, etstop2;  /* Elapsed times using times() */
    unsigned long long usecstart, usecstop;
    struct tms cputstart, cputstop;  /* CPU times for my processes */
    int i,j,k;
    double sum;
  A=(double**) malloc(MAXN*sizeof(double));
					dummyMethod3();
   for(i=0;i<MAXN;i++)
{
A[i]=(double *) malloc(MAXN * sizeof(double));
}
					dummyMethod4();
   B=(double**) malloc(MAXN*sizeof(double));
					dummyMethod3();
   for(i=0;i<MAXN;i++)
{
B[i]=(double *) malloc(MAXN * sizeof(double));
}
					dummyMethod4();
     C=(double**) malloc(MAXN*sizeof(double));
					dummyMethod3();
   for(i=0;i<MAXN;i++)
{
C[i]=(double *) malloc(MAXN * sizeof(double));
}
					dummyMethod4();

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
     
sum=0.0;
   /* Matrix Multiplication */
#pragma omp parallel shared(A,B,C,N) private(i,j)
{
#pragma omp for schedule(static)
dummyMethod3();
for(i=0;i<N;i++)
{
for(j=0;j<N;j++)
{
C[i][j]=0.0;
}
}
dummyMethod4();
}
       
      
	for(i=0;i<N;i++){
                	
                    for(j=0;j<N;j++)
                 {
                
																																			dummyMethod1();
                 #pragma omp parallel for schedule(static) reduction(+:sum) shared(k)
	
                 	for(k=0;k<N;k++)
                              {
                             //  printf("Thread Count : %d",omp_get_num_threads());   
				sum=A[i][k]*B[k][j];
                              }
																																			dummyMethod2();
			
		
         C[i][j]=sum;
         sum=0.0; 
          }
         
	}


    print_outputs();
    /* Stop Clock */
    gettimeofday(&etstop, &tzdummy);
    etstop2 = times(&cputstop);
    printf("Stopped clock.\n");
    usecstart = (unsigned long long)etstart.tv_sec * 1000000 + etstart.tv_usec;
    usecstop = (unsigned long long)etstop.tv_sec * 1000000 + etstop.tv_usec;
   
    /* Display output */

    /* Display timing results */
    printf("\nElapsed time = %g ms.\n",
           (float)(usecstop - usecstart)/(float)1000);
    /*printf("               (%g ms according to times())\n",
     *       (etstop2 - etstart2) / (float)CLK_TCK * 1000);
     */
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