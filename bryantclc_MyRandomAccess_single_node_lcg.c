#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/time.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* If want to check the update results, define the UPDATE_CHECK macro  */
#define UPDATE_CHECK

#define LCG_MUL64 6364136223846793005ULL
#define LCG_ADD64 1


typedef unsigned long u64Int;
typedef long s64Int;
#define FSTR64 "%ld"
#define FSTRU64 "%lu"
#define ZERO64B 0L
//typedef unsigned long u64Int;  //in our 64 bits machine, the unsigned long is 64 bits

/* Number of updates to table (suggested: 4x number of table entries) */
#define NUPDATE (4 * TableSize)

#define BLOCK_SIZE 1024

/* Utility routine to start LCG random number generator at Nth step */
u64Int
HPCC_starts_LCG(s64Int n)
{
  u64Int mul_k, add_k, ran, un;

  mul_k = LCG_MUL64;
  add_k = LCG_ADD64;

  ran = 1;
			dummyMethod3();
  for (un = (u64Int)n; un; un >>= 1) {
    if (un & 1)
      ran = mul_k * ran + add_k;
    add_k *= (mul_k + 1);
    mul_k *= mul_k;
  }
			dummyMethod4();

	return ran;
}

void
RandomAccessUpdate_LCG(u64Int TableSize, u64Int *Table) {
	u64Int i;
  	u64Int ran[BLOCK_SIZE];              /* Current random numbers */
  	int j, logTableSize;


	dummyMethod3();
	for (j=0; j<BLOCK_SIZE; j++)
    		ran[j] = HPCC_starts_LCG((NUPDATE/BLOCK_SIZE) * j);
	dummyMethod4();


  	logTableSize = 0;
					dummyMethod3();
  	for (i = 1; i < TableSize; i <<= 1)
    		logTableSize += 1;
					dummyMethod4();
	

	for (i=0; i<NUPDATE/BLOCK_SIZE; i++) {
		/* #pragma ivdep */
#ifdef _OPENMP
			dummyMethod1();
		#pragma omp parallel for
#endif
		for (j=0; j<BLOCK_SIZE; j++) {
      			ran[j] = LCG_MUL64 * ran[j] + LCG_ADD64;
      			Table[ran[j] >> (64 - logTableSize)] ^= ran[j];
    		}
			dummyMethod2();
  	}
}


int
RandomAccess_LCG(unsigned long totalMemSize, int doIO, char *outFname, double *GUPs, int *failure) {
	u64Int i;
  	u64Int temp;
  	//double cputime;               /* CPU time to update table */
  	double realtime;              /* Real time to update table */
	struct timeval gups_start, gups_end;
  	double totalMem;
  	u64Int *Table;
  	u64Int logTableSize, TableSize;
  	FILE *outFile = NULL;

  	if (doIO) {
    		outFile = fopen( outFname, "a" );
    		if (! outFile) {
      			outFile = stderr;
      			fprintf( outFile, "#### Cannot open output file.\n" );
      			return 1;
    		}
  	}

	/* calculate local memory per node for the update table */
  	totalMem = (double)totalMemSize;
  	totalMem /= sizeof(u64Int);


  	/* calculate the size of update array (must be a power of 2) */
  	for (totalMem *= 0.5, logTableSize = 0, TableSize = 1;
       		totalMem >= 1.0;
       		totalMem *= 0.5, logTableSize++, TableSize <<= 1)
	;
	
	
	Table = (u64Int*)malloc(TableSize * sizeof(u64Int));
	printf("$$$$ Malloc Table: %lu MB , size u64Int %d\n", ((TableSize * sizeof(u64Int)) >> 20), sizeof(u64Int));

	if (!Table) {
		fprintf(stderr, "#### Failed to malloc space for Table\n");
		exit(-8);
    		if (doIO) {
      			fprintf( outFile, "Failed to allocate memory for the update table (" FSTR64 ").\n", TableSize);
      			fclose( outFile );
    		}
    		return 1;
  	}

	/* Print parameters for run */
 	if (doIO) {
  		fprintf( outFile, "Main table size   = 2^" FSTR64 " = " FSTR64 " words\n", logTableSize,TableSize);
  		fprintf( outFile, "Number of updates = " FSTR64 "\n", NUPDATE);
  	}
	

#ifdef _OPENMP
#pragma omp parallel 
    {
#pragma omp master
	{
		printf("$$ In omp, Num of omp threads:%d\n", omp_get_num_threads());
		if(doIO)
		{
			fprintf( outFile, "Num of threads = %d\n", omp_get_num_threads());
		}
	}
    }

#pragma omp parallel
    {
    	printf ("Printing one line per active thread....\n");
    }

#endif


	/* Initialize main table */
	for (i=0; i<TableSize; i++) {
		Table[i] = i;
	}

        printf("$$$$ NUpdate %lu\n", NUPDATE);

	/* Begin timing here */
	gettimeofday(&gups_start, NULL);

  	RandomAccessUpdate_LCG( TableSize, Table );

  	/* End timed section */
	gettimeofday(&gups_end, NULL);
	
	realtime = (gups_end.tv_sec - gups_start.tv_sec) + ((double)(gups_end.tv_usec - gups_start.tv_usec)) / 1.0E6;

  	/* make sure no division by zero */
  	*GUPs = (realtime > 0.0 ? 1.0 / realtime : -1.0);
  	*GUPs *= 1e-9*NUPDATE;
	
	/* Print timing results */
  	if (doIO) {
  		//fprintf( outFile, "CPU time used  = %.6f seconds\n", cputime);
  		fprintf( outFile, "Real time used = %.6f seconds\n", realtime);
  		fprintf( outFile, "%.9f Billion(10^9) Updates    per second [GUP/s]\n", *GUPs );
  	}

	temp = 0;
#ifdef UPDATE_CHECK
	 /* Verification of results (in serial or "safe" mode; optional) */
  	temp = 0x1;
  	for (i=0; i<NUPDATE; i++) {
    		temp = LCG_MUL64 * temp + LCG_ADD64;
    		Table[temp >> (64 - (int)logTableSize)] ^= temp;
  	}

  	temp = 0;
  	for (i=0; i<TableSize; i++)
    		if (Table[i] != i)
      			temp++;

  	if (doIO) {
  		fprintf( outFile, "Found " FSTR64 " errors in " FSTR64 " locations (%s).\n",
           		temp, TableSize, (temp <= 0.01*TableSize) ? "passed" : "failed");
  	}
#endif
  	if (temp <= 0.01*TableSize) *failure = 0;
  	else *failure = 1;

	free(Table);

	if (doIO) {
		fprintf( outFile, "-------------------------------------------------------------\n\n");
    		fflush( outFile );
    		fclose( outFile );
  	}
	

  	return 0;

}

void print_help_msg()
{
	printf("Usage:./RandomAccess TotalMemSize(MB) [numThreads] [outFileName=gupsout]\n");
}

int main(int argc, char *argv[])
{
	unsigned long totalMemSize = 0;
	char *outFileName = "gupsout";
	int numThreads = 1;

	double GUPS;
	int faillure;

	if(argc != 2 && argc != 3 && argc != 4)
	{
		fprintf(stderr, "Error: invalid input parameters\n");
		print_help_msg();
		exit(-8);
	}

	totalMemSize = atoi(argv[1]);
	totalMemSize <<= 20;
	
	printf("$$ Get total memory size:%lu MB\n",totalMemSize>>20);

	if(argc == 3)
	{
		numThreads = atoi(argv[2]);
		printf("$$ Get num of threads:%d\n",numThreads);
#ifdef _OPENMP
		omp_set_num_threads(numThreads);
#endif
	}
	
	if(argc == 4)
	{
		outFileName = argv[3];
		printf("$$ Get Out File Name:%s\n", outFileName);
	}	
	//u64Int *test = malloc(totalMemSize * sizeof(u64Int));
	//memset(test, 0, totalMemSize * sizeof(u64Int));
	//free(test);

	RandomAccess_LCG(totalMemSize, 1, outFileName, &GUPS, &faillure);

	if(!faillure)
	{
		printf("$$ Run RandomAccess Successfully, GUPS=%.6f\n", GUPS);
	}	
	else
	{
		fprintf(stderr, "## Run RandomAccess Failed\n");
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