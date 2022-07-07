#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <mpi.h>
#include <math.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]) {
	long long int i, N=1000000;
	int numprocs,rank;
	int thread_nums = 4;
	double pi=0.0, begin=0.0, end=0.0, result=0.0, step=1/(double)N, sum=0.0, x;
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD,&numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD,&rank);
	MPI_Barrier(MPI_COMM_WORLD);
    begin = MPI_Wtime();
	int low = rank * (N / numprocs);
	int up = low + N / numprocs - 1;
	#pragma omp parallel num_threads(thread_nums)
    {
dummyMethod1();
        #pragma omp parallel for reduction(+:result) private(x)
		for(i = low; i < up; i++) {
			x = (i+0.5)*step;
			result += 4.0 / (1.0 + x * x);
		}
dummyMethod2();
    }
    result *= step;
	MPI_Reduce(&result, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
	MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();
    //Caculate and print PI
    if (rank==0)
    {
        pi=sum;
        printf("numprocs=%2d \t Time=%fs \t PI=%0.4f\n",numprocs, end-begin, pi);
    }
    MPI_Finalize();
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