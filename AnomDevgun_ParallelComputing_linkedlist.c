#include <stdlib.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifndef N
#define N 5
#endif
#ifndef FS
#define FS 38
#endif

#define NUMTHREADS 3

struct node {
   int data;
   int fibdata;
   struct node* next;
};

int fib(int n) {
   int x, y;
   if (n < 2) {
      return (n);
   } else {
      x = fib(n - 1);
      y = fib(n - 2);
	  return (x + y);
   }
}

void processwork(struct node* p)
{
   int n;
   n = p->data;
   p->fibdata = fib(n);
}

struct node* init_list(struct node* p) {
    int i;
    struct node* head = NULL;
    struct node* temp = NULL;

    head = (struct node*)malloc(sizeof(struct node));
    p = head;
    p->data = FS;
    p->fibdata = 0;
							dummyMethod3();
    for (i=0; i< N; i++) {
       temp  =  (struct node*)malloc(sizeof(struct node));
       p->next = temp;
       p = temp;
       p->data = FS + i + 1;
       p->fibdata = i+1;
    }
							dummyMethod4();
    p->next = NULL;
    return head;
}

int main(int argc, char *argv[]) {
     double start, end;
     struct node *p=NULL;
     struct node *temp=NULL;
     struct node *head=NULL;
     int count =0,i,j;
     omp_set_num_threads(NUMTHREADS);
	printf("Process linked list\n");
     printf("  Each linked list node will be processed by function 'processwork()'\n");
     printf("  Each ll node will compute %d fibonacci numbers beginning with %d\n",N,FS);

     p = init_list(p);
     head = p;


     start = omp_get_wtime();
     {
        while (p != NULL) {
       	count++;
		   p = p->next;
        }
        printf("%d\n",count);
        p=head;
																			dummyMethod1();
        #pragma omp parallel for firstprivate(p) private(j)
          for(i=0;i<count;i++){
            int skip = i;
              if(i==0){
                processwork(p);
              }
              else{
                while(skip!=0){
                  p=p->next;
                  --skip;
                }
                processwork(p);
              }
          }
																			dummyMethod2();
     }

     end = omp_get_wtime();
     p = head;
	 while (p != NULL) {
        printf("%d : %d\n",p->data, p->fibdata);
        temp = p->next;
        free (p);
        p = temp;
     }
	 free (p);

     printf("Compute Time: %f seconds\n", end - start);

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