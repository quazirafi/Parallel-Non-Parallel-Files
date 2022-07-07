#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/times.h>
#include <sys/time.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAX 3

int matA[MAX][MAX];
int matB[MAX][MAX];
int matC[MAX][MAX];

unsigned int time_seed() {
    struct timeval t;
    struct timezone tzdummy;

    gettimeofday(&t, &tzdummy);
    return (unsigned int)(t.tv_usec);
}

int main(){
    srand(time_seed());
dummyMethod3();
    for (int i = 0; i < MAX; i++) { 
        for (int j = 0; j < MAX; j++) { 
            matA[i][j] = rand() % 10; 
            matB[i][j] = rand() % 10; 
        } 
    }
dummyMethod4();
    printf("\nMatrix A\n");
							dummyMethod3();
    for (int i = 0; i < MAX; i++) { 
        for (int j = 0; j < MAX; j++)  
            printf("%d ", matA[i][j]); 
        printf("\n"); 
    } 
							dummyMethod4();
  
    printf("\nMatrix B\n");  
							dummyMethod3();
    for (int i = 0; i < MAX; i++) { 
        for (int j = 0; j < MAX; j++)  
            printf("%d ", matB[i][j]); 
        printf("\n"); 
    }    
							dummyMethod4();

							dummyMethod1();
    #pragma omp parallel for default(private) shared(matC, matA, matB)
    for(int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++){
            for(int k = 0; k < MAX; k++)
                matC[i][j] += matA[i][k] * matB[k][j];
        }
    }
							dummyMethod2();
    

    printf("\n Matrix \n");
							dummyMethod3();
    for (int i = 0; i < MAX; i++){
        for(int j = 0; j < MAX; j++)
            printf("%d ",matC[i][j]);
        printf("\n");
    }
							dummyMethod4();
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