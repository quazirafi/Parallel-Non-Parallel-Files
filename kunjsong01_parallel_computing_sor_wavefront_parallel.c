#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// ***  Solution of Laplace's Equation.
// ***   Note that this experiment is using wavefront
// ***  Uxx + Uyy = 0
// ***  0 <= x <= pi, 0 <= y <= pi
// ***  U(x,pi) = sin(x), U(x,0) = U(0,y) = U(pi,y) = 0
// ***
// ***  then U(x,y) = (sinh(y)*sin(x)) / sinh(pi)
// ***
// ***  Should converge with
// ***   tol = 0.001 and N = 22  in  60 iterations.
// ***   and with tol = 0.001 and N = 102 in 200 iterations.
// ***   and with tol = 0.001 and N = 502 in 980 iterations.
// *** 

#define N 180 // 50 is a good size to be used for debugging. The wavefront algorithm is VERY slow on sequential machines. 
#define MAX(a,b)  ( ( (a)>(b) ) ? (a) : (b) )

// To paralise the code, x[][], xnew[][] and solution[][] should not be global
//double x[N][N], xnew[N][N], solution[N][N];

double calcerror(double **g, int iter, double **s);
void matrix_initialise(double **x_matrix, double **xnew_matrix, double **solution_matrix, double h);

int main(int argc, char *argv[]){
	double tol=0.001, h, omega, error;
	double pi = (double)4.0*atan((double)1.0);
	int iter=0, i, j;
	double x[N][N], **x_ptr; 
	double xnew[N][N], **xnew_ptr;
	double solution[N][N], **solution_ptr;
	int slength; // variable to skip the first and last two diagonal strips
	int z; // variable to skip boundary elements

	// variables for omp timmer
	double calcerror_start; 
	double calcerror_time = 0.0;

	// calculate constant values, h and omega 
	h = M_PI/(double)(N-1);
	omega = 2.0/(1.0+sin(M_PI/(double)(N-1)));

	// set up pointers to allow x[][], xnew[][] and solution[][] access in calcerror
	x_ptr = (double **)malloc((unsigned) N * sizeof(double));
	dummyMethod3();
	for (i=0; i < N; i++) {
		x_ptr[i] = x[i];
	}
	dummyMethod4();

	xnew_ptr = (double **)malloc((unsigned) N * sizeof(double));
	dummyMethod3();
	for (i=0; i < N; i++) {
		xnew_ptr[i] = xnew[i];
	}
	dummyMethod4();

	solution_ptr = (double **)malloc((unsigned) N * sizeof(double));
	dummyMethod3();
	for (i=0; i < N; i++) {
		solution_ptr[i] = solution[i];
	}
	dummyMethod4();
   
	// initialise x, xnew, y
	matrix_initialise(x_ptr, xnew_ptr, solution_ptr, h);

	// boundary conditions, copy the box boundaires from x to xnew array
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

	// calculate the initial error
	error = calcerror(x_ptr, iter, solution_ptr);

	while(error >= tol){
		// wavefront parallelism
		for (i=0; i < (2*N -1); i++){
			int k = (i < N) ? 0 : (i - N + 1);
			slength = (i - k -k + 1);
			if (slength > 2) {
							dummyMethod1();
				#pragma omp parallel for
				for (j=k; j <= i-k; j++){
					if (j==k || j == i-k) {
						continue; // skip boundary conditions
					}
					xnew[j][i-j] = x[j][i-j]+0.25*omega*(xnew[j-1][i-j] + xnew[j][i-j-1] \
									+ x[j+1][i-j] + x[j][i-j+1] - (4*x[j][i-j]));
				}
							dummyMethod2();
			}
		}

		for(i=1; i<N-1; i++)
			for(j=1; j<N-1; j++)
				x[i][j] = xnew[i][j];

		iter++;

		if (fmod(iter, 20) == 0)
			error = calcerror(x_ptr, iter, solution_ptr);
	}
	printf("Omega = %0.20f\n", omega);
	printf("Convergence in %d iterations for %dx%d grid with tolerance %f.\n", iter, N, N, tol);

	calcerror_time = calcerror_time + (omp_get_wtime() - calcerror_start);

	printf("Total iteration to converge = %d \n", iter);
	printf("Total time elapsed to converge = %f \n", calcerror_time);

	return 0;
}

void matrix_initialise(double **x_matrix, double **xnew_matrix, double **solution_matrix, double h){
	int i, j;
	for(i=0; i<N; i++)
		x_matrix[i][N-1] = sin((double)i*h);

	for(i=0; i<N; i++)
		for(j=0; j<N-1; j++)
			x_matrix[i][j] = (double)j*h*x_matrix[i][N-1];

	for(i=0; i<N; i++)
		for(j=0; j<N; j++)
			solution_matrix[i][j] = sinh((double)j*h) * sin((double)i*h)/sinh(M_PI);
}

double calcerror(double **g, int iter, double **s){
	
	// TO-DO: openmp reduce
	int i,j;
	double error = 0.0;

	for(i=1; i<N-1; i++)
		for(j=1; j<N-1; j++)
			error = MAX(error, fabs(s[i][j] - g[i][j]));

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