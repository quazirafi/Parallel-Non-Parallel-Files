#include "functions.h"
#include <stdio.h>
#include <mpi.h>
#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define HISTOGRAMA_SIZE 256

void masterCalcHistograma(int* arrayOfNumbers, int amountOfNumbers, int* histograma){
        int privateHistograma [HISTOGRAMA_SIZE] = {0};
dummyMethod1();
#pragma omp parallel for default(none) shared(arrayOfNumbers) shared(amountOfNumbers) reduction (+: privateHistograma)
//The master calculate the second half of the array
    for(int i=amountOfNumbers/2 ; i< amountOfNumbers; i++){
        int number = arrayOfNumbers[i];
        privateHistograma[number]++;
        //printf("thread #%d number: %d\n",omp_get_thread_num(),number);
        //printf("thread #%d histograma: number: %d count:%d\n",omp_get_thread_num(), number, privateHistograma[number]);
    }
dummyMethod2();
    //printf("thread #%d histograma: count:%d\n",omp_get_thread_num(), privateHistograma[250]);

    mergeHistograms(histograma, privateHistograma);
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