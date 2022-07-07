#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//#define SIZE 46350
#define SIZE 16

int main(){

	int A[ SIZE ] , i ;
dummyMethod1();
	#pragma omp parallel for schedule( static , 2 ) num_threads( 4 ) ordered
	for( i = 0 ; i < SIZE ; i++){
// Correccion, debe usarse tanto 'ordered clause' como 'ordered construct'
dummyMethod2();
// Introducao ao OpenMP, pagina 50
		A[ i ] = i * i ;
		#pragma omp ordered
		{
			printf( "Th[ %d ]: %02d = %03d\n" , omp_get_thread_num() , i , A[ i ] ) ;
		}
	}
	return 0 ;
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