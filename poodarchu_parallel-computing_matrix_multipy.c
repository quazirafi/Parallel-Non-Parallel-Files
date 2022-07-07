#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define size 10
double	a[size][size], b[size][size], c[size][size];

#define MASTER 0
#define FROM_MASTER 1
#define FROM_WORKER 2

int main (int argc, char *argv[])
{
    int	numtasks;
    int taskid;
    int numworkers;
    int source, dest;
    int mtype;                 // message type
    int rows;                  //rows of matrix A sent to each worker
    int averow, extra, offset; // used to determine rows sent to each worker
    int i, j, k, rc;

    MPI_Status status;

    MPI_Init(&argc,&argv);
    MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
    MPI_Comm_size(MPI_COMM_WORLD,&numtasks);

    if (numtasks < 2 ) {
        printf("Need at least two MPI tasks. Quitting...\n");
        MPI_Abort(MPI_COMM_WORLD, rc);
        exit(1);
    }

    numworkers = numtasks-1;

    if (taskid == MASTER)
    {
        printf("mpi_mm has started with %d tasks\n ",numtasks);
        printf("Initializing arrays...\n");

															dummyMethod1();
#pragma omp parallel  for private(j)
        for (i=0; i<size; i++)
        {
            for (j=0; j<size; j++)
            {
                a[i][j] = (float)i + j;
                b[i][j] = (float)i - j;
            }
        }
															dummyMethod2();

        /* Send matrix data to the worker tasks */
        averow = size/numworkers;
        extra = size%numworkers;
        offset = 0;
        mtype = FROM_MASTER;

															dummyMethod1();
#pragma omp parallel for
        for (dest=1; dest<=numworkers; dest++)
        {
            rows = (dest <= extra) ? averow+1 : averow;
            printf("Sending %d rows to task %d offset=%d\n",rows,dest,offset);
            MPI_Send(&offset, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
            MPI_Send(&rows, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
            MPI_Send(&a[offset][0], rows*size, MPI_DOUBLE, dest, mtype,
                     MPI_COMM_WORLD);
            MPI_Send(&b, size*size, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);
            offset = offset + rows;
        }
															dummyMethod2();

        /* Receive results from worker tasks */
        mtype = FROM_WORKER;
															dummyMethod3();
        for (i=1; i<=numworkers; i++)
        {
            source = i;
            MPI_Recv(&offset, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
            MPI_Recv(&rows, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
            MPI_Recv(&c[offset][0], rows*size, MPI_DOUBLE, source, mtype,
                     MPI_COMM_WORLD, &status);
            printf("Received results from task %d\n",source);
        }
															dummyMethod4();

        /* Print results */
        printf("\nResult Matrix:");
															dummyMethod3();
        for (i=0; i<size; i++)
        {
           printf("\n");
           for (j=0; j<size; j++)
              printf("%6.2f   ", c[i][j]);
        }
															dummyMethod4();
        printf("\n");
        printf ("Done.\n");

    }

    if (taskid > MASTER)
    {
        mtype = FROM_MASTER;
        MPI_Recv(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
        MPI_Recv(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
        MPI_Recv(&a, rows*size, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);
        MPI_Recv(&b, size*size, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);

															dummyMethod3();
        for (k=0; k<size; k++)
            for (i=0; i<size; i++)
            {
                c[i][k] = 0.0;
                for (j=0; j<size; j++)
                    c[i][k] = c[i][k] + a[i][j] * b[j][k];
            }
															dummyMethod4();
        mtype = FROM_WORKER;
        MPI_Send(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
        MPI_Send(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
        MPI_Send(&c, rows*size, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD);
    }
    MPI_Finalize();
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