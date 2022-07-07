/******************************************************************************
 * Parallelization:  Sieve of Eratosthenes
 * By Aaron Weeden, The Shodor Education Foundation, Inc.
 *
 * Hybrid MPI+OpenMP code
 *  -- to run, use ./sieve.exe -n N, where N is the value under which to find
 *     primes.
 *  -- to list the primes, include the -o option.
 *  -- see http://shodor.org/petascale/materials/UPModules/sieveOfEratosthenes/
 *     for module document with discussion of the code and its algorithm
 *****************************************************************************/
#include <math.h> // for sqrt
#include <mpi.h> // for calls that start with MPI_
#include "omp.h"
#include <stdbool.h> // for true and false
#include <stdio.h> // for printf
#include <stdlib.h> // for malloc and free
#include <unistd.h> // for getopt
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char **argv)
{
  // Declare variables
  int N = 16; // The positive integer under which we are finding primes
  int sqrtN; // The square root of N, which is stored in a variable to
             // avoid making excessive calls to sqrt(N)
  int c; // Used to check the next number to be circled
  int m; // Used to check the next number to be marked
  int *list1; // The list of numbers <= sqrtN -- if list1[x] equals 1, then x 
              // is marked. If list1[x] equals 0, then x is unmarked.
  int *my_list2; // The list of numbers > sqrtN -- if list2[x - low] is marked,
                 // then x is marked.  If list2[x - low] equals 0, then x is
                 // unmarked.
  char next_option = ' '; // Used for parsing command line arguments
  double startTime = omp_get_wtime(); // Start the timer
  bool is_printing = false; // Decide whether to print the primes
  int split; // A near-as-possible even split of the count of numbers above 
             // sqrtN
  int remainder; // The remainder of the near-as-possible even split
  int low; // The lowest number in the current process' split
  int high; // The highest number in the current process' split
  int my_rank; // The rank of the current process
  int their_rank; // The rank of another process
  int num_procs; // The total number of processes
  int list1_size; // The number of elements in list1
  int list2_size; // The number of elements in the overall list2
  int max_list2_size; // The max number of elements in a process' list2
  int my_list2_size; // The number of elements in the current process' list2
  int their_low; // Lowest number in a split from another process, received
                 // at the end
  int their_high; // Highest number in a split from another process, received
                  // at the end
  int their_list2_size; // The number of elements received by another process
                        // at the end
  int *their_list2; // List of numbers received by another process at the
                    // end 
  
  // Initialize the MPI Environment
  MPI_Init(&argc, &argv);
  
  // Determine the rank of the current process and the number of processes
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);
   
  // Parse command line arguments -- see the manual page for getopt
  while((next_option = getopt(argc, argv, "n:o")) != -1)
  {
    switch(next_option)
    {
      case 'n':
        N = atoi(optarg);
        break;
      case 'o':
        is_printing = true;
        break;
      case '?':
      default:
        fprintf(stderr, "Usage: %s [OPTIONS]\n",
          "-n N, where N is the number under which to find primes\n"
          "-o to print out the primes after they have been found\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }
  
  // Calculate size of list1
  sqrtN = (int)sqrt(N);
  list1_size = sqrtN + 1;
  
  // Divvy up list2
  list2_size = N - list1_size;
  split = list2_size / num_procs;
  remainder = list2_size % num_procs;
  low = list1_size + my_rank * split;
  high = low + split - 1;
  if(my_rank == num_procs - 1)
  {
    high += remainder;
  }
  my_list2_size = high - low + 1;
  max_list2_size = split + remainder;
  
  // Allocate memory for lists
  list1 = (int*)malloc(list1_size * sizeof(int));
  my_list2 = (int*)malloc(my_list2_size * sizeof(int));
  if(my_rank == 0)
  {
    their_list2 = (int*)malloc(max_list2_size * sizeof(int));
  }
  
  // Exit if malloc failed
  if(list1 == NULL)
  {
    fprintf(stderr, "Error: Failed to allocate memory for list1.\n");
    exit(EXIT_FAILURE);
  }
  if(my_list2 == NULL)
  {
    fprintf(stderr, "Error: Failed to allocate memory for my_list2.\n");
    exit(EXIT_FAILURE);
  }
  if(my_rank == 0 && their_list2 == NULL)
  {
    fprintf(stderr, "Error: Failed to allocate memory for their_list2.\n");
    exit(EXIT_FAILURE);
  }
  // Run through each number in list1
			dummyMethod1();
#pragma omp parallel for private(c)
  for(c = 2; c <= sqrtN; c++)
  {
    // Set each number as unmarked
    list1[c] = 0;
  }
			dummyMethod2();
  // Run through each number in my_list2
			dummyMethod1();
#pragma omp parallel for private(c)
  for(c = low; c <= high; c++)
  {
    // Set each number as unmarked
    my_list2[c - low] = 0;
  }
			dummyMethod2();
  // Run through each number in list1
  for(c = 2; c <= sqrtN; c++)
  {
    // If the number is unmarked
    if(list1[c] == 0)
    {
      // Run through each number bigger than c in list1
											dummyMethod1();
#pragma omp parallel for private(m)
      for(m = c+1; m <= sqrtN; m++)
      {
        // If m is a multiple of c
        if(m % c == 0)
        {
          // Mark m
          list1[m] = 1;
        }
      }
											dummyMethod2();
      // Run through each number bigger than c in my_list2
											dummyMethod1();
#pragma omp parallel for private(m)
      for(m = low; m <= high; m++)
      {
        // If m is a multiple of c
        if(m % c == 0)
        {
          // Mark m
          my_list2[m - low] = 1;
        }
      }
											dummyMethod2();
    }
  }
  // If Rank 0 is the current process
  if(my_rank == 0)
  {
    // Run through each of the numbers in list1
    for(c = 2; c <= sqrtN; c++)
    {
      // If the number is unmarked
      if(list1[c] == 0)
      {
        // The number is prime; print it
        if(is_printing)
        {
          printf("%d ", c);
        }
      }
    }
    // Run through each of the numbers in my_list2
    for(c = low; c <= high; c++)
    {
      // If the number is unmarked
      if(my_list2[c - low] == 0)
      {
        // The number is prime; print it
        if(is_printing)
        {
          printf("%d ", c);
        }
      }
    }
    // Run through each of the other processes
    for(their_rank = 1; their_rank < num_procs; their_rank++)
    {
      // Receive data from the process about their_list2
      MPI_Recv(&their_low, 1, MPI_INT, their_rank, 0,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Recv(&their_high, 1, MPI_INT, their_rank, 1,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Recv(&their_list2_size, 1, MPI_INT, their_rank, 2,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      MPI_Recv(their_list2, their_list2_size, MPI_INT, their_rank, 3,
               MPI_COMM_WORLD, MPI_STATUS_IGNORE);
      
      // Run through the list2 that was just received
      for(c = their_low; c <= their_high; c++)
      {
        // If the number is unmarked
        if(their_list2[c - their_low] == 0)
        {
          // The number is prime, print it
          if(is_printing)
          {
            printf("%d ", c);
          }
        }
      }
    }
    if(is_printing)
    {
      printf("\n");
    }
  }
  // If the process is not Rank 0
  else
  {
    // Send data to Rank 0 about my_list2
    MPI_Send(&low, 1, MPI_INT, 0, 0, MPI_COMM_WORLD);
    MPI_Send(&high, 1, MPI_INT, 0, 1, MPI_COMM_WORLD);
    MPI_Send(&my_list2_size, 1, MPI_INT, 0, 2, MPI_COMM_WORLD);
    MPI_Send(my_list2, my_list2_size, MPI_INT, 0, 3, MPI_COMM_WORLD);
  }
  // Deallocate memory for lists
  if(my_rank == 0)
  {
    free(their_list2);
  }
  free(my_list2);
  free(list1);
  
  // Finalize the MPI environment
  MPI_Finalize();
  
  // Print the runtime
  if(my_rank == 0)
  {
    printf("Runtime: %f seconds\n", omp_get_wtime() - startTime); 
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