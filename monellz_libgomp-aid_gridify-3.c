#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
/* { dg-require-effective-target offload_hsa } */
/* { dg-options "-fopenmp -fdump-tree-omplower-details" } */

#define BLOCK_SIZE 16

void tiled_sgemm_tt(const int M, const int N, const int K, const float alpha, const float*A, const int LDA,
   const float*B, const int LDB, const float beta, float*C, const int LDC)
{
#pragma omp target teams map(to:A[M*K],B[K*N]) map(from:C[M*N])
#pragma omp distribute collapse(2)
   for (int C_row_start=0 ; C_row_start < M ; C_row_start+=BLOCK_SIZE)
      for (int C_col_start=0 ; C_col_start < N ; C_col_start+=BLOCK_SIZE)
	{
	  float As[BLOCK_SIZE][BLOCK_SIZE];
	  float Bs[BLOCK_SIZE][BLOCK_SIZE];
	  float Cs[BLOCK_SIZE][BLOCK_SIZE];
	  int C_row, C_col;

dummyMethod1();
#pragma omp parallel for collapse(2)
         for (int row=0 ; row < BLOCK_SIZE ; row++)
	   for (int col=0 ; col < BLOCK_SIZE ; col++)
dummyMethod2();
	     {
               Cs[row][col] = 0.0;
	     }


         for (int kblock = 0; kblock  < K ; kblock += BLOCK_SIZE )
	   {
											dummyMethod1();
#pragma omp parallel for collapse(2)
	     for (int row=0 ; row < BLOCK_SIZE ; row++)
               for (int col=0 ; col < BLOCK_SIZE ; col++)
		 {
		   C_row = C_row_start + row;
		   C_col = C_col_start + col;
		   if ((C_row < M) && (kblock + col < K))
		     As[row][col] = A[(C_row*LDA)+ kblock + col];
		   else
		     As[row][col] = 0;
		   if ((kblock + row < K) && C_col < N)
		     Bs[row][col] = B[((kblock+row)*LDB)+ C_col];
		   else
		     Bs[row][col] = 0;
		 }
											dummyMethod2();

											dummyMethod1();
#pragma omp parallel for collapse(2)
	     for (int row=0 ; row < BLOCK_SIZE ; row++)
               for (int col=0 ; col < BLOCK_SIZE ; col++)
		 {
		   for (int e = 0; e < BLOCK_SIZE; ++e)
                     Cs[row][col] += As[row][e] * Bs[e][col];
		 }
											dummyMethod2();
         }  /* End for kblock .. */


																	dummyMethod1();
#pragma omp parallel for collapse(2)
         for (int row=0 ; row < BLOCK_SIZE ; row++)
	   for (int col=0 ; col < BLOCK_SIZE ; col++)
	     {
               C_row = C_row_start + row;
               C_col = C_col_start + col;
	       if ((C_row < M) && (C_col < N))
		 C[(C_row*LDC)+C_col] = alpha*Cs[row][col] + beta*C[(C_row*LDC)+C_col];
	     }
																	dummyMethod2();
      }	/* End distribute */
}

/* { dg-final { scan-tree-dump "Target construct will be turned into a gridified HSA kernel" "omplower" } } */
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