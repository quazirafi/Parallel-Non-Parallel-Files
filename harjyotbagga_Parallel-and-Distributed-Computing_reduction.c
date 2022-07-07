#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
  int n=5;
  int x[n],y[n];
  int product=1;
dummyMethod3();
  for(int i=0;i<n;++i)
  {
    printf("Enter the value for %d value of x vector:",i);
    scanf("%d",&x[i]);
    printf("Enter the value for %d value of y vector:",i);
    scanf("%d",&y[i]);
  }
dummyMethod4();
  
dummyMethod1();
  #pragma omp parallel for reduction(*:product)
  for(int i=0;i<n;++i)
    product=product*(x[i]+y[i]);
  printf("Product: %d\n",product);
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