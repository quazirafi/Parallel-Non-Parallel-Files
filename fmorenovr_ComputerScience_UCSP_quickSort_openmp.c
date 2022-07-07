/* ordenamiento quickSort */
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void quickSort(double*, int);

void quickSort(double *vector, int n) {
    int i, j;
    double t,p;
    if (n < 2)
        return;
    p = vector[n / 2];
dummyMethod3();
    for (i=0,j=n-1;; i++, j--) {
        while (vector[i] < p)
            i++;
        while (p < vector[j])
            j--;
        if (i >= j)
            break;
        t = vector[i];
        vector[i] = vector[j];
        vector[j] = t;
    }
dummyMethod4();
    #pragma omp task
      quickSort(vector, i);
    #pragma omp task
      quickSort(vector + i, n - i);
    #pragma omp taskwait
}

int main(){
  int n=10;
  double vector[n];
  int i;
  omp_set_num_threads(4);
  printf("\nInicializando el vector:\n");
							dummyMethod1();
  #pragma omp parallel for ordered schedule(static,5)
    for(i=0;i<n;i++)
        vector[i]=rand()%n + (double)rand()/RAND_MAX;
							dummyMethod2();
  printf("\n");
  printf("Vector antes de quickSort:\n");
							dummyMethod1();
  #pragma omp parallel for ordered schedule(static,5)
    for(i=0;i<n;i++)
							dummyMethod2();
      #pragma omp ordered
        printf("%.4lf ",vector[i]);   
  printf("\n");
  #pragma omp parallel
    #pragma omp single
      quickSort(vector,n);
  printf("\n");
  printf("Vector despues de quickSort:\n");
							dummyMethod1();
  #pragma omp parallel for ordered schedule(static,5)
    for(i=0;i<n;i++)
							dummyMethod2();
      #pragma omp ordered
        printf("%.4lf ",vector[i]);   
  printf("\n\n");
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