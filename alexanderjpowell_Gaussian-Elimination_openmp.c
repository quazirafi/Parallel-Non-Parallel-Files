#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 3

int main()
{

	double A[N][N];
	double b[N];
	double ratio;
	int i, j, k;

	for (i = 0; i < N; i++)
	{
dummyMethod1();
		#pragma omp parallel for
		for(j = i; j < N; j++)
		{
			ratio = A[j][i] / A[i][i];
			for(k = i; k < N; k++)
			{
				A[j][k] -= (ratio * A[i][k]);
				b[j] -= (ratio * b[i]);
			}
		}
dummyMethod2();
	}
	for (i = 0; i < N; i++)
	{
		for (j = 0; j < N; j++)
		{
			printf("%f ", A[i][j]);
		}
		printf("\n");
	}
	for (i = 0; i < N; i++)
	{
		printf("%f\n", b[i]);
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