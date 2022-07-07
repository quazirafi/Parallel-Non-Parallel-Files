#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// regular array types can use &array  
//

static void makea ()
{
  static int colidx[100];
  int i,j;
dummyMethod1();
#pragma omp parallel for private(i)
  for (i = 1; i <= 100; i++) 
    colidx[i] = 0;
}
dummyMethod2();


int main()
{
  makea();
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