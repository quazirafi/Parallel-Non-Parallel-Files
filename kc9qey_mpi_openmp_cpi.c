#include <stdio.h>
#include <mpi.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char *argv[])
{
	int n, myid, numprocs, i;
	double PI25DT = 3.141592653589793238462643;
	double mypi, pi, h, sum, x;
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &myid);
	while (1) {
		if (myid == 0) {
			printf("Enter the number of intervals: (0 quits) ");
			scanf("%d",&n);
		}
		MPI_Bcast(&n, 1, MPI_INT, 0, MPI_COMM_WORLD);
		if (n == 0)
			break;
		else {
			h   = 1.0 / (double) n;
			sum = 0.0;
dummyMethod1();
#pragma omp parallel for reduction(+: sum)
			for (i = myid + 1; i <= n; i += numprocs) {
				x = h * ((double)i - 0.5);
				sum += (4.0 / (1.0 + x*x));
			}
dummyMethod2();
			mypi = h * sum;
			MPI_Reduce(&mypi, &pi, 1, MPI_DOUBLE, MPI_SUM, 0,
					MPI_COMM_WORLD);
			if (myid == 0)
				printf("\npi is approximately %.16f, Error is %.16f\n",
						pi, fabs(pi - PI25DT));
		}
	}
	MPI_Finalize();
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