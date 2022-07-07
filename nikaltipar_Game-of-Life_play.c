#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include <game-of-life.h>

void play (int **board, int **newboard, int N, int comm_size, int this_rank)
{
  int i, j, a;

  int* temp_board;
  int* up = (int *) malloc(N * sizeof(int)); 
  int* down = (int *) malloc(N * sizeof(int)); 
  MPI_Request req;
  MPI_Status stat;

  MPI_Isend(&pBoard(0, 0),
      N, 
      MPI_INT, 
      PosMod(this_rank - 1, comm_size),
      1,
      MPI_COMM_WORLD,
      &req
      );

  MPI_Isend(&pBoard(N/comm_size - 1, 0),
      N, 
      MPI_INT, 
      PosMod(this_rank + 1, comm_size),
      2, 
      MPI_COMM_WORLD,
      &req
      );



			dummyMethod1();
#pragma omp parallel for schedule(static)
  for (i = 1; i < N/comm_size - 1; i++)
  {
    for (j = 0; j < N; j++)
    {
      a = adjacent_to (*board, i, j, N);
      pNewBoard(i, j) = count_adj(pBoard(i, j), a);
    }
  }
			dummyMethod2();

  MPI_Irecv(down, 
      N, 
      MPI_INT, 
      PosMod(this_rank + 1, comm_size),
      1,
      MPI_COMM_WORLD,
      &req
      );

  MPI_Recv(up,
      N, 
      MPI_INT, 
      PosMod(this_rank - 1, comm_size),
      2,
      MPI_COMM_WORLD,
      &stat
      );

  MPI_Barrier(MPI_COMM_WORLD);

  i = 0;

			dummyMethod1();
#pragma omp parallel for schedule(static)
  for (j = 0; j < N; j++)
  {
    a = barrier_adjacent_to (*board, i, j, N, comm_size, up, down);
    pNewBoard(i, j) = count_adj(pBoard(i, j), a);
  }
			dummyMethod2();

  i = N/comm_size - 1;
  if (i != 0)
  {

    MPI_Wait(&req, &stat);

							dummyMethod1();
#pragma omp parallel for schedule(static)
    for (j = 0; j < N; j++)
    {
      a = barrier_adjacent_to (*board, i, j, N, comm_size, up, down);
      pNewBoard(i, j) = count_adj(pBoard(i, j), a);
    }
							dummyMethod2();
  }

  temp_board = *board;
  *board = *newboard;
  *newboard = temp_board;

  MPI_Barrier(MPI_COMM_WORLD);
  free(up);
  free(down);
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