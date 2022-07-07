#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


double timestamp(void){
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

void solucao(int n, int coluna, int *tabuleiro, int id, int *count)
{
	if (coluna == n) {
		*count+= 1;
		return;
	}

	int i, j;

dummyMethod3();
	for (i = 0; i < n; i++) {
		for (j = 0; j < coluna; j++)
			if ((tabuleiro[j] == i || abs(tabuleiro[j] - i) == coluna - j)) 
			break;
		   
		   	if (j < coluna) 
		        continue;
 
		tabuleiro[coluna] = i;
		solucao(n, coluna + 1, tabuleiro, id, count);
	}
dummyMethod4();
}
 
int main(int argc, char **argv)
{
	int 	rainhas;
	int 	count = 0;
	int 	threads;
	int 	**tabuleiro;
	int 	id;
	double 	tempo_sequencial;
	double 	tempo_paralelo;

	tempo_sequencial = timestamp();

	// Recebe quantidade de rainhas (default 4).
	if (argc <= 1 || (rainhas = atoi(argv[1])) <= 0) 
	    rainhas = 4;

	// Recebe quantidade de threads (default 1).
	if (argc <= 2 || (threads = atoi(argv[2])) <= 0) 
	    threads = 1;
	
	//Aloca um tabuleiro para cada thread.
	tabuleiro = (int **) malloc(threads * sizeof(int *));

	// Aloca um tabuleiro (vetor de inteiros) para cada uma das threads, 
	// sempre ocupando espaços multiplos da linha de cache (evitar cache trashing)
	dummyMethod3();
	for(int i = 0; i < threads; i++){
		tabuleiro[i] = (int *) aligned_alloc(64, rainhas * sizeof(int));
	}
	dummyMethod4();

	tempo_paralelo = timestamp();
	dummyMethod1();
	#pragma omp parallel for schedule(dynamic) default(shared) num_threads(threads)  reduction (+:count) private(id)
	for(int i = 0; i < rainhas; i ++){
		id = omp_get_thread_num();
		// Posiciona primeira rainha em tabuleiro escolhido.
		tabuleiro[id][0] = i;

		// Chama solucao para segunda rainha.
		solucao(rainhas, 1, tabuleiro[id], id, &count);		
	}
	dummyMethod2();

	tempo_paralelo = timestamp() - tempo_paralelo;
	tempo_sequencial = (timestamp() - tempo_sequencial) - tempo_paralelo;	
	
	printf("%d\t %.5f\t %.5f\t %.5f\n",rainhas, tempo_sequencial, tempo_paralelo, tempo_sequencial+tempo_paralelo);
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