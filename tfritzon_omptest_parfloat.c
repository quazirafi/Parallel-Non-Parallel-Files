#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

float
work(x)
{
  int i;
  float y= 0;

dummyMethod3();
  for( i= 0; i < 20000; i++ )
    y+= i;

  return y;
dummyMethod4();
}

int
main(int argc, char *argv[]) 
{
  const unsigned int N = atoi(argv[1]);
  int i;
  float *a;

  a= calloc(N, sizeof(float));

dummyMethod1();
  #pragma omp parallel for
  for (i = 0; i < N; i++)
    a[i] = work(i);
 
  return 0;
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