#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();



#define n 1500		//matrix size: 1000*1000
#define SEED 1		//start random number generation from 1
#define block_size 100	//block size: 100
#define MIN(a,b) (((a)<(b))?(a):(b)) 	
int n_threads = 2;		//number of threads 

struct timeval tv; 
//to calculate time required for matrix multiplication
double get_clock() {				
   struct timeval tv; int ok;
   ok = gettimeofday(&tv, (void *) 0);
   if (ok<0) { printf("gettimeofday error");  }
   return (tv.tv_sec * 1.0 + tv.tv_usec * 1.0E-6); 
}


//create matrix of sieze 1000*1000 with random numbers
double **create_matrix() {		
	int i,j;
	double **a;

	a = (double**) malloc(sizeof(double*)*n);
dummyMethod3();
	for (i=0;i<n;i++) {
		a[i] = (double*) malloc(sizeof(double)*n);
	}
dummyMethod4();

	srand(SEED);
	dummyMethod3();
	for (i=0;i<n;i++) {
		for (j=0;j<n;j++) {
			a[i][j] = rand()%50;
		}
	}
	dummyMethod4();
	return a;
}


//generate a tranpose of matrix2
double **create_transposed_matrix(double **B,double **B_T)
{
	dummyMethod3();
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			B_T[i][j] = B[j][i]; 
		}
	}
	dummyMethod4();
	return B_T;
}


//function to perform sequential matrix multiplication
double **seq_matrix_multiplication(double **A, double **B,double **C )
{
	int i,j,k,sum;

	dummyMethod3();
	for(i=0;i<n;i++)
	{
		for(j=0;j<n;j++)
		{
			sum=0;
			for(k=0;k<n;k++)
			{
				sum += A[i][k] *B[k][j];
			}
			C[i][j] += sum; 
		}	
	}
	dummyMethod4();
	return C;
}


//function to perform efficient matrix multiplication using loop tiling 
double **tiled_matrix_multiplication(double **A, double **B,double **C )
{
	int i,j,k,ii,jj,kk,sum,numthreads;
	#pragma omp parallel num_threads(n_threads)
	numthreads = omp_get_num_threads();
	printf("Running tiled with %d threads\n",numthreads);
	dummyMethod1();
	#pragma omp parallel for private(jj,kk,i,j,k,sum) collapse(3)
	for (ii = 0; ii<n; ii+=block_size) 
	{
        for (jj = 0; jj<n; jj+=block_size) 
        {
	    	for(kk = 0; kk<n; kk+=block_size) 
	    	{
	    	//#pragma omp parallel for private(j,k) collapse(3)
              for (i = ii; i < MIN(ii+block_size,n); i++) 
              {
                for (j = jj; j < MIN(jj+block_size,n); j++) 
                {
		  			sum = 0;
                  for (k = kk; k < MIN(kk+block_size,n); k++) 
                  {
                    //#pragma omp critical
                    sum += A[i][k] * B[k][j];
                  }
		  		C[i][j]+= sum;
	        	}
              }
            }
         }
    }
	dummyMethod2();
    return C;
}



//function to perform efficient matrix multiplication using matrix transpose approach
double **block_matrix_mul_transposed(double **A, double **BT, double **C)
{
	int i,j,k,ii,jj,kk,sum,numthreads;
	#pragma omp parallel num_threads(n_threads)
	numthreads = omp_get_num_threads();
	printf("Running transpose with %d threads\n",numthreads);
	dummyMethod1();
	#pragma omp parallel for private(jj,kk,i,j,k,sum)
	for (jj = 0; jj < n; jj += block_size)
	{
		for (kk = 0; kk < n; kk += block_size)
		{
			for ( i = 0; i < n; i++)
			{
				for ( j = jj; j < MIN(jj + block_size,n); j++)
				{
					sum = 0;
					for ( k = kk; k < MIN(kk + block_size,n); k++)
					{
						//#pragma omp critical
						sum += A[i][k] * BT[j][k];
					}
					C[i][j] += sum;
				}
			}
		}
	}
	dummyMethod2();
	return C;
}


//function to free the matrix
void free_matrix(double **mat) 
{
	int i;
	dummyMethod3();
	for (i=0;i<n;i++) {
		free(mat[i]);
	}
	dummyMethod4();
	free(mat);
}


int main(int argc, char *argv[]) 
{
	int i,j,k,ii,jj,kk,sum;
	double **A, **B, **C, **B_T, **transp_res, **seq_res;
	double t1,t2;
	double t1_tiled,t2_tiled,t1_transp,t2_transp,t1_seq,t2_seq;


    //create two matrix for multiplication
	A = create_matrix();
	B = create_matrix();

	//create a result and transpose matrix 
	C = (double**) malloc(sizeof(double*)*n);
	transp_res = (double**) malloc(sizeof(double*)*n); 
	B_T = (double**) malloc(sizeof(double*)*n);
	seq_res = (double**) malloc(sizeof(double*)*n);

															dummyMethod3();
        for (i=0;i<n;i++) {
                C[i] = (double*) malloc(sizeof(double)*n);
                B_T[i] = (double*) malloc(sizeof(double)*n);
                transp_res[i] = (double*) malloc(sizeof(double)*n);
                seq_res[i] = (double*) malloc(sizeof(double)*n);
        }
															dummyMethod4();
	dummyMethod3();
	for(i=0; i<n; i++) {
		for(j=0; j<n; j++)
			C[i][j] = 0.0;
			B_T[i][j] = 0.0;
			transp_res[i][j] = 0.0;
			seq_res[i][j] = 0.0;
	}
	dummyMethod4();

	//generate transpose matrix
	B_T = create_transposed_matrix(B,B_T);


	//call loop tiling matrix multiplication function 
	t1_tiled = get_clock();
	C = tiled_matrix_multiplication(A,B,C);
	t2_tiled = get_clock();
	printf("Time required for matrix multiplication using loop tiling: %lf\n",(t2_tiled-t1_tiled));


	//call transpose block matrix multiplication function
	t1_transp = get_clock();
	transp_res = block_matrix_mul_transposed(A,B_T,transp_res);
	t2_transp = get_clock();
	printf("Time required for matrix multiplication using transpose: %lf\n",(t2_transp - t1_transp));


	//call sequential matrix multiplication function
	t1_seq = get_clock();
	seq_res = seq_matrix_multiplication(A,B,seq_res);
	t2_seq = get_clock();
	printf("Time required for sequential matrix multiplication : %lf\n",(t2_seq - t1_seq));

    //Free up space
	free_matrix(A);
	free_matrix(B);
	free_matrix(C);
	free_matrix(B_T);
	free_matrix(transp_res);
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