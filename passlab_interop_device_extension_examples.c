#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* device clause should support the following examples and 
 * detail grammar is specified in https://github.com/passlab/passlab.github.io/wiki/HOMP-Extensions-to-OpenMP
 
 device(0:*): all devices
 device(0, 2, 3, 5)
 device(0:2, 4:2) which is the list of 0,1,4,5.
 device(0:*:OMP_DEVICE_NVGPU): ALL GPU devices and consider OMP_DEVICE_NVGPU as a enum/integer so just pass it as 
 expression.  
 */

void axpy(int N, float *Y, float *X, float a) {
    int i;

/* official */
#pragma omp target device(0)
dummyMethod1();
#pragma omp parallel for
    for (i = 0; i < N; ++i)
        Y[i] += a * X[i];
}
dummyMethod2();


void axpy_ext(int N, float *Y, float *X, float a) {
    int i;
/* the rest are extensions */
#pragma omp target device(0:*)
dummyMethod1();
#pragma omp parallel for
    for (i = 0; i < N; ++i)
        Y[i] += a * X[i];

#pragma omp target device(0,2,3,5)
dummyMethod2();
							dummyMethod1();
#pragma omp parallel for
    for (i = 0; i < N; ++i)
        Y[i] += a * X[i];
							dummyMethod2();

#pragma omp target device(0:2, 4:2)
							dummyMethod1();
#pragma omp parallel for
    for (i = 0; i < N; ++i)
        Y[i] += a * X[i];
							dummyMethod2();

#pragma omp target device(0:8:OMP_DEVICE_NVGPU)
							dummyMethod1();
#pragma omp parallel for
    for (i = 0; i < N; ++i)
        Y[i] += a * X[i];
							dummyMethod2();

#pragma omp target device(0:*:OMP_DEVICE_NVGPU)
							dummyMethod1();
#pragma omp parallel for
    for (i = 0; i < N; ++i)
        Y[i] += a * X[i];
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