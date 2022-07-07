#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
#include<math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//Functions
int backsubstitution_p(double *A, double *b, double *x, int n);
int backsubstitution_s(double *A, double *b, double *x, int n);
int conjugategradient_p(double *A, double *b, double *x, int n);
int conjugategradient_s(double *A, double *b, double *x, int n);
int seidel_p(double *A, double *b, double *x, int n);
int seidel_s(double *A, double *b, double *x, int n);

int main(int argc, char *argv[])
{
    long n;
    //input matrix dimensions
    printf("Enter matrix dimension for a square matrix: ");
    scanf("%ld", &n);

    //defining requirements
    double *matrix = malloc(sizeof(double)*n*n);
    double *b = malloc(sizeof(double)*n);
    double *x = malloc(sizeof(double)*n);

dummyMethod3();
    for(int i = 0; i< (n*n) ; i++)
    {
        double x = (rand()/(double)RAND_MAX);
        matrix[i] = x;
    }
dummyMethod4();

							dummyMethod3();
    for(int i = 0; i<n; i++)
    {
        double x = (rand()/(double)RAND_MAX);
        b[i]= x;
    }
							dummyMethod4();

    // matrices
    double *matrix2 = malloc(sizeof(double)*n*n);
    double *b2 = malloc(sizeof(double)*n);
    double *x2 = malloc(sizeof(double)*n);

    double *matrix3 = malloc(sizeof(double)*n*n);
    double *b3 = malloc(sizeof(double)*n);
    double *x3 = malloc(sizeof(double)*n);

    double *matrix4 = malloc(sizeof(double)*n*n);
    double *b4 = malloc(sizeof(double)*n);
    double *x4 = malloc(sizeof(double)*n);

    double *matrix5 = malloc(sizeof(double)*n*n);
    double *b5 = malloc(sizeof(double)*n);
    double *x5 = malloc(sizeof(double)*n);

    double *matrix6 = malloc(sizeof(double)*n*n);
    double *b6 = malloc(sizeof(double)*n);
    double *x6 = malloc(sizeof(double)*n);


							dummyMethod3();
    for(int i =0; i<n*n; i++)
    {
        matrix2[i] = matrix[i];
        matrix3[i] = matrix[i];
        matrix4[i] = matrix[i];
        matrix5[i] = matrix[i];
        matrix6[i] = matrix[i];
    }
							dummyMethod4();

							dummyMethod3();
    for(int i = 0; i<n ; i++)
    {
        b2[i] = b[i];
        b3[i] = b[i];
        b4[i] = b[i];
        b5[i] = b[i];
        b6[i] = b[i];
    }
							dummyMethod4();


    printf("\n\nA * x = b  \n");
    printf("To find : x \n\n");

    //A Matrix
    printf("Matrix A: \n");
							dummyMethod3();
    for(int i = 0; i<n*n; i++)
    {
        printf("%f ",matrix[i]);
        if((i+1)%n == 0)
        {
            printf("\n");
        }
    }
							dummyMethod4();

    //B Matrix
    printf("\n\nMatrix b: \n");
							dummyMethod3();
    for(int i = 0; i<n; i++)
    {
        printf("%f\n", b[i]);
    }
							dummyMethod4();

    printf("\n\nFINDING SOLUTIONS: \n");

    //Back Substitution
    printf("\n 1. Back substitution: \n");
    printf("\t A. Serially: \n");
    double ta = omp_get_wtime();
    backsubstitution_s(matrix, b, x, n);
    ta = omp_get_wtime() - ta;

    printf("\t B. Parallely: \n");
    double ta1 = omp_get_wtime();
    backsubstitution_p(matrix2, b2, x2, n);
    ta1 = omp_get_wtime() - ta1;

    printf("\n\t Time for serial execution: %0.30f\n\n", ta);
    printf("\n\t Time for parallel execution: %0.30f\n\n", ta1);

    //Conjugate Gradient
    printf("\n 2. Conjugate Gradient: \n");
    printf("\t A. Serially: \n");
    double tb = omp_get_wtime();
    conjugategradient_s(matrix3, b3, x3, n);
    tb = omp_get_wtime() - tb;
    printf("\t B. Parallely: \n");
    double tb1 = omp_get_wtime();
    conjugategradient_p(matrix4,b4,x4,n);
    tb1 = omp_get_wtime() - tb1;

    printf("\n\t Time for serial execution: %0.30f\n\n", tb);
    printf("\n\t Time for parallel execution: %0.30f\n\n", tb1);

    //Gauss Seidel
    printf("\n 3. Gauss Seidel: \n");
    printf("\t A. Serially: \n");
    double tc = omp_get_wtime();
    seidel_s(matrix6, b6, x6, n);
    tc = omp_get_wtime() - tc;

    printf("\t B. Parallely: \n");
    double tc1 = omp_get_wtime();
    seidel_p(matrix5,b5,x5,n);
    tc1 = omp_get_wtime() - tc1;

    printf("\n\t Time for serial execution: %0.30f\n\n", tc);
    printf("\n\t Time for parallel execution: %0.30f\n\n", tc1);

    free(matrix);
    free(b);
    free(x);
    free(matrix2);
    free(b2);
    free(x2);
    free(matrix3);
    free(b3);
    free(x3);
    free(matrix4);
    free(b4);
    free(x4);
    free(matrix5);
    free(b5);
    free(x5);

    return 0;
}

// For Back substitution:
// Use Gaussian elimination to get a matrix into upper triangular form
//Solve a triangular system using the row oriented algorithm
int backsubstitution_p(double *A, double *b, double *x, int n)
{
    int t;
    printf("\nEnter number of threads: ");
    scanf("%d", &t);
    double temp;
    int i, j, k;
							dummyMethod3();
    for(i =0; i < n-1; i++)
    {
        #pragma omp parallel default(none) num_threads(t) shared(n,A,b,i) private(j,k,temp)
		#pragma omp for schedule(static)
        for(j = i+1; j < n; j++)
        {
                temp = (A[j*(n)+i]) / (A[i*(n)+i]);

                for(k = i; k < n; k++)
                {
                    A[j*(n)+k] -= temp * (A[i*(n)+k]);
                }
                b[j] -= temp * (b[i]);
        }
    }
							dummyMethod4();
    double tmp;
    #pragma omp parallel num_threads(t) default(none) private(i,j) shared(A, b, x, n, tmp)
							dummyMethod3();
    for(int i= n-1; i >=0; i--)
    {
        #pragma omp single
        tmp = b[i];

        #pragma omp for reduction(+: tmp)

        for(j = i+1; j< n; j++)
            tmp += -A[i*n+j]*x[j];

        #pragma omp single
        x[i] = tmp/A[i*n+i];
    }
							dummyMethod4();

							dummyMethod3();
    for(int i =0; i < n; i++)
    {
        printf("\t\t%lf\n",x[i]);
    }
							dummyMethod4();

    return 0;
}


int backsubstitution_s(double *A, double *b, double *x, int n)
{
    int i, j, k;
							dummyMethod3();
    for(i =0; i < n-1; i++)
    {
        for(j = i+1; j < n; j++)
        {
                double temp = (A[j*(n)+i]) / (A[i*(n)+i]);

                for(k = i; k < n; k++)
                {
                    A[j*(n)+k] -= temp * (A[i*(n)+k]);
                }
                b[j] -= temp * (b[i]);
        }
    }
							dummyMethod4();
    double tmp;
							dummyMethod3();
    for(int i= n-1; i >=0; i--)
    {
        tmp = b[i];
        for(j = i+1; j< n; j++)
            tmp += -A[i*n+j]*x[j];
        x[i] = tmp/A[i*n+i];
    }
							dummyMethod4();

							dummyMethod3();
    for(int i =0; i < n; i++)
    {
        printf("\t\t%f\n",x[i]);
    }
							dummyMethod4();

    return 0;
}

int conjugategradient_p(double *A, double *b, double *x,  int n)
{
    int t;
    int max_iterations;
    printf("\nEnter number of iterations: ");
    scanf("%d", &max_iterations);

    printf("\nEnter number of threads: ");
    scanf("%d", &t);
    double r[n];
    double p[n];
    double px[n];

							dummyMethod1();
    #pragma omp parallel for num_threads(t)
    for( int i = 0 ; i<n ; i++)
    {
        x[i] = 0;
        p[i] = b[i];
        r[i] = b[i];
        px[i] = 0;
    }
							dummyMethod2();


    int q = max_iterations;

    double alpha = 0;

    while(q--)
    {
        double sum = 0;
															dummyMethod1();
        #pragma omp parallel  for num_threads(t) reduction(+ : sum)
        for(int i = 0 ; i < n ; i++)
        {
            sum = r[i]*r[i] + sum;
        }
															dummyMethod2();

        double temp[n];
															dummyMethod1();
        #pragma omp parallel for num_threads(t)
        for( int i = 0; i<n ; i++ )
        {
            temp[i] = 0;
        }
															dummyMethod2();

        double num = 0;
															dummyMethod1();
        #pragma omp parallel for num_threads(t)
        for(int i = 0 ; i < n ; i++)
        {
            #pragma omp parallel for reduction(+ : temp[i])
            for(int j = 0 ; j < n ; j++ )
            {
                temp[i] = A[i*n+j]*p[j] + temp[i];
            }
        }
															dummyMethod2();
															dummyMethod1();
        #pragma omp parallel for num_threads(t) reduction(+ : num)
        for(int j = 0 ; j < n ; j++)
        {
            num = num + temp[j]*p[j];
        }
															dummyMethod2();

        alpha = sum / num;

															dummyMethod1();
        #pragma omp parallel for num_threads(t)
        for(int i = 0; i < n ; i++ )
        {
            px[i] = x[i];
            x[i] = x[i] + alpha*p[i];
            r[i] = r[i] - alpha*temp[i];
        }
															dummyMethod2();

        double beta = 0;
															dummyMethod1();
        #pragma omp parallel for num_threads(t) reduction(+ : beta)
        for(int i = 0 ; i < n ; i++)
        {
            beta = beta + r[i]*r[i];
        }
															dummyMethod2();

        beta = beta / sum;

															dummyMethod1();
        #pragma omp parallel for num_threads(t)
        for (int i = 0 ; i < n ; i++ )
        {
            p[i] = r[i] + beta*p[i];
        }
															dummyMethod2();

          int c=0;
															dummyMethod3();
        for(int i = 0 ; i<n ; i++ )
        {
            if(r[i]<0.000001)
                c++;
        }
															dummyMethod4();

        if(c==n)
            break;
    }

							dummyMethod3();
    for( int i = 0 ; i<n ; i++ )
        printf("\t\t%f\n", x[i]);
							dummyMethod4();

    return 0;
}


int conjugategradient_s(double *A, double *b, double *x,  int n)
{
    int max_iterations;
    printf("\nEnter number of iterations: ");
    scanf("%d", &max_iterations);
    double r[n];
    double p[n];
    double px[n];
							dummyMethod3();
    for( int i = 0 ; i<n ; i++)
    {
        x[i] = 0;
        p[i] = b[i];
        r[i] = b[i];
        px[i] = 0;
    }
							dummyMethod4();


    double alpha = 0;
    while(max_iterations--)
    {

        double sum = 0;
															dummyMethod3();
        for(int i = 0 ; i < n ; i++)
        {
            sum = r[i]*r[i] + sum;
        }
															dummyMethod4();

        double temp[n];
															dummyMethod3();
        for( int i = 0; i<n ; i++ )
        {
            temp[i] = 0;
        }
															dummyMethod4();

        double num = 0;
															dummyMethod3();
        for(int i = 0 ; i < n ; i++)
        {
            for(int j = 0 ; j < n ; j++ )
            {
                temp[i] = A[i*n+j]*p[j] + temp[i];
            }
        }
															dummyMethod4();
															dummyMethod3();
        for(int j = 0 ; j < n ; j++)
        {
            num = num + temp[j]*p[j];
        }
															dummyMethod4();

        alpha = sum / num;
															dummyMethod3();
        for(int i = 0; i < n ; i++ )
        {
            px[i] = x[i];
            x[i] = x[i] + alpha*p[i];
            r[i] = r[i] - alpha*temp[i];
        }
															dummyMethod4();
        double beta = 0;
															dummyMethod3();
        for(int i = 0 ; i < n ; i++)
        {
            beta = beta + r[i]*r[i];
        }
															dummyMethod4();
        beta = beta / sum;
															dummyMethod3();
        for (int i = 0 ; i < n ; i++ )
        {
            p[i] = r[i] + beta*p[i];
        }
															dummyMethod4();
        int c=0;
															dummyMethod3();
        for(int i = 0 ; i<n ; i++ )
        {
            if(r[i]<0.000001 )
                c++;
        }
															dummyMethod4();
        if(c==n)
            break;
    }
							dummyMethod3();
    for( int i = 0 ; i<n ; i++ )
        printf("\t\t%f\n", x[i]);
							dummyMethod4();

    return 0;
}


int seidel_p(double A[], double b[], double x[], int n)
{
    double *dx;
    dx = (double*) calloc(n,sizeof(double));
    int i,j,k;
    double dxi;
    int maxit;
    double epsilon = 1.0e-4;
    double m[n];
    int p;
							dummyMethod3();
    for(int i = 0; i<n; i++)
    {
        x[i] = 0;
    }
							dummyMethod4();

    printf("\nEnter number of iterations: ");
    scanf("%d", &maxit);

    printf("\nEnter number of threads: ");
    scanf("%d", &p);
    int z = n/p;

    int id;
    int start, stop;

    for(k=0; k<maxit; k++)
    {
            printf("\n%d th iteration => \n", k+1);
																							dummyMethod1();
            #pragma omp parallel for num_threads(p) schedule(static, n) reduction(+:dxi)
            for(int i=0; i<n; i++)
            {
                dxi = b[i];

                    for(int j=0; j<n; j++)
                    {
                        if(j!=i)
                        {
                            dxi-=A[i*n + j] * x[j];
                        }

                        x[i] = dxi / A[i*n + i];
                    }



                printf("x %d  = %f \n", i+1,  x[i]);
            }
																							dummyMethod2();

        }
    }

int seidel_s(double A[], double b[], double x[], int n)
{
    double *dx;
    dx = (double*) calloc(n,sizeof(double));
    int i,j,k;
    double dxi;
    double epsilon = 1.0e-4;
    int maxit ;
    double m[n];

    for(int i = 0; i<n; i++)
    {
        x[i] = 0;
    }
    printf("\nEnter number of iterations: ");
    {
        scanf("%d", &maxit);
    }

    for(k=0; k<maxit; k++)
    {
        double sum = 0.0;
        printf("\n%d th iteration => \n", k+1);
        for(int i=0; i<n; i++)
        {
            dxi = b[i];
            for(int j=0; j<n; j++)
            {
                if(j!=i)
                {
                    dxi-=A[i*n + j] * x[j];
                }

                x[i] = dxi / A[i*n + i];
            }
            printf("x %d = %f \n", i+1, x[i]);
        }
    }
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