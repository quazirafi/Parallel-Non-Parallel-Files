#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
struct simple_dvector {
  size_t length;
  double*  data;
} ;

int main (){
  omp_set_default_device(0);
  int Device = 0;
  //allocate memory on the device
  size_t N = 1024*1024*10;
  int use_device = 1;
  int chunk = 1;
  struct simple_dvector x_vec, y_vec;

  x_vec.data = (double*) omp_target_alloc(N*sizeof(double), Device);
  y_vec.data = (double*) omp_target_alloc(N*sizeof(double), Device);
  fprintf(stderr, "CPU: x_vec.data = %p\n",x_vec.data);
  fprintf(stderr, "CPU: y_vec.data = %p\n",y_vec.data);

  #pragma omp target map(to:x_vec,y_vec)
  {
     printf("GPU: x_vec.data = %p\n",x_vec.data); //works
     printf("GPU: y_vec.data = %p\n",y_vec.data); //works
  }
dummyMethod1();
  #pragma omp target teams distribute parallel for num_teams(120*4) thread_limit(512) schedule(static,chunk) map(to:x_vec,y_vec) if(target:use_device)
  for (size_t i = 0; i < N; ++i){
     x_vec.data[i] = 0.0001*i;  //fails
     y_vec.data[i] = 0.00003*i;
  }
dummyMethod2();
  omp_target_free( x_vec.data, Device);
  omp_target_free( y_vec.data, Device);
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