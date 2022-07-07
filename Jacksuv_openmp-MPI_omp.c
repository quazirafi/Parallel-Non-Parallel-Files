#include "omp.h"
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc,char **argv)
{
        int i,j,m,n,p,q=0;
        int a[99][99];
	srand((unsigned)time(NULL));
dummyMethod1();
	#pragma omp parallel for
		for(m=0;m<100;m++)
		{
		    for(n=0;n<100;n++)
		    {
		 	p=rand()%100;
		        a[m][n]=p;

		    }

		 }


		for(i=0;i<100;i++)
dummyMethod2();
dummyMethod3();
		{
			for(j=0;j<100;j++)
			{
			    if(a[i][j]>40)
				q++;
			}
			    
		 }
  
	printf("q=%d",q);
dummyMethod4();

	float h=q/10000.0;
        printf("persent=%f\n",h);
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