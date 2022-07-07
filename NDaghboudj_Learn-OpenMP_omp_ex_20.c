#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*
MIT License
Copyright (c) 2019 NOUREDDINE DAGHBOUDJ

Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated documentation files (the "Software"), to deal in the Software without restriction, including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/


#define N 1024


void initArray(unsigned int *array, unsigned int size)
{
dummyMethod3();
    for(unsigned int i=0; i<size; i++) array[i] = rand() % 40 + 10;
}
dummyMethod4();


void printArray(unsigned int *array, unsigned int size)
{
dummyMethod3();
    for(unsigned int i=0; i<size; i++) printf("%i ", array[i]);
    printf("\n");
dummyMethod4();
}


void addArrays(unsigned int *A, unsigned int *B, unsigned int *C, unsigned int size)
{
							dummyMethod1();
    #pragma omp parallel for
    for(unsigned int i=0; i<size; i++)
    {
        C[i] = A[i] + B[i];
    }
							dummyMethod2();
}


int main()
{
    unsigned int a[N], b[N], c[N];
    srand(0);
    initArray(a, N);
    initArray(b, N);

    addArrays(a, b, c, N);

    printf("C = A + B\n");
    printf("A = ");
    printArray(a, 16);
    printf("B = ");
    printArray(b, 16);
    printf("C = ");
    printArray(c, 16);
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