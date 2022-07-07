/***
	Programa: 		 parallel-loop.c
	Autor: 	  		 Mustafa Atik
	Implementado en c: 	 E. López - J. García
	Función:  		 Algoritmo breve de realización de un ciclo en una claúsula de parallel.
	Fecha de implementación: 4 de octubre, 2020	
 ***/

#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    printf("the begin of loop");

dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < 10; ++i) {
        printf("%d", i);
    }
dummyMethod2();
    printf("the end of loop");

//    Expected output will be similar to this:
//    the begin of loop
//    6378049152
//    the end of loop
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