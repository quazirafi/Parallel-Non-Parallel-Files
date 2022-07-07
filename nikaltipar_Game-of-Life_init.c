#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include <game-of-life.h>

void initialize_board (int *board, int N, int comm_size) {
  int   i, j;

dummyMethod1();
#pragma omp parallel for schedule(static)
  for (i = 0; i < N/comm_size; i++)
  {
    for (j = 0; j < N; j++) 
    {
      Board(i,j) = 0;
    }
  }
dummyMethod2();
}

void generate_table (int *board, int N, int comm_size, int this_rank, float threshold) 
{

  int i, j;
  int counter = 0;

  srand(time(NULL) + 1234 * this_rank);

			dummyMethod1();
#pragma omp parallel for schedule(static)

  for (i = 0; i < N/comm_size; i++)
  {
    for (j = 0; j < N; j++)
    {
      //printf("%d\n", omp_get_thread_num());
      Board(i,j) = ( (float)rand() / (float)RAND_MAX ) < threshold;
      counter += Board(i,j);
    }
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