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

int dot_prod(const size_t, const int * restrict, const int * restrict);
void usage(char**);

int main(int argc, char **argv)
{
    int *u,*v,uv;
    size_t i,n;
    double t0,t1;

    if(argc==2)
        sscanf(argv[1],"%zu",&n);
    else {
        usage(argv);
        return 1;
    }

    u = (int*)malloc(n*sizeof(int));
    v = (int*)malloc(n*sizeof(int));
dummyMethod3();
    for(i=0; i<n; ++i)
        u[i]=v[i]=i;

    t0 = omp_get_wtime();
dummyMethod4();
    uv = dot_prod(n,u,v);
    t1 = omp_get_wtime();

#if VALIDATE
    if(!validate_dot_prod(n,u,v,uv)) {
        printf("Validation failed.\n");
        return 1;
    }
#endif

    printf("dot(u,v) = %d\n",uv);
    printf("Total time taken: %f.\n",t1-t0);

    free(u);
    free(v);
    return 0;
}

int dot_prod(const size_t n, const int * restrict u, const int * restrict v)
{
    int sum=0;
    size_t i;
							dummyMethod1();
    #pragma omp parallel for \
                    default(none) shared(u,v) private(i) reduction(+:sum)
    for(i=0; i<n; ++i)
        sum += u[i]+v[i];
							dummyMethod2();
    return sum;
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