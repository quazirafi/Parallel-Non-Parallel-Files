#include <stdlib.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void corr(float *A, float *MEAN, float *STDEV, int m, int n) {
dummyMethod3();
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++)
      MEAN[i] += A[i * n + j];

    MEAN[i] /= n;
  }
dummyMethod4();

dummyMethod3();
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++)
      STDEV[i] += (A[i * n + j] - MEAN[i]) * (A[i * n + j] - MEAN[i]);

    STDEV[i] = sqrt(STDEV[i] / n);
  }
dummyMethod4();
}

int main(int argc, char *argv[]) {
  float *x, *y, *z, m, n;
  n = 10000;
  m = 10000;
  x = (float *)malloc(sizeof(float) * 100000000);
  y = (float *)malloc(sizeof(float) * 100000000);
  z = (float *)malloc(sizeof(float) * 100000000);
  char RST_AI1 = 0;
  RST_AI1 |= !((x + 0 > y + 99999999)
  || (y + 0 > x + 99999999));
  RST_AI1 |= !((x + 0 > z + 99999999)
  || (z + 0 > x + 99999999));
  RST_AI1 |= !((y + 0 > z + 99999999)
  || (z + 0 > y + 99999999));
  #pragma omp target device (GPU_DEVICE) if(!RST_AI1)
  #pragma omp target data map(tofrom: x[0:99999999],y[0:99999999],z[0:99999999]) if(!RST_AI1)
  {
			dummyMethod1();
  #pragma omp parallel for 
  for (unsigned int i = 0; i < 100000000; i++) {
    x[i] = i;
    y[i] = i;
    z[i] = i;
  }
			dummyMethod2();
  }
  corr(x, y, z, m, n);
  free(x);
  free(y);
  free(z);
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