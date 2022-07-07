#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include "timer.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv)
{
        const long N = 10000;
        const long M = 1000000;
        double tempo, fim, inicio;
        int i, j, cont, T;
        T = atoi(argv[1]);
        GET_TIME(inicio);

dummyMethod1();
        #pragma omp parallel for num_threads(T) private(i,j,cont)
        for (i = 0; i < N; i++)
                for(j = 0; j < M; j++)
                        cont = cont + 1;

        GET_TIME(fim);
dummyMethod2();
        tempo = fim - inicio;
        printf("Tempo: %.8lf\n", tempo);
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