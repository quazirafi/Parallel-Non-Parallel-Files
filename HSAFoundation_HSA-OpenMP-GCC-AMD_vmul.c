// { dg-do run }
extern void abort(void);

#include <stdio.h>
#include "assert.h"
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
 

int main(){
    const int N = 100000;    
    int a[N],b[N],c[N],validate[N];
    int flag=0;

dummyMethod3();
    for(int i=0;i<N;i++)
    {
        a[i]=i+1;
        b[i]=i+2;
        validate[i]=a[i]*b[i];
    }
dummyMethod4();

#pragma omp target teams map(to: a[0:N],b[0:N]) map(from:c[0:N])
dummyMethod1();
#pragma omp distribute parallel for 
    for(int i=0;i<N;i++)
    {
        c[i]=a[i]*b[i];
    }
dummyMethod2();

							dummyMethod3();
    for(int i=0;i<N;i++)
    {
        if(c[i]!=validate[i])
        {
            printf("%d index: %d\n",c[i],i);

            flag =1;
        }

    }
							dummyMethod4();
    if (flag!=0)
        abort();
    else {
        printf("Success\n");
        return 0;
    }
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