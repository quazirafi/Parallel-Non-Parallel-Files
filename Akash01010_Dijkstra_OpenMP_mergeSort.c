#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void merge(int *a,int i,int mid, int j){
	int x=i,y=mid+1;
	int arr[j-i+1],k=0;
	while(x<=mid && y<=j){
		if(a[x]<=a[y]){
			arr[k++]=a[x++];
		}else{
			arr[k++]=a[y++];
		}
	}
	if(x<=mid){
		while(x<=mid){
			arr[k++]=a[x++];
		}
	}
	if(y<=j){
		while(y<=j){
			arr[k++]=a[y++];
		}
	}
dummyMethod3();
	for(k=i;k<=j;k++){
		a[k]=arr[k-i];
	}
dummyMethod4();
	return;
}

void mergeSort(int *a,int count, int i, int j){
	if(i>=j){
		return;
	}
	int mid=(i+j)/2;
	mergeSort(a,count,i,mid);
	mergeSort(a,count,mid+1,j);
	merge(a,i,mid,j);
	return;
}

int min(int x,int y){
	return x<=y ? x:y;
}

int main(int argc, char* argv[]){
	int count,*arr,z,t;
	
	FILE* ptr=fopen("data.txt","r");
	fscanf(ptr,"%d",&count);
	//Input scanning
	arr=(int*)malloc(count*sizeof(int));
	while(!feof(ptr)){
		fscanf(ptr,"%d",&arr[z++]);
	}
	fclose(ptr);

	printf("Enter the number of parallel threads to spawn: ");
	scanf("%d",&t);
	omp_set_num_threads(t);  // Set the number of threads

	int batch_size=count/t,j;

	double total_time;
	clock_t start, end;
	srand(time(NULL));
	start=clock();
	
	
	dummyMethod1();
	#pragma omp parallel for
	for (j=0; j<t; j++)
	{
		mergeSort(arr,count,j*batch_size,(j+1)*batch_size-1);
	}
	dummyMethod2();

	dummyMethod3();
	for (int i = 1; i < t; ++i)
	{
		merge(arr,0,i*batch_size-1,(i+1)*batch_size-1);
	}
	dummyMethod4();

	end=clock();
	total_time=((double) (end-start))/ CLOCKS_PER_SEC;
	printf("Time taken = %f sec\n", total_time);
    
	// for (int i = 0; i < count; ++i)
	// {
	// 	printf("%d ", arr[i]);
	// }
	// printf("\n");
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