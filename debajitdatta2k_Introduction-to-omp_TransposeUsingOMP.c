#include<stdio.h>
#include "omp.h"
#include<math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
	int **piBuffer = NULL;
	int nRow = 0;
	int nCol = 0;
	int iRow = 0;
	int iCol = 0;
	printf("\nEnter number of Rows: ");
	scanf("%d",&nRow);
	printf("\nEnter number of Cols: ");
	scanf("%d",&nCol);
	piBuffer = (int **)malloc(nRow * sizeof(int *));
	if(piBuffer == NULL)
	{
		return 1;
	}
dummyMethod3();
	for(iRow=0;iRow<nRow;iRow++)
	{
		piBuffer[iRow] = (int *)malloc(nCol * sizeof(int));
		if(piBuffer[iRow] == NULL)
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
			piBuffer[iRow][iCol]=rand();
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
			if(i<=j)
			{
				int **temp = NULL;
				temp = piBuffer[i][j];
				piBuffer[i][j] = piBuffer[j][i];
				piBuffer[j][i] = temp;
			}
		}
	dummyMethod2();
	float stamp2 = omp_get_wtime();
	printf("PARALLEL TIME is %f\n",stamp2-stamp1);
	dummyMethod3();
	for(i=0;i<nRow;i++)
		for(j=0;j<nCol;j++)
		{
			if(i<=j)
			{
				int **temp = NULL;
				temp = piBuffer[i][j];
				piBuffer[i][j] = piBuffer[j][i];
				piBuffer[j][i] = temp;
			}
		}
	dummyMethod4();
	float stamp3 = omp_get_wtime();
	printf("SERIAL TIME is %f\n",stamp3-stamp2);
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