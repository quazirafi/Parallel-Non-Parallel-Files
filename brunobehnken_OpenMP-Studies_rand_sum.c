#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
#include <sys/time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SEED_DEFAULT 100
#define TAM_DEFAULT 200000000

long int gettime_interval(struct timeval tv1, struct timeval tv2) {
    return (tv2.tv_sec - tv1.tv_sec) * 1000000 + (tv2.tv_usec - tv1.tv_usec);
}

int main(int argc, char* argv[]) {

    int tam, i,nthreads, tid;
    unsigned long long sum;
    int *vec1, *vec2;
    int seed;
    struct timeval tv[2];

    if(argc == 2) {
        tam = atoi(argv[1]);
        seed = SEED_DEFAULT;
    } else if(argc >= 3) {
        tam = atoi(argv[1]);
        seed = atoi(argv[2]);
    } else {
        tam = TAM_DEFAULT;
        seed = SEED_DEFAULT;
    }

    srand(seed);
    vec1 = (int*) malloc(tam*sizeof(int));
    vec2 = (int*) malloc(tam*sizeof(int));
    omp_set_num_threads(4);
    gettimeofday(&tv[0],NULL);

					dummyMethod1();
#pragma omp parallel for simd schedule(dynamic,5000000) shared(vec1,vec2)
   for(i=0;i<tam;i++) {
        vec1[i] = i%10000; //valores pequenos para a soma nao escalar muito
        vec2[i] = i%10000;
    }
					dummyMethod2();

    sum = 0;   

							dummyMethod1();
#pragma omp parallel for simd reduction(+:sum) schedule(dynamic,5000000) shared(vec1,vec2)
    for(i=0;i<tam;i++) {
        sum += vec1[i] * vec2[i];
    }
							dummyMethod2();
    
    if(tid == 0) {
        printf("O resultado da operacao eh: %lld\n", sum);
    }
    
    gettimeofday(&tv[1],NULL);
	printf("\n%ld microsegundos\n\n", gettime_interval(tv[0],tv[1]));

    free(vec1);
    free(vec2);

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