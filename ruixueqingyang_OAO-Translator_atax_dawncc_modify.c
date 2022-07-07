/**
 * atax.c: This file was adapted from PolyBench/GPU 1.0 test suite
 * to run on GPU with OpenMP 4.0 pragmas and OpenCL driver.
 *
 * http://www.cse.ohio-state.edu/~pouchet/software/polybench/GPU 
 *
 * Contacts: Marcio M Pereira <mpereira@ic.unicamp.br>
 *           Rafael Cardoso F Sousa <rafael.cardoso@students.ic.unicamp.br>
 *	     Luís Felipe Mattos <ra107822@students.ic.unicamp.br>
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
#include <unistd.h>
#include <sys/time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//polybenchUtilFuncts.h
//Scott Grauer-Gray (sgrauerg@gmail.com)
//Functions used across hmpp codes

#ifndef POLYBENCH_UTIL_FUNCTS_H
#define POLYBENCH_UTIL_FUNCTS_H

//define a small float value
#define SMALL_FLOAT_VAL 0.00000001f

double rtclock()
{
    struct timezone Tzp;
    struct timeval Tp;
    int stat;
    stat = gettimeofday (&Tp, &Tzp);
    if (stat != 0) printf("Error return from gettimeofday: %d",stat);
    return(Tp.tv_sec + Tp.tv_usec*1.0e-6);
}

float absVal(float a)
{
	if(a < 0)
	{
		return (a * -1);
	}
   	else
	{ 
		return a;
	}
}

float percentDiff(double val1, double val2)
{
	if ((absVal(val1) < 0.01) && (absVal(val2) < 0.01))
	{
		return 0.0f;
	}

	else
	{
    		return 100.0f * (absVal(absVal(val1 - val2) / absVal(val1 + SMALL_FLOAT_VAL)));
	}
} 

#endif //POLYBENCH_UTIL_FUNCTS_H

int main();
//define the error threshold for the results "not matching"
#define PERCENT_DIFF_ERROR_THRESHOLD 0.5

/* Problem size. */
#define NX 8192
#define NY 8192

#define GPU_DEVICE 1

#ifndef M_PI
#define M_PI 3.14159
#endif

/* Can switch DATA_TYPE between float and double */
typedef float DATA_TYPE;

void init_array(DATA_TYPE *x, DATA_TYPE *A)
{
  int i, j;

			dummyMethod3();
  for (i = 0; i < NX; i++)
    {
      x[i] = i * M_PI;
      for (j = 0; j < NY; j++)
	{
	  A[i*NY + j] = ((DATA_TYPE) i*(j)) / NX;
	}
    }
			dummyMethod4();
}

void compareResults(DATA_TYPE *z, DATA_TYPE *z_outputFromGpu)
{
  int i, fail;
  fail = 0;

			dummyMethod3();
  for (i=0; i<NY; i++)
    {
      if (percentDiff(z[i], z_outputFromGpu[i]) > PERCENT_DIFF_ERROR_THRESHOLD)
	{
	  fail++;
	}		
    }
			dummyMethod4();
	
  // print results
  printf("Non-Matching CPU-GPU Outputs Beyond Error Threshold of %4.2f Percent: %d\n", PERCENT_DIFF_ERROR_THRESHOLD, fail);
}

void atax_cpu(DATA_TYPE* A, DATA_TYPE* x, DATA_TYPE* y, DATA_TYPE* tmp)
{
  int i,j;
	
			dummyMethod3();
  for (i= 0; i < NY; i++)
    {
      y[i] = 0;
    }
			dummyMethod4();
  
			dummyMethod3();
  for (i = 0; i < NX; i++)
    {
      tmp[i] = 0;
      
      for (j = 0; j < NY; j++)
	{
	  tmp[i] = tmp[i] + A[i*NY + j] * x[j];
	}
      
      for (j = 0; j < NY; j++)
	{
	  y[j] = y[j] + A[i*NY + j] * tmp[i];
	}
    }
			dummyMethod4();
}

void GPU__atax(DATA_TYPE *A, DATA_TYPE *x, DATA_TYPE *y, DATA_TYPE *tmp) {
  int i, j;
  double s1, s2, e1, e2;

			dummyMethod3();
  for (i = 0; i < NY; i++) {
    y[i] = 0;
  }
			dummyMethod4();
  char RST_AI1 = 0;
  RST_AI1 |= !(((void*) (A + 0) > (void*) (tmp + 8192))
  || ((void*) (tmp + 0) > (void*) (A + 67108864)));
  RST_AI1 |= !(((void*) (A + 0) > (void*) (x + 8192))
  || ((void*) (x + 0) > (void*) (A + 67108864)));
  RST_AI1 |= !(((void*) (A + 0) > (void*) (y + 8192))
  || ((void*) (y + 0) > (void*) (A + 67108864)));
  RST_AI1 |= !(((void*) (tmp + 0) > (void*) (x + 8192))
  || ((void*) (x + 0) > (void*) (tmp + 8192)));
  RST_AI1 |= !(((void*) (tmp + 0) > (void*) (y + 8192))
  || ((void*) (y + 0) > (void*) (tmp + 8192)));
  RST_AI1 |= !(((void*) (x + 0) > (void*) (y + 8192))
  || ((void*) (y + 0) > (void*) (x + 8192)));
  s1 = rtclock();
  #pragma omp target enter data map(to: A[0:67108864],x[0:8192],tmp[0:8192],y[0:8192]) if(!RST_AI1)
  e1 = rtclock();
  {
			dummyMethod1();
#pragma omp target teams distribute parallel for if(!RST_AI1)
  for (i = 0; i < NX; i++) {
    tmp[i] = 0;
    for (j = 0; j < NY; j++) {
      tmp[i] = tmp[i] + A[i * NY + j] * x[j];
    }
  }
			dummyMethod2();

// Note that the Loop has been reversed
			dummyMethod1();
#pragma omp target teams distribute parallel for if(!RST_AI1)
  for (j = 0; j < NY; j++)
    for (i = 0; i < NX; i++) {
      { y[j] = y[j] + A[i * NY + j] * tmp[i]; }
    }
			dummyMethod2();
  }
  s2 = rtclock();
  #pragma omp target update from(tmp[0:8192],y[0:8192])
  e2 = rtclock();
  //printf("Extra cost time(s) is: %0.6lf\n", e1 - s1);

  printf("Host to Device number of times is: %d\n", 4);
  printf("Host to Device number of byte is: %ld\n", (67108864+8192+8192+8192) * sizeof(DATA_TYPE));
  printf("Host to Device spend of time(s) is: %0.6lf\n", e1 - s1);
  
  printf("Device to Host number of times is: %d\n", 2);
  printf("Device to Host number of byte is: %ld\n", (8192+8192) * sizeof(DATA_TYPE));
  printf("Device to Host spend of time(s) is: %0.6lf\n", e2 - s2);

  return;
}

inline void update(DATA_TYPE* y_outputFromGpu)
{
  DATA_TYPE yy = y_outputFromGpu[0];
}

//int main(int argc, char** argv)
int main()
{
  double t_start, t_end;

  DATA_TYPE* A;
  DATA_TYPE* x;
  DATA_TYPE* y;
  DATA_TYPE* y_outputFromGpu;
  DATA_TYPE* tmp;

  A = (DATA_TYPE*)malloc(NX*NY*sizeof(DATA_TYPE));
  x = (DATA_TYPE*)malloc(NY*sizeof(DATA_TYPE));
  y = (DATA_TYPE*)malloc(NY*sizeof(DATA_TYPE));
  y_outputFromGpu = (DATA_TYPE*)malloc(NY*sizeof(DATA_TYPE));
  tmp = (DATA_TYPE*)malloc(NX*sizeof(DATA_TYPE));

  printf( "<< Matrix Transpose and Vector Multiplication >>\n");
  printf("Data size NX: %d\n", NX);
  printf("Data size NY: %d\n", NY);

  init_array(x, A);

  t_start = rtclock();
  GPU__atax(A, x, y_outputFromGpu, tmp);
  
  update(y_outputFromGpu);
  
  t_end = rtclock();
  printf("GPU Runtime(s): %0.6lf\n", t_end - t_start);
	
  // t_start = rtclock();
  // atax_cpu(A, x, y, tmp);
  // t_end = rtclock();
  // printf("CPU Runtime: %0.6lfs\n", t_end - t_start);

  // compareResults(y, y_outputFromGpu);

  free(A);
  free(x);
  free(y);
  free(y_outputFromGpu);
  free(tmp);

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