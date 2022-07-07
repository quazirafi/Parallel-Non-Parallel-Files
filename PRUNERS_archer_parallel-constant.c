// RUN: %libsword-compile-and-run-race 2>&1 | FileCheck %s
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 10

int main (int argc, char* argv[])
{
	int i,j;
	int a[N];
	a[0] = 2;

dummyMethod1();
#pragma omp parallel for num_threads(2)
          for (i = 0;i < N; i++) {
            a[i] = a[i] + a[0];
          }
dummyMethod2();

	return 0;
}

// CHECK: --------------------------------------------------
// CHECK: WARNING: SWORD: data race (program={{.*}})
// CHECK:   Two different threads made the following accesses:
// CHECK:     Read of size 4 in .omp_outlined.{{.*}} at {{.*}}parallel-constant.c:15:27
// CHECK:     Write of size 4 in .omp_outlined.{{.*}} at {{.*}}parallel-constant.c:15:18
// CHECK: --------------------------------------------------
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