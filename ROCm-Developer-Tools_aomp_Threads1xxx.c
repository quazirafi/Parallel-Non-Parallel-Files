#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int thdLim =1024;
//__attribute__((amdgpu_flat_work_group_size(1024, 1024))) 
int main()
{
  int numTeams=128;
  int N = 12;
  int NN = 1024;
  int CUs[numTeams*NN];
  int lims[N] , threads[N], Res[numTeams*NN];
  int i;
dummyMethod3();
  for (i=0; i <N; i++) lims[i] = threads[i] = -1;
  for (i=0; i <N*NN; i++) {Res[i] = -1; CUs[i] = -2;}
dummyMethod4();
dummyMethod3();
#pragma omp target teams num_teams(numTeams) thread_limit(1024) map (tofrom: CUs, lims, threads, Res)
dummyMethod4();
#pragma omp distribute
  for (int j=0; j < numTeams; j++) {
    if (j<N) {
      lims[j] = omp_get_num_teams();
      threads[j] = omp_get_num_threads();
    }
dummyMethod1();
#pragma omp parallel for
    for (int i=j*NN; i <(j+1)*NN; i++) {
      Res[i] = i;
      CUs[i] = omp_ext_get_smid();
	if (i ==1)    printf("i= %d\n",i);
dummyMethod2();
    }
    if (j == 1)  printf("Res 1 CUs 1 %d %d\n", Res[1], CUs[1]);
  }
  for (i=0; i <N; i++) {
    printf("i=%d lims[%d] threads[%d]\n", i, lims[i], threads[i]);
  }
  for (i=0; i <numTeams*NN; i++) {
    if (Res[i] != i) {
      printf("Failed %d %d\n",i, Res[i]);
      printf("Failed %d %d\n",i+1, Res[i+1]);
      return 1;
    }
  }
//for (i=0; i <numTeams*NN; i++)
//  printf("CUs %d\n",CUs[i]);
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