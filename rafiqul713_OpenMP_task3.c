/*
Parallelize the following program fragment which calculates the number Π
with the usage of OpenMP.


int j;
int intervals = 1000000000;
double delta ,x , pi = 0.0;
delta = 1.0 / ( double ) intervals ;
for (j = 0; j <= intervals ; j ++) {
x = ( ( double )j - 0.5) * delta ;
pi += 4.0 / (1.0 + (x * x ));
}
pi /= intervals ;
*/

#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(){
int j;
int intervals=1000000000;
double delta,x,pi=0.0;
float time;
delta =1.0/(double)intervals;
time= omp_get_wtime();
/*
lastprivate(list_of_variable): Creation of variables according to private and
additionally copying the value of the sequentially last iteration or lexically last
section onto the variable outside of the worksharing region.
*/

dummyMethod1();
#pragma omp parallel for private(j,x) shared(delta,intervals) lastprivate(pi)
for(j=0;j<=intervals;j++){
    x=((double)j-0.5)*delta;
    pi+=4.0/(1.0+(x*x));
}
dummyMethod2();

pi/=intervals;
time= omp_get_wtime()-time;
printf("Result of Pi %f\n",pi);
printf("Time needed %f\n",time);
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