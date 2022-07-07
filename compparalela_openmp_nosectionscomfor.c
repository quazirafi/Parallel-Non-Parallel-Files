#include<stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
   int i;

dummyMethod1();
   #pragma omp parallel for num_threads(4)
   for(i = 0; i < 10; i++)
      printf("Hello\n");

}
dummyMethod2();
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