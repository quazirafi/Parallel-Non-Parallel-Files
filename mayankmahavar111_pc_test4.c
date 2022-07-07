#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main() {
  char str[10];
  char temp[20] = "files/";
  int i=0,length=0,count=0;
  length=strlen(temp);
dummyMethod1();
  #pragma omp parallel for shared(temp,i)
    for(i=0;i<5;i++){
        temp[length+i]='c';

      //  printf("%d %d\n",i ,omp_get_thread_num());
    }
dummyMethod2();
    temp[length+5]='\0';
    printf("%s %d\n",temp,i );
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