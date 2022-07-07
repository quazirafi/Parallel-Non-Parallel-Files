/*
 * OpenMP C API Test Suite
 * Example A.7 from OpenMP C/C++ API sepecification
 */
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define  N	1024

void work(ip, jp)
    int  *ip, *jp;
{
    *ip = 1;
    *jp = -1;
}

void pd002s(
//#pragma omp declaration n
    int  n,
    int*a, int *b)
{
//#pragma omp declaration i
    int  i;
//#pragma omp declaration alocal
    int  alocal;
//#pragma omp declaration blocal
    int  blocal;
//#pragma omp declaration x
    int  x;
//#pragma omp declaration y
    int  y;

    x = 0;
    y = 0;
							dummyMethod1();
#pragma omp parallel for private(i, alocal, blocal) shared(n) reduction(+: x, y)
    for( i = 0 ; i < n ; i++ ){
	work(&alocal, &blocal);
	x += alocal;
	y += blocal;
    }
							dummyMethod2();
    *a += x;
    *b += y;
}

int tiny07(int argc, char *argv[])
{
    int  i, n, errors;
    int  a, b;

    n = N;
    a = 0;
    b = n;
    pd002s(n, &a, &b);

    errors = 0;
    if ( a != n ){
	errors += 1;
	printf("parallel for 002 - EXPECTED A = %d OBSERVED %d\n", n, a);
    }
    if ( b != 0 ){
	errors += 1;
	printf("parallel for 002 - EXPECTED B = %d OBSERVED %d\n", 0, b);
    }

    if ( errors == 0 )
	printf("parallel for 007 PASSED\n");
    else
	printf("parallel for 007 FAILED\n");
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