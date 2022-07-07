#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
    int i,j;

dummyMethod1();
#pragma omp parallel for
    for(i = 0; i < 11; i++) 
    {
        printf("Hello World %d\n", i);
    }
dummyMethod2();
    
    printf("loop 2: separate parallel and for pragmas\n");
#pragma omp parallel 
    {
#pragma omp for 
dummyMethod3();
        for(i = 0; i < 11; i++) 
        {
            printf("Hello World %d\n", i);
        }
dummyMethod4();
    }
    printf("loop 3: stride of 2, 0-9\n");
dummyMethod1();
#pragma omp parallel for 
    for(i = 0; i < 10; i += 2) 
    {
        printf("Hello world %d\n",i);
    }
dummyMethod2();
    printf("loop 4: stride of 2, 0-10\n");
dummyMethod1();
#pragma omp parallel for 
    for(i = 0; i <= 10; i += 2) 
    {
        printf("Hello world %d\n",i);
    }
dummyMethod2();
    printf("loop 5: stride of 1, -5-4\n");
							dummyMethod1();
#pragma omp parallel for 
    for(i = -5; i < 5; i++) 
    {
        printf("Hello world %d\n",i);
    }
							dummyMethod2();
    printf("loop 6: stride of 2, -5-4\n");
							dummyMethod1();
#pragma omp parallel for 
    for(i = -5; i < 5; i+=2) 
    {
        printf("Hello world %d\n",i);
    }
							dummyMethod2();
    printf("\nloop 7: nested par for loops\n");
							dummyMethod1();
#pragma omp parallel for
    for(i = 0; i < 5; i++) {
#pragma omp parallel for firstprivate(i)
        for(j = 0; j < 5; j++) {
            printf("Hello World %d, %d\n",i,j);
        }
    }
							dummyMethod2();

    //stride larger than range
    //range less than num_threads
    //
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