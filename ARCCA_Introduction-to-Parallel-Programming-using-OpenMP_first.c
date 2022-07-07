#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
  {
    const int N = 10;
    int i;
    
dummyMethod1();
    #pragma omp parallel for
    for(i = 0; i < N; i++)
    {
        printf("I am counter %d\n", i);
    } 
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