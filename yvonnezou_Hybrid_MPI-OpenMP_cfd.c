/**
 *
 * This the hybrid programme in single style on ARCHER.
 * We parallel it from the pure-MPI programme and remove useless code to keep the output clean.
 * Also some code in jacobi.c has been revised.
 *
**/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include <mpi.h>
#include "omp.h"

#include "arraymalloc.h"
#include "boundary.h"
#include "jacobi.h"
#include "cfdio.h"

#define nthread 4

int main(int argc, char **argv)
{
  int printfreq=1000; //output frequency
  double localerror, error, localbnorm, bnorm;
  double tolerance=0.0; //tolerance for convergence. <=0 means do not check

  //main arrays
  double **psi, **zet;
  //temporary versions of main arrays
  double **psitmp, **zettmp;

  //command line arguments
  int scalefactor, numiter;

  double re; // Reynold's number - must be less than 3.7

  //simulation sizes
  int bbase=10;
  int hbase=15;
  int wbase=5;
  int mbase=32;
  int nbase=32;

  int irrotational = 1, checkerr = 0;

  int m,n,lm,b,h,w;
  int iter;
  int i,j;

  double tstart, tstop, ttot, titer;

  //parallelisation parameters
  int rank, size;
  MPI_Comm comm;

  if (tolerance > 0) {checkerr=1;}

  comm=MPI_COMM_WORLD;

  MPI_Init(&argc,&argv);

  MPI_Comm_rank(comm,&rank);
  MPI_Comm_size(comm,&size);

  omp_set_num_threads(nthread);

  //check command line parameters and parse them

  if (argc <3|| argc >4)
    {
      if (rank == 0) printf("Usage: cfd <scale> <numiter> [reynolds]\n");
      MPI_Finalize();
      return 0;
    }

  if (rank == 0)
    {
      scalefactor=atoi(argv[1]);
      numiter=atoi(argv[2]);

      if (argc == 4)
	{
	  re=atof(argv[3]);
	  irrotational=0;
	}
      else
	{
	  re=-1.0;
	}

      if(!checkerr)
	{
	  printf("Scale Factor = %i, iterations = %i\n",scalefactor, numiter);
	}
      else
	{
	  printf("Scale Factor = %i, iterations = %i, tolerance= %g\n",scalefactor,numiter,tolerance);
	}

      if (irrotational)
	{
	  printf("Irrotational flow\n");
	}
      else
	{
	  printf("Reynolds number = %f\n",re);
	}
    }


  //broadcast runtime params to other processors
  MPI_Bcast(&scalefactor,1,MPI_INT,0,comm);
  MPI_Bcast(&numiter,1,MPI_INT,0,comm);
  MPI_Bcast(&re,1,MPI_DOUBLE,0,comm);
  MPI_Bcast(&irrotational,1,MPI_INT,0,comm);

  //Calculate b, h & w and m & n
  b = bbase*scalefactor;
  h = hbase*scalefactor;
  w = wbase*scalefactor;
  m = mbase*scalefactor;
  n = nbase*scalefactor;

  re = re / (double)scalefactor;

  //calculate local size
  lm = m/size;

  //consistency check
  if (size*lm != m)
    {
      if (rank == 0)
	{
	  printf("ERROR: m=%d does not divide onto %d processes\n", m, size);
	}
      MPI_Finalize();
      return -1;
    }

  if (rank == 0)
    {
      printf("Running CFD on %d x %d grid using %d process(es) and %d thread(s) \n",m,n,size,nthread);
    }

  //allocate arrays

  psi    = (double **) arraymalloc2d(lm+2,n+2,sizeof(double));
  psitmp = (double **) arraymalloc2d(lm+2,n+2,sizeof(double));

  //zero the psi array
			dummyMethod3();
  for (i=0;i<lm+2;i++)
    {
      for(j=0;j<n+2;j++)
	{
	  psi[i][j]=0.;
	}
    }
			dummyMethod4();

  if (!irrotational)
    {
      //allocate arrays

      zet =   (double **) arraymalloc2d(lm+2,n+2,sizeof(double));
      zettmp =(double **) arraymalloc2d(lm+2,n+2,sizeof(double));

      //zero the zeta array

											dummyMethod3();
      for (i=0;i<lm+2;i++)
	{
	  for(j=0;j<n+2;j++)
	    {
	      zet[i][j]=0.;
	    }
	}
											dummyMethod4();
    }

  //set the psi boundary conditions

  boundarypsi(psi,lm,n,b,h,w,comm);

  //compute normalisation factor for error

  localbnorm=0.;

			dummyMethod3();
  for (i=0;i<lm+2;i++)
    {
      for (j=0;j<n+2;j++)
	{
	  localbnorm += psi[i][j]*psi[i][j];
	}
    }
			dummyMethod4();

  //boundary swap of psi

  haloswap(psi,lm,n,comm);

  if (!irrotational)
    {
      //update zeta BCs that depend on psi
      boundaryzet(zet,psi,lm,n,comm);

      //update normalisation

											dummyMethod3();
      for (i=0;i<lm+2;i++)
	{
	  for (j=0;j<n+2;j++)
	    {
	      localbnorm += zet[i][j]*zet[i][j];
	    }
	}
											dummyMethod4();

      //boundary swap zeta
      haloswap(zet,lm,n,comm);
    }

  //get global bnorm
  MPI_Allreduce(&localbnorm,&bnorm,1,MPI_DOUBLE,MPI_SUM,comm);

  bnorm=sqrt(bnorm);

  //begin iterative Jacobi loop

  if (rank == 0)
    {
      printf("\nStarting main loop...\n\n");
    }

  //barrier for accurate timing - not needed for correctness

  MPI_Barrier(comm);

  tstart=MPI_Wtime();

  for(iter=1;iter<=numiter;iter++)
    {
      //calculate psi for next iteration
      /**
       * The code is modified here
       * Because there is a loop in the jacobi algorithm, it is easy to get paralleled with OpenMP
       * These two functions are modified and the details are in file jacobi.c
      **/

      if (irrotational)
	{
	/**
	 * Modified
	**/
	  jacobistep(psitmp,psi,lm,n);
	}
      else
	{
	/**
	 * Modified
	**/
	  jacobistepvort(zettmp,psitmp,zet,psi,lm,n,re);
	}

      //calculate current error if required

      if (checkerr || iter == numiter)
	{
	  localerror = deltasq(psitmp,psi,lm,n);

	  if(!irrotational)
	    {
	      localerror += deltasq(zettmp,zet,lm,n);
	    }

	  MPI_Allreduce(&localerror,&error,1,MPI_DOUBLE,MPI_SUM,comm);
	  error=sqrt(error);
	  error=error/bnorm;
	}

      //quit early if we have reached required tolerance

      if (checkerr)
	{
	  if (error < tolerance)
	    {
	      if (rank == 0)
		{
		  printf("Converged on iteration %d\n",iter);
		}
	      break;
	    }
	}

      /**
       * This part is modified to be paralleled by OpenMP
       * It is designed to copy the new array back. Because the loop is balance and the default schedule way is applied.
       * The work is split evenly and assigned to each thread.
       * The variable i and j are to calculate the number of iterations. Each thread has a copy of them.
       * The variable psi(zet), psitmp(zettmp), lm, m are set to shared. All threads are able to see it.
      **/
											dummyMethod1();
#pragma omp parallel for default(none) private(i,j) shared(psi,psitmp,lm,n)
      for(i=1;i<=lm;i++)
	{
	  for(j=1;j<=n;j++)
		{
	 	psi[i][j]=psitmp[i][j];
		}
	}
											dummyMethod2();

      if (!irrotational)
	{
					dummyMethod1();
#pragma omp parallel for default(none) private(i,j) shared(zet,zettmp,lm,n)
	  for(i=1;i<=lm;i++)
	    {
	      for(j=1;j<=n;j++)
		{
		  zet[i][j]=zettmp[i][j];
		}
	    }
					dummyMethod2();
	}

      //do a boundary swap

      haloswap(psi,lm,n,comm);

      if (!irrotational)
	{
	  haloswap(zet,lm,n,comm);
	  boundaryzet(zet,psi,lm,n,comm);
	}

      //print loop information

      if(iter%printfreq == 0)
	{
	  if (rank==0)
	    {
	      if (!checkerr)
		{
		  printf("Completed iteration %d\n",iter);
		}
	      else
		{
		  printf("Completed iteration %d, error = %g\n",iter,error);
		}
	    }
	}
    }

  if (iter > numiter) iter=numiter;

  MPI_Barrier(comm);
  tstop=MPI_Wtime();

  ttot=tstop-tstart;
  titer=ttot/(double)iter;


  //print out some stats
  if (rank == 0)
    {
      printf("\n... finished\n");
      printf("After %d iterations, the error is %g\n",iter,error);
      printf("Time for %d iterations was %g seconds\n",iter,ttot);
      printf("Each iteration took %g seconds\n",titer);
    }

  //output results

  writedatafiles(psi,lm,n, scalefactor,comm);

  if (rank == 0) writeplotfile(m,n,scalefactor);

  //free un-needed arrays
  free(psi);
  free(psitmp);

  if (!irrotational)
    {
      free(zet);
      free(zettmp);
    }

  MPI_Finalize();

  if (rank == 0)
    {
      printf("... finished\n");
    }

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