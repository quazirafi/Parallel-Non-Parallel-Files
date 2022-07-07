/*
Compilar: gcc -o Q2 Q2.c -ansi -Wall -fopenmp
Executar: ./Q2 4 10000
*/

#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void uniqueRandom(int *vetor, int tam); /*Gera números aletórios distintos.*/
void rankSort(int **vetor, int tam);

int main(int argc, char *argv[]){
    int *vetor, /*i,*/ tam;
    double t_final, t_inicial;

    srand(time(NULL));

    if(argc < 3){
        perror("Número de argumentos insuficiente, insira a quantidade de threads e o tamanho do vetor respectivamente.");
        return 0;
    }else{
        omp_set_num_threads(atoi(argv[1]));
        tam = atoi(argv[2]);
        vetor = (int*) malloc(sizeof(int)*tam);
    }

    puts("Começando a gerar randômicos únicos");
    uniqueRandom(vetor, tam);
    puts("Randômicos gerados");

    t_inicial = omp_get_wtime();
    rankSort(&vetor, tam);
    t_final = omp_get_wtime();

 /*   for(i = 0; i < tam; i++){
        printf("%d\n", vetor[i]);
    }*/
    
    printf("Tempo de execução: %lf\n", t_final-t_inicial);

    return 0;
}

void uniqueRandom(int *vetor, int tam){
    int i = 0, *aux, random; 
    aux = (int*) malloc(sizeof(int)*tam);
    
							dummyMethod3();
    for(i=0; i<tam; i++){
        aux[0]=0;
    }
							dummyMethod4();
    i= 0;

    while(i < tam){
        random = rand()%tam;
        if(aux[random] == 0){
            vetor[i] = random;
            aux[random] = 1;
            i++;
        }
    }
}

void rankSort(int **vetor, int tam){
    int rank=0, i, j, *ordenado;
    ordenado = (int*) malloc(sizeof(int)*tam);

							dummyMethod1();
    #pragma omp parallel for private(i,j) firstprivate(rank) shared(vetor, ordenado, tam)
    for(i = 0; i<tam; i++){
        for(j=0; j<tam; j++){
            if((*vetor)[i] > (*vetor)[j])
                rank++;
        }
        ordenado[rank] = (*vetor)[i];
        rank = 0;
    }
							dummyMethod2();
    free(*vetor);
    *vetor = ordenado;
    
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