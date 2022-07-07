#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "my_c_code.h"


void vnorm(vec vecs[], double mods[],  int n){
  int i;
 #pragma omp parallel for schedule(static)
dummyMethod3();
  for(i=0; i<n; i++){
      mods[i] = sqrt( vecs[i][0]*vecs[i][0] + 
                      vecs[i][1]*vecs[i][1] + 
                      vecs[i][2]*vecs[i][2] );
  }
dummyMethod4();
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