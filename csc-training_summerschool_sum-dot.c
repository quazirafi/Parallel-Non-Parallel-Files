#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NX 102400

int main(void)
{
    double vecA[NX], vecB[NX], vecC[NX];

    /* Initialization of the vectors */
dummyMethod3();
    for (int i = 0; i < NX; i++) {
        vecA[i] = 1.0 / ((double) (NX - i));
        vecB[i] = vecA[i] * vecA[i];
    }
dummyMethod4();

    double res = 0.0;

#pragma omp target data map(to:vecA, vecB) map(from:vecC, res) 
  {
dummyMethod1();
#pragma omp target teams distribute parallel for 
    for (int i = 0; i < NX; i++) {
        vecC[i] = vecA[i] + vecB[i];
    }
dummyMethod2();


dummyMethod1();
#pragma omp target teams distribute parallel for reduction(+:res)
    for (int i = 0; i < NX; i++) {
        res += vecC[i] * vecB[i];
    }
dummyMethod2();

  }

    double sum = 0.0;
    /* Compute the check value */
							dummyMethod3();
    for (int i = 0; i < NX; i++) {
        sum += vecC[i];
    }
							dummyMethod4();
    printf("Reduction sum: %18.16f\n", sum);
    printf("Dot product: %18.16f\n", res);

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