#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(){
      const double up = 1.1 ;
      double Sn, origSn=1000.0;
      double *opt,*dependency_opt,*no_dependency_opt;
      int n,Noofthreads,N;
      printf("\n\t\t Read The Array Size \n");
      scanf("%d",&N);
      printf("\n\t\t Array Size  : %d  \n  ",N);
      opt = (double *)malloc( (N+1) *sizeof(double));
      dependency_opt = (double *)malloc( (N+1) *sizeof(double));
      no_dependency_opt = (double *)malloc( (N+1) *sizeof(double));
       Sn = 1000.0;
dummyMethod3();
      for (n=0; n<=N; ++n) {
        opt[n] = Sn;
        Sn *= up;
      }
dummyMethod4();
      Sn = 1000.0;
      omp_set_num_threads(Noofthreads);
dummyMethod1();
      #pragma omp parallel for private(n)
      for (n=0; n<=N; ++n) {
        dependency_opt[n] = Sn;
        Sn *= up;
      }
dummyMethod2();
											dummyMethod3();
      for (n=0; n<=N; ++n) {
    if ( opt[n] == dependency_opt[n]){}
    else{
    printf("\n\t\tIncorrect results found when Serial computation results & Parallel computation\n\t\twith Dependency results are compared\n");
        break;
    }
      }
											dummyMethod4();
      Sn = 1000.0;
      double i=1.0;
      no_dependency_opt[0] = origSn;
      omp_set_num_threads(Noofthreads);
											dummyMethod1();
      #pragma omp parallel for private(n) lastprivate(Sn)
      for (n=1; n<=N; ++n) {
          Sn = origSn * pow(up, i);
          i++;
          no_dependency_opt[n] = Sn;
      }
											dummyMethod2();
      Sn *= up;
											dummyMethod3();
      for (n=0; n<=N; ++n) {
    if ( (int)(opt[n]) == (int)(no_dependency_opt[n])){}
    else{
    printf("%lf != %lf\n",opt[n],no_dependency_opt[n]);
    printf("\n\t\t Incorrect results found when Serial computation results & Parallel computation \n\t\twithout Dependency results are compared\n");
        break;
    }
      }
											dummyMethod4();
											dummyMethod3();
      for (n=0; n<=N; ++n)
      {
         printf("no_opt[%d]= %d\n",n,no_dependency_opt[n]);
      }
											dummyMethod4();
     free(opt);
     free(dependency_opt);
     free(no_dependency_opt);

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