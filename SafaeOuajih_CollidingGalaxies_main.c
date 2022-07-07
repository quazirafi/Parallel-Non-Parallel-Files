#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main( int argc, char ** argv ) {
	
	int i, j;
	int sum = 0;
	
	omp_set_num_threads( 4 );

	#pragma omp parallel
	{
		printf( "in parallel region\n" );

	}

dummyMethod1();
	#pragma omp parallel for reduction(+:sum)
	for ( i = 0; i < 1000; i++ ) {
		for ( j = 0; j < 1000; j++ ) {	
			sum = sum + i + j;
		}
	}
dummyMethod2();

	#pragma omp parallel sections
	{
		#pragma omp section
		{
			printf( "section executed by thread id = %d\n", omp_get_thread_num() );



		}

		#pragma omp section
		{
			printf( "section executed by thread id = %d\n", omp_get_thread_num() );




		}
	}

	printf( "done\n" );

	return 1;
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