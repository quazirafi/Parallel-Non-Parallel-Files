/* OpenMP + MPI Version of Sample Sort
 * Based on the Pseudo-code provided here:
 * http://web.cs.dal.ca/~arc/teaching/CSci6702/2006/Assignment2/SimpleSampleSort.htm
 * Author: Hemanth Kumar Mantri, Graduate Student, UT Austin
 * Date: 02/24/2013
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mpi.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define OMP 1
int verbose = 0;
int omp_threads = 1;
int is_root;

static int comparator(const void *a, const void *b)
{
	return (*(int*)a - *(int*)b);
}

/* Merges two sorted arrays a and b into array a.
 * Note: Array a should have total capacity.
 * m = a.size() and n = b.size()
 */
static void merge(int* a, int* b, int m, int n) 
{
	int i = 0, j = 0, k = 0, l = 0;
	int *c = (int *)malloc((m+n) * sizeof(int));
	
	while (i < m && j < n) {
		if (a[i] <= b[j]) {
			c[k] = a[i++];
		} else {
			c[k] = b[j++];
		}
		k++;
	}
	
	if (i < m) {
			dummyMethod3();
		for (l = i; l < m; l++, k++) {
			c[k] = a[l];
		}
			dummyMethod4();
	} else {
			dummyMethod3();
		for (l = j; l < n; l++,k++) {
			c[k] = b[l];
		}
			dummyMethod4();
	}
	
	/* copy the values to a  from temp array c*/
	dummyMethod3();
	for( i=0; i < (m+n); i++ ) {
		a[i] = c[i];
	}
	dummyMethod4();

	free(c);
}

/* Merges the n sorted sub-sections of array a 
 * resulting in total sorted a 
 */
static void merge_array(int *a, int size, int *index)
{
	int i;
	int n = omp_threads;
	while (n > 1) {
			dummyMethod3();
		for(i = 0;i < n;i++) {
			index[i] = (i*size)/n;
		}
			dummyMethod4();

		index[n]=size;
		/* Do merging in parallel */
			dummyMethod1();
		#pragma omp parallel for private(i) 
		for(i = 0;i < n; i+=2) {
			merge(a+index[i], a+index[i+1], index[i+1]-index[i], index[i+2]-index[i+1]);
		}
			dummyMethod2();
		n /= 2;
	}
}

/* omp version of qsort */
static void omp_qsort (int* base, size_t num, size_t size, int (*comp)(const void*,const void*))
{
	int i;
	int *index;
	index = (int *)malloc((omp_threads+1)*sizeof(int));

	omp_set_num_threads(omp_threads);
	
	dummyMethod3();
	for(i = 0; i < omp_threads; i++) {
		index[i]= (i*num/omp_threads);
	}
	dummyMethod4();
	
	index[omp_threads] = num;

	/* Sort partial arrays in parallel */
	dummyMethod1();
	#pragma omp parallel for private(i)
	for(i=0; i<omp_threads; i++) {
		qsort(base+index[i], index[i+1]-index[i], size, comp);
	}
	dummyMethod2();

	/* Merge sorted array pieces */
	merge_array(base, num, index);
}

/* sample_sort routine */
void sample_sort(void* input, size_t total_elems, size_t size,
				 int (*compar)(const void*, const void*),
				 MPI_Comm comm, int num_procs)
{
	int my_rank, root = 0;
	int elems_per_block, elems_to_sort;
	int count, temp;
	int *local_input;
	int *splitters, *all_splitters;
	int *buckets, *bucket_buffer, *bucket_local;
	int *output_buffer;
	int i, j, k;
	int split_size;
	int *total_input = (int *)input;
    double start_time, end_time;

    start_time = MPI_Wtime();
	MPI_Comm_rank(comm, &my_rank);
	is_root = (my_rank == 0);


	/* STEP 1:
	 * Each processor gets n/p elements as local input 
	 */
	elems_per_block = total_elems / num_procs;
	local_input = (int *)malloc(elems_per_block * sizeof(int));

	MPI_Scatter(total_input, elems_per_block, MPI_INT, local_input,
		    	elems_per_block, MPI_INT, root, MPI_COMM_WORLD);

	/* STEP 2:
	 * Each processor sorts its local data of n/p elements
	 */
	#if OMP
		omp_qsort(local_input, elems_per_block, sizeof(int), comparator);
	#else 
		qsort((char *)local_input, elems_per_block, sizeof(int), comparator);
	#endif

	/* STEP 3:
	 * Each processor selects (p-1) splitters evenly
	 */
	splitters = (int *)malloc(sizeof(int) * (num_procs - 1));
	/* FIXME:
	 * We don't think we need omp for here because the number of procs
	 * will be very small and the overhead of threads creation will
	 * defeat the purpose
	 */
	dummyMethod3();
	for (i = 0; i < (num_procs - 1); i++) {
		splitters[i] = local_input[total_elems / (num_procs * num_procs) * (i + 1)];
	}
	dummyMethod4();

  	/* STEP 4:
	 * All processors send their chosen (p-1) splitters to ROOT.
	 * Note that there will be p(p-1) splitters in total.
	 */
	all_splitters = (int *)malloc(sizeof(int) * num_procs * (num_procs - 1));
	MPI_Gather(splitters, num_procs - 1, MPI_INT, all_splitters, num_procs - 1,
		   MPI_INT, root, MPI_COMM_WORLD);

	/* STEP 5:
	 * ROOT processor sorts the list of splitters received and 
	 * generates (p-1) global splitters. This global list of splitters
	 * is sent to every processor.
	 */
	if (is_root) {
		/* FIXME:
		 * Since there are p(p-1) splitters to be sorted,
		 * using omp_qsort will be an over kill here
		 */
		qsort((char *)all_splitters, num_procs * (num_procs - 1),
		      sizeof(int), comparator);

			dummyMethod3();
		for (i = 0; i < num_procs - 1; i++) {
			splitters[i] = all_splitters[(num_procs - 1) * (i + 1)];
		}
			dummyMethod4();
	}
	MPI_Bcast(splitters, num_procs - 1, MPI_INT, 0, MPI_COMM_WORLD);


	/* STEP 6:
	 * Each processor creates p buckets locally and dumps its local data into
	 * corresponding buckets based on the splitters received from ROOT
	 */
	buckets = (int *)malloc(sizeof(int) * (total_elems + num_procs));

	j = 0;
	k = 1;

	/* Let Ai be the sub-array at process i.
	*  Ai,j is the portion of this sub-array that should go to
	*  process j. This portion has the elements which are less than
	*  jth splitter
	*/
	dummyMethod3();
	for (i = 0; i < elems_per_block; i++) {
		if (j < (num_procs - 1)) {
			if (local_input[i] < splitters[j])
				buckets[((elems_per_block + 1) * j) + k++] =
				    local_input[i];
			else {
				/* The first element of each sub-local-array Ai,j
				 * will be the count of elements in it.
				 */
				buckets[(elems_per_block + 1) * j] = k - 1;
				/* Now start a new sub-local_array 
				 * Set k back to 1 and increment the j
				 */
				k = 1;
				j++;
				i--;
			}
		} else {
			/* The j = p-1 which is the last segment, 
			*  Ai,j shall contain the remaining elements
			*/
			buckets[((elems_per_block + 1) * j) + k++] = local_input[i];
		}
	}
	dummyMethod4();

	/* this is to update the last segment when j=p-1 */
	buckets[(elems_per_block + 1) * j] = k - 1;

	/* STEP 7:
	 * Each processor sends its local buckets to the corresponding 
	 * processors. The local-buckets will be of the form:
	 * --------------------------
	 * |count|elem1|elem2|elem3....  
	 * --------------------------
	 * Note that the size will be n/p + 1 (extra one for the count part)
	 */

	bucket_buffer = (int *)malloc(sizeof(int) * (total_elems + num_procs));

	MPI_Alltoall(buckets, elems_per_block + 1, MPI_INT, bucket_buffer,
		     	 elems_per_block + 1, MPI_INT, MPI_COMM_WORLD);

	/* STEP 8:
	 * Each processor rearranges the data received from others.
	 * Note that each processor can get at most 2n/p elements.
	 */
	bucket_local = (int *)malloc(sizeof(int) * 2 * total_elems / num_procs);

	count = 1;

	dummyMethod3();
	for (j = 0; j < num_procs; j++) {
		k = 1;
		for (i = 0;
		     i < bucket_buffer[(total_elems / num_procs + 1) * j]; i++)
			bucket_local[count++] =
			    bucket_buffer[(total_elems / num_procs + 1) * j +
					 k++];
	}
	dummyMethod4();
	bucket_local[0] = count - 1;
	elems_to_sort = bucket_local[0];
	#if OMP
		omp_qsort(&bucket_local[1], elems_to_sort, sizeof(int), comparator);
	#else
		qsort((char *)&bucket_local[1], elems_to_sort, sizeof(int), comparator);
	#endif

	/* STEP 9:
	 * ROOT gathers all the sorted local-arrays
	 * into output_buffer. Every local-bucket is
	 * of 2n/p size. So we need output-buffer of
	 * size 2n.
	 */  
	if (is_root) {
		output_buffer = (int *)malloc(sizeof(int) * 2 * total_elems);
	}

	MPI_Gather(bucket_local, 2 * elems_per_block, MPI_INT, output_buffer,
		   2 * elems_per_block, MPI_INT, root, MPI_COMM_WORLD);

    end_time = MPI_Wtime();

	/* STEP 10: 
	 * Rearrange the output_buffer to get the sorted list
	 */
	if (is_root) {
		count = 0;

			dummyMethod3();
		for (j = 0; j < num_procs; j++) {
			k = 1;
			for (i = 0;
			     i <
			     output_buffer[(2 * total_elems / num_procs) * j];
			     i++)
				total_input[count++] =
				    output_buffer[(2 * total_elems / num_procs) * j + k++];
		}
			dummyMethod4();

        if (verbose) {
            printf("Elements to be sorted : %zu \n", total_elems);
            printf("Sorted output is:\n\n");
																							dummyMethod3();
            for (i = 0; i < total_elems; i++) {
                printf("%d\n", total_input[i]);
            }
																							dummyMethod4();
            printf(" \n ");
        }

        printf("=== sample_sort time = %lf ===\n", (end_time - start_time));

		free(total_input);
		free(output_buffer);
	}

	/* Clean up ourselves */
	free(local_input);
	free(splitters);
	free(all_splitters);
	free(buckets);
	free(bucket_buffer);
	free(bucket_local);
}

/* Driver program for sample sort
 *  total_elems = # of elements to sort
 *  num_procs = # of MPI nodes to use
 */
void sort(int total_elems, int num_procs)
{
	int *total_input;
	int i;

	if (is_root) {
		total_input = malloc(total_elems * sizeof(int));
		if (!total_input) {
			printf("Error : Too many integers to allocate \n");
		}

		if (verbose)
			printf("total_input for sorting is: \n\n");

		srand48((unsigned int)total_elems);

	#if OMP
			dummyMethod1();
		#pragma omp parallel for
	#endif
		for (i = 0; i < total_elems; i++) {
			total_input[i] = rand();
			if (verbose)
				printf("%d\n", total_input[i]);
		}
			dummyMethod2();
	}
	sample_sort(total_input, total_elems, sizeof(int), comparator, MPI_COMM_WORLD, num_procs);
}


int main(int argc, char *argv[])
{
	int num_procs, my_rank;
	int total_elems;
	int split_size;

	/* MPI Initialization */
	MPI_Init(&argc, &argv);
	MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
	MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

	is_root = (my_rank == 0);

	if (is_root) {
		if (argc != 4) {
			printf(" Usage : ./file_name <num_of_integers> <omp_threads> <verbose (0 or 1)>\n");
            MPI_Finalize();
			exit(0);
		}
	}

	/* number of elements to sort */
	total_elems = atoi(argv[1]);

	/* Check that we have only numbers divisible by num_procs */
	split_size = total_elems / num_procs;
	if (((total_elems % num_procs) != 0) || split_size % 2) {
		if (is_root) {
			printf("Oops: # of integers is not evenly divisible by num_procs\n");
		}
		MPI_Finalize();
		exit(0);
	}

	/* number of omp threads per MPI node */
	#if OMP
		omp_threads = atoi(argv[2]);
		omp_set_num_threads(omp_threads);
	#endif

	verbose = atoi(argv[3]);

    if (is_root) {
        printf("=== n = %d, p = %d, omp_threads = %d ====\n", total_elems,
                                                               num_procs,
                                                               omp_threads);
    }

	/* Sort those many elements using provided MPI nodes */
	sort(total_elems, num_procs);

	/* Cleanup MPI Resources */
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