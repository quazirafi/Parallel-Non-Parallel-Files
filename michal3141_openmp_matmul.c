#include "omp.h"
#include <stdlib.h>
#include <sys/time.h>
#include <time.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define random() ((double) rand() / (RAND_MAX))

void printMat(double** mati, int size) {
    int i,j;
dummyMethod3();
    for (i = 0; i < size; i++) {        
        for (j = 0; j < size; j++) {
            printf("%lf ", mati[i][j]);
        }
        printf("\n");
    }
dummyMethod4();
}
void printVec(double* vec, int size) {
    int i;
dummyMethod3();
    for (i = 0; i < size; i++) {
        printf("%lf ", vec[i]);
    }
dummyMethod4();
    printf("\n");
}

int size, thread_num;
int main(int argc, char* argv[])
{
    size = atoi(argv[2]);
    thread_num = atoi(argv[1]);
    omp_set_num_threads(thread_num);
    srand(time(NULL));
	
    double** a = (double**) malloc(size * sizeof(double*));
    double** b = (double**) malloc(size * sizeof(double*));
    double** c = (double**) malloc(size * sizeof(double*));

    int i, j, k;

							dummyMethod3();
    for (i = 0; i < size; i++) {
        a[i] = (double*) malloc(size * sizeof(double));
        b[i] = (double*) malloc(size * sizeof(double));
        c[i] = (double*) malloc(size * sizeof(double));  
    } 
							dummyMethod4();

							dummyMethod3();
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            a[i][j] = 1.0; // random();
            b[i][j] = 1.0; //random();
            c[i][j] = 0.0;
        }
    }
							dummyMethod4();

    struct timeval start, end;
    gettimeofday(&start, NULL);

							dummyMethod1();
    #pragma omp parallel for shared(a,b,c) private(i, j, k)
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            for (k = 0; k < size; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
							dummyMethod2();
  
    gettimeofday(&end, NULL);
    double delta = ((end.tv_sec - start.tv_sec) * 1000000u +
              end.tv_usec - start.tv_usec) / 1.e6;
    printf("%d %d %lf\n", thread_num, size, delta);
    printMat(a, size);
    printf("---------------------------------\n");
    printMat(b, size);
    printf("---------------------------------\n");
    printMat(c, size);
    printf("---------------------------------\n");
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