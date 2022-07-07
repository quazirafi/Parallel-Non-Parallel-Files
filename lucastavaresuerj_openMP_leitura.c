//DONT READ FILE IN PARALLEL, IT IS WAY WORST 
#include <stdio.h>
#include <stdlib.h>
#include "../timer.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[]) {
    FILE* pfile;
    int T=1;
    long int sizeOfVet, i;
    int* bigVet;
    double tempo, inicio, fim;
    GET_TIME(inicio); 
    pfile = fopen (argv[1],"r");
    fscanf(pfile, "%ld", &sizeOfVet);
    bigVet = (int*) malloc(sizeOfVet*sizeof(int));
dummyMethod1();
    #pragma omp parallel for num_threads(T) private (i)
    for(i=0;i<sizeOfVet;i++) {
        fscanf(pfile, "%d", &(bigVet[i]));
    }
dummyMethod2();
    GET_TIME(fim);
    printf("tempo: %.4lf\n", fim-inicio);
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