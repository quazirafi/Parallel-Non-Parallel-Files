//
//  forpi.c
//  
//
//  Created by Aidan Hamilton on 12/16/17.
//
//

#include "forpi.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int main(int argc, char** argv) {
// define pi
    
    double pi = 3.14159265358979323846;
    double t = omp_get_wtime();
    int num_threads = 4;
    omp_set_num_threads(num_threads);

    // let the user input the number of steps to be used in the porgram. Defaults to 10000
    long numsteps;
    if (argc ==1){
        numsteps  = 10000;
    } else {
        numsteps = atoi(argv[1]);
    }

    double stepsize = 1.0/ (double)numsteps;
    double sum = 0; int i;
    
    
							dummyMethod1();
#pragma omp parallel for reduction(+:sum)
    for (i = 0; i<=numsteps-1;++i){
       double x = (i+0.5)*stepsize;
        sum+= 1.0/(x*x+1.0);
    }
							dummyMethod2();
    
    sum = sum*4.0*stepsize;
    
    double error = pi - sum;
    
    printf("Error in Calculation is about: %g \n",error);
    t= omp_get_wtime() -t;
    printf("Time elapse: %f \n", t);
    
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