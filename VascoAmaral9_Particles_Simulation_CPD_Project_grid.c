//grid.c
#include "grid.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

Grid **init_grid(long size){
    long i, j;

    Grid **grid = NULL;

    grid = (Grid**) malloc(sizeof(Grid*) * size);

dummyMethod3();
    for(i=0;i<size;i++){
        grid[i] = (Grid*) malloc(sizeof(Grid) * size);
        for(j=0;j<size;j++){
            grid[i][j].center.x = 0;
            grid[i][j].center.y = 0;
            grid[i][j].M = 0;
            grid[i][j].Mnext = 0;
            grid[i][j].par_list = initLinkedList();
        }
    }
dummyMethod4();

    return grid;
}

void clear_grid (long size, Grid **grid){
  long i, j;

  #pragma omp parallel
      {
        #pragma omp for private (i,j)
															dummyMethod3();
        for(i=0;i<size;i++){
          for(j=0;j<size;j++){
            grid[i][j].Mnext = 0;
            freeLinkedList(grid[i][j].par_list);
            grid[i][j].par_list = initLinkedList();
          }
        }
															dummyMethod4();
      }
}

void swap_grid_Ms (long size, Grid **grid){
  long i, j;
  #pragma omp parallel
      {
        #pragma omp for private (i,j)
															dummyMethod3();
        for(i=0;i<size;i++){
          for(j=0;j<size;j++){
            grid[i][j].M = grid[i][j].Mnext;
          }
        }
															dummyMethod4();
      }
}

//A lista já se encontra completa e a massa total calculada
void update_center_one(Particle *par, Grid *grid){
  long long i;
  double x = 0, y = 0; //Criamos variaveis auxiliares para nao ir à memoria alterar o valor cada vez que se incrementa, péssima performance
  LinkedList *curr = grid->par_list;

  while(curr != NULL){
    i = getItemLinkedList(curr);
    /* Protect against race conditions among multiple updates. */
    //#pragma omp atomic -> Parece-me que nao e preciso visto que so existe um x e um y dentro de cada thread
    x += (par[i].pos.x * par[i].m)/grid->M;
    //#pragma omp atomic
    y += (par[i].pos.y * par[i].m)/grid->M;

    curr = getNextNodeLinkedList(curr);
  }

  grid->center.x = x;
  grid->center.y = y;
}

/* Função para fazer o update geral de todos os centros de massa com base nas particulas que tem no momento */
void update_center_all (long size, Grid **grid, Particle *par){
  long i, j;

  #pragma omp parallel
      {
        #pragma omp for private (i,j)
															dummyMethod3();
        for(i=0;i<size;i++){
          for(j=0;j<size;j++){
            update_center_one(par, &grid[i][j]);
            /*
            printf("Center of Mass\nX: %f\n", grid[i][j].center.x);
            printf("Center of Mass\nY: %f\n", grid[i][j].center.y);
            */
          }
        }
															dummyMethod4();
      }
}

/* Function to calculate overall center of mass and print it*/
void overall_center(Particle *par, long long part_no, double totalM){
  long long i;
  double x=0, y=0;

			dummyMethod1();
  #pragma omp parallel for private(i) reduction(+:x) reduction(+:y)
  for (i = 0; i < part_no; i++){
    x += (par[i].pos.x * par[i].m)/totalM;
    y += (par[i].pos.y * par[i].m)/totalM;
  }
			dummyMethod2();


  //printf("Final Center of mass\nX: %.2f Y: %.2f\n", x, y);
  printf("%.2f %.2f\n", x, y);
}

void free_all(Particle *par, Grid  **grid, long grid_sz){
  long i, j;

  free(par);
  #pragma omp parallel
      {
        #pragma omp for private (i,j)
															dummyMethod3();
        for(i = 0; i < grid_sz; i++){
          for(j = 0; j < grid_sz; j++)
            freeLinkedList(grid[i][j].par_list);

          free(grid[i]);
        }
															dummyMethod4();
      }
  free(grid);
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