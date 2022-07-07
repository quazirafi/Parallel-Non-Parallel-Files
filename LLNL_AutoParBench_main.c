// # ifdef __cplusplus
// extern "C" {
// # endif
//========================================================================================================================================================================================================200
//======================================================================================================================================================150
//====================================================================================================100
//==================================================50
//========================================================================================================================================================================================================200
//	INFORMATION
//========================================================================================================================================================================================================200
//======================================================================================================================================================150
//	UPDATE
//======================================================================================================================================================150
// 2009; Amittai Aviram; entire code written in C; 
// 2010; Jordan Fix and Andrew Wilkes; code converted to CUDA; 
// 2011.10; Lukasz G. Szafaryn; code converted to portable form, to C, OpenMP, CUDA, PGI versions; 
// 2011.12; Lukasz G. Szafaryn; Split different versions for Rodinia.
// 2011.12; Lukasz G. Szafaryn; code converted to OpenCL;
//======================================================================================================================================================150
//	DESCRIPTION
//======================================================================================================================================================150
// Description
//======================================================================================================================================================150
//	USE
//======================================================================================================================================================150
// EXAMPLE:
// ./a.out -file ./input/mil.txt -cores 16
// ...then enter any of the following commands after the prompt > :
// f <x>  -- Find the value under key <x>
// p <x> -- Print the path from the root to key k and its associated value
// t -- Print the B+ tree
// l -- Print the keys of the leaves (bottom row of the tree)
// v -- Toggle output of pointer addresses ("verbose") in tree and leaves.
// k <x> -- Run <x> bundled queries on the CPU and GPU (B+Tree) (Selects random values for each search)
// j <x> <y> -- Run a range search of <x> bundled queries on the CPU and GPU (B+Tree) with the range of each search of size <y>
// x <z> -- Run a single search for value z on the GPU and CPU
// y <a> <b> -- Run a single range search for range a-b on the GPU and CPU
// q -- Quit. (Or use Ctl-D.)
//======================================================================================================================================================150
//	END
//======================================================================================================================================================150
//========================================================================================================================================================================================================200
//	DEFINE/INCLUDE
//========================================================================================================================================================================================================200
//======================================================================================================================================================150
//	LIBRARIES
//======================================================================================================================================================150
#include <stdio.h>									// (in directory known to compiler)			needed by printf, stderr
#include <limits.h>									// (in directory known to compiler)			needed by INT_MIN, INT_MAX
#include <sys/time.h>							// (in directory known to compiler)			needed by ???
#include <math.h>									// (in directory known to compiler)			needed by log, pow
#include <string.h>									// (in directory known to compiler)			needed by memset
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//======================================================================================================================================================150
//	COMMON
//======================================================================================================================================================150
#include "./common.h"								// (in directory provided here)
//======================================================================================================================================================150
//	DEFINE
//======================================================================================================================================================150
//======================================================================================================================================================150
//	UTILITIES
//======================================================================================================================================================150
#include "./util/timer/timer.h"						// (in directory provided here)
#include "./util/num/num.h"							// (in directory provided here)
//======================================================================================================================================================150
//	KERNEL HEADERS
//======================================================================================================================================================150
#include "./kernel/kernel_cpu.h"					// (in directory provided here)
#include "./kernel/kernel_cpu_2.h"					// (in directory provided here)
//======================================================================================================================================================150
//	HEADER
//======================================================================================================================================================150
#include "./main.h"									// (in directory provided here)
//======================================================================================================================================================150
//	END
//======================================================================================================================================================150
//========================================================================================================================================================================================================200
//	VARIABLES
//========================================================================================================================================================================================================200
// general variables
#include "omp.h"
knode *knodes;
record *krecords;
char *mem;
long freeptr;
long malloc_size;
long size;
long maxheight;
/* The order determines the maximum and minimum
* number of entries (keys and pointers) in any
* node.  Every node has at most order - 1 keys and
* at least (roughly speaking) half that number.
* Every leaf has as many pointers to data as keys,
* and every internal node has one more pointer
* to a subtree than the number of keys.
* This global variable is initialized to the
* default value.
*/
int order = 508;
/* The queue is used to print the tree in
* level order, starting from the root
* printing each entire rank on a separate
* line, finishing with the leaves.
*/
node *queue = ((void *)0);
/* The user can toggle on and off the "verbose"
* property, which causes the pointer addresses
* to be printed out in hexadecimal notation
* next to their corresponding keys.
*/
_Bool verbose_output = 0;
//========================================================================================================================================================================================================200
//	FUNCTIONS
//========================================================================================================================================================================================================200
//======================================================================================================================================================150
//	Components
//======================================================================================================================================================150

void list_init(list_t *l,int32_t (*compare)(const void *, const void *),void (*datum_delete)(void *))
{
  l -> head = l -> tail = ((void *)0);
  l -> length = 0;
  l -> compare = compare;
  l -> datum_delete = datum_delete;
}

void list_delete(list_t *l)
{
  list_item_t *li;
  list_item_t *del;
			dummyMethod3();
  for (li = l -> head; li; ) {
    del = li;
    li = li -> next;
    list_item_delete(del,l -> datum_delete);
  }
			dummyMethod4();
  l -> head = l -> tail = ((void *)0);
  l -> length = 0;
}

void list_reset(list_t *l)
{
  list_delete(l);
}

void list_insert_item_head(list_t *l,list_item_t *i)
{
  if (l -> head) {
    i -> next = l -> head;
    l -> head -> pred = i;
    l -> head = i;
    l -> head -> pred = ((void *)0);
  }
   else {
    l -> head = l -> tail = i;
    i -> next = i -> pred = ((void *)0);
  }
  l -> length++;
}

void list_insert_item_tail(list_t *l,list_item_t *i)
{
  if (l -> head) {
    l -> tail -> next = i;
    i -> pred = l -> tail;
    i -> next = ((void *)0);
    l -> tail = i;
  }
   else {
    l -> head = l -> tail = i;
    i -> next = i -> pred = ((void *)0);
  }
  l -> length++;
}

void list_insert_item_before(list_t *l,list_item_t *next,list_item_t *i)
{
/* Assume next is actually in the list! */
/* If it's not, we may lose the list.   */
  if (l -> head == next) {
    i -> next = next;
    i -> pred = ((void *)0);
    l -> head = i;
    next -> pred = i;
  }
   else {
    i -> next = next;
    i -> pred = next -> pred;
    next -> pred -> next = i;
    next -> pred = i;
  }
  l -> length++;
}

void list_insert_item_after(list_t *l,list_item_t *pred,list_item_t *i)
{
/* Assume pred is actually in the list! */
/* If it's not, we may lose the list.   */
  if (l -> tail == pred) {
    i -> pred = pred;
    i -> next = ((void *)0);
    l -> tail = i;
    pred -> next = i;
  }
   else {
    i -> pred = pred;
    i -> next = pred -> next;
    pred -> next -> pred = i;
    pred -> next = i;
  }
  l -> length++;
}

void list_insert_item_sorted(list_t *l,list_item_t *i)
{
  list_item_t *itr;
  if (l -> head) {
							dummyMethod3();
    for (itr = l -> head; itr && ((l -> compare)((list_item_get_datum(i)),(list_item_get_datum(itr)))) < 0; itr = itr -> next) 
      ;
							dummyMethod4();
    if (itr) {
      i -> next = itr;
      i -> pred = itr -> pred;
      itr -> pred = i;
      i -> pred -> next = i;
    }
     else {
      l -> tail -> next = i;
      i -> pred = l -> tail;
      i -> next = ((void *)0);
      l -> tail = i;
    }
  }
   else {
    l -> head = l -> tail = i;
    i -> pred = i -> next = ((void *)0);
  }
  l -> length++;
}



void list_remove_head(list_t *l)
{
  list_remove_item(l,l -> head);
}

void list_remove_tail(list_t *l)
{
  list_remove_item(l,l -> tail);
}

list_item_t *list_find_item(list_t *l,void *datum)
{
  list_item_t *li;
			dummyMethod3();
  for (li = l -> head; li && ((l -> compare)(datum,(list_item_get_datum(li)))); li = li -> next) 
    ;
			dummyMethod4();
  return li;
}

list_item_t *list_get_head_item(list_t *l)
{
  return l -> head;
}

list_item_t *list_get_tail_item(list_t *l)
{
  return l -> tail;
}

void *list_find(list_t *l,void *datum)
{
  list_item_t *li;
			dummyMethod3();
  for (li = l -> head; li && ((l -> compare)(datum,(list_item_get_datum(li)))); li = li -> next) 
    ;
			dummyMethod4();
  return li?li -> datum : ((void *)0);
}

void *list_get_head(list_t *l)
{
  return l -> head?l -> head -> datum : ((void *)0);
}

void *list_get_tail(list_t *l)
{
  return l -> tail?l -> tail -> datum : ((void *)0);
}

uint32_t list_get_length(list_t *l)
{
  return l -> length;
}

_Bool list_is_empty(list_t *l)
{
  return (l -> length == 0);
}

_Bool list_not_empty(list_t *l)
{
  return (l -> length != 0);
}

void list_visit_items(list_t *l,void (*visitor)(void *))
{
  list_item_t *li;
			dummyMethod3();
  for (li = l -> head; li; li = li -> next) 
    visitor((list_item_get_datum(li)));
			dummyMethod4();
}

void list_item_init(list_item_t *li,void *datum)
{
  li -> pred = li -> next = ((void *)0);
  li -> datum = datum;
}

void list_item_delete(list_item_t *li,void (*datum_delete)(void *))
{
  if (datum_delete) {
    datum_delete((li -> datum));
  }
  free(li);
}

void *list_item_get_datum(list_item_t *li)
{
  return li -> datum;
}

void list_iterator_init(list_t *l,list_iterator_t *li)
{
   *li = (l?l -> head : ((void *)0));
}

void list_iterator_delete(list_iterator_t *li)
{
   *li = ((void *)0);
}

void list_iterator_next(list_iterator_t *li)
{
  if ( *li) 
     *li = ( *li) -> next;
}

void list_iterator_prev(list_iterator_t *li)
{
  if ( *li) 
     *li = ( *li) -> pred;
}

void *list_iterator_get_datum(list_iterator_t *li)
{
  return  *li?( *li) -> datum : ((void *)0);
}

_Bool list_iterator_is_valid(list_iterator_t *li)
{
  return ( *li != ((void *)0));
}

void list_reverse_iterator_init(list_t *l,list_reverse_iterator_t *li)
{
   *li = (l?l -> tail : ((void *)0));
}

void list_reverse_iterator_delete(list_reverse_iterator_t *li)
{
   *li = ((void *)0);
}

void list_reverse_iterator_next(list_reverse_iterator_t *li)
{
  if ( *li) 
     *li = ( *li) -> pred;
}

void list_reverse_iterator_prev(list_reverse_iterator_t *li)
{
  if ( *li) 
     *li = ( *li) -> next;
}

void *list_reverse_iterator_get_datum(list_reverse_iterator_t *li)
{
  return  *li?( *li) -> datum : ((void *)0);
}

_Bool list_reverse_iterator_is_valid(list_reverse_iterator_t *li)
{
  return (li != ((void *)0));
}
//======================================================================================================================================================150
// OUTPUT AND UTILITIES
//======================================================================================================================================================150
/*   */

void *kmalloc(int size)
{
//printf("size: %d, current offset: %p\n",size,freeptr);
  void *r = (void *)freeptr;
  freeptr += size;
  if (freeptr > malloc_size + ((long )mem)) {
    printf("Memory Overflow\n");
    exit(1);
  }
  return r;
}
//transforms the current B+ Tree into a single, contiguous block of memory to be used on the GPU

long transform_to_cuda(node *root,_Bool verbose)
{
  struct timeval one;
  struct timeval two;
  double time;
  gettimeofday(&one,((void *)0));
  long max_nodes = (long )(pow(order,log(size) / log(order / 2.0) - 1) + 1);
  malloc_size = (size * sizeof(record ) + max_nodes * sizeof(knode ));
  freeptr = ((long )mem);
  krecords = ((record *)(kmalloc((size * sizeof(record )))));
// printf("%d records\n", size);
  knodes = ((knode *)(kmalloc((max_nodes * sizeof(knode )))));
// printf("%d knodes\n", max_nodes);
  queue = ((void *)0);
  enqueue(root);
  node *n;
  knode *k;
  int i;
  long nodeindex = 0;
  long recordindex = 0;
  long queueindex = 0;
  knodes[0] . location = (nodeindex++);
  while(queue != ((void *)0)){
    n = dequeue();
    k = &knodes[queueindex];
    k -> location = (queueindex++);
    k -> is_leaf = n -> is_leaf;
    k -> num_keys = n -> num_keys + 2;
//start at 1 because 0 is set to INT_MIN
    k -> keys[0] = - 0x7fffffff - 1;
    k -> keys[k -> num_keys - 1] = 0x7fffffff;
    
							dummyMethod1();
#pragma omp parallel for private (i)
    for (i = k -> num_keys; i <= order - 1; i += 1) {
      k -> keys[i] = 0x7fffffff;
    }
							dummyMethod2();
    if (!k -> is_leaf) {
      k -> indices[0] = (nodeindex++);
// if(k->indices[0]>3953){
// printf("ERROR: %d\n", k->indices[0]);
// }
											dummyMethod3();
      for (i = 1; i <= k -> num_keys - 1 - 1; i += 1) {
        k -> keys[i] = n -> keys[i - 1];
        enqueue((node *)n -> pointers[i - 1]);
        k -> indices[i] = (nodeindex++);
// if(k->indices[i]>3953){
// printf("ERROR 1: %d\n", k->indices[i]);
// }
//knodes[nodeindex].location = nodeindex++;
      }
											dummyMethod4();
//for final point of n
      enqueue((node *)n -> pointers[i - 1]);
    }
     else {
      k -> indices[0] = 0;
											dummyMethod3();
      for (i = 1; i <= k -> num_keys - 1 - 1; i += 1) {
        k -> keys[i] = n -> keys[i - 1];
        krecords[recordindex] . value = ((record *)n -> pointers[i - 1]) -> value;
        k -> indices[i] = (recordindex++);
// if(k->indices[i]>3953){
// printf("ERROR 2: %d\n", k->indices[i]);
// }
      }
											dummyMethod4();
    }
    k -> indices[k -> num_keys - 1] = queueindex;
// if(k->indices[k->num_keys-1]>3953){
// printf("ERROR 3: %d\n", k->indices[k->num_keys-1]);
// }
    if (verbose) {
      printf("Successfully created knode with index %d\n",k -> location);
      printf("Is Leaf: %d, Num Keys: %d\n",(k -> is_leaf),k -> num_keys);
      printf("Pointers: ");
											dummyMethod3();
      for (i = 0; i <= k -> num_keys - 1; i += 1) {
        printf("%d | ",k -> indices[i]);
      }
											dummyMethod4();
      printf("\nKeys: ");
											dummyMethod3();
      for (i = 0; i <= k -> num_keys - 1; i += 1) {
        printf("%d | ",k -> keys[i]);
      }
											dummyMethod4();
      printf("\n\n");
    }
  }
  long mem_used = (size * sizeof(record ) + nodeindex * sizeof(knode ));
  if (verbose) {
							dummyMethod3();
    for (i = 0; ((long )i) <= size - 1; i += 1) {
      printf("%d ",krecords[i] . value);
    }
							dummyMethod4();
    printf("\nNumber of records = %d, sizeof(record)=%d, total=%d\n",size,sizeof(record ),size * sizeof(record ));
    printf("Number of knodes = %d, sizeof(knode)=%d, total=%d\n",nodeindex,sizeof(knode ),nodeindex * sizeof(knode ));
    printf("\nDone Transformation. Mem used: %d\n",mem_used);
  }
  gettimeofday(&two,((void *)0));
  double oneD = one . tv_sec + ((double )one . tv_usec) * .000001;
  double twoD = two . tv_sec + ((double )two . tv_usec) * .000001;
  time = twoD - oneD;
  printf("Tree transformation took %f\n",time);
  return mem_used;
}
/*   */

list_t *findRange(node *root,int start,int end)
{
  int i;
  node *c = find_leaf(root,start,0);
  if (c == ((void *)0)) 
    return ((void *)0);
  list_init(retList,((void *)0),((void *)0));
  int counter = 0;
  _Bool cont = 1;
  while(cont && c != 0){
    cont = 0;
							dummyMethod3();
    for (i = 0; i <= c -> num_keys - 1; i += 1) {
      if (c -> keys[i] >= start && c -> keys[i] <= end) {
//list_insert_tail(retList,(record *)c->pointers[i]);
        counter++;
        cont = 1;
      }
       else {
        cont = 0;
        break; 
      }
    }
							dummyMethod4();
    c = ((node *)c -> pointers[order - 1]);
  }
  return retList;
}
/* First message to the user. */

void usage_1()
{
  printf("B+ Tree of Order %d.\n",order);
  printf("\tAmittai Aviram -- amittai.aviram@yale.edu  Version %s\n","1.5");
  printf("\tfollowing Silberschatz, Korth, Sidarshan, Database Concepts, 5th ed.\n\n");
  printf("To build a B+ tree of a different order, start again and enter the order\n");
  printf("as an integer argument:  bpt <order>.  ");
  printf("3 <= order <=20\n");
  printf("To start with input from a file of newline-delimited integers, start again and enter\n");
  printf("the order followed by the filename:  bpt <order> <inputfile>.\n");
}
/* Second message to the user. */

void usage_2()
{
  printf("Enter any of the following commands after the prompt > :\n");
  printf("\ti <k>  -- Insert <k> (an integer) as both key and value).\n");
  printf("\tf <k>  -- Find the value under key <k>.\n");
  printf("\tp <k> -- Print the path from the root to key k and its associated value.\n");
  printf("\td <k>  -- Delete key <k> and its associated value.\n");
  printf("\tx -- Destroy the whole tree.  Start again with an empty tree of the same order.\n");
  printf("\tt -- Print the B+ tree.\n");
  printf("\tl -- Print the keys of the leaves (bottom row of the tree).\n");
  printf("\tv -- Toggle output of pointer addresses (\"verbose\") in tree and leaves.\n");
  printf("\tq -- Quit. (Or use Ctl-D.)\n");
  printf("\t? -- Print this help message.\n");
}
/* Helper function for printing the tree out.  See print_tree. */

void enqueue(node *new_node)
{
  node *c;
  if (queue == ((void *)0)) {
    queue = new_node;
    queue -> next = ((void *)0);
  }
   else {
    c = queue;
    while(c -> next != ((void *)0)){
      c = c -> next;
    }
    c -> next = new_node;
    new_node -> next = ((void *)0);
  }
}
/* Helper function for printing the tree out.  See print_tree. */

node *dequeue()
{
  node *n = queue;
  queue = queue -> next;
  n -> next = ((void *)0);
  return n;
}
/* Prints the bottom row of keys of the tree (with their respective pointers, if the verbose_output flag is set. */

void print_leaves(node *root)
{
  int i;
  node *c = root;
  if (root == ((void *)0)) {
    printf("Empty tree.\n");
    return ;
  }
  while(!c -> is_leaf)
    c = ((node *)c -> pointers[0]);
  while(1){
							dummyMethod3();
    for (i = 0; i <= c -> num_keys - 1; i += 1) {
      if (verbose_output) 
//printf("%x ", (unsigned int)c->pointers[i]);
        printf("%d ",c -> keys[i]);
    }
							dummyMethod4();
    if (verbose_output) 
//printf("%x ", (unsigned int)c->pointers[order - 1]);
      if (c -> pointers[order - 1] != ((void *)0)) {
        printf(" | ");
        c = ((node *)c -> pointers[order - 1]);
      }
       else 
        break; 
  }
  printf("\n");
}
/* Utility function to give the height of the tree, which length in number of edges of the path from the root to any leaf. */

int height(node *root)
{
  int h = 0;
  node *c = root;
  while(!c -> is_leaf){
    c = ((node *)c -> pointers[0]);
    h++;
  }
  return h;
}
/* Utility function to give the length in edges of the path from any node to the root. */

int path_to_root(node *root,node *child)
{
  int length = 0;
  node *c = child;
  while(c != root){
    c = c -> parent;
    length++;
  }
  return length;
}
/* Prints the B+ tree in the command line in level (rank) order, with the keys in each node and the '|' symbol to separate nodes. With the verbose_output flag set. the values of the pointers corresponding to the keys also appear next to their respective keys, in hexadecimal notation. */

void print_tree(node *root)
{
  node *n = ((void *)0);
  int i = 0;
  int rank = 0;
  int new_rank = 0;
  if (root == ((void *)0)) {
    printf("Empty tree.\n");
    return ;
  }
  queue = ((void *)0);
  enqueue(root);
  while(queue != ((void *)0)){
    n = dequeue();
    if (n -> parent != ((void *)0) && n == n -> parent -> pointers[0]) {
      new_rank = path_to_root(root,n);
      if (new_rank != rank) {
        rank = new_rank;
        printf("\n");
      }
    }
    if (verbose_output) 
      printf("(%x)",n);
							dummyMethod3();
    for (i = 0; i <= n -> num_keys - 1; i += 1) {
      if (verbose_output) 
        printf("%x ",n -> pointers[i]);
      printf("%d ",n -> keys[i]);
    }
							dummyMethod4();
    if (!n -> is_leaf) 
											dummyMethod3();
      for (i = 0; i <= n -> num_keys; i += 1) {
        enqueue((node *)n -> pointers[i]);
      }
											dummyMethod4();
    if (verbose_output) {
      if (n -> is_leaf) 
        printf("%x ",n -> pointers[order - 1]);
       else 
        printf("%x ",n -> pointers[n -> num_keys]);
    }
    printf("| ");
  }
  printf("\n");
}
/* Traces the path from the root to a leaf, searching by key.  Displays information about the path if the verbose flag is set. Returns the leaf containing the given key. */

node *find_leaf(node *root,int key,_Bool verbose)
{
  int i = 0;
  node *c = root;
  if (c == ((void *)0)) {
    if (verbose) 
      printf("Empty tree.\n");
    return c;
  }
  while(!c -> is_leaf){
    if (verbose) {
      printf("[");
											dummyMethod3();
      for (i = 0; i <= c -> num_keys - 1 - 1; i += 1) {
        printf("%d ",c -> keys[i]);
      }
											dummyMethod4();
      printf("%d] ",c -> keys[i]);
    }
    i = 0;
    while(i < c -> num_keys){
      if (key >= c -> keys[i]) 
        i++;
       else 
        break; 
    }
    if (verbose) 
      printf("%d ->\n",i);
    c = ((node *)c -> pointers[i]);
  }
  if (verbose) {
    printf("Leaf [");
							dummyMethod3();
    for (i = 0; i <= c -> num_keys - 1 - 1; i += 1) {
      printf("%d ",c -> keys[i]);
    }
							dummyMethod4();
    printf("%d] ->\n",c -> keys[i]);
  }
  return c;
}
/* Finds and returns the record to which a key refers. */

record *find(node *root,int key,_Bool verbose)
{
  int i = 0;
  node *c = find_leaf(root,key,verbose);
  if (c == ((void *)0)) 
    return ((void *)0);
			dummyMethod3();
  for (i = 0; i <= c -> num_keys - 1; i += 1) {
    if (c -> keys[i] == key) 
      break; 
  }
			dummyMethod4();
  if (i == c -> num_keys) 
    return ((void *)0);
   else 
    return (record *)c -> pointers[i];
}
/* Finds the appropriate place to split a node that is too big into two. */

int cut(int length)
{
  if (length % 2 == 0) 
    return length / 2;
   else 
    return length / 2 + 1;
}
//======================================================================================================================================================150
// INSERTION
//======================================================================================================================================================150
/* Creates a new record to hold the value to which a key refers. */

record *make_record(int value)
{
  if (new_record == ((void *)0)) {
    perror("Record creation.");
    exit(1);
  }
   else {
    new_record -> value = value;
  }
  return new_record;
}
/* Creates a new general node, which can be adapted to serve as either a leaf or an internal node. */

node *make_node()
{
  node *new_node;
  if (new_node == ((void *)0)) {
    perror("Node creation.");
    exit(1);
  }
  if (new_node -> keys == ((void *)0)) {
    perror("New node keys array.");
    exit(1);
  }
  new_node -> next = ((void *)0);
  return new_node;
}
/* Creates a new leaf by creating a node and then adapting it appropriately. */

node *make_leaf()
{
  node *leaf = make_node();
  leaf -> is_leaf = 1;
  return leaf;
}
/* Helper function used in insert_into_parent to find the index of the parent's pointer to the node to the left of the key to be inserted. */

int get_left_index(node *parent,node *left)
{
  int left_index = 0;
  while(left_index <= parent -> num_keys && parent -> pointers[left_index] != left)
    left_index++;
  return left_index;
}
/* Inserts a new pointer to a record and its corresponding key into a leaf. Returns the altered leaf. */

node *insert_into_leaf(node *leaf,int key,record *pointer)
{
  int i;
  int insertion_point;
  insertion_point = 0;
  while(insertion_point < leaf -> num_keys && leaf -> keys[insertion_point] < key)
    insertion_point++;
			dummyMethod3();
  for (i = leaf -> num_keys; i >= insertion_point + 1; i += -1) {
    leaf -> keys[i] = leaf -> keys[i - 1];
    leaf -> pointers[i] = leaf -> pointers[i - 1];
  }
			dummyMethod4();
  leaf -> keys[insertion_point] = key;
  leaf -> pointers[insertion_point] = pointer;
  leaf -> num_keys++;
  return leaf;
}
/* Inserts a new key and pointer to a new record into a leaf so as to exceed the tree's order, causing the leaf to be split in half. */

node *insert_into_leaf_after_splitting(node *root,node *leaf,int key,record *pointer)
{
  node *new_leaf;
  int *temp_keys;
  void **temp_pointers;
  int insertion_index;
  int split;
  int new_key;
  int i;
  int j;
  new_leaf = make_leaf();
  while(leaf -> keys[insertion_index] < key && insertion_index < order - 1)
    insertion_index++;
			dummyMethod3();
  for ((i = 0 , j = 0); i <= leaf -> num_keys - 1; (i++ , j++)) {
    if (j == insertion_index) 
      j++;
    temp_keys[j] = leaf -> keys[i];
    temp_pointers[j] = leaf -> pointers[i];
  }
			dummyMethod4();
  temp_keys[insertion_index] = key;
  temp_pointers[insertion_index] = pointer;
  leaf -> num_keys = 0;
  split = cut(order - 1);
			dummyMethod3();
  for (i = 0; i <= split - 1; i += 1) {
    leaf -> pointers[i] = temp_pointers[i];
    leaf -> keys[i] = temp_keys[i];
    leaf -> num_keys++;
  }
			dummyMethod4();
			dummyMethod3();
  for ((i = split , j = 0); i <= order - 1; (i++ , j++)) {
    new_leaf -> pointers[j] = temp_pointers[i];
    new_leaf -> keys[j] = temp_keys[i];
    new_leaf -> num_keys++;
  }
			dummyMethod4();
  free(temp_pointers);
  free(temp_keys);
  new_leaf -> pointers[order - 1] = leaf -> pointers[order - 1];
  leaf -> pointers[order - 1] = new_leaf;
  
			dummyMethod1();
#pragma omp parallel for private (i)
  for (i = leaf -> num_keys; i <= order - 1 - 1; i += 1) {
    leaf -> pointers[i] = ((void *)0);
  }
			dummyMethod2();
  
			dummyMethod1();
#pragma omp parallel for private (i) firstprivate (order)
  for (i = new_leaf -> num_keys; i <= order - 1 - 1; i += 1) {
    new_leaf -> pointers[i] = ((void *)0);
  }
			dummyMethod2();
  new_leaf -> parent = leaf -> parent;
  new_key = new_leaf -> keys[0];
  return insert_into_parent(root,leaf,new_key,new_leaf);
}
/* Inserts a new key and pointer to a node into a node into which these can fit without violating the B+ tree properties. */

node *insert_into_node(node *root,node *n,int left_index,int key,node *right)
{
  int i;
			dummyMethod3();
  for (i = n -> num_keys; i >= left_index + 1; i += -1) {
    n -> pointers[i + 1] = n -> pointers[i];
    n -> keys[i] = n -> keys[i - 1];
  }
			dummyMethod4();
  n -> pointers[left_index + 1] = right;
  n -> keys[left_index] = key;
  n -> num_keys++;
  return root;
}
//======================================================================================================================================================150
// DELETION
//======================================================================================================================================================150
/* Utility function for deletion. Retrieves the index of a node's nearest neighbor (sibling) to the left if one exists.  If not (the node is the leftmost child), returns -1 to signify this special case. */

int get_neighbor_index(node *n)
{
  int i;
/* Return the index of the key to the left
* of the pointer in the parent pointing
* to n.  
* If n is the leftmost child, this means
* return -1.
*/
  
			dummyMethod1();
#pragma omp parallel for private (i)
  for (i = 0; i <= n -> parent -> num_keys; i += 1) {
    if (n -> parent -> pointers[i] == n) 
      return i - 1;
  }
			dummyMethod2();
// Error state.
  printf("Search for nonexistent pointer to node in parent.\n");
//printf("Node:  %#x\n", (unsigned int)n);
  exit(1);
}
/*   */

node *remove_entry_from_node(node *n,int key,node *pointer)
{
  int i;
  int num_pointers;
// Remove the key and shift other keys accordingly.
  i = 0;
  while(n -> keys[i] != key)
    i++;
			dummyMethod3();
  for (++i; i <= n -> num_keys - 1; i += 1) {
    n -> keys[i - 1] = n -> keys[i];
  }
			dummyMethod4();
// Remove the pointer and shift other pointers accordingly.
// First determine number of pointers.
  num_pointers = (n -> is_leaf?n -> num_keys : n -> num_keys + 1);
  i = 0;
  while(n -> pointers[i] != pointer)
    i++;
			dummyMethod3();
  for (++i; i <= num_pointers - 1; i += 1) {
    n -> pointers[i - 1] = n -> pointers[i];
  }
			dummyMethod4();
// One key fewer.
  n -> num_keys--;
// Set the other pointers to NULL for tidiness.
// A leaf uses the last pointer to point to the next leaf.
  if (n -> is_leaf) {
    
							dummyMethod1();
#pragma omp parallel for private (i) firstprivate (order)
    for (i = n -> num_keys; i <= order - 1 - 1; i += 1) {
      n -> pointers[i] = ((void *)0);
    }
							dummyMethod2();
  }
   else {
    
							dummyMethod1();
#pragma omp parallel for private (i) firstprivate (order)
    for (i = n -> num_keys + 1; i <= order - 1; i += 1) {
      n -> pointers[i] = ((void *)0);
    }
							dummyMethod2();
  }
  return n;
}
/*   */

node *adjust_root(node *root)
{
  node *new_root;
/* Case: nonempty root.
* Key and pointer have already been deleted,
* so nothing to be done.
*/
  if (root -> num_keys > 0) 
    return root;
/* Case: empty root. 
*/
// If it has a child, promote 
// the first (only) child
// as the new root.
  if (!root -> is_leaf) {
    new_root = ((node *)root -> pointers[0]);
    new_root -> parent = ((void *)0);
  }
   else 
// If it is a leaf (has no children),
// then the whole tree is empty.
    new_root = ((void *)0);
  free((root -> keys));
  free((root -> pointers));
  free(root);
  return new_root;
}
/* Coalesces a node that has become too small after deletion with a neighboring node that can accept the additional entries without exceeding the maximum. */

node *coalesce_nodes(node *root,node *n,node *neighbor,int neighbor_index,int k_prime)
{
  int i;
  int j;
  int neighbor_insertion_index;
  int n_start;
  int n_end;
  int new_k_prime;
  node *tmp;
  _Bool split;
/* Swap neighbor with node if node is on the
* extreme left and neighbor is to its right.
*/
  if (neighbor_index == - 1) {
    tmp = n;
    n = neighbor;
    neighbor = tmp;
  }
/* Starting point in the neighbor for copying
* keys and pointers from n.
* Recall that n and neighbor have swapped places
* in the special case of n being a leftmost child.
*/
  neighbor_insertion_index = neighbor -> num_keys;
/*
* Nonleaf nodes may sometimes need to remain split,
* if the insertion of k_prime would cause the resulting
* single coalesced node to exceed the limit order - 1.
* The variable split is always false for leaf nodes
* and only sometimes set to true for nonleaf nodes.
*/
  split = 0;
/* Case:  nonleaf node.
* Append k_prime and the following pointer.
* If there is room in the neighbor, append
* all pointers and keys from the neighbor.
* Otherwise, append only cut(order) - 2 keys and
* cut(order) - 1 pointers.
*/
  if (!n -> is_leaf) {
/* Append k_prime.
	*/
    neighbor -> keys[neighbor_insertion_index] = k_prime;
    neighbor -> num_keys++;
/* Case (default):  there is room for all of n's keys and pointers
	* in the neighbor after appending k_prime.
	*/
    n_end = n -> num_keys;
/* Case (special): k cannot fit with all the other keys and pointers
	* into one coalesced node.
	*/
// Only used in this special case.
    n_start = 0;
    if (n -> num_keys + neighbor -> num_keys >= order) {
      split = 1;
      n_end = cut(order) - 2;
    }
							dummyMethod3();
    for ((i = neighbor_insertion_index + 1 , j = 0); j <= n_end - 1; (i++ , j++)) {
      neighbor -> keys[i] = n -> keys[j];
      neighbor -> pointers[i] = n -> pointers[j];
      neighbor -> num_keys++;
      n -> num_keys--;
      n_start++;
    }
							dummyMethod4();
/* The number of pointers is always
	* one more than the number of keys.
	*/
    neighbor -> pointers[i] = n -> pointers[j];
/* If the nodes are still split, remove the first key from
	* n.
	*/
    if (split) {
      new_k_prime = n -> keys[n_start];
											dummyMethod3();
      for ((i = 0 , j = n_start + 1); i <= n -> num_keys - 1; (i++ , j++)) {
        n -> keys[i] = n -> keys[j];
        n -> pointers[i] = n -> pointers[j];
      }
											dummyMethod4();
      n -> pointers[i] = n -> pointers[j];
      n -> num_keys--;
    }
/* All children must now point up to the same parent.
	*/
							dummyMethod3();
    for (i = 0; i <= neighbor -> num_keys + 1 - 1; i += 1) {
      tmp = ((node *)neighbor -> pointers[i]);
      tmp -> parent = neighbor;
    }
							dummyMethod4();
  }
   else 
/* In a leaf, append the keys and pointers of
* n to the neighbor.
* Set the neighbor's last pointer to point to
* what had been n's right neighbor.
*/
{
							dummyMethod3();
    for ((i = neighbor_insertion_index , j = 0); j <= n -> num_keys - 1; (i++ , j++)) {
      neighbor -> keys[i] = n -> keys[j];
      neighbor -> pointers[i] = n -> pointers[j];
      neighbor -> num_keys++;
    }
							dummyMethod4();
    neighbor -> pointers[order - 1] = n -> pointers[order - 1];
  }
  if (!split) {
    root = delete_entry(root,n -> parent,k_prime,n);
    free((n -> keys));
    free((n -> pointers));
    free(n);
  }
   else 
							dummyMethod3();
    for (i = 0; i <= n -> parent -> num_keys - 1; i += 1) {
      if (n -> parent -> pointers[i + 1] == n) {
        n -> parent -> keys[i] = new_k_prime;
        break; 
      }
    }
							dummyMethod4();
  return root;
}
/* Redistributes entries between two nodes when one has become too small after deletion but its neighbor is too big to append the small node's entries without exceeding the maximum */

node *redistribute_nodes(node *root,node *n,node *neighbor,int neighbor_index,int k_prime_index,int k_prime)
{
  int i;
  node *tmp;
/* Case: n has a neighbor to the left. 
* Pull the neighbor's last key-pointer pair over
* from the neighbor's right end to n's left end.
*/
  if (neighbor_index != - 1) {
    if (!n -> is_leaf) 
      n -> pointers[n -> num_keys + 1] = n -> pointers[n -> num_keys];
							dummyMethod3();
    for (i = n -> num_keys; i >= 1; i += -1) {
      n -> keys[i] = n -> keys[i - 1];
      n -> pointers[i] = n -> pointers[i - 1];
    }
							dummyMethod4();
    if (!n -> is_leaf) {
      n -> pointers[0] = neighbor -> pointers[neighbor -> num_keys];
      tmp = ((node *)n -> pointers[0]);
      tmp -> parent = n;
      neighbor -> pointers[neighbor -> num_keys] = ((void *)0);
      n -> keys[0] = k_prime;
      n -> parent -> keys[k_prime_index] = neighbor -> keys[neighbor -> num_keys - 1];
    }
     else {
      n -> pointers[0] = neighbor -> pointers[neighbor -> num_keys - 1];
      neighbor -> pointers[neighbor -> num_keys - 1] = ((void *)0);
      n -> keys[0] = neighbor -> keys[neighbor -> num_keys - 1];
      n -> parent -> keys[k_prime_index] = n -> keys[0];
    }
  }
   else 
/* Case: n is the leftmost child.
* Take a key-pointer pair from the neighbor to the right.
* Move the neighbor's leftmost key-pointer pair
* to n's rightmost position.
*/
{
    if (n -> is_leaf) {
      n -> keys[n -> num_keys] = neighbor -> keys[0];
      n -> pointers[n -> num_keys] = neighbor -> pointers[0];
      n -> parent -> keys[k_prime_index] = neighbor -> keys[1];
    }
     else {
      n -> keys[n -> num_keys] = k_prime;
      n -> pointers[n -> num_keys + 1] = neighbor -> pointers[0];
      tmp = ((node *)n -> pointers[n -> num_keys + 1]);
      tmp -> parent = n;
      n -> parent -> keys[k_prime_index] = neighbor -> keys[0];
    }
							dummyMethod3();
    for (i = 0; i <= neighbor -> num_keys - 1; i += 1) {
      neighbor -> keys[i] = neighbor -> keys[i + 1];
      neighbor -> pointers[i] = neighbor -> pointers[i + 1];
    }
							dummyMethod4();
    if (!n -> is_leaf) 
      neighbor -> pointers[i] = neighbor -> pointers[i + 1];
  }
/* n now has one more key and one more pointer;
* the neighbor has one fewer of each.
*/
  n -> num_keys++;
  neighbor -> num_keys--;
  return root;
}
/* Deletes an entry from the B+ tree. Removes the record and its key and pointer from the leaf, and then makes all appropriate changes to preserve the B+ tree properties. */

node *delete_entry(node *root,node *n,int key,void *pointer)
{
  int min_keys;
  node *neighbor;
  int neighbor_index;
  int k_prime_index;
  int k_prime;
  int capacity;
// Remove key and pointer from node.
  n = remove_entry_from_node(n,key,(node *)pointer);
/* Case:  deletion from the root. 
*/
  if (n == root) 
    return adjust_root(root);
/* Case:  deletion from a node below the root.
* (Rest of function body.)
*/
/* Determine minimum allowable size of node,
* to be preserved after deletion.
*/
  min_keys = (n -> is_leaf?cut(order - 1) : cut(order) - 1);
/* Case:  node stays at or above minimum.
* (The simple case.)
*/
  if (n -> num_keys >= min_keys) 
    return root;
/* Case:  node falls below minimum.
* Either coalescence or redistribution
* is needed.
*/
/* Find the appropriate neighbor node with which
* to coalesce.
* Also find the key (k_prime) in the parent
* between the pointer to node n and the pointer
* to the neighbor.
*/
  neighbor_index = get_neighbor_index(n);
  k_prime_index = (neighbor_index == - 1?0 : neighbor_index);
  k_prime = n -> parent -> keys[k_prime_index];
  neighbor = (neighbor_index == - 1?((node *)n -> parent -> pointers[1]) : ((node *)n -> parent -> pointers[neighbor_index]));
  capacity = (n -> is_leaf?order : order - 1);
/* Coalescence. */
  if (neighbor -> num_keys + n -> num_keys < capacity) 
    return coalesce_nodes(root,n,neighbor,neighbor_index,k_prime);
   else 
/* Redistribution. */
    return redistribute_nodes(root,n,neighbor,neighbor_index,k_prime_index,k_prime);
}
/* Master deletion function. */

node *deleteVal(node *root,int key)
{
  node *key_leaf;
  record *key_record;
  key_record = find(root,key,0);
  key_leaf = find_leaf(root,key,0);
  if (key_record != ((void *)0) && key_leaf != ((void *)0)) {
    free(key_record);
    root = delete_entry(root,key_leaf,key,key_record);
  }
  return root;
}
/*   */

void destroy_tree_nodes(node *root)
{
  int i;
  if (root -> is_leaf) 
							dummyMethod3();
    for (i = 0; i <= root -> num_keys - 1; i += 1) {
      free(root -> pointers[i]);
    }
							dummyMethod4();
   else 
							dummyMethod3();
    for (i = 0; i <= root -> num_keys + 1 - 1; i += 1) {
      destroy_tree_nodes((node *)root -> pointers[i]);
    }
							dummyMethod4();
  free((root -> pointers));
  free((root -> keys));
  free(root);
}
/*   */

node *destroy_tree(node *root)
{
  destroy_tree_nodes(root);
  return ((void *)0);
}
//======================================================================================================================================================150
//	END
//======================================================================================================================================================150
//========================================================================================================================================================================================================200
//	MAIN FUNCTION
//========================================================================================================================================================================================================200

int main(int argc,char **argv)
{
// assing default values
  int cur_arg;
  int cores_arg = 1;
  char *input_file = ((void *)0);
  char *command_file = ((void *)0);
  char *output = "output.txt";
  FILE *pFile;
// go through arguments
			dummyMethod3();
  for (cur_arg = 1; cur_arg <= argc - 1; cur_arg += 1) {
    if (strcmp(argv[cur_arg],"cores") == 0) {
// check if value provided
      if (argc >= cur_arg + 1) {
// check if value is a number
        if (isInteger(argv[cur_arg + 1]) == 1) {
          cores_arg = atoi(argv[cur_arg + 1]);
          if (cores_arg < 0) {
            printf("ERROR: Wrong value to cores parameter, cannot be <=0\n");
            return - 1;
          }
          cur_arg = cur_arg + 1;
        }
         else 
// value is not a number
{
          printf("ERROR: Value to cores parameter in not a number\n");
          return 0;
        }
      }
    }
     else 
// check if -file
if (strcmp(argv[cur_arg],"file") == 0) {
// check if value provided
      if (argc >= cur_arg + 1) {
        input_file = argv[cur_arg + 1];
        cur_arg = cur_arg + 1;
// value is not a number
      }
       else 
// value not provided
{
        printf("ERROR: Missing value to -file parameter\n");
        return - 1;
      }
    }
     else if (strcmp(argv[cur_arg],"command") == 0) {
// check if value provided
      if (argc >= cur_arg + 1) {
        command_file = argv[cur_arg + 1];
        cur_arg = cur_arg + 1;
// value is not a number
      }
       else 
// value not provided
{
        printf("ERROR: Missing value to command parameter\n");
        return - 1;
      }
    }
  }
			dummyMethod4();
// Print configuration
  if (input_file == ((void *)0) || command_file == ((void *)0)) 
    printf("Usage: ./b+tree file input_file command command_list\n");
// For debug
  printf("Input File: %s \n",input_file);
  printf("Command File: %s \n",command_file);
  FILE *commandFile;
  long lSize;
  char *commandBuffer;
  size_t result;
  commandFile = fopen(command_file,"rb");
  if (commandFile == ((void *)0)) {
    fputs("Command File error",stderr);
    exit(1);
  }
// obtain file size:
  fseek(commandFile,0,2);
  lSize = ftell(commandFile);
  rewind(commandFile);
// allocate memory to contain the whole file:
  if (commandBuffer == ((void *)0)) {
    fputs("Command Buffer memory error",stderr);
    exit(2);
  }
// copy the file into the buffer:
  result = fread(commandBuffer,1,lSize,commandFile);
  if (result != lSize) {
    fputs("Command file reading error",stderr);
    exit(3);
  }
/* the whole file is now loaded in the memory buffer. */
// terminate
  fclose(commandFile);
// For Debug
  char *sPointer = commandBuffer;
  printf("Command Buffer: \n");
  printf("%s",commandBuffer);
//
  pFile = fopen(output,"w+");
  if (pFile == ((void *)0)) 
    fputs("Fail to open %s !\n",output);
  fprintf(pFile,"******starting******\n");
  fclose(pFile);
// ------------------------------------------------------------60
// general variables
// ------------------------------------------------------------60
  FILE *file_pointer;
  node *root;
  root = ((void *)0);
  record *r;
  int input;
  char instruction;
  order = 508;
  verbose_output = 0;
//usage_1();  
//usage_2();
// ------------------------------------------------------------60
// get input from file, if file provided
// ------------------------------------------------------------60
  if (input_file != ((void *)0)) {
    printf("Getting input from file %s...\n",argv[1]);
// open input file
    file_pointer = fopen(input_file,"r");
    if (file_pointer == ((void *)0)) {
      perror("Failure to open input file.");
      exit(1);
    }
// get # of numbers in the file
    fscanf(file_pointer,"%d\n",&input);
    size = input;
// save all numbers
    while(!feof(file_pointer)){
      fscanf(file_pointer,"%d\n",&input);
      root = insert(root,input,input);
    }
// close file
    fclose(file_pointer);
//print_tree(root);
//printf("Height of tree = %d\n", height(root));
  }
   else {
    printf("ERROR: Argument -file missing\n");
    return 0;
  }
// ------------------------------------------------------------60
// get tree statistics
// ------------------------------------------------------------60
  printf("Transforming data to a GPU suitable structure...\n");
  long mem_used = transform_to_cuda(root,0);
  maxheight = (height(root));
  long rootLoc = ((long )knodes) - ((long )mem);
// ------------------------------------------------------------60
// process commands
// ------------------------------------------------------------60
  char *commandPointer = commandBuffer;
  printf("Waiting for command\n");
  printf("> ");
  while(sscanf(commandPointer,"%c",&instruction) != - 1){
    commandPointer++;
    switch(instruction){
// ----------------------------------------40
// Insert
// ----------------------------------------40
      case 'i':
{
        scanf("%d",&input);
        while(getchar() != ((int )'\n'))
          ;
        root = insert(root,input,input);
        print_tree(root);
        break; 
      }
// ----------------------------------------40
// n/a
// ----------------------------------------40
      case 'f':
{
      }
// ----------------------------------------40
// find
// ----------------------------------------40
      case 'p':
{
        scanf("%d",&input);
        while(getchar() != ((int )'\n'))
          ;
        r = find(root,input,(instruction == 'p'));
        if (r == ((void *)0)) 
          printf("Record not found under key %d.\n",input);
         else 
          printf("Record found: %d\n",r -> value);
        break; 
      }
// ----------------------------------------40
// delete value
// ----------------------------------------40
      case 'd':
{
        scanf("%d",&input);
        while(getchar() != ((int )'\n'))
          ;
        root = ((node *)(deleteVal(root,input)));
        print_tree(root);
        break; 
      }
// ----------------------------------------40
// destroy tree
// ----------------------------------------40
      case 'x':
{
        while(getchar() != ((int )'\n'))
          ;
        root = destroy_tree(root);
        print_tree(root);
        break; 
      }
// ----------------------------------------40
// print leaves
// ----------------------------------------40
      case 'l':
{
        while(getchar() != ((int )'\n'))
          ;
        print_leaves(root);
        break; 
      }
// ----------------------------------------40
// print tree
// ----------------------------------------40
      case 't':
{
        while(getchar() != ((int )'\n'))
          ;
        print_tree(root);
        break; 
      }
// ----------------------------------------40
// toggle verbose output
// ----------------------------------------40
      case 'v':
{
        while(getchar() != ((int )'\n'))
          ;
        verbose_output = (!verbose_output);
        break; 
      }
// ----------------------------------------40
// quit
// ----------------------------------------40
      case 'q':
{
        while(getchar() != ((int )'\n'))
          ;
        return 0;
      }
// ----------------------------------------40
// [OpenMP] find K (initK, findK)
// ----------------------------------------40
      case 'k':
{
// get # of queries from user
        int count;
        sscanf(commandPointer,"%d",&count);
        while(( *commandPointer) != 32 && commandPointer != '\n')
          commandPointer++;
        printf("\n ******command: k count=%d \n",count);
        if (count > 65535) {
          printf("ERROR: Number of requested querries should be 65,535 at most. (limited by # of CUDA blocks)\n");
          exit(0);
        }
// INPUT: records CPU allocation (setting pointer in mem variable)
        record *records = (record *)mem;
        long records_elem = (((long )rootLoc) / sizeof(record ));
        long records_mem = (long )rootLoc;
// printf("records_elem=%d, records_unit_mem=%d, records_mem=%d\n", (int)records_elem, sizeof(record), (int)records_mem);
// INPUT: knodes CPU allocation (setting pointer in mem variable)
        knode *knodes = (knode *)(((long )mem) + ((long )rootLoc));
        long knodes_elem = ((((long )mem_used) - ((long )rootLoc)) / sizeof(knode ));
        long knodes_mem = ((long )mem_used) - ((long )rootLoc);
// printf("knodes_elem=%d, knodes_unit_mem=%d, knodes_mem=%d\n", (int)knodes_elem, sizeof(knode), (int)knodes_mem);
// INPUT: currKnode CPU allocation
        long *currKnode;
// OUTPUT: ans CPU initialization
        
															dummyMethod1();
#pragma omp parallel for private (i)
        for (i = 0; i <= count - 1; i += 1) {
          ans[i] . value = - 1;
        }
															dummyMethod2();
// New OpenMP kernel, same algorighm across all versions(OpenMP, CUDA, OpenCL) for comparison purposes
        kernel_cpu(cores_arg,records,knodes,knodes_elem,order,maxheight,count,currKnode,offset,keys,ans);
// Original OpenMP kernel, different algorithm
// int j;
// for(j = 0; j < count; j++){
// find(	root,				// node *
// keys[j],			// int
// false);				// bool
// }
        pFile = fopen(output,"aw+");
        if (pFile == ((void *)0)) {
          fputs("Fail to open %s !\n",output);
        }
        fprintf(pFile,"\n ******command: k count=%d \n",count);
															dummyMethod3();
        for (i = 0; i <= count - 1; i += 1) {
          fprintf(pFile,"%d    %d\n",i,ans[i] . value);
        }
															dummyMethod4();
        fprintf(pFile," \n");
        fclose(pFile);
// free memory
        free(currKnode);
        free(offset);
        free(keys);
        free(ans);
// break out of case
        break; 
      }
// ----------------------------------------40
// find range
// ----------------------------------------40
      case 'r':
{
        int start;
        int end;
        scanf("%d",&start);
        scanf("%d",&end);
        if (start > end) {
          input = start;
          start = end;
          end = input;
        }
        printf("For range %d to %d, ",start,end);
        list_t *ansList;
        ansList = findRange(root,start,end);
        printf("%d records found\n",(list_get_length(ansList)));
//list_iterator_t iter;
        free(ansList);
        break; 
      }
// ----------------------------------------40
// [OpenMP] find Range K (initK, findRangeK)
// ----------------------------------------40
      case 'j':
{
// get # of queries from user
        int count;
        sscanf(commandPointer,"%d",&count);
        while(( *commandPointer) != 32 && commandPointer != '\n')
          commandPointer++;
        int rSize;
        sscanf(commandPointer,"%d",&rSize);
        while(( *commandPointer) != 32 && commandPointer != '\n')
          commandPointer++;
        printf("\n******command: j count=%d, rSize=%d \n",count,rSize);
        if (rSize > size || rSize < 0) {
          printf("Search range size is larger than data set size %d.\n",(int )size);
          exit(0);
        }
// INPUT: knodes CPU allocation (setting pointer in mem variable)
        knode *knodes = (knode *)(((long )mem) + ((long )rootLoc));
        long knodes_elem = ((((long )mem_used) - ((long )rootLoc)) / sizeof(knode ));
        long knodes_mem = ((long )mem_used) - ((long )rootLoc);
// printf("knodes_elem=%d, knodes_unit_mem=%d, knodes_mem=%d\n", (int)knodes_elem, sizeof(knode), (int)knodes_mem);
// INPUT: currKnode CPU allocation
        long *currKnode;
        free(recstart);
        free(reclength);
// break out of case
        break; 
      }
// ----------------------------------------40
// default
// ----------------------------------------40
      default:
{
//usage_2();
        break; 
      }
    }
    printf("> ");
  }
  printf("\n");
// ------------------------------------------------------------60
// free remaining memory and exit
// ------------------------------------------------------------60
  free(mem);
  return 0;
}
//========================================================================================================================================================================================================200
//	END
//========================================================================================================================================================================================================200
// # ifdef __cplusplus
// }
// # endif
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