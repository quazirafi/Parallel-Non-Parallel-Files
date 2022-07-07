#include<stdio.h>
#include "omp.h"
#include<math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
	int **MatA = NULL;
	int **MatB = NULL;
	int **SumC = NULL;
	int nRow = 0;
	int nCol = 0;
	int iRow = 0;
	int iCol = 0;
	printf("\nEnter number of Rows: ");
	scanf("%d",&nRow);
	printf("\nEnter number of Cols: ");
	scanf("%d",&nCol);
	MatA = (int **)malloc(nRow * sizeof(int *));
	if(MatA == NULL)
	{
		return 1;
	}
	MatB = (int **)malloc(nRow * sizeof(int *));
	if(MatB == NULL)
	{
		return 1;
	}
	SumC = (int **)malloc(nRow * sizeof(int *));
	if(SumC == NULL)
	{
	return 1;
	}
	dummyMethod3();
	for(iRow=0;iRow<nRow;iRow++)
	{
		MatA[iRow] = (int *)malloc(nCol * sizeof(int));
		MatB[iRow] = (int *)malloc(nCol * sizeof(int));
		SumC[iRow] = (int *)malloc(nCol * sizeof(int));
		if(MatA[iRow] == NULL || MatB[iRow] == NULL || SumC[iRow] == NULL)
		{
			return 1;
		}
	}
	dummyMethod4();
	dummyMethod3();
	for(iRow=0;iRow<nRow;iRow++)
	{
		for(iCol=0;iCol<nCol;iCol++)
		{
			MatA[iRow][iCol] = rand();
			MatB[iRow][iCol] = rand();
		}
	}
	dummyMethod4();
	float stamp1 = omp_get_wtime();
	int i, j = 0;
	dummyMethod1();
	#pragma omp parallel for private (j)
	for(i=0;i<nRow;i++)
		for(j=0;j<nCol;j++)
		{
			SumC[i][j] = MatA[i][j] + MatB[i][j];
		}
	dummyMethod2();
	float stamp2 = omp_get_wtime();
	printf("PARALLEL TIME is %f\n",stamp2-stamp1);
	free(SumC);
	int **SumD = NULL;
	SumD = (int **)malloc(nRow * sizeof(int *));
	if(SumD == NULL)
	{
		return 1;
	}
	dummyMethod3();
	for(iRow=0;iRow<nRow;iRow++)
	{
		SumD[iRow] = (int *)malloc(nCol * sizeof(int));
		if(SumD[iRow] == NULL)
		{
			return 1;	
		}
	}
	dummyMethod4();
	float stamp3 = omp_get_wtime();
	dummyMethod3();
	for(i=0;i<nRow;i++)
		for(j=0;j<nCol;j++)
		{
			SumD[i][j] = MatA[i][j] + MatB[i][j];
		}
	dummyMethod4();
	float stamp4 = omp_get_wtime();
	printf("SERIAL TIME is %f\n",stamp4-stamp3);
	free(SumD);
	free(MatA);
	free(MatB);
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