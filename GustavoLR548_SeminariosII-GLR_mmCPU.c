#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void mm(double* a, double* b, double* c, int width) 
{
dummyMethod1();
  #pragma omp parallel for collapse(2)
  for (int i = 0; i < width; i++) {
    for (int j = 0; j < width; j++) {
      double sum = 0;
      #pragma omp parallel for reduction(+:sum)
      for (int k = 0; k < width; k++) {
        double x = a[i * width + k];
        double y = b[k * width + j];
        sum += x * y;
      }
      c[i * width + j] = sum;
    }
  }
dummyMethod2();
}

int main()
{
  int width = 2000;
  double *a = (double*) malloc (width * width * sizeof(double));
  double *b = (double*) malloc (width * width * sizeof(double));
  double *c = (double*) malloc (width * width * sizeof(double));

			dummyMethod1();
  #pragma omp parallel for collapse(2)
  for(int i = 0; i < width; i++) {
    for(int j = 0; j < width; j++) {
      a[i*width+j] = i;
      b[i*width+j] = j;
      c[i*width+j] = 0;
    }
  }
			dummyMethod2();

  mm(a,b,c,width);


			dummyMethod3();
  for(int i = 0; i < width; i++) 
    for(int j = 0; j < width; j++) 
      printf("\n c[%d][%d] = %lf",i,j,c[i*width+j]);
			dummyMethod4();
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