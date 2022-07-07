#include<stdlib.h>
#include<stdio.h>
#include<time.h>
#include "omp.h"
#include<math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define interval 1000000000

int main()
{ double pi=0.0;
   double c_point=0.0;
    double s_point=0.0;



    double s_time=omp_get_wtime();
     srand(time(NULL));

    printf("Parallel code Start:%lf",s_time);
	    
	unsigned int myseed;
dummyMethod1();
    #pragma omp parallel for reduction(+:c_point)
    for(long int i=0; i<interval;i++){
	myseed = omp_get_thread_num();
dummyMethod2();
        double r_x=(double)(rand_r(&myseed) % (interval + 1)) / interval;
        double r_y=(double)(rand_r(&myseed) % (interval + 1)) / interval;

        double tot= r_x*r_x+r_y*r_y;

        if(tot<=1.0)
            c_point++;
       // s_point++;

    }

     double e_time=omp_get_wtime();

    printf("\nParallel code End:%lf",e_time) ;
    printf("\nExecution Time:%lf",e_time-s_time) ;

    pi= (double)(c_point/(interval))*4;


    printf("\nCalculated pi value:%lf\n",pi);
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