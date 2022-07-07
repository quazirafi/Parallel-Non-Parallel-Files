#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <sys/time.h>
#include "omp.h"
#include "rcm.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// Sparse Matrix functions

//  Read File and use the data for the sparse matrix
void readSparseMatrix(const char* file_name,sparseMatrix *A, int n)
{
	FILE* fptr = fopen(file_name, "r");
	if (fptr == NULL) {
		printf("Could not opent he file. Exiting...\n");
		exit(-1);
	}
	else {

    fread(A->row,sizeof(int),n,fptr);
    fread(A->col,sizeof(int),n,fptr);
    fclose(fptr);
	}

}

// A functions that allocates memory for the members if the sparseMatrix struct
void initSpMat(sparseMatrix *A,int nnz){


  A->row = (int*)malloc(nnz*sizeof(int));
  if(A->row == NULL)
  {
      printf("Memory coudldn't be allocated exiting...\n");
      exit(1);
  }
  A->col = (int*)malloc(nnz*sizeof(int));
  if(A->col == NULL)
  {
      printf("Memory coudldn't be allocated exiting...\n");
      exit(1);
  }
}

// Used for clean up
void freeSpMat(sparseMatrix *A){

  free(A->col);
  free(A->row);
  free(A);

}

// Constructor for the Queue
void initQ(rcmQueue *q,int N){




  q->elems = (int*)malloc(N*sizeof(int));

  if( (q->elems) == NULL)
  {
      printf("memory coudldn't be allocated exiting...\n");
      exit(1);
  }

  q->N = N;
  q->start_ = 0;
  q-> end_ = -1;
  q->size = 0;
}

// Adds one element to the Queue

void add2Q(rcmQueue* q,int key){

  // Queue is full so don't add anything. This should not happen in rcm problem.
  if ( isFull(q) ){
    printf("\nThe Queue is full!Can't add any more elements...\n");
    exit(1);
  }

  // Incriment end pointer by one. If end > size start over
  q->end_ = (q->end_ + 1)%(q->N);
  q->size++;
  q->elems[q->end_] = key;

}


//Pop one element

int popFromQ(rcmQueue *q){

  // Queue is empty so return without popping. This should not happen in rcm problem.
  if(isEmpty(q)){
    printf("\nThe Queue is empty!Can't pop elements from an empty Queue...\n");
    exit(1);
  }

  int key = q->elems[q->start_] ;
  q->start_ = (q->start_ + 1)%(q->N);
  q->size--;

  return key;

}

// Used to clear memory
void freeQ(rcmQueue *q){

  free(q->elems);
  free(q);
}

// Check Queue size.
int isEmpty(rcmQueue *q){return (q->size == 0);}
int isFull(rcmQueue *q){return (q->size == q->N);}

// Print Queue for debugging

void printQueue(rcmQueue *q){
  int start = q->start_;
  int en = q->end_;
  printf("\nQ:");
  if (!isEmpty(q)){
    if(start<= en){
											dummyMethod3();
      for(int i=0;i<q->N;i++){
        if(i >= start && i <= en)
          printf(" %d |",q->elems[i]);
        else
          printf(" -1 |");

      }
											dummyMethod4();
    }else{
											dummyMethod3();
      for(int i=0;i<q->N;i++){
        if(i >en && i<start)
          printf(" -1 |");
        else
          printf(" %d |",q->elems[i] );
      }
											dummyMethod4();
    }
  }
  printf("\n");

}
// Testing
void testQueue(rcmQueue *q){
  add2Q(q,1);
  printQueue(q);
  popFromQ(q);
  printQueue(q);
  add2Q(q,2);
  printQueue(q);
  add2Q(q,3);
  printQueue(q);
  add2Q(q,4);
  printQueue(q);
  add2Q(q,5);
  printQueue(q);
  add2Q(q,6);
  printQueue(q);
  add2Q(q,7);
  printQueue(q);
  popFromQ(q);
  printQueue(q);
  popFromQ(q);
  printQueue(q);
  popFromQ(q);
  printQueue(q);
  add2Q(q,8);
  printQueue(q);
  printQueue(q);
  popFromQ(q);
  printQueue(q);
  popFromQ(q);
  printQueue(q);
  popFromQ(q);
  printQueue(q);
  popFromQ(q);
}
//------------------------------------------------------------------------------
// Functions that implement the vertexNeibs struct

// Constructor for the vertexNeibs struct
void initVN(vertexNeibs* vn,int n,int *D){





  vn->neibs = (int*)malloc(n*sizeof(int));

  if( (vn->neibs) == NULL)
  {
      printf("memory coudldn't be allocated exiting...\n");
      exit(1);
  }

  vn->D = D;

}

void freeVn(vertexNeibs *vn){

  free(vn->neibs);
  free(vn->D);
  free(vn);
}

//------------------------------------------------------------------------------
// Functions implementing the resaults list

// Constructor
void initR(rcmRes *R,int *prem,int n){




  R->elems = prem;


  R->size =0;

  R->N =n;

}

// Add element
void add2R(rcmRes *R,int key){

  R->elems[R->size] = key; //Insert Key in the List
  R->size = R->size + 1; // Incriment size

}

//Check if Full

int isRFull(rcmRes *R){return (R->size == R->N);}



//------------------------------------------------------------------------------
// Basic Functions

// This Function finds the Adjacent nodes of the input vertex that haven't been visited yet.
// Each node found is marked as visited.



// Rcm with new distance
// This function is used to find Adjacent nodes of the vertex that have not yet been added to the Queue
// Vector P is used to check if a vertex has already been added : P[i] = 1 iff i has been added to the Queue

void getNewNeibs(sparseMatrix* A,int vertex,vertexNeibs *verNeibs,int *firsts,int *P,int n,int *totalNeibsFound){

  int *D = verNeibs->D;
  int first = firsts[vertex];
  int last = D[vertex] + first -1;
  int i;

  verNeibs->cnt =0;
	// sequential version if the Degree is small
  if( D[vertex] < SEQTH){

							dummyMethod3();
    for( i= first;i<=last;i++){

      int potential_neib = A->row[i];
      if(P[potential_neib]==0){

        P[potential_neib] = 1;
        verNeibs->neibs[verNeibs->cnt++] = potential_neib;
        *totalNeibsFound = *totalNeibsFound + 1;
      }

    }
							dummyMethod4();

  }else{
		// parallel version
		// Each thread searches it's own chunk of the array for new nodes.
		// All nodes found are then merged into one output array


      int cnts[NUMTHREADS] = {0};
      int tid;
      int start_of_chunk;
      int chunk;

      int N = last - first + 1;
      int potential_neib;

      # pragma omp parallel shared(A,N,vertex,verNeibs,P,totalNeibsFound,first) private(i,chunk,potential_neib,tid,start_of_chunk) num_threads(NUMTHREADS)
      {
        tid = omp_get_thread_num();
        start_of_chunk = N*tid/NUMTHREADS;
        chunk = N/NUMTHREADS;
        if(tid == NUMTHREADS-1)chunk += N%NUMTHREADS;
															dummyMethod3();
        for(i = 0 ;i<chunk;i++){

          potential_neib = A->row[i+start_of_chunk+first];
          if(P[potential_neib]==0){

              P[potential_neib] = 1;
              verNeibs->neibs[start_of_chunk + cnts[tid]++] = potential_neib;

          }
        }
															dummyMethod4();
      }
			// Count total number of new nodes
											dummyMethod3();
      for(int i=0;i<NUMTHREADS;i++)
        verNeibs->cnt =cnts[i] + verNeibs->cnt;
											dummyMethod4();

      *totalNeibsFound = *totalNeibsFound + verNeibs->cnt;

      int acc = 0;
			// merge them
											dummyMethod3();
      for(int i=1;i<NUMTHREADS;i++){
        acc+=cnts[i-1];
        for(int j =0;j<cnts[i];j++)
          verNeibs->neibs[acc+j] = verNeibs->neibs[i*N/NUMTHREADS + j ];
      }
											dummyMethod4();
  }

}



// This Function Adds the Sorted,by Degree, adjacent vertexes of the current node to the Q

void addVn2Q(vertexNeibs *vn,rcmQueue *q){

  int n = vn->cnt;

			dummyMethod3();
  for(int i=0;i<n;i++)
    add2Q(q,vn->neibs[i]);
			dummyMethod4();

}

// Sorting Functionallity
// This function is used to sort the new found nodes based on degree. Then they are inserted on the Queue
void sortVn(vertexNeibs *vn){

  int n = vn->cnt-1;
  int *D = vn->D;
  int *arr = vn->neibs;

  //quickSort(arr,D,0,n);
  quickSortPar(arr,D,n);
}

// This function is used to find the node with the minimum degree
int getMinDegree(int *P,int *D,int n){

  int  min = n + 1; // Degree is a positive number can't be grater than n.
  int idx = -1;
			dummyMethod3();
  for(int i =0;i<n;i++){
    // If Deggre is less than min and it's not yes put in R update min.
    if(D[i] < min && P[i]==0 ){
      idx = i;
      min = D[i];
    }
  }
			dummyMethod4();

  return idx;
}

// Main routine for the rcm algorithm
void rcmOmp(sparseMatrix *A,int *D,int *firsts,int *prem,int n,int nnz){


  // Initialize Queue and other structures

  rcmRes *R ;
  rcmQueue *q ;
  vertexNeibs *vn ;

  q =(rcmQueue*)malloc(sizeof(rcmQueue));

  if( q == NULL)
  {
      printf("memory coudldn't be allocated exiting...\n");
      exit(1);
  }
  initQ(q,n);


  R =(rcmRes*)malloc(sizeof(rcmRes));
  if(R == NULL)
  {
      printf("memory coudldn't be allocated exiting...\n");
      exit(1);
  }
  initR(R,prem,n);

  vn = (vertexNeibs*)malloc(sizeof(vertexNeibs));
  if(vn == NULL)
  {
      printf("memory coudldn't be allocated exiting...\n");
      exit(1);
  }
  initVN(vn,n,D);

  int *P = (int*)malloc(n*sizeof(int));
	// P[i] == 1 iff the ith node is added to the Queue
  if(P == NULL)
  {
      printf("memory coudldn't be allocated exiting...\n");
      exit(1);
  }



			dummyMethod4();
			dummyMethod3();
  for(int i=0;i<n;i++)P[i] =0;


  while(!isRFull(R)){

    // If the graph is not connected make sure all subgraphs are visited

    // Get vertex with minimum deggre that's not yet visited,add to to resaults
    // and mark it as visited
    int vertex = getMinDegree(P,D,n);

    add2R(R,vertex);
    P[vertex] = 1;
    int totalNeibsFound = 1;// Counts how many ones are in P

    // Get adjacent nodes of the vertex that are not yet visited
    getNewNeibs(A,vertex,vn,firsts,P,n,&totalNeibsFound);

    // Sort them by degree and add them to the Queue
    sortVn(vn);
    addVn2Q(vn,q);

    // Do a BFS doing the same thing as above

    while ((!isEmpty(q)) ) {
      //printf("\nStarting inner loop\n");
      //getchar();


      // Pop a vertex from Queue and od the same thing as above
      // The popped vertexes are already marked

      int vertex = popFromQ(q);
      add2R(R,vertex);
      if (totalNeibsFound < n){// If all neibs have benn added to the queue don't do the search again
      //This optimization works very well in the case of connected graphs
      //Otherwise it will work on the final while of the outter loop
        getNewNeibs(A,vertex,vn,firsts,P,n,&totalNeibsFound);
        //printf(" I found %d neibs \n",vn->cnt);
        sortVn(vn);

        addVn2Q(vn,q);
      }else{
        fillRPar(R,q);

      }
    }
  }
  // Reverse order of nodes
  reverseR(R);

  // Clean up
  freeQ(q);
  freeVn(vn);
  free(P);



}

// If every vertex has been found fill R and exist the loops
void fillRPar(rcmRes *R,rcmQueue *q){

  int i;
  int n = q->size;

  if(n<SEQTH){// If the Queue size is small do this sequentially

							dummyMethod3();
    for(i =0;i<n;i++)
      R->elems[R->size + i] = q->elems[i+ q->start_];
							dummyMethod4();
  }else{
    #pragma omp parallel shared(R,q,n) private(i) num_threads(NUMTHREADS)
    {

											dummyMethod1();
      #pragma omp parallel for
      for(i =0;i<n;i++)
        R->elems[R->size + i] = q->elems[i+ q->start_];
											dummyMethod2();
    }

  }

  R->size = R->N;
  q->size =0;
}

// Reverse the order of the premutation vector
void reverseR(rcmRes *R){


  int n = R->N;
  int *A = R->elems;

  int i;

  if(n<SEQTH){

							dummyMethod3();
    for( i=0;i<n/2;i++)
      swap(&A[i],&A[n-i-1]);
							dummyMethod4();

  }else{

    # pragma omp parallel shared(A,n) private(i) num_threads(NUMTHREADS)
    {


      #pragma omp for
											dummyMethod3();
      for( i=0;i<n/2;i++)
        swap(&A[i],&A[n-i-1]);
											dummyMethod4();

    }
  }
}




// A utility function to swap two elements
void swap(int* a, int* b){
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition (int *arr,int *D, int low, int high){
    int pivot = D[arr[high]];    // pivot
    int i = (low - 1);  // Index of smaller element

							dummyMethod3();
    for (int j = low; j <= high- 1; j++)
    {
        // If current element is smaller than the pivot
        if (D[arr[j]] < pivot)
        {
            i++;    // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
							dummyMethod4();
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

/* The main function that implements QuickSort
 arr[] --> Array to be sorted,
  low  --> Starting index,
  high  --> Ending index */

void quickSort(int *arr,int *D,int low, int high){
      if (low < high)
      {
          /* pi is partitioning index, arr[p] is now
             at right place */
          int pi = partition(arr,D,low, high);

          // Separately sort elements before
          // partition and after partition
          quickSort(arr,D ,low, pi - 1);
          quickSort(arr,D ,pi + 1, high);
      }
  }

void quickSort_parallel_internal(int* arr,int* D,int low, int high,int depth ){

    if(low < high){

      int pi = partition(arr,D,low,high);



    	if ( ((high-low)<SEQTH) || depth >= MAXDEPTH ){
    		 quickSort_parallel_internal(arr,D ,low, pi-1,depth+1);
    		 quickSort_parallel_internal(arr,D,pi+1, high,depth+1);
      }else{
    		#pragma omp task
    		{ quickSort_parallel_internal(arr,D ,low, pi-1,depth +1); }
    		#pragma omp task
    		{ quickSort_parallel_internal(arr,D ,pi+1, high,depth +1); }
    	}
    }
}



void quickSortPar(int* arr,int *D ,int last){

  if ( (last+1)<SEQTH ){
    quickSort(arr,D,0,last);
  }else{

  	#pragma omp parallel num_threads(NUMTHREADS)
  	{
  		#pragma omp single nowait
  		{
  			quickSort_parallel_internal(arr,D ,0, last,0);
  		}
  	}
  }
}




// Print Array function for testsing
void printArray(int *arr,int size){

  printf("\nArray :");
			dummyMethod3();
  for(int i=0;i<size;i++)
    printf("%d  ",arr[i]);
			dummyMethod4();
  printf("\n");

}

// sequential
void getMatDegree(sparseMatrix *A,int *D,int *firsts,int nnz,int n){

  if(n<SEQTH){ // Execute algorithm sequentially if n is small
							dummyMethod3();
    for(int i =0;i<n;i++){
      int first = findFirstOc(A->col,0,nnz-1,i,nnz);
      int last = findLastOc(A->col,0,nnz-1,i,nnz);
      if (first != -1 && last != -1){
        D[i] = last - first +1;
        firsts[i] = first;
      }else{
        D[i] = 0;
        firsts[i] = -1;
      }
    }
							dummyMethod4();
  }else{ // else fill the D and first matrixes is parralell
    int i,last,first;

    # pragma omp parallel shared(A,D,firsts,n,nnz) private(i,first,last) num_threads(NUMTHREADS)
    {

      #pragma omp for
											dummyMethod3();
      for(i =0;i<n;i++){
        first = findFirstOc(A->col,0,nnz-1,i,nnz);
        last = findLastOc(A->col,0,nnz-1,i,nnz);
        if (first != -1 && last != -1){
          D[i] = last - first +1;
          firsts[i] = first;
        }else{
          D[i] = 0;
          firsts[i] = -1;
        }
      }
											dummyMethod4();
    }


  }

}

// Binary search that finds the first occurance of a number in a sorted array
int findFirstOc(int *arr, int low, int high, int x, int n){
    if(high >= low)
    {
        int mid = low + (high - low)/2;
        if( ( mid == 0 || x > arr[mid-1]) && arr[mid] == x)
            return mid;
        else if(x > arr[mid])
            return findFirstOc(arr, (mid + 1), high, x, n);
        else
            return findFirstOc(arr, low, (mid -1), x, n);
    }
    return -1;
}


/* if x is present in arr[] then returns the index of
   LAST occurrence of x in arr[0..n-1], otherwise
   returns -1 */
int findLastOc(int *arr, int low, int high, int x, int n){
    if (high >= low)
    {
        int mid = low + (high - low)/2;
        if (( mid == n-1 || x < arr[mid+1]) && arr[mid] == x)
            return mid;
        else if (x < arr[mid])
            return findLastOc(arr, low, (mid -1), x, n);
        else
            return findLastOc(arr, (mid + 1), high, x, n);
    }
    return -1;
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