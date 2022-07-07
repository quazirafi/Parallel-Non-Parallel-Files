//Program to execute required number of thread
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main()
{

    int num = 10;               //Specify the number of thread
    omp_set_num_threads(num);   //Pass it to this function
dummyMethod1();
    #pragma omp parallel for ordered
    //It will execute thread for 10 times with 10 different threads
    for(int i=0;i<10;i++)
    {
        #pragma omp ordered     //To execute thread in order
        printf("Hello world! %d\n",omp_get_thread_num());
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