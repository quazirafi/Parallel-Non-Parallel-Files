#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char const *argv[])
{	
	//recibir el numero de hilos a crear
	int num_hilos = strtol(argv[1],NULL,10)	;
	
	double factor = -1.0, pi=0.0;
	int n=10000000;

	//paralelizar el for
	//el reduction cuida la seccion critica
	//private cuida el valor de factor (cada hilo tiene su 'propio' factor)
dummyMethod1();
	#pragma omp parallel for num_threads(num_hilos) \
	reduction(+:pi) private (factor)
	for (int k = 1; k <= n; ++k)
	{
		if (k&1) factor = 1.0;
		else factor = -1.0;
		pi += factor/(2*k-1);	//seccion critica
	}
dummyMethod2();
	pi *=4;

	printf("El valor de PI es %lf\n",pi );
	return 0;
}

//$ gcc -g -Wall -fopenmp -o A PI.c
//$ ./A 500
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