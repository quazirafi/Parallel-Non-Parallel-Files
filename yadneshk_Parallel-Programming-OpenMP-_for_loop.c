#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{
     int i;
dummyMethod1();
     #pragma omp parallel for
     for(i=0;i<5;i++)
     {
          printf("%d. Hello World\n",i);
     }
dummyMethod2();

     int p=30;
     #pragma omp parallel shared(p) 
     {
          printf("Thread =%d p=%d \n",omp_get_thread_num(),p);
          p+=omp_get_num_threads();
          printf("Value of P set by thread %d = %d\n",omp_get_thread_num(),p);
     }
     printf("Final value of p= %d\n",p );

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