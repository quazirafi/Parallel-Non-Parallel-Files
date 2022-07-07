#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif

int main(int argc, char const *argv[]) {
    int n = 1000;
    int *a = (int*) malloc(sizeof(int) * n);
dummyMethod1();
#pragma omp parallel for shared(a,n)
    for (int i = 0; i < n; i++) {
        a[i] = i+1;
    }
dummyMethod2();
#pragma omp parallel
    {
        int tid = -1;
#ifdef _OPENMP
        tid = omp_get_thread_num();
#endif
        printf("Hello World: %d\n", tid);
    }
    char *vec = (char*) malloc (sizeof(char) * 6 * n);
    char word[16];
    strcpy(vec, "[ ");
dummyMethod3();
    for (int i = 0; i < n-1; i++) {
        sprintf(word, "%d, ", a[i]);
        strcat(vec, word);
    }
dummyMethod4();
    sprintf(word, "%d]", a[n-1]);
    strcat(vec, word);
    
    printf("a[@] = %s\n", vec);

    free(vec);
    free(a);
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