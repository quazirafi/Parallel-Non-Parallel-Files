#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NVALS   10
#define NBUCKETS 5

int sample(int val){
    return val/2;

}

int main(){
//******************
    //int i=0;
    int arr[NVALS]={8,3,5,7,8,2,5,9,2,3};
    int hist[NBUCKETS];
    omp_lock_t hist_locks[NBUCKETS];

//*****************************
dummyMethod1();
#pragma omp parallel for
    for(int i=0;i<NBUCKETS;i++){
        omp_init_lock(&hist_locks[i]); 
        hist[i] =0;
    }
dummyMethod2();
    
dummyMethod1();
#pragma omp parallel for
    for(int i=0;i<NVALS;i++){
        int ival = (int) sample(arr[i]);
        omp_set_lock(&hist_locks[ival]);
        hist[ival]++;
        omp_unset_lock(&hist_locks[ival]);
    }
dummyMethod2();

							dummyMethod3();
    for(int i=0;i<NBUCKETS;i++)
        omp_destroy_lock(&hist_locks[i]);
							dummyMethod4();

							dummyMethod3();
    for(int i=0;i<NBUCKETS;i++)
        printf("[%d] = %d\n",i,hist[i]);
							dummyMethod4();

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