#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NUMTESTS 4

int applyFunction(int x)
{
    int y = x * x - 2 * x + 1;
    return y;
}

int main(int argc, char** argv)
{
    srand(time((time_t*)NULL));

    int size = 200, i;

    if (argc >= 2) {
        size = atoi(argv[1]);
    }

    if (size < 0) {
        printf("Size should be greater than 0\n");
        return 0;
    }

    int* inVector = (int*)malloc(size * sizeof(int));
    int* outVectorSeq = (int*)malloc(size * sizeof(int));
    int* outVectorPar = (int*)malloc(NUMTESTS * size * sizeof(int));

							dummyMethod3();
    for (i = 0; i < size; i++) {
        inVector[i] = rand() % 100 - 50;
    }
							dummyMethod4();

							dummyMethod3();
    for (i = 0; i < size; i++) {
        if (i % 2 == 0) {
            outVectorSeq[i] = applyFunction(inVector[i]);
        } else {
            outVectorSeq[i] = inVector[i];
        }
    }
							dummyMethod4();

    int xx, yy = 9;
    (void)xx;

#pragma omp parallel private(xx) shared(yy)
    {
        xx = 0 + yy;
        (void)xx;

#pragma omp for schedule(runtime) // private(i)
															dummyMethod3();
        for (i = 0; i < size; i++) {
            if (i % 2 == 0) {
                *(outVectorPar + i) = applyFunction(inVector[i]);
            } else {
                *(outVectorPar + i) = inVector[i];
            }
        }
															dummyMethod4();

#pragma omp for private(i) schedule(static, 2)
															dummyMethod3();
        for (i = 0; i < size; i++) {
            if (i % 2 == 0) {
                *(outVectorPar + i + size) = applyFunction(inVector[i]);
            } else {
                *(outVectorPar + i + size) = inVector[i];
            }
        }
															dummyMethod4();

#pragma omp for private(i) schedule(dynamic, 3)
															dummyMethod3();
        for (i = 0; i < size; i++) {
            if (i % 2 == 0) {
                *(outVectorPar + i + size * 2) = applyFunction(inVector[i]);
            } else {
                *(outVectorPar + i + size * 2) = inVector[i];
            }
        }
															dummyMethod4();
    }

							dummyMethod1();
#pragma omp parallel for private(i) schedule(dynamic)
    for (i = 0; i < size; i++) {
        if (i % 2 == 0) {
            *(outVectorPar + i + size * 3) = applyFunction(inVector[i]);
        } else {
            *(outVectorPar + i + size * 3) = inVector[i];
        }
    }
							dummyMethod2();

    int good = 1;
							dummyMethod3();
    for (int n = 0; n < NUMTESTS && good == 1; n++) {
        for (i = 0; i < size && good == 1; i++) {
            if (*(outVectorSeq + i) != *(outVectorPar + i + size * n)) {
                printf("Error in parallel test=%d pos=%d\n", n, i);
                good = 0;
            }
        }
    }
							dummyMethod4();

    free(inVector);
    free(outVectorPar);
    free(outVectorSeq);

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