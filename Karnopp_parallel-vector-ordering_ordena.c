#include "ordena.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void swap(int *a, int *b){
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bubbleSort_Seq(int *vet, int n){
    int i, j;
dummyMethod3();
    for (i = 0; i < n-1; i++){
        for (j = 0; j < n-1; j++){
            if (vet[j] > vet[j+1]){
                swap(&vet[j], &vet[j+1]);
            }
        }
    }
dummyMethod4();
}

void bubbleSort_OMP(int *vet, int n){
    int i, j;
    for (i = 0; i < n-1; i++){
dummyMethod1();
        #pragma omp parallel for private(j)
        for (j = 0; j < n-1; j++){
            if (vet[j] > vet[j+1]){
                swap(&vet[j], &vet[j+1]);
            }
        }
dummyMethod2();
    }
}

/*
temp = vet[j+1];
vet[j+1] = vet[j];
vet[j] = temp;
*/
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