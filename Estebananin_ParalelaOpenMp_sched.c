/***
	Programa: 	   	 sched.c
	Autor: 	  	   	 Mustafa Atik
	Implementado en c: 	 E. López - J. García
	Función:  		 Uso de diferentes claúsulas de agendamiento de OMP para la realización de la toma de tiempo promedio 
				 alternando entre static, dynamic y auto (automatic).
	Fecha de implementación: 3 de octubre, 2020
 ***/
 
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void schedule_static();
void schedule_dynamic();
void schedule_auto();

int main() {
    int i, N = 10;

dummyMethod1();
    #pragma omp parallel for num_threads(2) schedule(static)   //Static usado para definir que los hilos en este tendrán casi siempre el mismo número de iteraciones
    for (i = 0; i < N; i++) {
        if (omp_get_thread_num() == 0)
        printf("Thread %d is doing iteration %d.\n", omp_get_thread_num( ), i);
    }
dummyMethod2();
//    Thread 0 is doing iteration 0.
//    Thread 0 is doing iteration 1.
//    Thread 0 is doing iteration 2.
//    Thread 0 is doing iteration 3.
//    Thread 0 is doing iteration 4.

							dummyMethod1();
    #pragma omp parallel for num_threads(2) schedule(static)
    for (i = 0; i < N; i++) {
        if (omp_get_thread_num() == 1)
            printf("Thread %d is doing iteration %d.\n", omp_get_thread_num( ), i);
    }
							dummyMethod2();
//    Thread 1 is doing iteration 5.
//    Thread 1 is doing iteration 6.
//    Thread 1 is doing iteration 7.
//    Thread 1 is doing iteration 8.
//    Thread 1 is doing iteration 9.

							dummyMethod1();
    #pragma omp parallel for num_threads(2) schedule(static, 4)
    for (i = 0; i < N; i++) {
        if (omp_get_thread_num() == 0)
            printf("Thread %d is doing iteration %d.\n", omp_get_thread_num( ), i);
    }
							dummyMethod2();
//    Thread 0 is doing iteration 0.
//    Thread 0 is doing iteration 1.
//    Thread 0 is doing iteration 2.
//    Thread 0 is doing iteration 3.
//    Thread 0 is doing iteration 8.
//    Thread 0 is doing iteration 9.

							dummyMethod1();
    #pragma omp parallel for num_threads(2) schedule(dynamic, 3)  //Las iteraciones por hilo serán asignadas dinámicamente 
    for (i = 0; i < N; i++) {
        if (omp_get_thread_num() == 1)
            printf("Thread %d is doing iteration %d.\n", omp_get_thread_num( ), i);
    }
							dummyMethod2();
//    Thread 1 is doing iteration 3.
//    Thread 1 is doing iteration 4.
//    Thread 1 is doing iteration 5.
//    or
//    Thread 1 is doing iteration 0.
//    Thread 1 is doing iteration 1.
//    Thread 1 is doing iteration 2.

    return 0;
}

/***
	Método: 	schedule_static
	Función: 	Procesamiento paralelo con agendamiento estático con hilos de un promedio, imprime el tiempo tomado.
***/
void schedule_static() {
    int N = 1000000000;
    int i;
    double avg = 0;

    omp_set_num_threads(16);

    double timer_started = omp_get_wtime();

							dummyMethod1();
#pragma omp parallel for reduction(+:avg) schedule(static)
    for (i = 0; i < N; ++i) {
        avg += i;
    }
							dummyMethod2();

    avg /= N;

    double elapsed = omp_get_wtime() - timer_started;
    printf("%d took %f \n", avg, elapsed);
    // 5e+08 took 1.41788
}

/***
	Método: 	schedule_dynamic
	Función: 	Procesamiento paralelo con agendamiento dinámico de hilos de un promedio, imprime el tiempo tomado.
***/
void schedule_dynamic() {
    int N = 1000000000;
    int i;
    double avg = 0;

    omp_set_num_threads(16);

    double timer_started = omp_get_wtime();
							dummyMethod1();
    #pragma omp parallel for reduction(+:avg) schedule(dynamic, 1000)
    for (i = 0; i < N; ++i) {
        avg += i;
    }
							dummyMethod2();

    avg /= N;

    double elapsed = omp_get_wtime() - timer_started;
    printf("%d took %f \n", avg, elapsed);
    // 5e+08 took 1.34788
}


/***
	Método: 	schedule_auto
	Función: 	Procesamiento paralelo con agendamiento asignado de manera automática de hilos de un promedio, 
				imprime el tiempo tomado.
***/
void schedule_auto() {
    int N = 1000000000;
    int i;
    double avg = 0;

    omp_set_num_threads(16);

    double timer_started = omp_get_wtime();

							dummyMethod1();
#pragma omp parallel for reduction(+:avg) schedule(auto)
    for (i = 0; i < N; ++i) {
        avg += i;
    }
							dummyMethod2();

    avg /= N;

    double elapsed = omp_get_wtime() - timer_started;

    printf("%d took %f \n", avg, elapsed);
    // 5e+08 took 1.39788
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