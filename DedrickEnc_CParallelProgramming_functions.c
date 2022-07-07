/**
* this program is for illustrating openmp functions
**/

#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char const *argv[])
{

int i, sum = 0;
omp_lock_t lk; //the omp lock variable

//setting the number of thread to use
omp_set_num_threads(3);

//returns the number of threads activated , should return 1 because we are not in parallel area 

printf("the number of threads are : %d \n", omp_get_num_threads());

omp_set_num_threads(3);
dummyMethod1();
#pragma omp parallel for
for(i=0; i<10; i++){
 printf("The number of threads are : %d \n", omp_get_num_threads()); //should print 3 ten times
}
dummyMethod2();

printf("The number of available threads are : %d \n", omp_get_max_threads()); // should print the number of available threads to activate

printf("The thread number execting this statement is : %d \n", omp_get_thread_num()); //the thread number witch excute this statement

printf("The number of virtual CPU : %d \n", omp_get_num_procs()); //number of virtual processor

#pragma omp parallel
{
 printf("we are in a parallel area the value is not null : %d \n", omp_in_parallel());
}

printf("we are in a sequntial zone the value is null : %d \n", omp_in_parallel());

omp_set_dynamic(1); //alowing dynamic thread changing number
omp_set_num_threads(2);
#pragma omp parallel
{
 //The number of threads  thris 2 threads number was changed dynamicly
 printf("The number of threads are : %d threads number was changed dynamicly \n", omp_get_num_threads()); 
}
omp_set_num_threads(3);

#pragma omp parallel
{
 //The number of threads is 3 threads number was changed dynamicly
 #pragma omp single
 printf("The number of threads are : %d threads number was changed dynamicly \n", omp_get_num_threads()); 

 #pragma omp single
 printf("The number of threads are : %d before disactivating dynamic change \n", omp_get_num_threads());

 //disable the dynamic change
 #pragma omp single
 omp_set_dynamic(0);

 #pragma omp single
 {
  omp_set_num_threads(2);
  printf("The number of threads still : %d \n", omp_get_num_threads());
 }
}

//to know if dynamic change is allowed
printf("The dynamic change is disactived so the value is null : %d \n", omp_get_dynamic());

//to know if nested parallel is allowed
printf("The nested parallel is disactived so the value is null : %d use omp_set_nested(not null) to activate \n", omp_get_nested());

#pragma omp single
 omp_set_dynamic(1); //reset to activated


/**
*using the lock functions
* to sum a in a for loop
**/

omp_init_lock(&lk); //initializing a lock

	dummyMethod1();
 #pragma omp parallel for
 for (i = 0; i<10; i++){
  omp_set_lock(&lk); //passing by address to let each thread accesses the same value at the same address
  sum+=i;  //one thread at time will update the sum variable
  omp_unset_lock(&lk);
 }
	dummyMethod2();

printf("sum by using lock function is %d \n", sum);

sum = 0;

dummyMethod3();
for (i = 0; i<10; i++){
   sum+=i;  
}
dummyMethod4();

printf("sum by using sequential statement is %d \n", sum);

	dummyMethod1();
 #pragma omp parallel for
 for (i = 0; i<10; i++){
  sum+=i;  
 }
	dummyMethod2();

printf("sum by using parallel statement without lock function will be random : %d \n", sum);

omp_destroy_lock(&lk); // to destroy the lock

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