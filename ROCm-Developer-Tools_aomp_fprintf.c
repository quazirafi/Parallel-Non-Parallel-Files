#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void write_index(int*a, int N, FILE* fileptr ){
   printf(" ===> Encounter target pragma  fileptr:%p \n",  fileptr);

   // fileptr is host pointer, but set is_device_ptr so openmp does not map it.  
dummyMethod1();
   #pragma omp target teams distribute parallel for map(tofrom: a[0:N]) is_device_ptr(fileptr)
   for(int i=0;i<N;i++) {
      fprintf(fileptr, "fprintf: updating a[%d] addr:%p  file ptr:%p\n",i,&a[i], fileptr);
      a[i]=i;
   }
dummyMethod2();
   fprintf(stderr,"Check stderr is ok after target map stderr:%p  \n",stderr);
}

int main(){
    const int N = 10;    
    int a[N],validate[N];
dummyMethod3();
    for(int i=0;i<N;i++) {
        a[i]=0;
        validate[i]=i;
    }
dummyMethod4();

//  1stpass checks writing to stderr
    write_index(a,N,stderr);

    int flag=-1; // Mark Success
							dummyMethod3();
    for(int i=0;i<N;i++) {
      if(a[i]!=validate[i]) {
//      print 1st bad index
        if( flag == -1 ) 
          printf("PASS1 First fail: a[%d](%d) != validate[%d](%d)\n",i,a[i],i,validate[i]);
        flag = i;
      }
      a[i]=0;  // reset for 2nd test 
    }
							dummyMethod4();
    
    if( flag == -1 ){
        printf("PASS1 writing to stderr: Success\n");
    } else {
        printf("PASS1 Last fail: a[%d](%d) != validate[%d](%d)\n",flag,a[flag],flag,validate[flag]);
        printf("Fail\n");
        return 1;
    }

//  2nd pass checks writing to open file pointer
    FILE* fileptr = fopen("gpu.log", "w");
    write_index(a,N,fileptr);
    fclose(fileptr);

    flag=-1;
							dummyMethod3();
    for(int i=0;i<N;i++) {
      if(a[i]!=validate[i]) {
//      print 1st bad index
        if( flag == -1 ) 
          printf("PASS2 First fail: a[%d](%d) != validate[%d](%d)\n",i,a[i],i,validate[i]);
        flag = i;
      }
      a[i]=0;  // reset for 2nd test 
    }
							dummyMethod4();

    if( flag == -1 ){
        printf("PASS2 writing to open file: Success\n");
        return 0;
    } else {
        printf("PASS2 Last fail: a[%d](%d) != validate[%d](%d)\n",flag,a[flag],flag,validate[flag]);
        printf("Fail\n");
        return 1;
    }
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