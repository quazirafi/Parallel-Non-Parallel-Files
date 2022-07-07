#include "stdio.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//# define ARRAY_SIZE 100

void saxpy(int n, float a, float * restrict x, float * restrict y)
{
    double start_time, run_time;
    /*start timer */
	start_time = omp_get_wtime();
dummyMethod1();
    #pragma omp parallel for
    for (int i = 0; i < n; ++i){
        y[i] = a*x[i] + y[i];
    }
dummyMethod2();

    run_time = omp_get_wtime() - start_time;
    printf("Paralled Version Duration:  %f \n", run_time);
    printf("With a vector size of:  %d \n", n);
}
void *random_Gen(float *x, float *y, int n){
	srand(time(0));
dummyMethod3();
	for (int i = 0; i < n; i++){
        x[i] = (rand() % 1000);
        y[i] = (rand() % 1000);
        
    }
};
dummyMethod4();

int main(){
    int n = 1000000;
    float x[n];
    float y[n];
    random_Gen(x,y,n);
    saxpy(n, 2.0, x, y);
    
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