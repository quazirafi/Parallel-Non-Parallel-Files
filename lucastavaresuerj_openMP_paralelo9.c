#include <stdio.h>
#include "timer.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void main() {
    int i = 0;
    int N = 200000;
    int j=0, count1=0, pc=0;
    double tempo, fim, inicio;
    const int T = 4;
    GET_TIME(inicio);
dummyMethod1();
    #pragma omp parallel for schedule(dynamic,1) reduction(+:pc) num_threads(T) private (count1,i,j)
    for (i=2; i<=N; i++) {
        int count1 = 0;
        for (j=1;j<=i;j++) {
            if((i%j) == 0) count1++;
        }
        if (count1 == 2) pc++;
    }
dummyMethod2();
    GET_TIME(fim);
    tempo=fim-inicio;
    printf("Tempo: %.8lf\n",tempo);
    printf("PRIMOS: %d\n",pc);
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