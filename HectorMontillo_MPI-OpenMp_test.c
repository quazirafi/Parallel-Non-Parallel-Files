#include "mpi.h"
#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MASTER 0      /* taskid of first task */
#define FROM_MASTER 1 /* setting a message type */
#define FROM_WORKER 2 /* setting a message type */

int main(int argc, char *argv[])
{
    int MATSIZE = atoi(argv[1]);
    int N = MATSIZE;
    int tam;
    int taskid, sz,               /* a task identifier */
    numworkers; 
    double start, end;              /* number of tasks */

  /*
  double a[MATSIZE][MATSIZE],       
      b[MATSIZE][MATSIZE],           
      c[MATSIZE][MATSIZE]; */
    MPI_Status status;

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &taskid);
    MPI_Comm_size(MPI_COMM_WORLD, &numworkers);
    int *a = (int *)malloc(N * N * sizeof(int));
    int *b = (int *)malloc(N * N * sizeof(int));
    double *c = (double *)malloc(N * N * sizeof(double));

    if (taskid == 0){
      tam = MATSIZE;
      srand(time(NULL));
											dummyMethod3();
      for (int x = 0; x < tam; x++)
      {

        for (int y = 0; y < tam; y++)
        {
          a[x * tam + y] = (int)(rand() % 100);
          b[x * tam + y] = (int)(rand() % 100);
          c[x * tam + y] = 0.0;
        }
      }
											dummyMethod4();
    }
    MPI_Bcast(&tam,1,MPI_INT, 0,MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    sz = tam * tam / numworkers;
    int *a1 = (int *)malloc(sz * sizeof(int));
    int *b1 = (int *)malloc(tam * tam * sizeof(int));
    double *c1 = (double *)malloc(sz * sizeof(double));
    
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Scatter(a, sz, MPI_INT, a1, sz, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Scatter(b, tam * tam, MPI_INT, b1, tam * tam, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    MPI_Scatter(c, sz, MPI_DOUBLE, c1, sz, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    
    if (taskid == 0){
      start = MPI_Wtime();
    }
    
    omp_set_num_threads(omp_get_num_procs());
    
    int i,j,k;
    int auxiliar = tam / numworkers;
															dummyMethod1();
    #pragma omp parallel for shared(a1, b1, c1) private(i,j,k) schedule(static)
        for (i = 0; i < auxiliar; i++)
        {
            //printf("%i\n", omp_get_num_threads());
            for (j = 0; j < tam; j++)
            {
                for (k = 0; k < tam; k++)
                {
                c1[i * tam + j] = c1[i * tam + j] + (a1[i * tam + k] * b1[k * tam + j]);
                }
            }
        }
															dummyMethod2();
    MPI_Gather(c1, sz, MPI_DOUBLE, c, sz, MPI_DOUBLE, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();
    if (taskid == 0){
    printf("%f \n",end-start);
    }
    MPI_Finalize();
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