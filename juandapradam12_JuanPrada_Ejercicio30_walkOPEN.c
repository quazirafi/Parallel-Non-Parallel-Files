#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* COMPILO CON gcc -fopenmp walkOPEN.c -o walkOPEN_c Y EJECUTO CON ./walkOPEN_c */

int walk(double barrier, int seed);
double *reserva(int n_points);
void print(double *x, int n_points);

void main (){ 
  double *A;
  int i;
  int n_walkers = 500000;

  A = reserva(n_walkers);
dummyMethod1();
	#pragma omp parallel for shared(A)     
  for (i=0; i<n_walkers; i++){
     A[i] = walk(10.0, i);

	
	
  }
dummyMethod2();

	FILE *walkOPEN = fopen("walkOPEN.dat", "w");
dummyMethod3();
	for(int i = 0; i < n_walkers; i++)
	{
            	fprintf(walkOPEN, "%f ",  A[i]);
        	fprintf(walkOPEN, "\n");
    	}
	fclose(walkOPEN);
dummyMethod4();
}

int walk(double barrier, int seed){

  double pos;
  int n_steps;
  srand48(seed);
  pos = 0.0;
  n_steps = 0;
  do{
    pos += (drand48()-0.5) * 2.0;
    n_steps++;
  }while(fabs(pos)<barrier);

  return n_steps;
}


void print(double *x, int n_points){
  int i;
			dummyMethod1();
	#pragma omp parallel for shared(x)
  for(i = 0 ; i < n_points ; i++){
    fprintf(stdout, "%f\n", x[i]);
  }
			dummyMethod2();
}

double *reserva(int n_points){
  double *x;
  int i;
  if(!(x=malloc(sizeof(double) * n_points))){
    printf("malloc problem\n");
    exit(1);
}
			dummyMethod1();
	#pragma omp parallel for shared(x)
  for(i=0;i<n_points;i++){
    x[i] = 0.0;
  }
			dummyMethod2();

  return x;
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