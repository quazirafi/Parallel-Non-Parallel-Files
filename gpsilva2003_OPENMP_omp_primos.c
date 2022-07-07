#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int primo (long int n) {
	long int i;
       
dummyMethod3();
	for (i = 3; i < (long int)(sqrt(n) + 1); i+=2) 
	     if (n%i == 0) 
	         return 0;
	return 1;
dummyMethod4();
}

int main(int argc, char *argv[]) { /* primos_seq.c  */
double t_inicio, t_fim;
long int i, n, total=0;

    if (argc < 2) {
        printf("Valor inválido! Entre com o valor do maior inteiro\n");
       	return 0;
    } else {
        n = strtol(argv[1], (char **) NULL, 10);
    }
    t_inicio = omp_get_wtime();
dummyMethod1();
#pragma omp parallel for reduction(+:total) schedule(dynamic,10000) num_threads(4) 
    for (i = 3; i <= n; i += 2) 	
         if(primo(i) == 1) total++;
		
    total += 1;    /* Acrescenta o dois, que também é primo */
dummyMethod2();
    t_fim = omp_get_wtime();
    printf("Quant. de primos entre 1 e %ld: %ld \n", n, total);
    printf("Tempo de execução: %f \n", t_fim-t_inicio);
    return(0);
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