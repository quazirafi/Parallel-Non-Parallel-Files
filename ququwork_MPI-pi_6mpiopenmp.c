#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<mpi.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MTAG1 1
#define MTAG2 2
static long N = 100000;

int main(int argc, char** argv){
    int  myid, incresment, i;
    double thispi, pi, step, sum ,x;

    MPI_Init(&argc, &argv);
    MPI_Comm_size(MPI_COMM_WORLD, &incresment);
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);

    for(;;){
        MPI_Bcast(&N, 1, MPI_INT, 0, MPI_COMM_WORLD);
        step = 1.0/(double) N;
        sum = 0.0;

dummyMethod1();
        #pragma omp parallel for reduction(+:sum) private(i, x)
        for( i = myid + 1; i <= N; i += incresment){
            x = ((double)i - 0.5) * step;
            sum += 4.0/(1.0 + x*x);
        }
dummyMethod2();

        thispi = step * sum;
        MPI_Reduce(&thispi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

        if(myid == 0){
            printf(" Result of pi=%1f\n", pi);
            break;
        }
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