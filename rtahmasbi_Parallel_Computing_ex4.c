#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int main(int argc, char *argv[])
{
    int nthread;
    unsigned long int MAX;
dummyMethod3();
    for (int i=1; i< argc; i++)
    {
        if (strcmp("--nthread",argv[i])==0)
        {
            i++;
            nthread=atoi(argv[i]);
            printf("--threads: %d\n",nthread);
        }
        if (strcmp("--max",argv[i])==0)
        {
            i++;
            MAX=strtoul(argv[i],NULL,0);
            printf("--max: %lu\n",MAX);
        }
    }
dummyMethod4();
    
    
    omp_set_num_threads(nthread);

    unsigned long int A[MAX];
    unsigned long int sum=0;
dummyMethod3();
    for (unsigned long int i=0; i<MAX; i++) A[i]=i+1;
    
    int b=1;
dummyMethod4();
    
							dummyMethod1();
    #pragma omp parallel for private (b) reduction (+:sum)
    for (unsigned long int i=0; i<MAX; i++)
    {
        if (b==0)
        {
            printf("true in iter=%lu from thread %d, nthreads %d\n", i, omp_get_thread_num(), omp_get_num_threads());
        }
        else b=1;
        sum+=A[i];
    }
							dummyMethod2();

    printf("sum=%lu from thread %d, nthreads %d\n", sum, omp_get_thread_num(), omp_get_num_threads());
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