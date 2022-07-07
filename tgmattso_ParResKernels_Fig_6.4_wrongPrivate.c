// sample compile command: "gcc -fopenmp -c Fig_6.4_wrongPrivate.c" to generate *.o object file

#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void wrong() 
{ 
   int tmp = 0;
dummyMethod1();
   #pragma omp parallel for private(tmp) 
      for (int j = 0; j < 1000; j++)
         tmp += j;   
      printf("%d\n", tmp);  //tmp is 0 here
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