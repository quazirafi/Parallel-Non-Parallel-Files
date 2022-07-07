#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include "omp.h"
#include <mpi.h>
#include <stdbool.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAX_DIM 2
#define COUNT 15

struct kd_node_t{
    double x[MAX_DIM];
    struct kd_node_t *left, *right;
    int axis;
    int index;
};
 
static inline void swap(struct kd_node_t *x, struct kd_node_t *y) {
    double tmp[MAX_DIM];
    memcpy(tmp,  x->x, sizeof(tmp));
    memcpy(x->x, y->x, sizeof(tmp));
    memcpy(y->x, tmp,  sizeof(tmp));
}


/* Function to sort an array using insertion sort*/
void insertion_sort(struct kd_node_t *start, int n, int dim)
{
    int i,j;
    double key;
    struct kd_node_t *temp_j = (struct kd_node_t*)malloc(sizeof(struct kd_node_t));
    struct kd_node_t *temp_jprev = (struct kd_node_t*)malloc(sizeof(struct kd_node_t));

							dummyMethod1();
    #pragma omp parallel for
    for (i = 1; i < n; i++) {
        j = i ;
        temp_j = start + j;
        temp_jprev = temp_j - 1;

        /* Move elements of arr[0..i-1], that are
          greater than key, to one position ahead
          of their current position */
        while (j > 1 && temp_j-> x[dim]  < temp_jprev-> x[dim]) {
            swap(start + j, start + j - 1);
            j = j - 1;
            temp_j = start + j;
            temp_jprev = temp_j - 1;
        }
    }
							dummyMethod2();
}

size_t med_index(size_t i) {
    return (size_t)(floor(i/2));
}
 
struct kd_node_t* median_of_medians(struct kd_node_t *start, struct kd_node_t *end, int axis, int n_elts) {
    //struct kd_node_t *end = (struct kd_node_t*)malloc(sizeof(struct kd_node_t));
    struct kd_node_t *temp = (struct kd_node_t*)malloc(sizeof(struct kd_node_t));
    //end = &start[n_elts-1];

    // base case
    if (n_elts < 10){
        insertion_sort(start, n_elts, axis);
        temp =  start + (end - start) / 2;
        temp->index = (n_elts-1)/2;
        return temp;
    }

    int n_sublists = ceil(n_elts/5);
    struct kd_node_t* medians = (struct kd_node_t*)malloc(n_sublists * sizeof(struct kd_node_t));
    int i;
    // sort sublists of 5 elements with insertion sort O(n)
    #pragma parallel for
							dummyMethod3();
    for (i = 0; i < n_sublists; ++i) {

        int idx_right = i*5;

        int idx_left = n_elts - idx_right < 5 ? n_elts - 1:  idx_right + 4;

        insertion_sort(&start[idx_right], idx_left - idx_right + 1, axis);

        int index = floor((idx_right + idx_left) / 2);
        medians[i] =  start[idx_right + 2];
        medians[i].index = index;
    }
							dummyMethod4();

    
    // determine pivot recursively
    struct kd_node_t* pivot;
    if (n_sublists < 5)
        pivot = &medians[med_index(n_sublists)];
    else
        pivot = median_of_medians(medians, medians + n_sublists - 1,axis, n_sublists);

    return pivot; 
}

struct kd_node_t* make_tree(struct kd_node_t *t, int len, int i, int dim)
{
   
    int numprocs, rank, namelen;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int iam = 0, np = 1;

    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Get_processor_name(processor_name, &namelen);

    struct kd_node_t *temp = (struct kd_node_t*)malloc(sizeof(struct kd_node_t));
    struct kd_node_t *n= (struct kd_node_t*)malloc(sizeof(struct kd_node_t));

    int myaxis = (i + 1) % dim;

    if (!len) return 0;

    temp = median_of_medians(t, t + len - 1, myaxis, len);

    // extracting index to use element of original array for recursion make_tree
    int index = temp->index;
    n = &t[index];
    n->axis = myaxis;

   printf("The median value is: %f\n", *n->x);
//    printf("The axis is: %d\n", n->axis);

//    np = omp_get_num_threads();
    
    #pragma omp task 
    {
        n->left  = make_tree(t, n - t, myaxis, dim);
    }

    #pragma omp task 
    {
        n->right = make_tree(&t[index] + 1, t + len - (n + 1), myaxis, dim);
    }
    return n;
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(struct kd_node_t *root, int space)
{

    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    
    print2DUtil(root->right, space);
    
    // Print current node after space
    // count
    printf("\n");
    int i;
							dummyMethod3();
    for (i = COUNT; i < space; i++)
        printf(" ");
							dummyMethod4();
    printf("%f %d\n", *root->x, root->axis);
 
    // Process left child
    print2DUtil(root->left, space);
}
 
// Wrapper over print2DUtil()
void print2D(struct kd_node_t *root)
{
   // Pass initial space count as 0
   print2DUtil(root, 0);
}

void inOrderRecursive(struct kd_node_t *root, struct kd_node_t* nodes, int idx)
{
    // Only the first element is not null, theroot->left is already null, 
    // shouldnt be, print2D for the same root prints all recursively
    if (root == NULL)
      return;
    
      
    inOrderRecursive(root->left, nodes, idx); //visit left sub-tree

    swap(nodes + idx, root); // push_back in c++
    idx = idx - 1;
   
    inOrderRecursive(root->right, nodes, idx); //visit right sub-tree
}

struct kd_node_t* arrayFromTree(struct kd_node_t *root, int size)
{
    struct kd_node_t* nodes=(struct kd_node_t*)malloc(size * sizeof(struct kd_node_t));    
    inOrderRecursive(root, nodes, size-1);
    return nodes;
}


void treeFromArray(struct kd_node_t **t, struct kd_node_t  *a, int index, int n)
{
    if (index < n) {
        *t = malloc(sizeof(**t));
        struct kd_node_t *temp = (struct kd_node_t*)malloc(sizeof(struct kd_node_t));
        temp = a + index; 
        (*t)->x[0] = temp -> x[0];
        (*t)->x[1] = temp -> x[1];
        (*t)->left = NULL;
        (*t)->right = NULL;
        (*t)->axis = temp->axis;
        //printf("Node from array to be connected to left subtree %f\n", temp->x[0]);
        insert(&(*t)->left, a, 2 * index + 1, n);
        insert(&(*t)->right, a, 2 * index + 2, n);
    }
} 
int main(int argc, char* argv[])
{
    int rank, provided;
    double start_time, end_time;
    //struct kd_node_t *root;
    int number_of_process,chunk_size, index;
    struct kd_node_t *chunk;
    
    //MPI_Init(&argc, &argv);
    MPI_Init_thread(&argc, &argv, MPI_THREAD_FUNNELED, &provided);
    if (provided < MPI_THREAD_FUNNELED) MPI_Abort(MPI_COMM_WORLD,1);

    start_time=MPI_Wtime();
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &number_of_process);
    printf("Number of processes %d\n", number_of_process);
 
    struct kd_node_t* temp = (struct kd_node_t*)malloc(sizeof(struct kd_node_t));
    struct kd_node_t* n = (struct kd_node_t*)malloc(COUNT* sizeof(struct kd_node_t));
    struct kd_node_t* wp = (struct kd_node_t*)malloc(COUNT * sizeof(struct kd_node_t));
 
        if (rank == 0){
          #pragma omp parallel
          {
             struct kd_node_t *root;
             #pragma omp single nowait
             {
              struct kd_node_t* arr =  (struct kd_node_t*)malloc(sizeof(struct kd_node_t));    
              
              srand(time(NULL));
              int i;
       
																											dummyMethod3();
              for (i = 0; i < COUNT; i++){    
                if (arr == NULL) exit(1);
                int j;
                for(j=0; j<MAX_DIM;j++){
                  arr->x[j] = rand()%100;
                }
                wp[i] = *arr;
              }
																											dummyMethod4();
          
              int myaxis = (0 + 1) % 2;
              temp = median_of_medians(wp, wp + COUNT - 1, 0, COUNT);
              // extracting index to use element of original array for recursion make_tree
              index = temp->index;
              root = &wp[index];
              root->axis = myaxis;
         
              // Computing chunk size
              chunk_size= index;           
              //printf("In process 0 ...Chunk size to be sent to process 1 %d\n", chunk_size);
              //printf("In process 0 ... temp element %f\n", temp -> x[0]);
             
              MPI_Send(&chunk_size, 1, MPI_INT, 1, 2, MPI_COMM_WORLD);
              MPI_Send(wp, chunk_size*sizeof(struct kd_node_t), MPI_BYTE, 1, 0, MPI_COMM_WORLD);
         
              root -> right = make_tree(&wp[index] + 1, wp + COUNT - (root + 1),1 , 2);
          
              MPI_Recv(n,chunk_size* sizeof(struct kd_node_t), MPI_BYTE, 1, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

              //printf("In process 0 ... n element %f\n", n -> x[0]);
              treeFromArray(&root->left, n, 0, chunk_size);
              
              }
             
              #pragma omp barrier
              {
                print2D(root);
 
              }
          }           
        } 
 
        if  (rank == 1) {
            #pragma omp parallel
            {
              struct kd_node_t *chunk_send, *send_n;
              #pragma omp single nowait
              {
               
                MPI_Recv(&chunk_size, 1, MPI_INT, 0, 2, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                chunk = (struct kd_node_t*)malloc(chunk_size * sizeof(struct kd_node_t));
                
                //printf("In process 1 ... Chunk size is %d\n", chunk_size);         
           
                MPI_Recv(chunk, chunk_size*sizeof(struct kd_node_t), MPI_BYTE, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
                //printf("In process 1 ... Chunk element %f\n", chunk -> x[0]);
                send_n = make_tree(chunk, chunk_size, 1, 2);
                printf("In process 1 ... Median element %f\n", send_n -> x[0]);
                chunk_send = arrayFomTree(send_n, chunk_size);          
              
                int i;

																															dummyMethod3();
                for (i = 0; i < chunk_size; i++){
                  struct kd_node_t* arr_element =  (struct kd_node_t*)malloc(sizeof(struct kd_node_t));
                  arr_element = chunk_send + i;
                  printf("What is being sent to rank 0 as a chunk/array %f\n", arr_element->x[1]);
                }
																															dummyMethod4();

                MPI_Send(chunk_send,chunk_size*sizeof(struct kd_node_t), MPI_BYTE, 0, 1, MPI_COMM_WORLD);
                //printf("In process 1 ...sent n element %f\n", n -> x[0]);
                
               }
             #pragma omp barrier
             {
              // print2D(send_n);
             } 
           }
         }
      
  end_time = MPI_Wtime();
  
  printf("Start Time: %f, End Time: %f, Elapsed Time: %10.8f \n",start_time, end_time, end_time-start_time); 
  MPI_Finalize();
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