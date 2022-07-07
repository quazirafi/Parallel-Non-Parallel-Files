#include <stdio.h>
#include <sys/time.h>
#include "omp.h"
#include <math.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main()
{
    int  i,j,Noofthreads,Matsize;
    float   **Matrix;
    struct  timeval  TimeValue_Start, TimeValue_Start1;
        struct  timezone TimeZone_Start, TimeZone_Start1;
        struct  timeval  TimeValue_Final, TimeValue_Final1;
        struct  timezone TimeZone_Final, TimeZone_Final1;
        long    time_start, time_end;
        double  time_overhead1,time_overhead2;

       printf("\n\t\t Enter the size of the Matrix \n");
       scanf("%d",&Matsize);
       printf("\n\t\t Threads               : %d",Noofthreads);
       printf("\n\t\t Matrix Size           : %d",Matsize);
      Matrix = (float **)malloc( Matsize *sizeof(float *));
dummyMethod3();
         for(i=0 ; i<Matsize ; i++)
          {
                  Matrix[i] = (float *)malloc(Matsize * sizeof(float));
                      for(j=0; j<Matsize; j++) {
                               Matrix[i][j] = i*1.0 ;
                        }
            }
      gettimeofday(&TimeValue_Start, &TimeZone_Start);
dummyMethod4();
      omp_set_num_threads(Noofthreads);
      for(i = 1; i < Matsize ; i++){
															dummyMethod1();
          #pragma omp parallel for 
        for(j = 1 ;j  < Matsize;j++)
         {
                Matrix[i][j] =2 * Matrix[i-1][j];
            }
															dummyMethod2();
        }
      gettimeofday(&TimeValue_Final, &TimeZone_Final);
        time_start = TimeValue_Start.tv_sec * 1000000 + TimeValue_Start.tv_usec;
        time_end = TimeValue_Final.tv_sec * 1000000 + TimeValue_Final.tv_usec;
        time_overhead1 = (time_end - time_start)/1000000.0;
    time_start=0;
    time_end=0;
    gettimeofday(&TimeValue_Start1, &TimeZone_Start1);
													dummyMethod1();
       #pragma omp parallel for private(i)
       for(j = 1 ;j  < Matsize;j++) {
           for(i = 1; i < Matsize ; i++){
                        Matrix[i][j] =2 * Matrix[i-1][j];
           }
        }
													dummyMethod2();
        gettimeofday(&TimeValue_Final1, &TimeZone_Final1);
        time_start = TimeValue_Start1.tv_sec * 1000000 + TimeValue_Start1.tv_usec;
        time_end = TimeValue_Final1.tv_sec * 1000000 + TimeValue_Final1.tv_usec;
        time_overhead2 = (time_end - time_start)/1000000.0;
    printf("\n\n\t\t Time Taken in Seconds (By Parallel Computation )           :%lf  ", time_overhead1);
    printf("\n\t\t Time Taken in Seconds (By Inverting loop Computation )     :%lf \n ", time_overhead2);

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