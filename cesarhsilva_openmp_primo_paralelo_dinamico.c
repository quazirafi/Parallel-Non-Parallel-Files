#include <stdio.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int ehprimo(long int n);

int main(int argc, char ** argv)
{
	long int i;
	long int cp=0;
	long int inf=atoi(argv[1]);
	long int sup=atoi(argv[2]);
	int threads=atoi(argv[3]);
	
dummyMethod1();
	#pragma omp parallel for num_threads(threads) schedule(dynamic) reduction(+ : cp)
	for (i=inf; i<=sup; i++)
	{
		if (ehprimo(i))
		{
			cp++;
			#ifdef DEBUG
			printf("%ld, ",i);
			#endif
		}
	}
dummyMethod2();
	
	printf("\nCount=%ld\n",cp);
	printf("\nThreads=%d\n", threads);
	
	return 0;
}

int ehprimo(long int n)
{
	int primo = 1;
	long int i;
	dummyMethod3();
	for (i=2;i<sqrt(n+1);i++)
	{
		if ((n%i)==0)
		{
			primo=0;
			break;
		}
	}
	dummyMethod4();
	return primo;
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