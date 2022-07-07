/***
	Programa: 		 integral.c
	Autor: 	  		 Mustafa Atik
	Implementado en c: 	 E. López - J. García
	Función:  		 Este algoritmo muestra el resultado en tiempo de integrales utilizando el mismo procedimiento
				 pero alternando las claúsulas de pragma entre parallel, parallel + atomic, omp parallel for reduction
				 y parallel for private(x) reduction(+:sum)	
	Fecha de implementación: 3 de octubre, 2020
 ***/
 
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void integral_roundrobin();
void integral_atomic();
void integral_reduction();
void integral_better_reduction();

int main() {
//    integral_roundrobin();
    integral_reduction();
}

/*** 
	Método: 	integral_roundrobin
	Función: 	Integración a través de promedios haciendo uso de RR con hilos
***/
void integral_roundrobin() {
    int NTHREADS = 48, nthreads;
    long num_steps = 100000000;
    double step = 0;
    double pi = 0.0;
    double sum[NTHREADS];

    step = 1.0 / (double) num_steps;
    double timer_start = omp_get_wtime();
    omp_set_num_threads(NTHREADS);

    #pragma omp parallel
    {
        int i, id, lnthreads;
        double x;

        lnthreads = omp_get_num_threads();
        id = omp_get_thread_num();
        if (id == 0)
            nthreads = lnthreads;

															dummyMethod3();
        for (i = id, sum[id]=0; i < num_steps; i+=lnthreads) {
            x = (i+0.5) * step;
            sum[id] += 4.0 / (1.0 + x*x);
        }
															dummyMethod4();

    }
							dummyMethod3();
    for (int i = 0; i < nthreads; ++i) {
        pi += sum[i] * step;
    }
							dummyMethod4();

    double timer_took = omp_get_wtime() - timer_start;
    printf("%d --> %f \n", pi, timer_took);
    // 1 threads  --> 0.57 seconds.
    // 4 threads  --> 1.34 seconds.
    // 24 threads --> 0.59 seconds.
    // 48 threads --> 0.46 seconds.
}

/*** 
	Método: 	integral_atomic
	Función: 	Integración a través de promedios haciendo uso de RR con hilos pero haciendo uso
				de la claúsula "atomic" que funciona para asegurar que la condición de carrera sea eliminada				
***/
void integral_atomic() {
    int NTHREADS = 4;
    long num_steps = 100000000;
    double step = 0;
    double pi = 0.0;

    step = 1.0 / (double) num_steps;
    double timer_start = omp_get_wtime();
    omp_set_num_threads(NTHREADS);

    #pragma omp parallel
    {
        int i, id, lnthreads;
        double x, sum = 0;

        lnthreads = omp_get_num_threads();
        id = omp_get_thread_num();

															dummyMethod3();
        for (i = id; i < num_steps; i+=lnthreads) {
            x = (i+0.5) * step;
            sum += 4.0 / (1.0 + x*x);
        }
															dummyMethod4();

        #pragma omp atomic
        pi += sum * step;

    }

    double timer_took = omp_get_wtime() - timer_start;
    printf("%d --> %f \n", pi, timer_took);
    // 1 threads  --> 0.53 seconds.
    // 4 threads  --> 0.25 seconds.
    // 24 threads --> 0.24 seconds.
    // 48 threads --> 0.21 seconds.
}

/*** 
	Método: 	integral_reduction
	Función: 	Integración a través de promedios haciendo uso de RR con hilos pero haciendo uso
				de la claúsula "atomic" que funciona para asegurar que la condición de carrera sea eliminada				
***/
void integral_reduction() {
    int NTHREADS = 48;
    long num_steps = 100000000;
    double step = 0;
    double pi = 0.0;
    double sum = 0;
    int i = 0;

    step = 1.0 / (double) num_steps;

    omp_set_num_threads(NTHREADS);
    double timer_start = omp_get_wtime();

							dummyMethod1();
    #pragma omp parallel for reduction(+:sum)
    for (i = 0; i < num_steps; ++i) {
        int x = (i+0.5) * step;
        sum += 4.0 / (1.0 + x*x);
    }
							dummyMethod2();

    pi = sum * step;

    double timer_took = omp_get_wtime() - timer_start;
    printf("%d --> %f \n", pi, timer_took);
    // 1 threads  --> 0.55 seconds.
    // 4 threads  --> 0.24 seconds.
    // 24 threads --> 0.24 seconds.
    // 48 threads --> 0.23 seconds.
}

/*** 
	Método: 	integral_better_reduction
	Función: 	Integración a través de promedios haciendo uso de RR con hilos pero haciendo uso
				de la claúsula "parallel for " " reduction" que funciona para asegurar que la condición de carrera sea eliminada				
***/
void integral_better_reduction() {
    // this version is better because it can work in the case of non-threaded environments.
    int NTHREADS = 48;
    long num_steps = 100000000;
    double step = 0;
    double pi = 0.0;
    double sum = 0;
    int i = 0, x;

    step = 1.0 / (double) num_steps;

    omp_set_num_threads(NTHREADS);
    double timer_start = omp_get_wtime();

							dummyMethod1();
    #pragma omp parallel for private(x) reduction(+:sum)
    for (i = 0; i < num_steps; ++i) {
        x = (i+0.5) * step;
        sum += 4.0 / (1.0 + x*x);
    }
							dummyMethod2();

    pi = sum * step;

    double timer_took = omp_get_wtime() - timer_start;
    printf("%d --> %f \n", pi, timer_took);
    // 1 threads  --> 0.55 seconds.
    // 4 threads  --> 0.24 seconds.
    // 24 threads --> 0.24 seconds.
    // 48 threads --> 0.23 seconds.
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