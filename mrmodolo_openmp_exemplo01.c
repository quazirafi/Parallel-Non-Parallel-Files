#ifdef _OPENMP
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#endif /* _OPENMP */
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include <time.h>

#define ERRO_ENTRADA -1
#define ENTRADA_OK 0
#define EH_PRIMO 1
#define NAO_PRIMO 0
#define USO "USO: %s <LIMITE INFERIOR> <LIMITE SUPERIOR>\n"

/*
 * Verifica se um numero e primo (força bruta)
 */ 
int ehprimo(long int n);

/*
 * Valida os parãmetros de entrada:
 * O limite inferior e superior são obrigatórios.
 * O limite inferior deve ser menor que o superior.
 * O limite inferior e superior devem ser maiores que zero.
 * É sempre bom verificar o valor máximo aceitável usando limits.h.
 * long int * inf - O ponteiro é necessário já que vamos alterar o valor dentro da função!
 * long int * sup - O mesmo aqui!
 */ 
int retorna_inf_sup(int argc, char ** argv, long int * inf, long int * sup);

/*
 * Verifica se um numero e primo (força bruta)
 */ 
int ehprimo(long int n) {
	int primo = EH_PRIMO;	
							dummyMethod3();
    for (long int i = 2; i < sqrt(n + 1); i++) {
		if ( 0 == ( n % i ) ) {
			primo = NAO_PRIMO;
			break;
        }
    }
							dummyMethod4();
    return primo;
}

/*
 * Valida os parãmetros de entrada:
 * O limite inferior e superior são obrigatórios.
 * O limite inferior deve ser menor que o superior.
 * O limite inferior e superior devem ser maiores que zero.
 * É sempre bom verificar o valor máximo aceitável usando limits.h.
 * long int * inf - O ponteiro é necessário já que vamos alterar o valor dentro da função!
 * long int * sup - O mesmo aqui!
 */ 
int retorna_inf_sup(int argc, char ** argv, long int * inf, long int * sup) {

		// argc vale no mínimo 1, já que o nome do executável está em argv[0]
		// em nosso caso, existem dois parãmetros obrigatórios inf e sup
		if (argc < 3) {
				printf("Os parâmetros inferior e superior são obrigatórios!\n");
				printf(USO, argv[0]);
				return ERRO_ENTRADA;
		}

		// para atribuir um valor a um ponteiro, é necessário "dereference"
		*inf = atoi(argv[1]);
		*sup = atoi(argv[2]);

		if (*inf < 1 || LONG_MAX < *inf) {
				printf("O limite inferior '%ld' está fora do intervalo aceitável!\n", *inf);
				return ERRO_ENTRADA;
		}
		if (*sup < 1 || LONG_MAX < *sup) {
				printf("O limite superior '%ld' está fora do intervalo aceitável!\n", *sup);
				return ERRO_ENTRADA;
		}
		if (*sup <= *inf ) {
				printf("O limite superior '%ld' deve ser maior que o inferior '%ld'!\n", *sup, *inf);
				return ERRO_ENTRADA;
		}

		return ENTRADA_OK;
}	

int main(int argc, char ** argv) {
           
	long int i = 0;
	long int cp = 0;
	long int inf = 0;
	long int sup = 0;

	if ( retorna_inf_sup(argc, argv, &inf, &sup) != ENTRADA_OK ) {
		exit(EXIT_FAILURE);
	}

	// Inicializa
	clock_t start = clock();
	double omp_start = omp_get_wtime();

	// Primeiro teste
	dummyMethod1();
	#pragma omp parallel for schedule(runtime) reduction(+:cp)
	for (i = inf; i <= sup; i++) {
		if (ehprimo(i))	{
			cp++;
			#ifdef DEBUG
			printf("%ld, ",i);
			#endif
		}
	}
	dummyMethod2();

	// Fim!
	clock_t end = clock();
	double omp_end = omp_get_wtime();
	double elapsed_time = (end-start)/(double)CLOCKS_PER_SEC;
	double omp_elapsed_time = omp_end - omp_start;

	printf("count: %ld user elapsed: %lf omp elapsed: %lf\n", cp, elapsed_time, omp_elapsed_time);
	fprintf(stderr, "%ld\n", cp);
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