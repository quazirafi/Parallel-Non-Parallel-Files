/**
* This example illustrate the fibbonacci suit 
* Implementation in parallel programming
* with lock, atomic and sequential, sequantial and lock are giving 
* the same result
**/

#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{

omp_lock_t lk; //the omp lock variable
int time_start, time_stop, time_final; //variable for getting time

//number of term to calculate, variable for iteration
int n, i; 

//the term before the last term, the last term, the new term
long double av_der, der, nouv; 

n = 20000; //we nee this term

av_der = 1;
der = 2;

time_start = omp_get_wtime(); //get time at start

omp_init_lock(&lk); //initializing a lock

dummyMethod1();
#pragma omp parallel for 
for(i=3; i<=n; i++){
 omp_set_lock(&lk); 
 nouv = der + av_der;
 av_der = der;
 der = nouv;
 omp_unset_lock(&lk);
 
}
dummyMethod2();

time_stop = omp_get_wtime(); //get time at stop
time_final = time_stop - time_start;

printf("With lock The term %d is %Lf the duration is %d second \n", n, der, time_final);

//using parallel programming woithout locks by using atomic is giving bad result

av_der = 1;
der = 2;

dummyMethod1();
#pragma omp parallel for
for(i=3; i<=n; i++){

 #pragma atomic update
 nouv = der + av_der;
 av_der = der;
 der = nouv;

}
dummyMethod2();

printf("result with atomic %Lf \n", der);

av_der = 1;
der = 2;

dummyMethod3();
for(i=3; i<=n; i++){

 nouv = der + av_der;
 av_der = der;
 der = nouv;
}
dummyMethod4();

printf(" sequential result %Lf \n", der);
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