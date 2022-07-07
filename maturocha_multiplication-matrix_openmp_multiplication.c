/*
Algoritm: Matrix multiplication
Type: Open MPI
Compile: mpicc openmp_multiplication.c -lm -fopenmp -o openmp
Execute: mpirun -np 2 openmp 4
Autor: Matur
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <mpi.h> 
#include "omp.h"
#include <stdlib.h>
#include <sched.h>
#include <unistd.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE 512 
#define NRO_TESTS 10
#define DEBUG TRUE
#define MASTER 0 //Master ID
#define FROM_MASTER 0 //From Master to slave
#define FROM_SLAVE 1 //From Slave to Master
#define STEPS 5
#define PRINT 0


// Declare Matrix and Vector
double	A[SIZE][SIZE],  // Matrix A
	      B[SIZE][SIZE],  // Matrix B
	      C[SIZE][SIZE],  // Matrix C
        W[SIZE];     // Vector W
  
     
int process_id; // ID Proceso
int process_nro; // Cantidad de Procesos
int threads_nro; //Cantidad de hilos a ejecutar

//Functions
void init_vector();
void print_vector(double vec[],int n);
void init_matrix(double mat[SIZE][SIZE],int n);
void print_matrix(double mat[SIZE][SIZE],int n);
void master_task(int slaves, int threads_nro);
void slave_task();

int main (int argc, char *argv[]) 
{
  int error, slaves;

  if (argc != 2)
  {
    printf("Error! You must use parameter [nro_threads]. \n");
    exit (1);
  }

  threads_nro = atoi(argv[1]);

  omp_set_num_threads(threads_nro);

  MPI_Init(&argc, &argv); //Init MPI
  MPI_Comm_rank(MPI_COMM_WORLD, &process_id); //Get process_id
  MPI_Comm_size(MPI_COMM_WORLD, &process_nro); //Get #process

  slaves = process_nro-1;

  if (process_id == 0) 
      //master id = 0
          master_task(slaves, threads_nro); //Init master task
    else
    //slaves id != 0
          slave_task(); //Init slave task

  MPI_Finalize(); //Finalizar operaciones MPI
  return 0;
}


/*--------------------------------------
	VECTOR Functions
*/

void init_vector(){

	dummyMethod3();
	for (int i=0; i<SIZE; i++) {
      W[i] = 1;
  } 
	dummyMethod4();
  
}

void print_vector(double vec[],int n){
	dummyMethod3();
	for (int i = 0; i < n; ++i)
	{
		printf("%6.2f  ",vec[i] );
	}
	dummyMethod4();
}

/*--------------------------------------
	MATRIX Functions
*/


void init_matrix(double mat[SIZE][SIZE],int n){
	
  srand(time(NULL));
	dummyMethod3();
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			mat[i][j]= rand() % 10 + 1;
		}
	}
	dummyMethod4();
}

void print_matrix(double mat[SIZE][SIZE],int n){

	dummyMethod3();
	for (int i = 0; i < n; ++i)
	{
    printf("\n\t\t");
		for (int j = 0; j < n; ++j)
		{
			printf("%6.2f  ",mat[i][j]);
		}
	}
	dummyMethod4();
  printf("\n\n");

}

/*--------------------------------------
	Master TASK
*/
void master_task(int slaves, int threads_nro){

  //Vars
  double time_init, time_final; 
  int step; 
  int id_slave, rows, offset, rest, i, j;

  FILE *f;
 
  f = fopen("openmpi.csv", "a");

  //Vars MPI
  MPI_Status status; // MPI_Recv Status
  MPI_Datatype dt_aux, dt_column; //Special type of data to rcv columns

  offset = 0; //Offset var in rows and columns
  rows = (SIZE / slaves); // Part of Matrix to process
  rest = SIZE % slaves; // Last part of Matrix
  if (rest == 0)
    rest = rows;
  else
    rest = rest + rows;

			dummyMethod3();
  for (int test=1; test <= NRO_TESTS; test++) {
    printf("\nInicio test= %i\n", test);
    //Init structures
    init_vector();
    if (PRINT == 1)
      print_vector(W,SIZE);
    init_matrix(A,SIZE);
    if (PRINT == 1)
      print_matrix(A,SIZE);
    init_matrix(B,SIZE);
    if (PRINT == 1)
      print_matrix(B,SIZE);

    step=1; //Inicializar en step 1
    time_init = MPI_Wtime();
    while (step <= STEPS)
    {
      printf("\nstep = %i\n", step);
      //Send task to slaves
      for (id_slave= 1; id_slave <= slaves; id_slave++) {           
        //Last slave
        if (id_slave == slaves)
          rows = rest;

      MPI_Send(&step, 1, MPI_INT, id_slave, FROM_MASTER,MPI_COMM_WORLD); //Send step num.
      MPI_Send(&rows, 1, MPI_INT, id_slave, FROM_MASTER,MPI_COMM_WORLD); //Send rows num.
      MPI_Send(&offset, 1, MPI_INT, id_slave, FROM_MASTER,MPI_COMM_WORLD); //Send offset
      //Depends on the step -> the action to do
      
      switch (step) {
        case 1:
        case 3:
        case 5:
            MPI_Send(&A[offset][0], rows*SIZE, MPI_DOUBLE, id_slave, FROM_MASTER,MPI_COMM_WORLD); //Send part of rows of A
            MPI_Send(&B, SIZE*SIZE, MPI_DOUBLE, id_slave, FROM_MASTER,MPI_COMM_WORLD); //Send B
            MPI_Send(&W, SIZE, MPI_DOUBLE, id_slave, FROM_MASTER,MPI_COMM_WORLD); // Send W
          break; 
        case 2:
            MPI_Send(&C[offset][0], rows*SIZE, MPI_DOUBLE, id_slave, FROM_MASTER,MPI_COMM_WORLD); //Send part of rows of vector C
          break;
        case 4:
            MPI_Type_vector(SIZE, 1, SIZE, MPI_DOUBLE, &dt_aux); 
            MPI_Type_create_resized(dt_aux, 0, sizeof(double), &dt_column);
            MPI_Type_commit(&dt_column);
            MPI_Send(&C[0][offset], rows, dt_column, id_slave, 0, MPI_COMM_WORLD);  //Send part of columns of vector C
          break;
      }  

      offset = offset + rows;          

     }

     //Recive task to slaves
     for (id_slave= 1; id_slave <= slaves; id_slave++)
     {  

        MPI_Recv(&offset  , 1, MPI_INT, id_slave, FROM_SLAVE, MPI_COMM_WORLD, &status); //Rcv offset
        MPI_Recv(&rows, 1, MPI_INT, id_slave, FROM_SLAVE, MPI_COMM_WORLD, &status); //Rcv rows num

        switch (step) {
          case 1:
          case 3:
          case 5:
               MPI_Recv(&C[offset][0], rows*SIZE, MPI_DOUBLE, id_slave, FROM_SLAVE, MPI_COMM_WORLD, &status); //Recibe parte en rows procesada de la matriz C
          break; 
          case 2:
               MPI_Recv(&W[offset], rows, MPI_DOUBLE, id_slave, FROM_SLAVE, MPI_COMM_WORLD, &status); //Recibe parte procesada del vector W
          break;
          case 4:
               MPI_Recv(&W[offset], rows, MPI_DOUBLE, id_slave, FROM_SLAVE, MPI_COMM_WORLD, &status); //Recibe parte procesada del vector W
          break; }  
     }

      if (PRINT == 1)
        print_matrix(C,SIZE);

      if (PRINT == 1)
        print_vector(W,SIZE);

       // Finalize slaves
      if ((test == NRO_TESTS) && (step == 5)) {
        //Send int > 5 to finish the while
        for (id_slave= 1; id_slave <= slaves; id_slave++) {
          step = 100;
          MPI_Send(&step, 1, MPI_INT, id_slave, FROM_MASTER, MPI_COMM_WORLD);      
        }
          
      }    

      //Increment step
      step++;

      rows = (SIZE / slaves); 
      offset = 0; 

    
  } 

  time_final = MPI_Wtime(); 

  if (PRINT == 1)
    print_matrix(C,SIZE);
  
  if (PRINT == 1)
    print_vector(W,SIZE);

  printf("\nTime: %f\n\n", time_final - time_init);
  fprintf(f, "%d,%d,%d,%d,%lf\n", test, SIZE, process_nro, threads_nro, time_final - time_init); 
  }
			dummyMethod4();
}

/*--------------------------------------
	Slave TASK
*/

void slave_task(){
  int step=1, rows, offset, i, j, k,porcion,tid;
  int chunk; //Cantidad de iteraciones por bloques de iteraciones
  MPI_Status status; // Almacenar status de MPI_Recv
  MPI_Datatype dt_column,dt_aux;  //Tipo de datos especial para recibir columnas en vez de rows.
  double ac;

  while (step <= STEPS){
      MPI_Recv(&step, 1, MPI_INT, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status); //Rcv step nro
      if (PRINT == 1)
        printf("\nRecibo Step: %d\n\n", step);
      switch (step) {
        case 1: 
        case 3: 
        case 5:
          MPI_Recv(&rows, 1, MPI_INT, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status); 
          MPI_Recv(&offset  , 1, MPI_INT, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status); 
          MPI_Recv(&A,rows*SIZE, MPI_DOUBLE, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status); 
          MPI_Recv(&B,SIZE*SIZE, MPI_DOUBLE, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status); 
          MPI_Recv(&W,SIZE, MPI_DOUBLE, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status);

          /* 
            Parallel Code
          */
          //Chunk -> rows for each thread
          chunk = rows / threads_nro; 

          // parallel for
																							dummyMethod1();
          #pragma omp parallel  for schedule (static, chunk) num_threads(threads_nro) shared(A,B,chunk) private(ac,i,j,k)        
           
           // tid = omp_get_thread_num();
           // printf("Soy el hilo %d de %d del procesos MPI %d de %d. Procesando %d Estoy en el core %d del nodo %s\n",omp_get_thread_num(),threads_nro,process_id,process_nro,offset,sched_getcpu(),getenv("SLURM_NODEID"));


           //C(i,j) = ∑ √(A(i,k) − W(k))**2 * (B(k,j) − W(k))**2 
            for (i=0; i < rows; i++)  
               for (j=0; j<SIZE; j++)
               {
                 ac = 0;
                 for (k=0; k<SIZE; k++)
                   ac += sqrt( pow(A[i][k]-W[k],2) * pow(B[k][j]-W[k],2) );
                C[i][j]= ac;
                }
																							dummyMethod2();
           /* 
            End Parallel Code
          */
          MPI_Send(&offset, 1, MPI_INT, MASTER, FROM_SLAVE, MPI_COMM_WORLD); //Send offset to master
          MPI_Send(&rows, 1, MPI_INT, MASTER, FROM_SLAVE, MPI_COMM_WORLD);  //Send rows number
          MPI_Send(&C, rows*SIZE, MPI_DOUBLE, MASTER, FROM_SLAVE, MPI_COMM_WORLD); //Send part of C

        break;
        case 2:
          MPI_Recv(&rows, 1, MPI_INT, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status); //Rcv rows numbers
          MPI_Recv(&offset  , 1, MPI_INT, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status); //Rcv offset
          MPI_Recv(&C,rows*SIZE, MPI_DOUBLE, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status); //Rcv part of C

          /* 
            Parallel Code
          */
          //Chunk -> rows for each thread
          chunk = rows / threads_nro; 

																			dummyMethod1();
          #pragma omp parallel for schedule (static, chunk) num_threads(threads_nro) shared(C,chunk) private(ac,i,j)            
          
          //W[i] = Prom row i of C

          for (i=0; i<rows; i++) {
            ac = 0;
            for (j=0; j<SIZE; j++) {
                ac = ac + C[i][j];
              }
            W[i] = ac / SIZE;
          }            
																			dummyMethod2();
          
          /* 
            End Parallel Code
          */
         
          MPI_Send(&offset, 1, MPI_INT, MASTER, FROM_SLAVE, MPI_COMM_WORLD);
          MPI_Send(&rows, 1, MPI_INT, MASTER, FROM_SLAVE, MPI_COMM_WORLD);  
          MPI_Send(&W, rows, MPI_DOUBLE, MASTER, FROM_SLAVE, MPI_COMM_WORLD);

        break;
        case 4:

          MPI_Recv(&rows, 1, MPI_INT, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status); 
          MPI_Recv(&offset  , 1, MPI_INT, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status); 
          MPI_Type_vector(SIZE, 1, SIZE, MPI_DOUBLE, &dt_aux); 
          MPI_Type_create_resized(dt_aux, 0, sizeof(double), &dt_column);
          MPI_Type_commit(&dt_column);
          MPI_Recv(&C,rows, dt_column, MASTER, FROM_MASTER, MPI_COMM_WORLD, &status);

          /* 
            Parallel Code
          */
          //Chunk -> rows for each thread
          chunk = rows / threads_nro; 

																			dummyMethod1();
          #pragma omp parallel for schedule (static, chunk) num_threads(threads_nro) shared(C,chunk) private(ac,i,j) 

          //W[i] = Prom column i of C
          for (j=0; j<rows; j++) { 
            ac = 0;
            for (i=0; i<SIZE; i++){
              ac = ac + C[i][j];
                }
            W[j] = ac / SIZE;
          } 
																			dummyMethod2();
          
           /* 
            End Parallel Code
          */

          MPI_Send(&offset, 1, MPI_INT, MASTER, FROM_SLAVE, MPI_COMM_WORLD); 
          MPI_Send(&rows, 1, MPI_INT, MASTER, FROM_SLAVE, MPI_COMM_WORLD);  
          MPI_Send(&W, rows, MPI_DOUBLE, MASTER, FROM_SLAVE, MPI_COMM_WORLD);
        break;
      }              
   }
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