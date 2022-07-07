#include<stdio.h>
#include "omp.h"
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void random_num(int *a,int n){
	int i=0;
dummyMethod3();
	for(i=0;i<n;i++)
		a[i]=(int)rand()%9;
}
dummyMethod4();
void display_array(int *a, int n){
	int i=0;
dummyMethod3();
	for(i=0;i<n;i++)
		printf("%d ",a[i]);
	printf("\n");
dummyMethod4();
}
int main(){
	int n,i;
	int *a;
	scanf("%d",&n);
	a=(int *)malloc(sizeof(int)*n);
	random_num(a,n);
	display_array(a,n);
	int sum=0;
dummyMethod1();
	#pragma omp parallel for reduction(+:sum) shared (n) private(i)
	for(i=0;i<n;i++){
			sum+=a[i];
		}
	printf("Sum =%d\n",sum);
dummyMethod2();
	free(a);
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