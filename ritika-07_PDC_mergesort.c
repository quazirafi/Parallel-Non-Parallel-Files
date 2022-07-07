#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void merge(int b[],int c[],int a[],int p,int q)
{
          int i=0,j=0,k=0,x;

          while((i<p)&&(j<q))
         {
                 if(b[i]<=c[j])
                        a[k++]=b[i++];
                 else
                        a[k++]=c[j++];
         }


         if(i==p)
        {
dummyMethod1();
                 #pragma omp parallel for
                                    for(x=j;x<q;x++)
                       a[k++]=c[x];
dummyMethod2();
        }
        else
       {
dummyMethod1();
                #pragma omp parallel for
                           for(x=i;x<p;x++)
                       a[k++]=b[x];
dummyMethod2();
       }
}

void mergesort1(int a[],int n)
{
           int b[1000],c[1000],i,j=0;
           if(n>1)
          {
																																					dummyMethod3();
                   for(i=0;i<n/2;i++)
                         b[i]=a[i];
																																					dummyMethod4();
																																			dummyMethod3();
                  for(i=n/2;i<n;i++)
                  {
                    c[j]=a[i];
                     j++;
                  }
																																			dummyMethod4();

              #pragma omp parallel
              mergesort1(b,n/2);

              #pragma omp parallel
              mergesort1(c,j);

              #pragma omp parallel
              merge(b,c,a,n/2,j);
        }
}

void main()
{
	int i,a[1000],num;
    double  start_time,end_time;
    char f_name[10];
	int n=10;
    printf("\nDone by Ritika Kayal, 18BCE2518\n\n");
							dummyMethod3();
    for(i=0;i<n;i++)
    {
		a[i]=rand()%100;
    }
							dummyMethod4();

    printf("\nUnsorted array:");
							dummyMethod3();
    for(i=0;i<n;i++)
    printf("\t%d",a[i]);
							dummyMethod4();
    omp_set_num_threads(5);
    start_time=omp_get_wtime();
    mergesort1(a,n);
    end_time=omp_get_wtime();
	printf("\nSorted array:");
							dummyMethod3();
    for(i=0;i<n;i++)
    printf("\t%d",a[i]);
							dummyMethod4();
    printf("\nTime taken=%f\n",end_time-start_time);
    printf("\n");
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