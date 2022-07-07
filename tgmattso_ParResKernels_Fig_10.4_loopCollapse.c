#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// sample compile command: "gcc -fopenmp -c Fig_10.4_loopCollapse.c" to generate *.o object file



// apply a function (*MFUNC) to each element of an N by M array

void Apply(int N, int M, float* A, void(*MFUNC)(int, int, float*))
{ 
dummyMethod1();
   #pragma omp parallel for num_threads(4) collapse(2) if(N*M>100)
      for (int i = 0; i < N; i++)
         for (int j = 0; j < M; j++)
            MFUNC(i, j, (A+i*M+j));
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