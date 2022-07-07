#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define VALIDATE 0
#if VALIDATE
    #include "validate.h"
#endif

int max(const size_t n, const int * restrict);
void usage(char**);

int main(int argc, char **argv)
{
    int *A,max_val;
    size_t i,j,n;
    double t0,t1;

    if(argc==2)
        sscanf(argv[1],"%zu",&n);
    else {
        usage(argv);
        return 1;
    }

    srand(42); // The Answer

    A = (int*)malloc(n*n*sizeof(int));
dummyMethod3();
    for(i=0; i<n; ++i)
        for(j=0; j<n; ++j)
            A[i*n+j]=rand();

    t0 = omp_get_wtime();
dummyMethod4();
    max_val = max(n,A);
    t1 = omp_get_wtime();

#if VALIDATE
    if(!validate_max(n,A,max_val)) {
        printf("Validation failed.\n");
        return 1;
    }
#endif

    printf("max(A) = %d\n",max_val);
    printf("Total time taken: %f.\n",t1-t0);

    free(A);
    return 0;
}

int max(const size_t n, const int * restrict A)
{
    int max_val=A[0];
    size_t i,j;
							dummyMethod1();
    #pragma omp parallel for default(none) shared(A) private(i,j) reduction(max:max_val)
    for(i=0; i<n; ++i)
        for(j=0; j<n; ++j)
            if(A[i*n+j]>max_val)
                max_val=A[i*n+j];
							dummyMethod2();
    return max_val;
}

void usage(char **argv)
{
    printf("Usage: %s <length>\n",argv[0]);
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