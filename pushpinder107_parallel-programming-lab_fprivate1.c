#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int get_app_id(int i) /*function to assign Application ID to customer*/
{
return(i);
}

int get_main_token(int app_id) /*function to assign Main Counter Token ID to customer according to his Application ID*/
{
return(app_id);
}

int get_sub_token(int x) /* function to assign Sub counter token ID to a customer after he has been processed by the main counter*/
{
int k=x%5; 
if(k==0)     /*when main token ID is a multiple of 5*/
return(k+5); /*customer will go to counter 5 as there is no counter 0 */
else
return(k);
}



main()
{
int app_id=0,main_token=0,sub_token=0,i;

dummyMethod1();
#pragma omp parallel for firstprivate(app_id,main_token,sub_token)
for(i=1;i<=100;i++)
  {
  app_id=get_app_id(i);    /*private int i is used to generate application ID's for customers*/
  main_token=get_main_token(app_id);
  sub_token=get_sub_token(main_token);

  printf("\nMain counter is currently processing Application ID:%d \nMain Counter Token ID :%d \nCounter ID assigned:%d",app_id,main_token,sub_token);

  }
dummyMethod2();

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