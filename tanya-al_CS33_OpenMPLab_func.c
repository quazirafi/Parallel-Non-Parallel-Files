//Name: Tanya Al-Rehani
//UID: 604593556
#include "omp.h"
#include "func.h"
#include "util.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void func0(double *weights, double *arrayX, double *arrayY, int xr, int yr, int n)
{
	int i;
dummyMethod1();
	#pragma omp parallel for num_threads(16) firstprivate(weights,arrayX,arrayY,n,xr,yr) private(i)
	for(i = 0; i < n; i++){
		weights[i] = 1/((double)(n));
		arrayX[i] = xr;
		arrayY[i] = yr;
	}
dummyMethod2();
}

void func1(int *seed, int *array, double *arrayX, double *arrayY,
			double *probability, double *objxy, int *index,
			int Ones, int iter, int X, int Y, int Z, int n)
{
	int i, j;
   	int index_X, index_Y;
	int max_size = X*Y*Z;
dummyMethod1();
	#pragma omp parallel for num_threads(16)
  	for(i = 0; i < n; i++){
   		arrayX[i] += 1 + 5*rand2(seed, i);
   		arrayY[i] += -2 + 2*rand2(seed, i);
   	}
	#pragma omp parallel for num_threads(16) firstprivate(arrayX,arrayY,objxy,index,probability,array,Ones,n) private(index_X,index_Y,i,j)
dummyMethod2();
	dummyMethod1();
	for(i = 0; i<n; i++){
      		for(j = 0; j < Ones; j++){
   			index_X = round(arrayX[i]) + objxy[j*2 + 1];
   			index_Y = round(arrayY[i]) + objxy[j*2];
   			index[i*Ones + j] = fabs(index_X*Y*Z + index_Y*Z + iter);
   			if(index[i*Ones + j] >= max_size)
   				index[i*Ones + j] = 0;
   		}
		probability[i] = 0;
		for(j = 0; j < Ones; j++) {
                        probability[i] += (pow((array[index[i*Ones + j]] - 100),2) -
                                                          pow((array[index[i*Ones + j]]-228),2))/50.0;
                }
                probability[i] = probability[i]/((double) Ones);
   	}
	dummyMethod2();
}

void func2(double *weights, double *probability, int n)
{
	int i;
	double sumWeights=0;
	dummyMethod1();
	#pragma omp parallel for num_threads(16) private(i) firstprivate(n)
	for(i = 0; i < n; i++)
   		weights[i] = weights[i] * exp(probability[i]);
	dummyMethod2();
							dummyMethod1();
	#pragma omp parallel for num_threads(16) private(i) firstprivate(n) reduction(+:sumWeights)
   	for(i = 0; i < n; i++)
   		sumWeights += weights[i];
							dummyMethod2();
	dummyMethod1();
	#pragma omp parallel for num_threads(16) private(i) firstprivate(n)
	for(i = 0; i < n; i++)
   		weights[i] = weights[i]/sumWeights;
	dummyMethod2();
}

void func3(double *arrayX, double *arrayY, double *weights, double *x_e, double *y_e, int n)
{
	double estimate_x=0.0;
	double estimate_y=0.0;
    int i;

	dummyMethod3();
	for(i = 0; i < n; i++){
   		estimate_x += arrayX[i] * weights[i];
   		estimate_y += arrayY[i] * weights[i];
   	}
	dummyMethod4();

	*x_e = estimate_x;
	*y_e = estimate_y;

}

void func4(double *u, double u1, int n)
{
	int i;
	dummyMethod1();
	#pragma omp parallel for num_threads(16) private(i) firstprivate(n)
	for(i = 0; i < n; i++){
   		u[i] = u1 + i/((double)(n));
   	}
	dummyMethod2();
}

void func5(double *x_j, double *y_j, double *arrayX, double *arrayY, double *weights, double *cfd, double *u, int n)
{
	int i, j;
	dummyMethod1();
	#pragma omp parallel for num_threads(16) private(j,i) firstprivate(n)
	for(j = 0; j < n; j++){
   		//i = findIndex(cfd, n, u[j]);
   		i = findIndexBin(cfd, 0, n, u[j]);
   		if(i == -1)
   			i = n-1;
   		x_j[j] = arrayX[i];
   		y_j[j] = arrayY[i];

   	}
	dummyMethod2();
	dummyMethod1();
	#pragma omp parallel for num_threads(16) private(i) firstprivate(n)
	for(i = 0; i < n; i++){
		arrayX[i] = x_j[i];
		arrayY[i] = y_j[i];
		weights[i] = 1/((double)(n));
	}
	dummyMethod2();
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