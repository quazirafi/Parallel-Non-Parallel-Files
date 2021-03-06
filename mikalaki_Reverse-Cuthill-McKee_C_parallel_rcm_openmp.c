/*
*       Parallels and Distributed Systems Exercise 4
*       Parallel implementation of Reverse Cuthill Mckee algorithm for sparse matrices in C with openMP.
*       Author:Michael Karatzas
*       AEM:9137
*       September 2020
*/
#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
#include "rcm.h"
#include "queue.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


//Reverse Cuthill Mckee algorithm function definition.
int * rcm(int * matrix, int n ){


  //Array where the degrees of all nodes will be stored, degress[i], is the degree of i-st node.
  int * degrees= (int *) malloc(sizeof(int) * n);
  if( !degrees ){
    printf("Problem Allocating Memory!\n" );
    exit(1);
  }

  //Number of unvisited nodes, initialize it to n.
  int nOfUnvisitedNodes=n;

  //Array for indication of not visited nodes, if notVisitedNodes[i]==-1 , node is visited, else notVisitedNodes[i]= i;
  //initialization happens later.
  int * notVisitedNodes= (int *) malloc(sizeof(int) * n);
  if( !notVisitedNodes ){
    printf("Problem Allocating Memory!\n" );
    exit(1);
  }

  //Initializing the Q queue.
  queue * Q = queueInit(n);

  //Initializing queue that stores a node's neighbours,with capacity equals to n.
  queue * nodeNeighbours = queueInit(n);

  //Array to store the degrees of the node's neighbours ,for each node,passed to empty Q , it is reallocated.
  int * degreesToShort=(int *)malloc(sizeof(int));
  if( !degreesToShort ){
    printf("Problem Allocating Memory!\n" );
    exit(1);
  }

  //memory allocation for  permutation order array R.
  int * R=(int *) malloc(sizeof(int)*n);
  if( !R ){
    printf("Problem Allocating Memory!\n" );
    exit(1);
  }

  //Counter of number of elements that have inserted into R array, initialized to zero.
  int Rcounter=0;

  int minDegreeElement=0;

  //Auxilary variables
  int i=0;
  int j=0;
  int k=0;

  //Find the degree of each node.
  calculateDegrees(degrees,matrix,n);



  //initialize notVisitedNodes array.
  //We get a small time benefit by parallelizing the initialization . No race-condition exists here.
			dummyMethod1();
  #pragma omp parallel for shared(notVisitedNodes) private(i)
  for ( i = 0; i < n; i++) {
      notVisitedNodes[i]= i;
  }
			dummyMethod2();


  //running a loop for accessing also the elements of disjoint graphs.
  while(nOfUnvisitedNodes > 0){ // This loop is usefull only when there are unvisited (disjoint) nodes left.


    minDegreeElement=0;

    //Finding the minimun degree unvisited node. We dont parallelize the loop , due to serious race condition.
							dummyMethod3();
    for ( i = 0; i < n; i++)
      if (degrees[i]< degrees[minDegreeElement] && notVisitedNodes[i] !=-1 || notVisitedNodes[minDegreeElement]==-1 )
        minDegreeElement = i;
							dummyMethod4();

    //If there are not vissited elements left , we add the one with minimun degree in Q queue.
    if(notVisitedNodes[minDegreeElement]!=-1){
      queueAdd(Q,minDegreeElement);
      notVisitedNodes[minDegreeElement]=-1;
      nOfUnvisitedNodes--;
    }

    //While Q queue is not empty we sort its element by increasing order of degree and add them to R.
    while (!isEmptyQueue(Q)) {

        //By these way we "make empty" the node's neighbours queue
        nodeNeighbours->front=-1;
        nodeNeighbours->rear=-1;
        nodeNeighbours->size=0;



        /*Finding the neighbours of the node that is going to be add next in the R array.
        By parallelize the for loop, we get significant improve in time.
        By using the ordered property, race condition is avoided and correctness is quaranted.
        Furthermore ordered property, ensures that the nodeNeighbours queue will be filled with the same order as
        in sequential version of the code, so the R array is going to be exactly the same.*/
															dummyMethod1();
        #pragma omp parallel for ordered  shared(Q,matrix) private(j)
        for ( j = 0; j <n; j++) {


            if ( j != (Q->data[Q->front]) && notVisitedNodes[j] !=-1  && (matrix[Q->data[Q->front]*n+notVisitedNodes[j]] != 0) ) {
              //critical section is accesed by one openmp thread at a time, in same order as if code executed sequentialy.
              #pragma omp ordered
              {
                queueAdd(nodeNeighbours,notVisitedNodes[j]);
              }
            }

        }
															dummyMethod2();



        if(nodeNeighbours->size != 0){
          //reallocating neighbours'degrees array to size equal to the number of node's neigbours.
          int * p =(int *)realloc(degreesToShort,(size_t)sizeof(int)*(nodeNeighbours->size) );
          if (!p) {
            printf("Couldn't Reallocate Memory!\n" );
            exit(1);
          } else {
              degreesToShort = p;
          }


          //Getting the degrees of the node's neighbours
          //We get a small time benefit by parallelizing the loop . No race-condition exists here.
																			dummyMethod1();
          #pragma omp parallel for shared(Q,degreesToShort) private(k)
          for (k = 0; k < nodeNeighbours->size; k++) {
            degreesToShort[k]= degrees[nodeNeighbours->data[k]];
          }
																			dummyMethod2();

          //Sorting the degrees of the nodes and their indexes with the same order.
          mergeSort_degrees_indexes(degreesToShort,nodeNeighbours->data, 0, nodeNeighbours->size -1 );

          //Adding the neighbours of the "next in R" node in the Q queue .
          //We get a small time benefit by parallelizing the loop .
          //by using the ordered property race condition is avoided and correctness is quaranted.
																			dummyMethod1();
          #pragma omp parallel for ordered shared(Q,degreesToShort) private(k)
          for ( k = 0; k < nodeNeighbours->size; k++) {
            notVisitedNodes[nodeNeighbours->data[k]]=-1;
            //critical section is accesed by one openmp thread at a time, in same order as if code executed sequentialy.
            #pragma omp ordered
            {
              queueAdd(Q,nodeNeighbours->data[k]);
              nOfUnvisitedNodes--;
            }
          }
																			dummyMethod2();

        }
        //Adding the current front element of Q queue in R array
        R[Rcounter]= queuePoP(Q);
        //update the value of Rcounter, as an element has just inserted in R.
        Rcounter++;

    }
  }

  //Freeing memory from the heap
  free(degrees);
  free(notVisitedNodes);
  free(Q);
  free(nodeNeighbours);
  free(degreesToShort);

  //reverse the R vector
  reverseArray(R,0,n-1);
  return R;


}

//Definition of method for calculating degrees of nodes
void calculateDegrees(int * degrees,int * arr, int n ){ // problhma eiani oti den pernaei o 2d pinakas
  int i=0;

    //parallelize the calculation of nodes' degrees
							dummyMethod1();
    #pragma omp parallel for shared(arr,degrees) private(i)
    for ( i = 0; i < n; i++) {
      int count = 0;
      for (int j = 0; j < n; j++) {
        count += arr[i*n+j];
      }

      degrees[i]=count;
    }
							dummyMethod2();

}


/*Merge sort, the code bellow  is get from https://www.geeksforgeeks.org/, and
modified for the needs of our project.*/
// In this parallel version also, Openmp directives are used to make it be executed faster.

// Merges two subarrays of arr[].
// First subarray is arr[l..m]
// Second subarray is arr[m+1..r]
// idx is the array of indexes of arr's elements
void merge(int * arr,int * idx, int l, int m, int r)
{
    int i, j, k;
    int n1 = m - l + 1;
    int n2 = r - m;

    /* create temp arrays */
    int L[n1], R[n2];
    int Lidx[n1], Ridx[n2];

    /* Copy data to temp arrays L[] and R[], in parallel, with sections,
    one thread copies data to L[] array and the other copies to R[] */
    #pragma omp parallel sections  shared(arr,idx)
    {
      #pragma omp section
											dummyMethod3();
      for (i = 0; i < n1; i++){
          L[i] = arr[l + i];
          Lidx[i] = idx[l + i];
      }
											dummyMethod4();

      #pragma omp section
											dummyMethod3();
      for (j = 0; j < n2; j++){
          R[j] = arr[m + 1 + j];
          Ridx[j] = idx[m + 1 + j];
      }
											dummyMethod4();
    }
    /* Merge the temp arrays back into arr[l..r]*/
    i = 0; // Initial index of first subarray
    j = 0; // Initial index of second subarray
    k = l; // Initial index of merged subarray
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            idx[k] = Lidx[i];
            i++;
        }
        else {
            arr[k] = R[j];
            idx[k] = Ridx[j];
            j++;
        }
        k++;
    }

    /* Copy the remaining elements of L[], if there
       are any */
    while (i < n1) {
        arr[k] = L[i];
        idx[k] = Lidx[i];
        i++;
        k++;
    }

    /* Copy the remaining elements of R[], if there
       are any */
    while (j < n2) {
        arr[k] = R[j];
        idx[k] = Ridx[j];
        j++;
        k++;
    }
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort_degrees_indexes(int * arr,int * idx, int l, int r)
{
    if (l < r) {
        // Same as (l+r)/2, but avoids overflow for
        // large l and h
        int m = l + (r - l) / 2;

          // Sort first and second halves in parallel using openmp
          // (one thread sorts the first half, and another the second)
          #pragma omp parallel sections  shared(arr,idx)
          {
            #pragma omp section
            mergeSort_degrees_indexes(arr,idx, l, m);
            #pragma omp section
            mergeSort_degrees_indexes(arr,idx, m + 1, r);
          }


            merge(arr,idx, l, m, r);


    }
}



void reverseArray(int * arr, int start, int end)
{
    while (start < end)
    {
        int temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;
        start++;
        end--;
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