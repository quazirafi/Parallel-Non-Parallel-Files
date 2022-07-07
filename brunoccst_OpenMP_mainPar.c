#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
    int ARRAY_SIZE = 100000; //Tamanho do vetor
    int vetor[ARRAY_SIZE];
    int i;
    clock_t t;
    omp_set_num_threads(1);    //Numero de Threads
    int debug = 0;
    int j;
    int controleVar = 0;

dummyMethod3();
    for (i=0 ; i<ARRAY_SIZE; i++) //Populando o vetor
        vetor[i] = ARRAY_SIZE-i;

    printf("\nTamanho Array: %d\n", ARRAY_SIZE);
dummyMethod4();

    printf("Comecando a ordenar\n");
    if(debug == 1){
        printf("\nVetor Inicial: ");
dummyMethod3();
        for (i=0 ; i<ARRAY_SIZE; i++)             
            printf("[%d] ", vetor[i]);
    }
dummyMethod4();

    t = clock();

    for (i = 0; i <= ARRAY_SIZE; i++) //Executa as trocas uma quantidade
    {								  //de vezes igual ao tamanho do vetor
        
															dummyMethod1();
		#pragma omp parallel for      //Paraleliza as trocas
        for (j = controleVar; j < ARRAY_SIZE - 1; j = j + 2) 
        {   
            if (vetor[j] > vetor[j+1])
            {
                int aux1 = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux1;
            }
        }
															dummyMethod2();

        if(controleVar == 1){ // Alterna entre as trocas a serem executadas
            controleVar = 0;
        }else{
            controleVar = 1;
        }
    }

    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC;

    printf("\n\nOrdenado!!\n");
    if(debug == 1){
        printf("\nVetor Final: ");
        for (i=0 ; i<ARRAY_SIZE; i++)
            printf("[%d] ", vetor[i]);
    }

    printf("\nTempo de duracao: %f\n", time_taken);
    printf("\n");
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