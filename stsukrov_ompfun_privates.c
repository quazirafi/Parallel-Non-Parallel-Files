#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void main(){

  int x = 42;
  int y = 314;
  int z = 271;
  int t = 22;

  printf("Before x=%d, y=%d, z=%d, t=%d\n",x,y,z,t);

dummyMethod1();
  #pragma omp parallel for firstprivate(x) lastprivate(y) private(z)
  for(int i=0;i<20;++i){
    x += 1;
    y += 1;
    z += 1;
    t += 1;

    if(i==19)
      printf("Inside x=%d, y=%d, z=%d, t=%d\n",x,y,z,t);
  }
dummyMethod2();

  printf("After x=%d, y=%d, z=%d, t=%d\n",x,y,z,t);
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