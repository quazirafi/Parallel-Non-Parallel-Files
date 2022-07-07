#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main (void){
    int i, a =10;
    #if 0
    /* desactiva el compartir variables de serie y pone i a privado*/

    #pragma omp parallel for default(none) private(a)
    for ( i=0; i<5 ; i++){
        a = a + 1;
        printf( "Thread %d, valor %d \n", omp_get_thread_num(), a);
    }//Fin región paralela
    #endif


    #if 0
    /* Ejemplo firstprivate y las private*/

    #pragma omp parallel for default(none) firstprivate( a ) lastprivate( a )
    for ( i=0; i<5 ; i++){
        a = a + 1;
        printf( "Thread %d, valor %d \n", omp_get_thread_num(), a);
    }//Fin región paralela

    #endif

    //Ejemplo propio

							dummyMethod1();
     #pragma omp parallel for default(none) reduction(+:a)
    for ( i=0; i<5 ; i++){
        a = a + 1;
        printf( "Thread %d, valor %d \n", omp_get_thread_num(), a);
    }//Fin región paralela
							dummyMethod2();
    printf("Valor final: %d\n", a);
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