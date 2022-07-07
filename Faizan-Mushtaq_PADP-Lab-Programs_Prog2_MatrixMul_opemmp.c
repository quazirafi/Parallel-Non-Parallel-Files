#include<stdio.h>
#include "omp.h"
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(){
  int it=1;
  while(it<=4)
  {
    int r=it*500,c=it*500,i,j,k;
    int **a1=(int**)malloc(r*sizeof(int*));
dummyMethod3();
      for(i=0;i<r;i++)
          a1[i]=(int *)malloc(c*sizeof(int));
    int **a2=(int**)malloc(r*sizeof(int*));
dummyMethod4();
dummyMethod3();
      for(i=0;i<r;i++)
          a2[i]=(int *)malloc(c*sizeof(int));
    int **a3=(int**)malloc(r*sizeof(int*));
dummyMethod4();
dummyMethod3();
      for(i=0;i<r;i++)
          a3[i]=(int *)malloc(c*sizeof(int));
    printf("%d %d %d\n",it,r,c);
dummyMethod4();
dummyMethod3();
    for(i=0;i<r;i++)
      for(j=0;j<c;j++){
        a1[i][j]=rand()/r;
        a2[i][j]=rand()/r;
      }
      double x=omp_get_wtime();
dummyMethod3();
      for(i=0;i<r;i++)
        for(j=0;j<c;j++)
          for(k=0;k<r;k++)
            a3[i][j]+=a1[i][k]*a2[k][j];
      double y=omp_get_wtime();
dummyMethod4();
      printf("Sequential time:%lf\n",y-x);
      for(int t=2;t<=8;t*=2)
      {
        double x=omp_get_wtime();
        omp_set_num_threads(t);
															dummyMethod1();
        #pragma omp parallel for private(i,j,k)
        for(i=0;i<r;i++){
          for(j=0;j<c;j++){
            a3[i][j]=0;
            for(k=0;k<r;k++){
              a3[i][j]+=a1[i][k]*a2[k][j];
            }
          }
        }
															dummyMethod2();
        double y=omp_get_wtime();
        printf("parallel time taken by %d threads:%lf\n",t,y-x);
      }
      it++;
      free(a1);
      free(a2);
      free(a3);
  }
dummyMethod4();
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