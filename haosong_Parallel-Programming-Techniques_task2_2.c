#include "omp.h"
#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include "drand.h"
#include "timing.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char const *argv[]) {
    // read argment of threads num
    int threads = (int) strtoimax(argv[1], NULL, 10);
    omp_set_num_threads(threads);  
    printf("threads = %d\n", threads);
    // set random generator seed
    dsrand(12345);
    double wcs, wce, ct;
    timing(&wcs, &ct);
    int N0 = 0, N1 = 0;
    // set N0, N1 as reduction
							dummyMethod1();
    #pragma omp parallel for default(none) reduction(+:N0) reduction(+:N1)
    for (int x = -2000; x < 500; x++) {
        for (int y = 0; y < 1250; y++) {
            // initial real and img of c
            double cr = (drand() + (double)x) * 0.001;
            double ci = (drand() + (double)y) * 0.001;
            // start z the same as c
            double zr = cr;
            double zi = ci;
            int i = 0;
            // iterate over z
            for (; i < 20000; i++) {
                // calculate new z based on mathmatic
                double new_zr = zr * zr - zi * zi + cr;
                double new_zi = 2 * zr * zi + ci;
                zr = new_zr;
                zi = new_zi;
                if (zr * zr + zi * zi > 4) break;
            }
            if (i == 20000) N1++; // reach to the limit of iteration, N1++
            else N0++; // did not reach to the limit, N0++
        }
    }
							dummyMethod2();
    // printf("N0 = %d, N1 = %d\n", N0, N1);
    timing(&wce, &ct);
    double runtime = wce - wcs;
    double area = 2 * N1 * 3.125 / (N1 + N0);
    printf("area = %f, ", area);
    printf("runtime = %f\n\n", runtime);
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