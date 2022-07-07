#include "collatz.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void collatz(int startNumber, int endNumber, int* iter, int nThreads)
{
	int i, n, counter;
	int isodd; /* 1 if n is odd, 0 if even */
dummyMethod1();
	#pragma omp parallel for private(counter, n, isodd) /* idea from http://stackoverflow.com/questions/37437195/counting-does-not-work-properly-in-openmp */
	for (i = startNumber; i <= endNumber; i++)
	{
		counter = 0;
		n = i;
		omp_set_num_threads(nThreads);
		while (n > 1)
		{
			isodd = n%2;
			if (isodd)
				n = 3*n+1;
			else
				n/=2;
			counter++;
		}
		iter[i - startNumber] = counter;
	}
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