#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main (void)
{
 int i = 10;
int n;
printf("Enter value of n");
scanf("%d",&n);
int arr[10]={1,2,3,4,5,6,7,8,9,10};
printf("%d\n",arr[8]);
int fac_sum=0;
int j;
int start=1;
int factorial=0;
dummyMethod1();
 #pragma omp parallel for firstprivate(fac_sum,start,factorial) schedule(dynamic,2)
for(j=2;j<=n;j++){
 do{
factorial=j*start;
dummyMethod2();
if(
factorial>=arr[9]){
break;
}
fac_sum=fac_sum+factorial;
start++;
}while(factorial<arr[8]);
printf("Sum of factorials of %d is %d\n",j,fac_sum);
}
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