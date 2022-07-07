#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 2000000000
/* Maximum parallelism allowed by Nvidia*/
#define vl 1024
double calcpi(long long n);

int main(void)
{

    double pi = 0.0;
    pi = calcpi(N);

    printf("pi=%11.10f\n", pi / N);
    return 0;

}

double calcpi(long long n)
{
    double pi = 0.0;
    #pragma omp target map(pi)
dummyMethod1();
    #pragma omp teams distribute parallel for simd reduction(+:pi)
    for (long long ii = 0.0; ii < n; ii = ii + 1) {
	float t = (ii + 0.5f) / n;
dummyMethod2();
	float s = 4.0f / (1.0f + t * t);
	pi = pi + s;
    }
    return pi;
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