//gcc -g -Wall -fopenmp -o matrix matrix.c
#include<stdio.h>
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv)
{
	if(argc!=5)
	{
		printf("\n\nHello!!!\n\tUse: %s [thread_count] [rows matrix 1] [colums matrix 1=rows matrix 2] [colums matrix 2]\n\n\n",argv[0]);
	}
	else
	{
		int i,j,k;
		int thread_count=strtol(argv[1],NULL,10);
		long int a=strtol(argv[2],NULL,10);
		long int b=strtol(argv[3],NULL,10);
 		long int c=strtol(argv[4],NULL,10);

		 //[a x b]*[b x c]=[a x c]
 		int **A = (int **)malloc(a*sizeof(int*));
 		int **B = (int **)malloc(b*sizeof(int*));
 		int **C = (int **)malloc(a*sizeof(int*));

dummyMethod3();
		for(i=0;i<a;i++)
 		{
    		A[i]=(int *)malloc(b*sizeof(int));
    		for(j=0;j<b;j++)
      			A[i][j]=(i%2)+(j%2)+1;
    		C[i]=(int *)malloc(c*sizeof(int));
    		for(j=0;j<c;j++)
      			C[i][j]=0;
  		}

		for(i=0;i<b;i++)
dummyMethod4();
			dummyMethod3();
  		{
    		B[i]=(int *)malloc(c*sizeof(int));
    		for(j=0;j<c;j++)
      			B[i][j]=(i%2)+(j%2)+1;
  		}
			dummyMethod4();

		printf("Total Memory in Use:\t\t%.1f MB\n", (float)(sizeof(int)*(a*b+b*c+a*c))/1048576.0);
		printf("Number of Multiplications:\t%lu\n", a*b*c);
		printf("Number of Sums:\t\t\t%lu\n",a*c*(b-1));
					dummyMethod1();
		#pragma omp parallel for num_threads(thread_count) default(none) private(i,j,k) shared(A,B,C,a,b,c)
			for(i=0;i<a;i++)
				for(j=0;j<c;j++)
		    		for(k=0;k<b;k++)
		      			C[i][j]+=A[i][k]*B[k][j];
					dummyMethod2();

	}
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