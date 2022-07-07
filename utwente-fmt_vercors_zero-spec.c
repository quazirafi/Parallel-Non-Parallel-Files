// -*- tab-width:2 ; indent-tabs-mode:nil -*-
//:: case OpenMPzero
//:: suite puptol
//:: tools silicon
/*
 * Using a parallel for loop in OpenMP to blank an array.
 */
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/*@
  context \pointer(a, len, write);
  ensures   (\forall  int k;0 <= k && k < len ; a[k] == 0 );
@*/
void zero(int len,int a[]){
  int i;
dummyMethod1();
  #pragma omp parallel for private(i)
  for(i=0;i<len;i++)
  /*@
dummyMethod2();
    context a != NULL;
    context Perm(a[i],1);
    ensures a[i] == 0;
  @*/
  {
    a[i]=0;
    //@ spec_ignore {
    printf("item %d done by thread %d.\n",i,omp_get_thread_num());
    //@ spec_ignore }
  }
}

//@ requires false;
int main(int argc, char *argv[]){
  int a[]={1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
  int i;

  printf("a: ");
			dummyMethod4();
			dummyMethod3();
  for(i=0;i<16;i++){printf("%4d",a[i]);}
  printf("\n");

  printf("zero\n");
  zero(16,a);

  printf("a: ");
			dummyMethod4();
			dummyMethod3();
  for(i=0;i<16;i++){printf("%4d",a[i]);}
  printf("\n");
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