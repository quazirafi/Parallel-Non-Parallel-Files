#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int get_size(FILE *fp) { 
  int n = 1;
  char c;

  while(!feof(fp)) {
    c = fgetc(fp);
    if(c == '\n')
      n++;
  }
  return n;
}

int **loc_matrix(int n) {
  
  int **matrix = malloc(n*sizeof(int*));

dummyMethod3();
  for(int i = 0; i < n; i++){
    matrix[i] = malloc(n*sizeof(int));
  }
dummyMethod4();

  return matrix;
}

int **get_values(int n, FILE *fp) {
  int **matrix = loc_matrix(n); 

dummyMethod3();
  for(int i = 0; i < n; i++)
    for(int j = 0; j < n; j++)
      fscanf(fp,"%d",&matrix[i][j]); 

  return matrix; 
dummyMethod4();
}


int main() {
  int i,j,k;
  int **A;
  int **B;
  int **C;
  FILE *arq;

  arq = fopen("matrizA.txt","r");
  if(arq == NULL)
    printf("no such file");
  
  int n = get_size(arq); 
  rewind(arq); 
  A = get_values(n, arq); 
  fclose(arq);
 
  arq = fopen("matrizB.txt","r"); 
  if(arq == NULL)
    printf("no such file");
  
  B = get_values(n, arq); 
  fclose(arq);

  C = loc_matrix(n);

 // Multiplication
			dummyMethod1();
  #pragma omp parallel for
  for(i = 0; i < n; i++) {
    #pragma omp parallel for
    for(j = 0; j < n; j++) {
      C[i][j] = 0;
      #pragma omp parallel for
      for(k = 0; k < n; k++)
        C[i][j] += A[i][k]*B[k][j];
    }
  }
			dummyMethod2();

  arq = fopen("result.txt","w");
  if(arq == NULL)
	 printf("no such file");
  
			dummyMethod3();
  for(i = 0; i < n; i++) {
    for(j = 0; j < n; j++)
      fprintf(arq,"%d ", C[i][j]);
    fprintf(arq,"\n");
  }
			dummyMethod4();
  fclose(arq);
  
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