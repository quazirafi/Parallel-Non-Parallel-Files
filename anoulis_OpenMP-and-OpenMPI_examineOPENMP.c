#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define limit1 12
#define limit2 30
#define number 15000000



struct timespec start,end;

void print_time()
{
  const int DAS_NANO_SECONDS_IN_SEC = 1000000000;
  long timeElapsed_s = end.tv_sec -start.tv_sec;
  long timeElapsed_n = end.tv_nsec -start.tv_nsec;
  if ( timeElapsed_n < 0 )
  {
    timeElapsed_n = DAS_NANO_SECONDS_IN_SEC + timeElapsed_n;
    timeElapsed_s--;
  }
  printf("Time: %ld.%09ld secs \n",timeElapsed_s,timeElapsed_n);
}

void read_file(char* filename)
{
  FILE *fp;
  fp = fopen(filename, "r");
  if (fp == NULL)
  {
    puts("Error reading file");
    return;
  }

   float percentage,x;
   long size =(number*30);
   char *buffer,c[9];
   buffer=(char*)calloc(size,sizeof(char));
   int k=0,i=0,count1=0,count2=0;
  clock_gettime(CLOCK_MONOTONIC, &start);
  fread(buffer, size, 1, fp);
							dummyMethod1();
  #pragma omp nowait parallel for firstprivate(size) reduction(+:count1) reduction(+:count2)
    for(i=0;i<size;i++)
    { if(buffer[i]!=' ' && buffer[i]!='\n')
      {
        c[k]=buffer[i];
        k++;
      }
      else
      {
        x=atof(c);
        if (x>=limit1 && x<=limit2)
        count2++;
        count1++;
        k=0;
      }
    }
							dummyMethod2();

  free(buffer);
  clock_gettime(CLOCK_MONOTONIC, &end);
  fclose(fp);
  printf("Total coordinates read: %d\n",count1);
  printf("Total coordinates inside interval: %d\n",count2);
  percentage = ((float)count2/(float)count1)*100;
  printf("Percentage of coordinates inside interval: %f%c\n", percentage,37);
  print_time();

}



int main()
{
    read_file("data");
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