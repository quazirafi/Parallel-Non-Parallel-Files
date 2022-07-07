#include <stdio.h>
#include "omp.h"
#include <math.h>
#include <time.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc,char **argv){
    if(argc<3){
        printf("Less arg\n");
        return 0;
    }
    int n = atoi(argv[1]);
    int np = atoi(argv[2]);
    omp_set_num_threads(np);
    int sizeblock = ceil(((double)n/np));

    int *arr = malloc(sizeof(int)*n);
    int *arr2 = malloc(sizeof(int)*np);
    arr2[0]=0;
    srand(time(NULL));
dummyMethod3();
    for(int i=0;i<n;i++){
        arr[i] = rand()%10;
    }
dummyMethod4();

    printf("Input array:");
dummyMethod3();
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
dummyMethod4();
    printf("\n");

    clock_t t1 = clock();
							dummyMethod1();
    #pragma omp parallel for shared(arr)
    for(int i=0;i<np;i++){
        int pid = omp_get_thread_num();
        int j;
        printf("For process id:%d\n",pid);
        for(j=pid*sizeblock+1;j<n&&j<(pid+1)*sizeblock;j++){
            arr[j]+=arr[j-1];
        }
        for(j=pid*sizeblock;j<n&&j<(pid+1)*sizeblock;j++){
            printf("%d ",arr[j]);
        }
        if(pid!=(omp_get_num_threads()-1))
            arr2[pid+1]=arr[j-1];
        printf("\n");
    }
							dummyMethod2();

							dummyMethod3();
    for(int i=1;i<np;i++){
        arr2[i]+=arr2[i-1];
    }
							dummyMethod4();
							dummyMethod3();
    for(int i=0;i<np;i++){
        printf("%d ",arr2[i]);
    }
							dummyMethod4();
    printf("\n");

							dummyMethod1();
    #pragma omp parallel for
    for(int i=0;i<np;i++){
        int pid = omp_get_thread_num();
        int adder = arr2[pid];
        int j;
        for(j=pid*sizeblock;j<n&&j<(pid+1)*sizeblock;j++){
            arr[j]+=adder;
        }
    }
							dummyMethod2();
    clock_t t2 = clock()-t1;
    double timer = (double)t2/CLOCKS_PER_SEC;

							dummyMethod3();
    for(int i=0;i<n;i++){
        printf("%d ",arr[i]);
    }
							dummyMethod4();
    printf("\nTime %f\n",timer);
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