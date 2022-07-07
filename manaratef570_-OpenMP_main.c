#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
#include <mpi.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define RESULT 1



int power(int x, int y)
{
    if (y == 0)
        return 1;
    else if (y%2 == 0)
        return power(x, y/2)*power(x, y/2);
    else
        return x*power(x, y/2)*power(x, y/2);

}

double calc ( int a){
	return ( double )1.0/power(2,a);
}

int main ( int argc , char * argv []){
	int n , myid , numprocs , i;
	double mypi , result , sum ;
	MPI_Init(& argc ,& argv );

	MPI_Comm_size( MPI_COMM_WORLD ,& numprocs );
	MPI_Comm_rank( MPI_COMM_WORLD ,& myid );
	n = 1;
while(n!=0){

		if ( myid == 0) {
			printf (" Enter the number of intervals : (0 quits ) ");
			scanf ("%d" ,&n );
		}
		  MPI_Bcast(&n, 1, MPI_INT , 0 , MPI_COMM_WORLD );

		if(n>0){
			sum = 0.0;
					dummyMethod1();
			#pragma omp parallel for reduction(+:sum) private(i)
			for ( i = myid + 1; i <= n ; i += numprocs) {
				sum += calc(i);
				printf("my rank %d, with index %d , from thread %d \n", myid,i, omp_get_thread_num());
			}
					dummyMethod2();
			MPI_Reduce(&sum , &result , 1 , MPI_DOUBLE , MPI_SUM , 0 , MPI_COMM_WORLD );
			if ( myid == 0) {
			printf ("result is approximatly : %.16f Error is: %.16f\n", result , fabs( result - RESULT ));
			}
		}
	}
	MPI_Finalize();
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