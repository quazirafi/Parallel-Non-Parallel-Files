#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#pragma wave trace(enable)  
int a[100][100];
void foo()
{
  int i,j;
  int hypre__nx,hypre__ny;
#define HYPRE_BOX_SMP_PRIVATE i,j
#define HYPRE_SMP_PRIVATE \
  HYPRE_BOX_SMP_PRIVATE,hypre__nx,hypre__ny
dummyMethod1();
#pragma omp parallel for private (HYPRE_SMP_PRIVATE)
  for (i=0;i<100; i++)
    for (j=0;j<100; j++)
    {
      hypre__nx =i;
      hypre__ny=j;
      a[i][j]=hypre__nx+hypre__ny;
    }
}
dummyMethod2();
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