#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
#include "myRead.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

struct tuple{
    int csrRowIdx;
    int csrCollIdx;
    short weight;
};
typedef struct tuple tuple;

struct csr{
    int n;  //size of matrix
    int nnz; // num of non-zero elements (edges)
    int *csrRowPtr; // Cumulative Sum of num of nnz in each row 
	tuple** tuple; // weights of edges and their row Index and coll Idx
};
typedef struct csr csr;

csr* getCsr(int n, int nnz){
    csr* Matrix = (csr*)malloc(sizeof(csr));
    Matrix -> n = n;
    Matrix -> nnz = nnz;
    Matrix -> csrRowPtr = (int*) calloc(n+1,sizeof(int) );
    Matrix -> tuple = (tuple**) calloc( nnz ,sizeof(tuple*));
    return Matrix;
}

int* sum(int n, int* arr1, int* arr2){
    int i = 0;
    // #pragma omp parallel for private(i)
							dummyMethod3();
    for(i = 0; i < n+1; i++){
        arr1[i] += arr2[i];
    }
							dummyMethod4();
    return arr1;
}

int comparator (const void * elem1, const void * elem2)  
{
    int f = ((tuple*)elem1)->csrCollIdx;
    int s = ((tuple*)elem2)->csrCollIdx;
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}

tuple** insertInOrder(tuple** arr, int start, int size, int insert){
    int i;
							dummyMethod3();
    for(i = start; i < size + 1; i ++){
        if(comparator(arr[insert], arr[i]) < 0){
            break;
        }
    }
							dummyMethod4();

    tuple* temp;
							dummyMethod3();
    for(int j = i; j < size + 1; j ++){
        temp = arr[j];
        arr[j] = arr[insert];
        arr[insert] = temp;
    }
							dummyMethod4();

    return arr;
}

tuple** insertionSort(tuple** arr, int start, int size){
							dummyMethod3();
    for(int i = start; i < size - 1; i ++){
        arr = insertInOrder(arr, start, i, i+1);
    }
							dummyMethod4();
    return arr;
}

void merge(csr* inMatrix, int start1, int mid, int end2)
{   
    tuple** a = inMatrix->tuple;    
    tuple** temp = (tuple**) malloc(sizeof(tuple*)*(end2-start1+1));    //array used for merging
    int i,j,k;
    i=start1;    //beginning of the first list
    j=mid+1;    //beginning of the second list
    k=0;

    while(i<=mid && j<=end2)    //while elements in both lists
    {
        if(a[i]->csrCollIdx <= a[j]->csrCollIdx)
            temp[k++]=a[i++];
        else
            temp[k++]=a[j++];
    }
    
    while(i<=mid)    //copy remaining elements of the first list
        temp[k++]=a[i++];
        
    while(j<=end2)    //copy remaining elements of the second list
        temp[k++]=a[j++];
        
    //Transfer elements from temp[] back to a[]
							dummyMethod3();
    for(i=start1,j=0;i<=end2;i++,j++)
        a[i]=temp[j];
							dummyMethod4();
    free(temp);
}

int *mergeTrans(csr* inMatrix, int i, int j)
{
    int mid;
    int* arr1;
    int* arr2;
    if(i + 10000 < j)
    {
        mid=(int)(i+j)/2;
        #pragma omp task shared(arr1, inMatrix,i,mid)
            arr1 = mergeTrans(inMatrix,i,mid);        //left recursion
        
        #pragma omp task shared(arr2, inMatrix,j,mid)
            arr2 = mergeTrans(inMatrix,mid+1,j);    //right recursion
        
        #pragma omp taskwait
        {   merge(inMatrix, i,mid,j);    //merging of two sorted sub-arrays
            arr1 =  sum( inMatrix->n, arr1, arr2 );
            free(arr2);
            return arr1;
        }
    }
    else{
        arr1 = (int*)calloc(inMatrix->n+1,sizeof(int));
        int  k = 0, l = 0;
															dummyMethod3();
        for(l = i; l <= j; l++){
            for(k =inMatrix->tuple[l]-> csrCollIdx+1; k < inMatrix->n+1; k++){
                arr1[k] += 1;
            }
        }   
															dummyMethod4();
        inMatrix -> tuple = insertionSort(inMatrix -> tuple, i, j + 1);
        return arr1;
    }
}


int main(int argc, char **argv)
{   
    int num_threads;
    char* filename;
    if(argc > 1) num_threads  = atoi(argv[1]);
    else num_threads = 1;

    if(argc > 2) filename = argv[2];
    else{
        filename = (char*) malloc(24 * sizeof(char));
        memset(filename, '\0', 24);
        strcpy(filename , "testcases/testcase.data");
    }

    int n, nnz;
    int *csrRowPtr, *csrColIdx, *csrVal;
    int *cscColPtr;

    init_values(filename, &csrRowPtr, &csrColIdx, &csrVal, &n, &nnz);

    csr* inMatrix = getCsr(n-1, nnz);
    int i = 0, j = 0, k =0;
    int chunk = 3;
    inMatrix->csrRowPtr = csrRowPtr;

    omp_set_num_threads(num_threads);

							dummyMethod1();
   #pragma omp parallel for private(j)
    for(j = 0; j < inMatrix->nnz; j++){
        inMatrix->tuple[j] = (tuple*) calloc(1 ,sizeof(tuple));
        inMatrix->tuple[j]-> csrRowIdx = 0 ;
        inMatrix->tuple[j]-> csrCollIdx = csrColIdx[j];
        inMatrix->tuple[j]-> weight = csrVal[j];
    }
							dummyMethod2();

    double starttime = omp_get_wtime();    
							dummyMethod1();
    #pragma omp parallel for  private(k,j)
    for(j = 1; j<inMatrix->n+1; j++){
        for(k = inMatrix->csrRowPtr[j-1]; k < inMatrix->csrRowPtr[j]; k++ ){
               inMatrix->tuple[k]-> csrRowIdx = j-1;        
        }
    }
							dummyMethod2();

     
    #pragma omp parallel
    {
       #pragma omp single
       cscColPtr = mergeTrans(inMatrix, 0, nnz-1);
    }
    printf("time taken %14.7f \n", (omp_get_wtime() - starttime));
							dummyMethod3();
    for(j = 0; j<inMatrix->n; j++){
        printf("%d ", cscColPtr[j] );
    }
							dummyMethod4();
    printf("%d", cscColPtr[j] );
    printf("\n");       

							dummyMethod3();
    for(j = 0; j<nnz-1; j++){
        printf("%d ", inMatrix->tuple[j]-> csrRowIdx );
    } 
							dummyMethod4();
    printf("%d", inMatrix->tuple[j]-> csrRowIdx );
    printf("\n");
							dummyMethod3();
    for(j = 0; j<nnz-1; j++){
        printf("%d ", inMatrix->tuple[j]->weight );
    }
							dummyMethod4();
    printf("%d", inMatrix->tuple[j]->weight );
    
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