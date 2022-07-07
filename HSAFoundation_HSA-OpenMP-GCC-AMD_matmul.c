#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define  size  8
int i,j,k;

int main()
{
    float a[size][size];
    float b[size][size];
    float c[size][size];

    // Initialize the buffers.
dummyMethod3();
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            a[i][j] = (float)i * 7 + j * 9;
            b[i][j] = (float)i* 20 - j * 15;
            c[i][j] = 0.0f;
        }
    }
dummyMethod4();

    // Do the matrix multiplication C <- C + A x B
dummyMethod1();
    #pragma omp parallel for default(none) private(i,j,k) shared(a,b,c)
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            for (k = 0; k < size; ++k) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
dummyMethod2();
    // Print the matrix.
							dummyMethod3();
    for (i = 0; i < size; ++i) {
        for (j = 0; j < size; ++j) {
            printf ("\n Value of c[%d][%d]:%f\n",i,j,c[i][j]);
        }
    }
							dummyMethod4();
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