#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifndef M_PI
    # define M_PI   3.14159265358979323846  /* pi */
#endif

double r2()
{
    return (double)(rand()%100003) / 100003.0;
}

int main(void)
{
    int count = 0;
    double x;
    double costhe;
    double costhel;
    const double a = 50;
    const double b = 2.6;
    const double p = 0.8e-4;
    const int n = 10000000; //1e7

    int t = omp_get_num_procs();
    omp_set_num_threads(t);
    printf("Threads number: %d\n", t);

    srand (time(0)); 

							dummyMethod1();
    #pragma omp parallel for private(x, costhe, costhel)\
        reduction(+:count) schedule(guided,1) 
    for (int i=1; i<=n; ++i){
        x = 0;
        costhe = 1;
        while(x>=0 & x<=a){
            x -= b * costhe * log(r2());
            if(r2()<p){
                count++;
                break;
            }else{
                costhel = 2*r2() - 1;
                costhe = costhe * costhel \
                        + sqrt(1-costhe*costhe) * sqrt(1-costhel*costhel) * cos(2*M_PI*r2());
            }
        }
    }
							dummyMethod2();
    
    printf("Transmittance: %f.\n", 1.0 - (double)count / (double)n);
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