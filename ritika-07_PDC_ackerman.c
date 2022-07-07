#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
 
int ackermann(int m, int n)
{
        if (!m) return n + 1;
        if (!n) return ackermann(m - 1, 1);
        return ackermann(m - 1, ackermann(m, n - 1));
}
 
int main()
{
        int m, n;
dummyMethod1();
        #pragma omp parallel for
        for (m = 0; m <= 4; m++) {
            printf("At thread: %d\n", omp_get_thread_num);
            #pragma omp parallel for
                for (n = 0; n < 6 - m; n++){
                        printf("At thread: %d\n", omp_get_thread_num);
                        printf("A(%d, %d) = %d\n", m, n, ackermann(m, n));
                }
        }
dummyMethod2();
 
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