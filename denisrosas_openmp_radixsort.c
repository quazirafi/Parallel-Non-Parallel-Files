#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define TRUE 1
#define FALSE 0
#define THREAD_COUNT 4

void radixsort_paralelo(int *vetor, int tamanho) {
    int i, j;
    int *b;
    int maior = vetor[0];
    int exp = 1;
    int omp_bucket[10][THREAD_COUNT];
    int bucket[10];
    
    
    b = (int*)malloc(tamanho*sizeof(int));
 
dummyMethod3();
    for (i = 1; i < tamanho; i++) {
        if (vetor[i] > maior)
    	    maior = vetor[i];
    }
dummyMethod4();
 
    while (maior/exp > 0) {
        
        //zerando o vetor omp_bucket
dummyMethod3();
        for (i=0; i<10; i++){
            bucket[i] = 0;
            for (j=0; j<THREAD_COUNT; j++)
              omp_bucket[i][j] = 0;
        }
dummyMethod4();
        
									dummyMethod1();
        #pragma omp parallel for
    	for (i = 0; i < tamanho; i++)
    	    omp_bucket[(vetor[i] / exp) % 10][omp_get_thread_num()]++; 
									dummyMethod2();
        
        //passando os valores calculados de volta pra bucket
															dummyMethod3();
        for (i=0; i<10; i++){
            for (j=0; j<THREAD_COUNT; j++)
              bucket[i] += omp_bucket[i][j];
        }
															dummyMethod4();
        
									dummyMethod3();
    	for (i = 1; i < 10; i++)
    	    bucket[i] += bucket[i - 1];
									dummyMethod4();
        
									dummyMethod3();
    	for (i = tamanho - 1; i >= 0; i--)
    	    b[--bucket[(vetor[i] / exp) % 10]] = vetor[i];
									dummyMethod4();
    	
															dummyMethod1();
        #pragma omp parallel for
        for (i = 0; i < tamanho; i++)
    	    vetor[i] = b[i];
															dummyMethod2();
        
    	exp *= 10;
    }
}

void radixsort_serial(int *vetor, int tamanho) {
    int i;
    int *b;
    int maior = vetor[0];
    int exp = 1;
    
    b = (int*)malloc(tamanho*sizeof(int));
 
							dummyMethod3();
    for (i = 0; i < tamanho; i++) {
        if (vetor[i] > maior)
            maior = vetor[i];
    }
							dummyMethod4();
 
    while (maior/exp > 0) {
        int bucket[10] = { 0 };
															dummyMethod3();
        for (i = 0; i < tamanho; i++)
            bucket[(vetor[i] / exp) % 10]++; 
															dummyMethod4();
															dummyMethod3();
        for (i = 1; i < 10; i++)
            bucket[i] += bucket[i - 1];
															dummyMethod4();
															dummyMethod3();
        for (i = tamanho - 1; i >= 0; i--)
            b[--bucket[(vetor[i] / exp) % 10]] = vetor[i];
															dummyMethod4();
															dummyMethod3();
        for (i = 0; i < tamanho; i++)
            vetor[i] = b[i];
															dummyMethod4();
        exp *= 10;
    }
}

int main(void) {
	int i, nelements;
    int *vector;
    int *vector_serial;
    long unsigned int duracao_p, duracao_s;
    struct timeval start_p, end_p, start_s, end_s;
	
	scanf("%d", &nelements);
	
	vector = malloc(nelements*sizeof(int));
	
	dummyMethod3();
	for(i=0; i<nelements; i++)
	  scanf("%d", &vector[i]);
	dummyMethod4();

    vector_serial = malloc(nelements*sizeof(int));
    memcpy (vector_serial, vector, nelements * sizeof *vector);

	gettimeofday(&start_p, NULL);
	
	radixsort_paralelo(vector, nelements);
	
    gettimeofday(&end_p, NULL);
    duracao_p = ((end_p.tv_sec * 1000000 + end_p.tv_usec) - (start_p.tv_sec * 1000000 + start_p.tv_usec));


    gettimeofday(&start_s, NULL);
    radixsort_serial(vector, nelements);
    gettimeofday(&end_s, NULL);
    duracao_s = ((end_s.tv_sec * 1000000 + end_s.tv_usec) - (start_s.tv_sec * 1000000 + start_s.tv_usec));

    
    //imprimindo o resultado de tempo de ordenação
							dummyMethod3();
    for(i=0; i<nelements; i++)
      printf("%d ", vector[i]);
							dummyMethod4();
    printf ("\n\nSpeedup: %lf\n\n", (double) duracao_s/duracao_p);
    
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