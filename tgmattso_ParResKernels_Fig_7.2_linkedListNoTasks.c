#include <stddef.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NMAX 10

struct node {
   int data;
   int procResult;
   struct node* next;
};
// initialize the list (not shown)
struct node* initList(struct node* p);

// a long computation (not shown)
int work(int data);

void procWork (struct node* p) {
   int n = p->data;
   p->procResult = work(n);
}

int main() {
   struct node *p = NULL;
   struct node *temp = NULL;
   struct node *head = NULL;
   struct node *parr;
   int i;
    
   p = initList(p);
    
   // save head of the list
   head = p;  

   int count = 0;
   while (p != NULL) { 
      p = p->next;
      count++; 
   }
   parr = (struct node*)malloc(count*sizeof(struct node));
   p = head;

   for (i = 0; i < count; i++) {
dummyMethod1();
      parr[i] = *p;
      p = p->next; 
   }

   #pragma omp parallel for schedule(static,1) 
					dummyMethod3();
   for (i = 0; i < count; i++)
      procWork(&parr[i]); 
					dummyMethod4();
}
dummyMethod2();
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