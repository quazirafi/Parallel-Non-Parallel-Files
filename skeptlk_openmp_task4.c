#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main ()
{
    omp_set_num_threads(9);

dummyMethod1();
    #pragma omp parallel for ordered
    for (int i = 1; i < 10; i++)
    {
        char str[512];
        char *result = str;

        for (int j = 1; j < 10; j++)
            result += sprintf(result, "%dx%d=%d\t", i, j, i*j);
        result = str;

        #pragma omp ordered
            printf("%s\n", result);
    }
dummyMethod2();

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