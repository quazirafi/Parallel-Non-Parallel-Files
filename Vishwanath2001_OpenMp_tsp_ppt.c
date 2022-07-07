#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
    int costarr[6][6],a1[8],a2[6][6],a3[6][6],v[5],arr[8],vis[8];
    int i,j,k,min,calc;
    //#pragma omp parallel for
dummyMethod3();
    for(i=1;i<=4;i++)
    {
        vis[i]=0;
    }
dummyMethod4();
dummyMethod3();
    for(i=1;i<=4;i++)
    {
        for(j=1;j<=4;j++)
        {
            if(j==i)
            {
                costarr[i][j]=0;
                continue;
            }
            else
            {
                printf("Enter path cost between path %d and path %d : ", i, j);
                scanf("%d", &costarr[i][j]);
            }
        }
    }
dummyMethod4();
    printf("Matrix for the cost:-\n");
							dummyMethod3();
    for(i=1;i<=4;i++)
    {
        for(j=1;j<=4;j++)
        {
            printf("%d ", costarr[i][j]);
        }
        printf("\n");
    }
							dummyMethod4();
							dummyMethod1();
    #pragma omp parallel for
    for(i=2;i<=4;i++)
    {
        a1[i]=costarr[i][1];
        printf("\nc(1 -> %d) = %d", i, a1[i]);
    }
							dummyMethod2();
    printf("\n");
							dummyMethod1();
    #pragma omp parallel for
    for(i=2;i<=4;i++)
    {
        #pragma omp parallel for
        for(j=2;j<=4;j++)
        {
            if(j==i)
            continue;
            else
            {
                a2[i][j]=costarr[i][j]+a1[j];
            }
            printf("\n(2 -> %d) , %d = %d", i, j, a2[i][j]);
        }
    }
							dummyMethod2();
    for(i=2;i<=4;i++)
    {
        min=999;
        for(j=2;j<=4;j++)
        {
            if(j==i)
            continue;
            else
            {
																															dummyMethod1();
                #pragma omp parallel for
                for(k=2;k<=4;k++)
                {
                    if(k!=i && k!=j)
                    {
                        a3[i][j]=costarr[i][j]+a2[j][k];
                    }
                }
																															dummyMethod2();
            }
            if(a3[i][j]<min)
            {
                min=a3[i][j];
                arr[i]=a3[i][j];
                v[i]=j;
            }
            printf("\n(3 -> %d) , %d ,%d = %d\n v[%d] = %d", i, j, (--k), a3[i][j], i, v[i]);
        }
    }
    min=999;
    //#pragma omp parallel for
    for(i=2;i<=4;i++)
    {
        calc=costarr[1][i]+arr[i];
        printf("\na3[1 , %d] = %d", i, calc);
        if(calc<min)
        {
            min=calc;
            a3[1][i]=calc;
            v[1]=i;
        }
    }
    printf("\nThe Path with least cost is as follows:-\n");
    i=1;
    j=1;
    printf("\n");
    while(vis[i]!=1)
    {
        printf("%d->", i);
        vis[i]=1;
        i=v[i];
    }
    for(i=1;i<=4;i++)
    {
        if(vis[i]==0)
        printf("->%d", i);
    }
    printf("->1\n");
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