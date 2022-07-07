#include <stdio.h>
#include <stdlib.h>
#include<time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//合并两个区间
void merge(int left, int mid, int right2, int* data, int* aux) {
    int k = left;
    int i = left;
    int j = mid;
    while (i < mid || j < right2) {
        if (i < mid && data[i] <= data[j]) {
            aux[k++] = data[i++];
        }
        else if (j >= right2){  
            aux[k++] = data[i++];
        }else{
            aux[k++] = data[j++];
        }
    }

dummyMethod3();
    for (k = left; k < right2; k++) {
        data[k] = aux[k];
    }
dummyMethod4();
}

void merge_sort(int left, int right, int* data, int length) {
    int i;
    int j;
    int t; 
    int *temp;
    temp = (int*)malloc(length * sizeof(int));
    //int mid = 0;
    //if(l<r){
    //mid = (first+last)/2; 
    //merge_sort(arr, l, mid);
    //merge_sort(arr, mid+1,r);
      
       
//sort-----------------------------------------------------------------
							dummyMethod1();
    #pragma omp parallel for   // 在sort部分使用OpenMP
    for (i = 0; i < length/2; i++)
        if (data[i*2] > data[i*2+1]) {
            t = data[i*2];
            data[i*2] = data[i*2+1];
            data[i*2+1] = t;
        }
							dummyMethod2();
//merge(arr,l,mid,r);
//merge-----------------------------------------------------------------
    for (i = 2; i < right; i *= 2) {
															dummyMethod1();
        #pragma omp parallel for  // 在merge部分使用OpenMP
        for (j = 0; j < right-i; j += i*2) {
             int end = 0;
             if(right > j+i*2){
             end = 2*i+j;
            }else{
             end = right;
}
            merge(j, j+i, end, data, temp);
        }
															dummyMethod2();
    }
}

void main(){
int a[30]={32,12,56,78,76,45,36,66,44,24,47,11,23,56,89,2,6,1,19,20,10,9,8,7,6,5,4,3,2,1};
clock_t t1 =  clock();
merge_sort(0,30,a,30);
clock_t t2 = clock();
for (int i = 0;i<30;i++){
printf("%d ",a[i]);
}
printf("TIME = %d\n",t2-t1);
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