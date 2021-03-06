/**
 * jacobi-2d-imper.c: This file is part of the PolyBench/C 3.2 test suite.
 *
 *
 * Contact: Louis-Noel Pouchet <pouchet@cse.ohio-state.edu>
 * Web address: http://polybench.sourceforge.net
 */
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* Include polybench common header. */
#include <polybench.h>
/* Include benchmark-specific header. */
/* Default data type is double, default size is 20x1000. */
#include "jacobi-2d-imper.h"
/* Array initialization. */

static void init_array(int n,double A[16 + 0][16 + 0],double B[16 + 0][16 + 0])
{
  int i;
  int j;
dummyMethod3();
  for (i = 0; i < n; i++) 
    for (j = 0; j < n; j++) {
      A[i][j] = (((double )i) * (j + 2) + 2) / n;
      B[i][j] = (((double )i) * (j + 3) + 3) / n;
    }
}
dummyMethod4();
/* DCE code. Must scan the entire live-out data.
   Can be used also to check the correctness of the output. */

static void print_array(int n,double A[16 + 0][16 + 0])
{
  int i;
  int j;
			dummyMethod3();
  for (i = 0; i < n; i++) 
    for (j = 0; j < n; j++) {
      fprintf(stderr,"%0.2lf ",A[i][j]);
      if ((i * n + j) % 20 == 0) {
        fprintf(stderr,"\n");
      }
    }
			dummyMethod4();
  fprintf(stderr,"\n");
}
/* Main computational kernel. The whole function will be timed,
   including the call and return. */

#pragma verify dataracefree tsteps==2 n==16
static void kernel_jacobi_2d_imper(int tsteps,int n,double A[16 + 0][16 + 0],double B[16 + 0][16 + 0])
{
  int t;
  int i;
  int j;
  
#pragma scop
{
    int c2;
    int c0;
    int c1;
    int c3;
    int c4;
    if (n >= 3 && tsteps >= 1) {
      for (c0 = 0; c0 <= (((4 * n + 9 * tsteps + -13) * 8 < 0?((8 < 0?-((-(4 * n + 9 * tsteps + -13) + 8 + 1) / 8) : -((-(4 * n + 9 * tsteps + -13) + 8 - 1) / 8))) : (4 * n + 9 * tsteps + -13) / 8)); c0++) {
															dummyMethod1();
#pragma omp parallel for private(c4, c3, c2)
        for (c1 = ((((8 * c0 + -1 * tsteps + 1) * 8 < 0?-(-(8 * c0 + -1 * tsteps + 1) / 8) : ((8 < 0?(-(8 * c0 + -1 * tsteps + 1) + - 8 - 1) / - 8 : (8 * c0 + -1 * tsteps + 1 + 8 - 1) / 8)))) > ((8 * c0 * 9 < 0?-(-(8 * c0) / 9) : ((9 < 0?(-(8 * c0) + - 9 - 1) / - 9 : (8 * c0 + 9 - 1) / 9))))?(((8 * c0 + -1 * tsteps + 1) * 8 < 0?-(-(8 * c0 + -1 * tsteps + 1) / 8) : ((8 < 0?(-(8 * c0 + -1 * tsteps + 1) + - 8 - 1) / - 8 : (8 * c0 + -1 * tsteps + 1 + 8 - 1) / 8)))) : ((8 * c0 * 9 < 0?-(-(8 * c0) / 9) : ((9 < 0?(-(8 * c0) + - 9 - 1) / - 9 : (8 * c0 + 9 - 1) / 9))))); c1 <= (((((((n + 2 * tsteps + -3) * 2 < 0?((2 < 0?-((-(n + 2 * tsteps + -3) + 2 + 1) / 2) : -((-(n + 2 * tsteps + -3) + 2 - 1) / 2))) : (n + 2 * tsteps + -3) / 2)) < (((16 * c0 + n + 13) * 18 < 0?((18 < 0?-((-(16 * c0 + n + 13) + 18 + 1) / 18) : -((-(16 * c0 + n + 13) + 18 - 1) / 18))) : (16 * c0 + n + 13) / 18))?(((n + 2 * tsteps + -3) * 2 < 0?((2 < 0?-((-(n + 2 * tsteps + -3) + 2 + 1) / 2) : -((-(n + 2 * tsteps + -3) + 2 - 1) / 2))) : (n + 2 * tsteps + -3) / 2)) : (((16 * c0 + n + 13) * 18 < 0?((18 < 0?-((-(16 * c0 + n + 13) + 18 + 1) / 18) : -((-(16 * c0 + n + 13) + 18 - 1) / 18))) : (16 * c0 + n + 13) / 18)))) < c0?(((((n + 2 * tsteps + -3) * 2 < 0?((2 < 0?-((-(n + 2 * tsteps + -3) + 2 + 1) / 2) : -((-(n + 2 * tsteps + -3) + 2 - 1) / 2))) : (n + 2 * tsteps + -3) / 2)) < (((16 * c0 + n + 13) * 18 < 0?((18 < 0?-((-(16 * c0 + n + 13) + 18 + 1) / 18) : -((-(16 * c0 + n + 13) + 18 - 1) / 18))) : (16 * c0 + n + 13) / 18))?(((n + 2 * tsteps + -3) * 2 < 0?((2 < 0?-((-(n + 2 * tsteps + -3) + 2 + 1) / 2) : -((-(n + 2 * tsteps + -3) + 2 - 1) / 2))) : (n + 2 * tsteps + -3) / 2)) : (((16 * c0 + n + 13) * 18 < 0?((18 < 0?-((-(16 * c0 + n + 13) + 18 + 1) / 18) : -((-(16 * c0 + n + 13) + 18 - 1) / 18))) : (16 * c0 + n + 13) / 18)))) : c0)); c1++) {
          for (c2 = (16 * c0 + -16 * c1 + 1 > 2 * c1 + -1 * n + 3?16 * c0 + -16 * c1 + 1 : 2 * c1 + -1 * n + 3); c2 <= ((((2 * c1 + n + -2 < n + 2 * tsteps + -3?2 * c1 + n + -2 : n + 2 * tsteps + -3)) < 16 * c0 + -16 * c1 + n + 13?((2 * c1 + n + -2 < n + 2 * tsteps + -3?2 * c1 + n + -2 : n + 2 * tsteps + -3)) : 16 * c0 + -16 * c1 + n + 13)); c2++) {
            if (c0 <= (((16 * c1 + c2 + -1 * n + 1) * 16 < 0?((16 < 0?-((-(16 * c1 + c2 + -1 * n + 1) + 16 + 1) / 16) : -((-(16 * c1 + c2 + -1 * n + 1) + 16 - 1) / 16))) : (16 * c1 + c2 + -1 * n + 1) / 16)) && c1 <= (((c2 + -1) * 2 < 0?((2 < 0?-((-(c2 + -1) + 2 + 1) / 2) : -((-(c2 + -1) + 2 - 1) / 2))) : (c2 + -1) / 2))) {
              if ((c2 + n + 1) % 2 == 0) {
                for (c4 = 2 * c1; c4 <= 2 * c1 + 1; c4++) {
                  A[-1 * c2 + c4 + n + -2][n + -2] = B[-1 * c2 + c4 + n + -2][n + -2];
                }
              }
            }
            if (c0 <= (((18 * c1 + -1 * n + 1) * 16 < 0?((16 < 0?-((-(18 * c1 + -1 * n + 1) + 16 + 1) / 16) : -((-(18 * c1 + -1 * n + 1) + 16 - 1) / 16))) : (18 * c1 + -1 * n + 1) / 16)) && c1 >= ((c2 * 2 < 0?-(-c2 / 2) : ((2 < 0?(-c2 + - 2 - 1) / - 2 : (c2 + 2 - 1) / 2))))) {
              if ((n + 1) % 2 == 0) {
                A[n + -2][-2 * c1 + c2 + n + -2] = B[n + -2][-2 * c1 + c2 + n + -2];
              }
            }
            for (c3 = ((((((2 * c1 + -1 * n + 2) * 2 < 0?-(-(2 * c1 + -1 * n + 2) / 2) : ((2 < 0?(-(2 * c1 + -1 * n + 2) + - 2 - 1) / - 2 : (2 * c1 + -1 * n + 2 + 2 - 1) / 2)))) > (((c2 + -1 * n + 2) * 2 < 0?-(-(c2 + -1 * n + 2) / 2) : ((2 < 0?(-(c2 + -1 * n + 2) + - 2 - 1) / - 2 : (c2 + -1 * n + 2 + 2 - 1) / 2))))?(((2 * c1 + -1 * n + 2) * 2 < 0?-(-(2 * c1 + -1 * n + 2) / 2) : ((2 < 0?(-(2 * c1 + -1 * n + 2) + - 2 - 1) / - 2 : (2 * c1 + -1 * n + 2 + 2 - 1) / 2)))) : (((c2 + -1 * n + 2) * 2 < 0?-(-(c2 + -1 * n + 2) / 2) : ((2 < 0?(-(c2 + -1 * n + 2) + - 2 - 1) / - 2 : (c2 + -1 * n + 2 + 2 - 1) / 2)))))) > 8 * c0 + -8 * c1?(((((2 * c1 + -1 * n + 2) * 2 < 0?-(-(2 * c1 + -1 * n + 2) / 2) : ((2 < 0?(-(2 * c1 + -1 * n + 2) + - 2 - 1) / - 2 : (2 * c1 + -1 * n + 2 + 2 - 1) / 2)))) > (((c2 + -1 * n + 2) * 2 < 0?-(-(c2 + -1 * n + 2) / 2) : ((2 < 0?(-(c2 + -1 * n + 2) + - 2 - 1) / - 2 : (c2 + -1 * n + 2 + 2 - 1) / 2))))?(((2 * c1 + -1 * n + 2) * 2 < 0?-(-(2 * c1 + -1 * n + 2) / 2) : ((2 < 0?(-(2 * c1 + -1 * n + 2) + - 2 - 1) / - 2 : (2 * c1 + -1 * n + 2 + 2 - 1) / 2)))) : (((c2 + -1 * n + 2) * 2 < 0?-(-(c2 + -1 * n + 2) / 2) : ((2 < 0?(-(c2 + -1 * n + 2) + - 2 - 1) / - 2 : (c2 + -1 * n + 2 + 2 - 1) / 2)))))) : 8 * c0 + -8 * c1); c3 <= (((((((((c2 + -2) * 2 < 0?((2 < 0?-((-(c2 + -2) + 2 + 1) / 2) : -((-(c2 + -2) + 2 - 1) / 2))) : (c2 + -2) / 2)) < c1 + -1?(((c2 + -2) * 2 < 0?((2 < 0?-((-(c2 + -2) + 2 + 1) / 2) : -((-(c2 + -2) + 2 - 1) / 2))) : (c2 + -2) / 2)) : c1 + -1)) < tsteps + -1?(((((c2 + -2) * 2 < 0?((2 < 0?-((-(c2 + -2) + 2 + 1) / 2) : -((-(c2 + -2) + 2 - 1) / 2))) : (c2 + -2) / 2)) < c1 + -1?(((c2 + -2) * 2 < 0?((2 < 0?-((-(c2 + -2) + 2 + 1) / 2) : -((-(c2 + -2) + 2 - 1) / 2))) : (c2 + -2) / 2)) : c1 + -1)) : tsteps + -1)) < 8 * c0 + -8 * c1 + 7?(((((((c2 + -2) * 2 < 0?((2 < 0?-((-(c2 + -2) + 2 + 1) / 2) : -((-(c2 + -2) + 2 - 1) / 2))) : (c2 + -2) / 2)) < c1 + -1?(((c2 + -2) * 2 < 0?((2 < 0?-((-(c2 + -2) + 2 + 1) / 2) : -((-(c2 + -2) + 2 - 1) / 2))) : (c2 + -2) / 2)) : c1 + -1)) < tsteps + -1?(((((c2 + -2) * 2 < 0?((2 < 0?-((-(c2 + -2) + 2 + 1) / 2) : -((-(c2 + -2) + 2 - 1) / 2))) : (c2 + -2) / 2)) < c1 + -1?(((c2 + -2) * 2 < 0?((2 < 0?-((-(c2 + -2) + 2 + 1) / 2) : -((-(c2 + -2) + 2 - 1) / 2))) : (c2 + -2) / 2)) : c1 + -1)) : tsteps + -1)) : 8 * c0 + -8 * c1 + 7)); c3++) {
              for (c4 = 2 * c1; c4 <= ((2 * c1 + 1 < 2 * c3 + n + -2?2 * c1 + 1 : 2 * c3 + n + -2)); c4++) {
                A[-2 * c3 + c4 + -1][c2 + -2 * c3 + -1] = B[-2 * c3 + c4 + -1][c2 + -2 * c3 + -1];
                B[-2 * c3 + c4][c2 + -2 * c3] = 0.2 * (A[-2 * c3 + c4][c2 + -2 * c3] + A[-2 * c3 + c4][c2 + -2 * c3 - 1] + A[-2 * c3 + c4][1 + (c2 + -2 * c3)] + A[1 + (-2 * c3 + c4)][c2 + -2 * c3] + A[-2 * c3 + c4 - 1][c2 + -2 * c3]);
              }
              if (2 * c1 == 2 * c3 + n + -2) {
                if (n % 2 == 0) {
                  A[n + -2][-2 * c1 + c2 + n + -3] = B[n + -2][-2 * c1 + c2 + n + -3];
                }
              }
            }
            if (c0 >= (((16 * c1 + c2 + -15) * 16 < 0?-(-(16 * c1 + c2 + -15) / 16) : ((16 < 0?(-(16 * c1 + c2 + -15) + - 16 - 1) / - 16 : (16 * c1 + c2 + -15 + 16 - 1) / 16)))) && c1 >= (((c2 + 1) * 2 < 0?-(-(c2 + 1) / 2) : ((2 < 0?(-(c2 + 1) + - 2 - 1) / - 2 : (c2 + 1 + 2 - 1) / 2)))) && c2 <= 2 * tsteps + -1) {
              if ((c2 + 1) % 2 == 0) {
                for (c4 = 2 * c1; c4 <= ((2 * c1 + 1 < c2 + n + -3?2 * c1 + 1 : c2 + n + -3)); c4++) {
                  B[-1 * c2 + c4 + 1][1] = 0.2 * (A[-1 * c2 + c4 + 1][1] + A[-1 * c2 + c4 + 1][1 - 1] + A[-1 * c2 + c4 + 1][1 + 1] + A[1 + (-1 * c2 + c4 + 1)][1] + A[-1 * c2 + c4 + 1 - 1][1]);
                }
              }
            }
            if (c0 >= (((9 * c1 + -7) * 8 < 0?-(-(9 * c1 + -7) / 8) : ((8 < 0?(-(9 * c1 + -7) + - 8 - 1) / - 8 : (9 * c1 + -7 + 8 - 1) / 8)))) && c1 <= (((((c2 + -1) * 2 < 0?((2 < 0?-((-(c2 + -1) + 2 + 1) / 2) : -((-(c2 + -1) + 2 - 1) / 2))) : (c2 + -1) / 2)) < tsteps + -1?(((c2 + -1) * 2 < 0?((2 < 0?-((-(c2 + -1) + 2 + 1) / 2) : -((-(c2 + -1) + 2 - 1) / 2))) : (c2 + -1) / 2)) : tsteps + -1))) {
              B[1][-2 * c1 + c2] = 0.2 * (A[1][-2 * c1 + c2] + A[1][-2 * c1 + c2 - 1] + A[1][1 + (-2 * c1 + c2)] + A[1 + 1][-2 * c1 + c2] + A[1 - 1][-2 * c1 + c2]);
            }
          }
        }
															dummyMethod2();
      }
    }
  }
  
#pragma endscop
}

#if 1
int main() { return 0; }
#else
int main(int argc,char **argv)
{
/* Retrieve problem size. */
  int n = 16;
  int tsteps = 2;
/* Variable declaration/allocation. */
  double (*A)[16 + 0][16 + 0];
  A = ((double (*)[16 + 0][16 + 0])(polybench_alloc_data(((16 + 0) * (16 + 0)),(sizeof(double )))));
  ;
  double (*B)[16 + 0][16 + 0];
  B = ((double (*)[16 + 0][16 + 0])(polybench_alloc_data(((16 + 0) * (16 + 0)),(sizeof(double )))));
  ;
/* Initialize array(s). */
  init_array(n, *A, *B);
/* Start timer. */
  ;
/* Run kernel. */
  kernel_jacobi_2d_imper(tsteps,n, *A, *B);
/* Stop and print timer. */
  ;
  ;
/* Prevent dead-code elimination. All live-out data must be printed
     by the function call in argument. */
  if (argc > 42 && !strcmp(argv[0],"")) {
    print_array(n, *A);
  }
/* Be clean. */
  free(((void *)A));
  ;
  free(((void *)B));
  ;
  return 0;
}
#endif
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