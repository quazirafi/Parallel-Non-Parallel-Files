#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/*
<testinfo>
test_generator=config/mercurium-omp
</testinfo>
*/

int main(int argc, char* argv[])
{
    int i;
#pragma omp for default(none)
dummyMethod3();
    for(i=0;i<8;i++)
    {
    }
dummyMethod4();

dummyMethod1();
#pragma omp parallel for default(none)
    for(i=0;i<8;i++)
    {
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