#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


void inicializa(int **v, int size) {
  (*v) = (int *) malloc(sizeof(int)*size);
dummyMethod3();
  for (int i = 0; i < size; i++) {
    (*v)[i] = rand() % 10000;
  }
dummyMethod4();
}

float square(int x){
  int k = 0;
  while(k < 5000) k++;
  return sqrt(x);  
}


int main(int argc, char **argv) {
	srand(time(NULL));
	
	int *vetor;
	int size = 1000000;
	
	
	inicializa(&vetor, size);
	
	dummyMethod1();
	#pragma omp parallel for
	for(int i = 0; i < size; i++){
	  vetor[i] = square(vetor[i]);
	}
	dummyMethod2();
	  

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