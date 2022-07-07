#include<stdio.h>
#include<stdlib.h>
#include "omp.h"
#include<math.h>
#include<time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define CSIZE 4
#define POINTS_SIZE 1000000

int cluster[CSIZE][2]={{75,25},{25,25},{25,75},{75,75}};
long long c_count[CSIZE];
int pts[POINTS_SIZE][2];
void populatepts(){
  long long i;
dummyMethod3();
  for(i=0;i<CSIZE;i++){
    c_count[i]=0;
  }
dummyMethod4();
dummyMethod3();
  for(i=0;i<POINTS_SIZE;i++){
    srand(i);
    pts[i][0]=rand()%100;
    pts[i][1]=rand()%100;
  }
dummyMethod4();
}
double get_distance(int x1,int y1,int x2,int y2){
        int x=x2-x1,y=y2-y1;
        return (double)sqrt((x*x) + (y*y));
 }
 int main()
 {
   populatepts();
   long long i;
   int nt;
   printf("Enter no of threads: ");
   scanf("%d",&nt);
   double t=omp_get_wtime();
					dummyMethod1();
   #pragma omp parallel for private(i)shared(pts,cluster)reduction(+:c_count)num_threads(nt)
   for(i=0;i<POINTS_SIZE;i++){
     double min_dist=999,cur_dist=-1;
     int j,index=-1;
     for(j=0;j<CSIZE;j++){
       cur_dist=get_distance(pts[i][0],pts[i][1],cluster[j][0],cluster[j][1]);
       if(cur_dist<min_dist){
         min_dist=cur_dist;
         index=j;
       }
     }
     c_count[index]++;
   }
					dummyMethod2();
   t=omp_get_wtime()-t;
					dummyMethod3();
   for(i=0;i<CSIZE;i++){
     printf("Cluster (%d %d):%lld\n",cluster[i][0],cluster[i][1],c_count[i]);
   }
					dummyMethod4();
   printf("Time Taken: %lf\n",t);
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