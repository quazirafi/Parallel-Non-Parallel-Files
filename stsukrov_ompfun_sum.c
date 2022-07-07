#include<stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int sum_all(int *data, int n){
  int sum = 0;
dummyMethod1();
  #pragma omp parallel for reduction(+:sum)
  for(int i=0;i<n;++i){
    sum += data[i];
  }
dummyMethod2();

  return sum;
}

void main()
{
  int arr[] = {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1};
  int n = sizeof(arr)/sizeof(arr[0]);
  int sum = sum_all(arr, n);
  printf("sum = %d\n", sum);
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