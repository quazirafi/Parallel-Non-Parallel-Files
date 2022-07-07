#include <stdlib.h>
#include <stdio.h>
#include "ext_shared.h"
#include "ext_chunk.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// Plots a three-dimensional dat file.
void plot2d(double* buffer, const char* name)
{
    // Open the plot file
    FILE* fp = fopen("plot2d.dat", "wb");
    if(!fp) { printf("Could not open plot file.\n"); }

    double bSum = 0.0;

dummyMethod1();
#pragma omp parallel for reduction(+:bSum)
    for(int jj = 0; jj < _chunk.y; ++jj)
    {
        for(int kk = 0; kk < _chunk.x; ++kk)
        {
            double val = buffer[kk+jj*_chunk.x];
            fprintf(fp, "%d %d %.12E\n", kk, jj, val);
            bSum+=val;
        }
    }
dummyMethod2();

    printf("%s: %.12E\n", name, bSum);
    fclose(fp);
}

// Aborts the application.
void panic(int lineNum, const char* file, const char* format, ...)
{
    printf("\x1b[31m");
    printf("\nError at line %d in %s:", lineNum, file);
    printf("\x1b[0m \n");

    va_list arglist;
    va_start(arglist, format);
    vprintf(format, arglist);
    va_end(arglist);

    exit(1);
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