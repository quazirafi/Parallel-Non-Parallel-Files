#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// ***  Solution of Laplace's Equation.
// ***
// ***  Uxx + Uyy = 0
// ***  0 <= x <= pi, 0 <= y <= pi
// ***  U(x,pi) = sin(x), U(x,0) = U(0,y) = U(pi,y) = 0
// ***
// ***  then U(x,y) = (sinh(y)*sin(x)) / sinh(pi)
// ***
// ***  Should converge with
// ***                 tol = 0.001 and M = 22  in  60 iterations.
// ***   and with tol = 0.001 and M = 102 in 200 iterations.
// ***   and with tol = 0.001 and M = 502 in 980 iterations.
// *** 

#define N 268 
#define MAX(a,b)  ( ( (a)>(b) ) ? (a) : (b) )

double x[N][N], xnew[N][N], solution[N][N];

double calcerror(double g[][N], int iter);

int main(int argc, char *argv[]){
	double tol=0.001, h, omega, error;
        double pi = (double)4.0*atan((double)1.0);
	int iter=0, i, j;

	h = M_PI/(double)(N-1);

	// variables for omp timmer
	double calcerror_start; 
	double calcerror_time = 0.0;

	dummyMethod3();
	for(i=0; i<N; i++)
		x[i][N-1] = sin((double)i*h);
	dummyMethod4();
	

	dummyMethod3();
	for(i=0; i<N; i++)
		for(j=0; j<N-1; j++)
			x[i][j] = (double)j*h*x[i][N-1];
	dummyMethod4();

	dummyMethod3();
	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			solution[i][j] = sinh((double)j*h) * sin((double)i*h)/sinh(M_PI);
	dummyMethod4();
	
	omega = 2.0/(1.0+sin(M_PI/(double)(N-1)));
   
	dummyMethod3();
	for(i=0; i<N; i++){
		for(j=0; j<N; j++){
			xnew[0][j] = x[0][j];
			xnew[N-1][j] = x[N-1][j];
		}
		xnew[i][0] = x[i][0];
		xnew[i][N-1] = x[i][N-1];
	}
	dummyMethod4();

	// start time
    calcerror_start = omp_get_wtime();
	error = calcerror(x, iter);

	while(error >= tol){

			dummyMethod1();
		#pragma omp parallel for ordered \
			schedule(static, 1)
		for(i=1; i<N-1; i++){
			#pragma omp ordered
			{
				// mimic the pipeline
				// The next thread is waiting for the previous thread finishing updating the first element in the row
				xnew[i][1] = x[i][1]+0.25*omega*(x[i-1][1] + x[i][1-1] + x[i+1][1] + x[i][1+1] - (4*x[i][1]));
				x[i][1] = xnew[i][1];
			}
			for(j=2; j<N-1; j++){
				xnew[i][j] = x[i][j]+0.25*omega*(x[i-1][j] + x[i][j-1] + x[i+1][j] + x[i][j+1] - (4*x[i][j]));
				x[i][j] = xnew[i][j];
			}

		}				
			dummyMethod2();

		iter++;

		if (fmod(iter, 20) == 0)
		  error = calcerror(x, iter);
		
	}
	
	printf("Omega = %0.20f\n", omega);
	printf("Convergence in %d iterations for %dx%d grid with tolerance %f.\n", iter, N, N, tol);

	calcerror_time = calcerror_time + (omp_get_wtime() - calcerror_start);

	printf("Total iteration to converge = %d \n", iter);
	printf("Total time elapsed to converge = %f \n", calcerror_time);

	return 0;
}

double calcerror(double g[][N], int iter){

	int i,j;
	double error = 0.0;

	dummyMethod3();
	for(i=1; i<N-1; i++)
		for(j=1; j<N-1; j++)
			error = MAX(error, fabs(solution[i][j] - x[i][j]));
	dummyMethod4();

	printf("On iteration %d error= %f\n",iter, error);
	return error;
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