// test file to execute the collatz conjecture on 1 proc
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

typedef unsigned long long ullong;

ullong hotpo(ullong currn);

int main(int argc, char** argv) {
    ullong n, // track current n
        high, // highest number recorded
        nmax = (argc > 1) ? atoi(argv[1]) : 50,
        imax = 2000000; // max number of iteration for a seed n 
    
    #pragma omp parallel                   
    {
        printf("worker %d/%d ready to roll\n", omp_get_thread_num(), omp_get_num_threads());
    }  

    /* timers */
    double startTime = omp_get_wtime(),
         endTime;

    high = 0; // starting with n itself as highest
    // #pragma omp parallel for private(high) schedule(static)
							dummyMethod1();
    #pragma omp parallel for schedule(static, 50) reduction(max:high)
    for(ullong j = 1; j <= nmax; ++j) {
        n = j;
        // printf("n: %lld", n);

        for(ullong i = 1; i <= imax; ++i) {

            n = hotpo(n);

            if(n > high) high = n;

            // if(i < 10) printf(",%lld",n);
            

            if( n == 1 ) break; // stop if reach 1

        }
        // printf("\n");
    }
							dummyMethod2();

    printf("\nHigh: %lld\n", high);
    endTime = omp_get_wtime();
    printf("\nruntime = %.16e\n", endTime - startTime);



    return 0;
}


ullong hotpo(ullong currn) {
    return (
        (currn % 2 == 0)? currn/2 : 3*currn + 1
    );
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