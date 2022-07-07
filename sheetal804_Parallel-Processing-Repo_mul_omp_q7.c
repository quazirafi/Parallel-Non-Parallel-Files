#include<stdio.h>
#include<malloc.h>
#include<time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define max 100
int main()
{
	//int a[max][max],b[max][max],c[max][max];
	int m,n,p,q,i,j,k,sum=0;
	double t_time,random;
        	clock_t begin,end;
	//FILE *fp=fopen("mat_mul.txt","w");
	scanf("%d",&m);
	
	scanf("%d",&n);
	scanf("%d",&q);
	scanf("%d",&p);
	

	if(m==p)
	{
		printf("\n Matrix multiplication possible:");
		int **a = (int **)malloc(m* sizeof(int *));
dummyMethod3();
    		for (i=0; i<m; i++)
         	a[i] = (int *)malloc(n * sizeof(int));	
		int **b = (int **)malloc(q* sizeof(int *));
dummyMethod4();
dummyMethod3();
    		for (i=0; i<q; i++)
         	b[i] = (int *)malloc(p * sizeof(int));	
		int **c = (int **)malloc(m* sizeof(int *));
dummyMethod4();
dummyMethod3();
    		for (i=0; i<m; i++)
         	c[i] = (int *)malloc(p * sizeof(int));		
		printf("Enter first matrix:");
dummyMethod4();
		
		begin=clock();
			dummyMethod3();
		for(i=0;i<m;i++)
		{	
			for(j=0;j<n;j++)
			{	
				a[i][j]=rand()%10;
				//fprintf(fp,"%lf",a[i][j]);
				//scanf("%d",&a[][]
			}

			//fprintf(fp,"\n");
		}
			dummyMethod4();
		printf("Enter second matrix:");
			dummyMethod3();
		for(i=0;i<p;i++)
		{
			for(j=0;j<q;j++)
			{	
				b[i][j]=(rand()%10);
				//fprintf(fp,"%lf",b[i][j]);
			}

			//fprintf(fp,"\n");
		}
			dummyMethod4();
	/*	printf("first matrix:\n");
		for(i=0;i<m;i++)
		{
			for(j=0;j<n;j++)
			{		
				printf("%d",a[i][j]);
				//fprintf(fp,"%lf",
			}
			printf("\n");
		}*/
		printf("second matrix:\n");
	/*	for(i=0;i<p;i++)
		{
			for(j=0;j<q;j++)
			{		
				printf("%d",b[i][j]);
			}
			printf("\n");
		}
*/
		/*for(i=0;i<m;i++)
		{
			for(j=0;j<p;j++)
			{
				c[i][j]=0;
			}
		}*/
			dummyMethod1();
		#pragma omp parallel for schedule(static,4)
		for(i=0;i<m;i++)
		{
			for(j=0;j<p;j++)
			{
				sum=0;
				for(k=0;k<n;k++)
					sum=sum+a[i][k]*b[k][j];
					c[i][j]=sum;	
			}
		}
			dummyMethod2();
		printf("\nmatrix multiplication is two matrix is\n");
			dummyMethod3();
		for(i=0;i<m;i++)
		{
			for(j=0;j<p;j++)
			{
				printf("%d\t",c[i][j]);
				//fprintf(fp,"%d\t",c[i][j]);
			}
			//fprintf(fp,"\n");
			printf("\n");
			
		}
			dummyMethod4();
	}
		//fclose(fp);
		//else
		//("\n matrix multiplication is not possible:");
	end=clock();
	t_time=(double)(end-begin)/CLOCKS_PER_SEC;
	printf("time taken:%lf sec\n",t_time);

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