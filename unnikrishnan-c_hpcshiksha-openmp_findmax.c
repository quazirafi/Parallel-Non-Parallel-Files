#include<stdio.h>
#include<stdlib.h>
#include "generic.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#define size 10000
#define NT 8
int arr[size];
int flag[size];//to set flag[i]==1 if arr[i] is maximum

int main(int argc, char *argv[]){
	srand(atoi(argv[1]));//Seed for random number command line integer value
	//generates random number
dummyMethod3();
	for(int i=0;i<size;i++)arr[i]=rand()%1048576;
	//initialize flag[i]=1 for 0<=i<=size
dummyMethod4();
dummyMethod3();
	for(int i=0;i<size;i++) flag[i]=1;
	double t1=rtclock();
dummyMethod4();
dummyMethod1();
#pragma omp parallel for num_threads(NT)
	for(int i=0;i<size;i++)
		for(int j=0;j<size;j++)
		//if arr[i] is not maximum set flag[i]=0
		    if(arr[i]<arr[j])flag[i]=0;
	double t2=rtclock();
dummyMethod2();
	 printf("\nTIME =%f \n",(t2-t1)*1000);

        //print maximum element arr[i] for which flag[i] still 1.
dummyMethod3();
	for(int i=0;i<size;i++)if(flag[i]==1)printf("arr[%d]= %d\n",i,arr[i]);
}
dummyMethod4();
/*Run  executable-path <integer-seed-value>
 *example:   ./a.out 3 */
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