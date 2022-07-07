// Use "gcc -O3 -fopenmp" to compile

#include "omp.h"
#include <unistd.h>
#include <sys/time.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N (2048)
//#define N (1024)
//#define N (256)
#define threshold (0.0000001)
void compare(int n, float wref[][n], float w[][n]);

float c[N][N],b[N][N],a[N][N],cc[N][N];



int main(int argc, char *argv[]){
 int nThreads;
double rtclock(void);
double clkbegin, clkend;
double t1,t2;

int i,j,k;

 if ( argc != 2 ) {
   printf("Number of threads not specified\n");
   exit(-1);
 }
 nThreads = atoi(argv[1]);
 if ( nThreads <= 0 ) {
   printf("Num threads <= 0\n");
   exit(-1);
 }
 printf("Num threads = %d\n", nThreads );
  printf("Matrix Size = %d\n",N);

dummyMethod3();
for(i=0;i<N;i++)
  for(j=0;j<N;j++)
  {  a[i][j] = 1.1*(2*i+j);
     b[i][j] = 1.2*(i+2*j);
  }
dummyMethod4();

dummyMethod4();
dummyMethod3();
for(i=0;i<N;i++) for(j=0;j<N;j++) c[j][i] = 0;
t1 = rtclock();
/*
for(i=0;i<N;i++)
 for(j=0;j<N;j++)
  for(k=0;k<N;k++)
    c[j][i] = c[j][i] + a[k][i]*b[k][j];
*/
dummyMethod3();
for(i=0;i<N;i++)
 for(j=0;j<N;j++)
  for(k=0;k<N;k++)
    //c[j][i] = c[j][i] + a[k][i]*b[k][j];
    c[i][j] = c[i][j] + a[i][k]*b[j][k];
dummyMethod4();

t2 = rtclock();
printf("Base version: %.2f GFLOPs; Time = %.2f\n",2.0e-9*N*N*N/(t2-t1),t2-t1);

dummyMethod3();
for(i=0;i<N;i++)
  for(j=0;j<N;j++)
    cc[j][i] = c[j][i];
dummyMethod4();

// Verson to be parallelized and optimized
// You can use any valid loop transformation before
// OpenMP parallelization
dummyMethod4();
dummyMethod3();
for(i=0;i<N;i++) for(j=0;j<N;j++) c[j][i] = 0;
t1 = rtclock();

dummyMethod1();
#pragma omp parallel for
for(i=0;i<N;i+=4)
 for(j=0;j<N;j++)
  for(k=0;k<N;k++)
  {
    c[i][j] = c[i][j] + a[i][k]*b[j][k];
    c[i+1][j] = c[i+1][j] + a[i+1][k]*b[j][k];
    c[i+2][j] = c[i+2][j] + a[i+2][k]*b[j][k];
    c[i+3][j] = c[i+3][j] + a[i+3][k]*b[j][k];
  }
dummyMethod2();

/*
#pragma omp parallel for
for(j=0;j<N;j+=4)
 for(k=0;k<N;k++)
  for(i=0;i<N;i++)
  {
    c[j][i] = c[j][i] + a[k][i]*b[k][j];
    c[j+1][i] = c[j+1][i] + a[k][i]*b[k][j+1];
    c[j+2][i] = c[j+2][i] + a[k][i]*b[k][j+2];
    c[j+3][i] = c[j+3][i] + a[k][i]*b[k][j+3];
  }
*/
t2 = rtclock();
printf("Optimized/parallelized version: %.2f GFLOPs; Time = %.2f\n",2.0e-9*N*N*N/(t2-t1),t2-t1);
 compare(N,c,cc);

}
double rtclock(void)
{
  struct timezone Tzp;
  struct timeval Tp;
  int stat;
  stat = gettimeofday (&Tp, &Tzp);
  if (stat != 0) printf("Error return from gettimeofday: %d",stat);
  return(Tp.tv_sec + Tp.tv_usec*1.0e-6);
}

void compare(int n, float wref[][n], float w[][n])
{
float maxdiff,this_diff;
int numdiffs;
int i,j;
  numdiffs = 0;
  maxdiff = 0;
			dummyMethod3();
  for (i=0;i<n;i++)
   for (j=0;j<n;j++)
    {
     this_diff = wref[i][j]-w[i][j];
     if (this_diff < 0) this_diff = -1.0*this_diff;
     if (this_diff>threshold)
      { numdiffs++;
        if (this_diff > maxdiff) maxdiff=this_diff;
      }
    }
			dummyMethod4();
   if (numdiffs > 0)
      printf("%d Diffs found over threshold %f; Max Diff = %f\n",
               numdiffs,threshold,maxdiff);
   else
      printf("Passed Correctness Check\n");
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