#include "omp.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(int argc, char **argv) {
	// считываем из консоли
    int N = atoi(argv[1]);
    int sum = 0;
    // статическое распределение интераций - одинаковое на каждый поток
dummyMethod1();
    #pragma omp parallel for schedule(static)
	for (intptr_t i = 0; i <= N; i++) {
		sum = sum + i;
	}
dummyMethod2();
    
    printf("%d\n", sum);
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