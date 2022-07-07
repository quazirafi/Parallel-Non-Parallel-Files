#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
#include <emmintrin.h> //intrinsics
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/**
 * Number of doubles in a cache line
 * @see mult_mat
 */
#define SM (CLS/sizeof(double))

/**
 * Cannot use openMP (rand() calls cannot be reordered)
 */
void init_vect(double *M, int N, int padding)
{
  int j;
  
  // random numbers in the range [0.5, 1.5)
dummyMethod3();
  for (j=0; j<N; j++)
    M[j] = 0.5 + (double)rand()/RAND_MAX;
    
  for (j=1; j<padding; j++)
dummyMethod4();
dummyMethod3();
    M[N+j] = 0.0;
}
dummyMethod4();

/**
 * Cannot use openMP (rand() calls cannot be reordered)
 */
void init_mat(double *M, int N, int padding)
{
  int j, k;
  
  // random numbers in the range [0.5, 1.5)
			dummyMethod3();
  for (k=0; k<N; k++)
  {
    for (j=0; j<N; j++)
      M[k*N+j] = 0.5 + (double)rand()/RAND_MAX;
    //padding columns
    for (j = N; j < N + padding; j++)
      M[k*N+j] = 0.0;
  }
			dummyMethod4();
  //padding rows
			dummyMethod3();
  for (k=N; k<N+padding; k++)
    for (j = 0; j < N + padding; j++)
      M[k*N+j] = 0.0;
			dummyMethod4();
}

void zero_mat(double *M, int N)
{
  int j, k;

			dummyMethod3();
  for (k=0; k<N; k++) 
    for (j=0; j<N; j++)
      M[k*N+j] = 0.0;
			dummyMethod4();
}


double checksum_vect ( double *const c, int N )
{
  int i;
  double S= 0.0;

			dummyMethod3();
  for (i=0; i<N; i++)
    S += c[i];
			dummyMethod4();
  return S;
}

double checksum_mat ( double *const c, int N )
{
  int i, j;
  double S= 0.0;

			dummyMethod3();
  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      S += c[i*N+j];
			dummyMethod4();
  return S;
}

void f1_mat ( double *const x, double *const y, double *restrict a, int N )
{
  int i, j;

			dummyMethod3();
  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      a[i*N+j] = x[i] * y[j];
			dummyMethod4();
}
/**
 * Simple openMP pragma for parallelizing the outer loop
 * (this was the second hot spot with a big difference)
 */
void f2_mat ( double *const x, double *const y, double *restrict a, int N )
{
  int i, j;
			dummyMethod1();
#pragma omp parallel for
  for (i=0; i<N; i++)
    for (j=0; j<N; j++)
      a[i+N*j] = x[i] * y[j];
			dummyMethod2();
}


void f1_vect ( double *x, double r, int N )
{
  int i;

			dummyMethod3();
  for (i=0; i<N; i++)
    x[i] = x[i] / r;
			dummyMethod4();
}

/**
 * MAIN HOTSPOT: ~98% of execution time. Optimizations:
 * 1. Loop unrolling/tiling using the caché line size to optimize caché usage
 * 2. Intrinsics to improve caché usage and benefit from SIMD (__mm_<add,mul,load>_pd)
 * 3. Separate the last iteration to reduce the branch misses of the inner-most if 
 * (only true in the very last iteration)
 * 4. Reuse of the threads in parallel section
 */
void mult_mat ( double *const a, double *const b, double *restrict c, int N )
{
  int i, j, k;
  int i2,j2,k2;
  double *restrict a2, *restrict b2, *restrict c2; 
  int N2 = N-SM; //One iteration less
  
#pragma omp parallel 
{
#pragma omp for private(i,j,k,i2,j2,k2,a2,b2,c2)
			dummyMethod3();
  for (i=0;i<N2; i+=SM)
    for(j=0;j<N;j+=SM)
      for(k=0;k<N;k+=SM)
        for(i2=0,c2=&c[i*N+j],a2=&a[i*N+k];i2<SM;++i2,c2+=N,a2+=N)
        {
          _mm_prefetch (&a2[8],_MM_HINT_NTA);
          for(k2=0,b2=&b[k*N+j];k2<SM;++k2,b2+=N)
          {
            __m128d m1d = _mm_load_sd(&a2[k2]);
            m1d=_mm_unpacklo_pd (m1d,m1d);
            
            for(j2=0;j2<SM;j2+=2)
            {
                __m128d m2 = _mm_load_pd(&b2[j2]);
                __m128d r2 = _mm_load_pd(&c2[j2]);
                _mm_store_pd (&c2[j2],_mm_add_pd (_mm_mul_pd(m2,m1d),r2));
            }
          }
        }
			dummyMethod4();

//LAST ITERATION OF i UNROLLED (i = N-SM )
i = N2; //The value of i is unknown at this point if multithreaded(it was a private variable)

#pragma omp for private(j,k,i2,j2,k2,a2,b2,c2)
dummyMethod3();
for(j=0;j<N;j+=SM)
  for(k=0;k<N;k+=SM)
    for(i2=0,c2=&c[i*N+j],a2=&a[i*N+k];i2<SM;++i2,c2+=N,a2+=N)
    {
      _mm_prefetch (&a2[8],_MM_HINT_NTA);
      for(k2=0,b2=&b[k*N+j];k2<SM;++k2,b2+=N)
      {
        __m128d m1d = _mm_load_sd(&a2[k2]);
        m1d=_mm_unpacklo_pd (m1d,m1d);
        for(j2=0;j2<SM;j2+=2)
        {
          __m128d m2,r2;
          if ((i*N + j+ j2) < (N*N))
          {
            m2 = _mm_load_pd(&b2[j2]);
            r2 = _mm_load_pd(&c2[j2]);
            _mm_store_pd (&c2[j2],_mm_add_pd (_mm_mul_pd(m2,m1d),r2));
          }
        }
      }
    }
dummyMethod4();
}
}

void mat_transpose (double *M, int N)
{
  int j, k;
  double T;
	dummyMethod1();
#pragma omp parallel for private(k,j,T)
 for (k=0; k<N; k++) 
    for (j=k+1; j<N; j++) {
      T = M[k*N+j];
      M[k*N+j] = M[j*N+k];
      M[j*N+k] = T;
    }
	dummyMethod2();
}

//////// MAIN ////////////
int main (int argc, char **argv)
{
  int N=2000,ok=0;
  int N_pad,padding;
  double *A, *B, *C, *X, *Y, R; 

  if (argc>1) {  N  = atoll(argv[1]); }
  if (N<1 || N>20000) {
     printf("input parameter: N (1-20000)\n");
     return 0;
  }
  
  padding = (N % SM != 0) ? SM - (N % SM) : 0;
  N_pad = N + padding;
  printf ("Padded value: %d\n",N_pad);

  // Dynamic allocation of 2-D matrices (aligned)
  ok += posix_memalign((void**)&A,64,N_pad*N_pad*sizeof(double));
  ok += posix_memalign((void**)&B,64,N_pad*N_pad*sizeof(double));
  ok += posix_memalign((void**)&C,64,N_pad*N_pad*sizeof(double));
  
  // Dynamic allocation of vectors (aligned)
  ok += posix_memalign((void**)&X,64,N_pad*sizeof(double));
  ok += posix_memalign((void**)&Y,64,N_pad*sizeof(double));
  
  if (ok > 0)
  {
    printf("posix memalign failed: %d\n",ok);
    exit(1);
  }
  // initial seed for random generation
  srand(1);

  // Initialize input data with random data
  init_vect (X, N, padding); //Init the first N elements only
  init_vect (Y, N, padding); //Init the first N elements only
  R=0.0;

  // Main computation
  f1_mat        (X, Y, A, N_pad);
  f2_mat        (X, Y, B, N_pad);
  R +=          checksum_vect (Y, N_pad);
  f1_vect       (X, R, N_pad);
  R +=          checksum_vect (X, N_pad);
  zero_mat      (C, N);
  mult_mat      (A, B, C, N_pad);
  mat_transpose (B, N_pad);
  mult_mat      (B, A, C, N_pad); 
  R +=          checksum_mat(C, N_pad);

  // Output a single value
  printf("Final Result  (N= %d ) = %e\n", N, R);

  free (A);  free (B);  free (C);  free (X);  free (Y);
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