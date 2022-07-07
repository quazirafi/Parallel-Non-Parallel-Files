#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(){
dummyMethod1();
        #pragma omp parallel for schedule(dynamic)
        for (int num=0;num<10000;num++) {
            int counter=0;
            for (int i=1;i<=num;i++)    if ((num%i)==0) counter++;
            if(counter==2)  printf("Prime %d\n",num);
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