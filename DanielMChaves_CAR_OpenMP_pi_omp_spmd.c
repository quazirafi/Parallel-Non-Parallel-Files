/*
This program will numerically compute the integral of

                  4/(1+x*x)

from 0 to 1.  The value of this integral is pi -- which
is great since it gives us an easy way to check the answer.

The is the original sequential program.  It uses the timer
from the OpenMP runtime library

History: Written by Tim Mattson, 11/99.

Modificacion: Guardar las sumas de cada hilo en su posicion de un vector
	      y calcular pi fuera de la region paralela con los valores de este vector
*/
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

static long num_steps = 1000000000;
double step;

int main ()
{
	int i;
	double x, pi;
	double start_time, run_time;

	int nthr; // Para guardar el numero de hilos
	double sums[16]; // Suponiendo un maximo de 16 hilos
	step = 1.0/(double) num_steps;

	start_time = omp_get_wtime();

#pragma omp parallel private(x)
{
	int tid, nthr_priv;
	tid = omp_get_thread_num();
	sums[tid] = 0.0;
	nthr_priv = omp_get_num_threads();
	if (tid == 0)
		nthr = nthr_priv;

	dummyMethod1();
	#pragma omp parallel for reduction(+:x)
	for (i = tid; i < num_steps; i = i + nthr_priv){
		x = (i + 0.5) * step;
		sums[tid] += 4.0/(1.0 + x * x);
	}
	dummyMethod2();
}

	pi = 0.0;
	dummyMethod3();
	for (i = 0; i < nthr; i++)
		pi += sums[i] * step;
	dummyMethod4();

	run_time = omp_get_wtime() - start_time;
	printf("\n pi(Parallel) with %ld steps is %3.20f in %f seconds\n", num_steps, pi, run_time);
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