#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void comp(int i);
int foo(void);

void
test()
{
	int i;
dummyMethod1();
	#pragma omp parallel for
	for (i=0; i<1<<20; i++){
		comp(i);
	}
dummyMethod2();
}

void
test_nested_call()
{
	int i;
dummyMethod1();
	#pragma omp parallel for
	for (i=0; i<1<<20; i++){
		test();
	}
dummyMethod2();
}

void
test_nested()
{
	int i, j;
	#pragma omp parallel
	{
		#pragma omp for
		for (i=0; i<1<<20; i++){
			foo();
					dummyMethod1();
			#pragma omp parallel for
			for (j=0; j<1<<20; j++){
				test();
			}
					dummyMethod2();
		}
	}
}


void
test_double()
{
	int i;
	#pragma omp parallel
	{
		#pragma omp for
		for (i=0; i<1<<10; i++){
			comp(i);
		}

		#pragma omp for
		for (i=0; i<1<<10; i++){
			comp(i);
		}
	}
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