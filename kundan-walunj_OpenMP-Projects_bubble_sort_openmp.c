#include<stdio.h>
#include<time.h>
#include<math.h>
#include<stdbool.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void oddevensort(int arr[],int n)
{
 bool flag= false;
 int temp;
 clock_t begin_s = clock();
 while(!flag)
 {
 flag=true;
 // for odd
dummyMethod3();
 for(int i=1;i<=n-2;i=i+2)
 {
 if(arr[i]>arr[i+1])
dummyMethod4();
 {
 temp=arr[i];
 arr[i]=arr[i+1];
 arr[i+1]=temp;
 flag=false;
 }
 }
 //for even
	dummyMethod3();
 for(int j=0;j<=n-2;j=j+2)
 {
 if(arr[j]>arr[j+1])
 {
 temp=arr[j];
 arr[j]=arr[j+1];
 arr[j+1]=temp;
 flag=false;
 }
 }
	dummyMethod4();
 }
 clock_t end_s = clock();
 double time_spent_s = (double)(end_s - begin_s) / CLOCKS_PER_SEC;
 printf("Serial execution time is: %f \n",time_spent_s);
}
void oddevensort2(int arr[],int n)
{
 bool flag= false;
 int temp;
 clock_t begin_p = clock();
 while(!flag)
 {
 flag=true;
 // for odd
	dummyMethod1();
 #pragma omp parallel for
 for(int i=1;i<=n-2;i=i+2)
 {
 if(arr[i]>arr[i+1])
 {
 temp=arr[i];
 arr[i]=arr[i+1];
 arr[i+1]=temp;
 flag=false;
 }
 }
	dummyMethod2();
 //for even
	dummyMethod1();
 #pragma omp parallel for
 for(int j=0;j<=n-2;j=j+2)
 {
 if(arr[j]>arr[j+1])
 {
 temp=arr[j];
 arr[j]=arr[j+1];
 arr[j+1]=temp;
 flag=false;
 }
 }
	dummyMethod2();
 }
 clock_t end_p = clock();
 double time_spent_p = (double)(end_p - begin_p) / CLOCKS_PER_SEC;
 printf("Parallel execution time is: %f \n",time_spent_p);
}
void display(int arr[],int n)
{
	dummyMethod3();
 for(int i=0;i<n;i++)
 {
 printf("%d ",arr[i]);
 }
	dummyMethod4();
}
int main()
{
 int n;
 printf("Enter the size of array: ");
 scanf("%d",&n);
 int arr[n];
	dummyMethod3();
 for(int i=0;i<n;i++)
 {
 arr[i]=rand()*10;
 }
	dummyMethod4();
 //printf("Array before Sorting: ");
 //display(arr,n);
 printf("\n");
 oddevensort(arr,n);
 oddevensort2(arr,n);
 //printf("Array after Sorting: ");
 //display(arr,n);
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