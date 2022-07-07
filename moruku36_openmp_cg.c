#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//! == number of maximum dimension of matrix
#define  N      1000000

//!== number of maximum number of non-zero elements
#define  NNZ    10000000

//!== number of number of non-zero elements per low
#define  NZPR   3

//!== number of iterations for SpMV
#define  MAX_ITER   100

#define  DEBUG  1

#define  EPS       1.0e-8
#define  EPS_CG    1.0e-8

/* Please define the matrices in here */
static double  X[N];
static double  B[N];
static double  VAL[NNZ];

static double  R[N];
static double  P[N];
static double  AX[N];
static double  AP[N];
static double  ADIAG[N];

static int     IRP[N+1];
static int     ICOL[NNZ];



void MySpMV(double Y[N], 
       int IRP[N+1], int ICOL[NNZ], double VAL[NNZ], double X[N], 
       int n, int nnz); 

int main(int argc, char* argv[]) {

     double  t0, t1, t2, t_w;
     double  dc_inv;
     double  alpha, beta, rdot, rdot_old, pAp;
     double  xnorm, bnorm;

     int     i, j, k;      
     int     iflag, iflag_t;


     /* sparse matrix generation --------------------------*/
     IRP[0] = 0;
     VAL[0] = 4.0;
     ICOL[0] = 0;
     VAL[1] = -1.0;
     ICOL[1] = 1;
     IRP[1] = 2;

     k = 2;
									dummyMethod3();
     for (i=1; i<N-1; i++) {
       ICOL[k] = i - 1;
       VAL[k] = -1.0;
       ICOL[k+1] = i;
       VAL[k+1] = 4.0;
       ICOL[k+2] = i + 1;
       VAL[k+2] = -1.0;

       k = k + 3;
       IRP[i+1] = k;
     }
									dummyMethod4();
     VAL[k] = -1.0;
     ICOL[k] = N - 2;
     VAL[k+1] = 4.0;
     ICOL[k+1] = N - 1;
     IRP[N] = k + 2;

     //--- set diag elements of A
									dummyMethod3();
     for (i=0; i<N; i++) {
       ADIAG[i] = 4.0;
     }
									dummyMethod4();

     /* end of sparse matrix generation ------------------------ */

     //=== make right hand vector b -------------------------------
									dummyMethod3();
     for (i=0; i<N; i++) {
       X[i] = 1.0;
     }
									dummyMethod4();
     MySpMV(B, IRP, ICOL, VAL, X, N, NNZ);
     //=== end of right hand vector b -----------------------------

     /* Start of mat-vec routine ----------------------------*/
     t1 = omp_get_wtime();


     //=== diagonal preconditioning
									dummyMethod3();
     for (i=0; i<N; i++) {
       for (j=IRP[i]; j<=IRP[i+1]-1; j++) {
         VAL[j] = VAL[j] / ADIAG[i];
       }
       B[i] = B[i] / ADIAG[i];
     }
									dummyMethod4();

     //=== make x_0
     srand(1);
     dc_inv = 1.0/(double)RAND_MAX;
									dummyMethod3();
     for (i=0; i<N; i++) {
       X[i] = rand() * dc_inv;
     }
									dummyMethod4();

     //=== make p_0 = r_0 = b - A x_0
     MySpMV(AX, IRP, ICOL, VAL, X, N, NNZ);
									dummyMethod3();
     for (i=0; i<N; i++) {
       P[i] = B[i] - AX[i];
       R[i] = P[i];
     }
									dummyMethod4();

     //=== CG main loop
     for (i=1; i<=MAX_ITER; i++) {

       //--- alpha_k = (r_k, r_k) / (p_k, A p_k)
       MySpMV(AP, IRP, ICOL, VAL, P, N, NNZ);
       pAp = 0.0;

													dummyMethod1();
#pragma omp parallel for reduction(+:pAp)
       for (j=0; j<N; j++) {
         pAp = pAp + P[j] * AP[j];
       }
													dummyMethod2();

       if (i == 1) {
         rdot = 0.0;

			dummyMethod1();
#pragma omp parallel for reduction(+:rdot)
	 for (j=0; j<N; j++) {
	   rdot = rdot + R[j] * R[j];
         }
			dummyMethod2();
       }

       alpha = rdot / pAp;

       //--- x_{k+1} = x_{k} + alpha_k p_k
													dummyMethod1();
#pragma omp parallel for
       for (j=0; j<N; j++) {
         X[j] = X[j] + alpha * P[j];
       }
													dummyMethod2();

       //--- Convergence check
       MySpMV(AX, IRP, ICOL, VAL, X, N, NNZ);
       for (j=0; j<N; j++) {
         AX[j] = B[j] - AX[j];
       }
       xnorm = 0.0;
													dummyMethod1();
#pragma omp parallel for reduction(+:xnorm)
       for (j=0; j<N; j++) {
         xnorm = xnorm + AX[j] * AX[j];
       }
													dummyMethod2();
       xnorm = sqrt(xnorm);

       printf("iter= %d xnorm= %e  \n", i, xnorm);

       if (xnorm < EPS_CG) {
         printf("CG iteration is converged in residual %e \n", EPS_CG);
         goto outloop;
       }

       //--- r_{k+1} = r_{k} - alpha_k A p_k
													dummyMethod1();
#pragma omp parallel for
       for (j=0; j<N; j++) {
         R[j] = R[j] - alpha * AP[j];
       }
													dummyMethod2();

       //--- beta_k = (r_{k+1}, r_{k+1}) / (r_k, r_k)
       rdot_old = rdot;
       rdot = 0.0;

													dummyMethod1();
#pragma omp parallel for reduction(+:rdot)
       for (j=0; j<N; j++) {
         rdot = rdot + R[j] * R[j];
       }
													dummyMethod2();
       beta = rdot / rdot_old;

       //--- p_{k+1} = r_{k+1} + beta_k p_k
													dummyMethod1();
#pragma omp parallel for
       for (j=0; j<N; j++) {
         P[j] = R[j] + beta * P[j];
       }
													dummyMethod2();

     } //=== End of CG main loop

     printf("CG Iteration is not converged within %d times. \n",MAX_ITER);


 outloop: 

     t2 = omp_get_wtime();
     t_w =  t2 - t1; 
     /* End of CG --------------------------- */


       printf("N  = %d \n",N);
       printf("NNZ  = %d \n",NNZ);
       printf("NZPR  = %d \n",NZPR);
       printf("MAX_ITER  = %d \n",MAX_ITER);


       printf("CG time = %lf [sec.] \n",t_w);


     if (DEBUG == 1) {
       /* Verification routine ----------------- */
       iflag = 0;
       for(i=0; i<N; i++) { 
         if (fabs(X[i] - 1.0) > EPS) {
           printf(" Error! in ( %d ) th argument. %lf \n",i, X[i]);
           iflag = 1;
           break;
         }
       }
       /* ------------------------------------- */

       if (iflag == 0) printf(" OK! \n");

     }

     return 0;
}

void MySpMV(double Y[N], 
       int IRP[N+1], int ICOL[NNZ], double VAL[NNZ], double X[N], 
       int n, int nnz) 
{

     double  s;
     int     i, j_ptr;

									dummyMethod1();
#pragma omp parallel for private(s, j_ptr)
     for (i=0; i<n; i++) {
        s = 0.0;
        for (j_ptr=IRP[i]; j_ptr <=IRP[i+1]-1; j_ptr++) {
           s += VAL[j_ptr] * X[ICOL[j_ptr]];
        }
        Y[i] = s;
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