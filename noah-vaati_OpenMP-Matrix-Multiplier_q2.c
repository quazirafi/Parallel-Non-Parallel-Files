//COMP 4510, A5, Q2
//Noah Redden, 7841009

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/timeb.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
 
#define N 100

int a[N][N];
int b[N][N];
int c[N][N];

struct timeb tstart, tend;
int tdelta;

int main(int argc, char *argv[]){
    ftime(&tstart);

    printf("N: %i\n",N);
        
    //initialize arrays
dummyMethod1();
    #pragma omp parallel for shared(a,b,c)
    for(int i = 0; i < N; i++)
    {
        for(int j = 0; j < N; j++){
            a[i][j] = 1;
            b[i][j] = 2;
            c[i][j] = 0;
        }
    }
dummyMethod2();

							dummyMethod1();
    #pragma omp parallel for shared(a,b,c)
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++){
            int sum = 0;
            for(int k = 0; k < N; k++){
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
							dummyMethod2();



    //print array
							dummyMethod3();
    for(int i = 0; i < N; i++){
        for(int j = 0; j < N; j++)
            printf("[%i] ", c[i][j]);
        printf("\n");
    }
							dummyMethod4();

    ftime(&tend);
    tdelta = (int) (1000.0*(tend.time - tstart.time)) +(tend.millitm - tstart.millitm);
    printf("\nTime: %ims\n",tdelta);

    return EXIT_SUCCESS;
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