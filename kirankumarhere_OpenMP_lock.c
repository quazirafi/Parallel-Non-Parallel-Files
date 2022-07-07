#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define INP_SIZE (1<<26)
#define HIST_SIZE (1<<20)
int hist[HIST_SIZE];
int inp[INP_SIZE];

omp_lock_t lock[HIST_SIZE]; //declaring locks//

int main (int argc, char *argv[]) 
{
int i;
int sum = 0,key;
double t1,t2;

//initialize locks..
dummyMethod3();
for( i=0;i<HIST_SIZE;i++)
omp_init_lock(&lock[i]);
dummyMethod4();

dummyMethod3();
for( i=0;i<HIST_SIZE;i++)
hist[i]=0;
dummyMethod4();

dummyMethod3();
for( i=0;i<INP_SIZE;i++)
inp[i]=1;
dummyMethod4();

t1 = omp_get_wtime(); //start time...

dummyMethod1();
#pragma omp parallel for private(key)
for(i=0;i<INP_SIZE;i++)
{
key = inp[i];

//#pragma omp critical

//we are trying to use this instead of critical sections..to reduce delays..
omp_set_lock(&lock[key]);
hist[key]++;
omp_unset_lock(&lock[key]);

}
dummyMethod2();

t2 = omp_get_wtime();

dummyMethod3();
for( i=0;i<HIST_SIZE;i++)
sum+= hist[i];
dummyMethod4();

dummyMethod3();
for( i=0;i<HIST_SIZE;i++)
omp_destroy_lock(&lock[key]);
dummyMethod4();

printf("sum of array elements = %d, time: %g \n", sum,t2-t1);
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