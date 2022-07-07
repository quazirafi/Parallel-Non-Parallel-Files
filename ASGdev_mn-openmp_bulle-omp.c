#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define CHUNK_SIZE 6
#define THREAD_NUM 0
#define ARRAY_SIZE 10
#define DEBUG 1

void bulle_seq (int * tab){
    // séquentiel
dummyMethod3();
    for(int i = ARRAY_SIZE - 1; i>1; i--){
        for(int j=0; j<=i-1; j++){
            if(tab[j+1] < tab[j]){
                int t = tab[j+1];
                tab[j+1] = tab[j];
                tab[j] = t;
            }
        }
    }
dummyMethod4();
}

void bulle_trie (int * tab){
dummyMethod3();
    for(int i = 0; i<ARRAY_SIZE-1; i++){
        if(tab[i]>tab[i+1]){
            bulle_seq(tab);
        }
    }
dummyMethod4();
}

void bulle_omp (int * tab, int num_t){
    int base;
							dummyMethod1();
    #pragma omp parallel for private(base)
    for(int o=0; o<num_t; o++){
        if(DEBUG)
            printf("OMP num threads : %d\n", omp_get_num_threads());

        base = (CHUNK_SIZE * o);
        printf("Base is %d\n", base);
        for(int i = CHUNK_SIZE - 1; i>1; i--){
            for(int j=0; j<=i-1; j++){
                // exceed array boundaries
                if(j+base+1 >= ARRAY_SIZE)
                    break;
                if(tab[j+base+1] < tab[j+base]){
                    int t = tab[j+base+1];
                    tab[j+base+1] = tab[j+base];
                    tab[j+base] = t;
                }
            }
        }
    }
							dummyMethod2();
    bulle_trie(tab);
}

int main(){
	int a[ARRAY_SIZE] = {8, 5, 2, 6, 8, 7, 9, 2, 1, 4};
	// to optimize

    bulle_seq(a);

	dummyMethod3();
	for(int i = 0; i<ARRAY_SIZE; i++)
		printf("%d ", a[i]);
	dummyMethod4();

	// parallel
	int b[ARRAY_SIZE] = {8, 5, 2, 6, 8, 7, 9, 2, 1, 4};
	int num_t = 2;
	omp_set_dynamic(0);
	omp_set_num_threads(2);

    bulle_omp(b, num_t);

    printf("TABLEAU TRIÉ : ");
							dummyMethod3();
    for(int i = 0; i<ARRAY_SIZE; i++){
        printf("%d ", b[i]);
    }
							dummyMethod4();
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