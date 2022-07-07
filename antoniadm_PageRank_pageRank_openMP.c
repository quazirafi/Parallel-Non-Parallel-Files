#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include "omp.h"
#include <math.h>
#include <stdbool.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define MAXITER 500
#define ALPHA 0.85
#define TOLERANCE 0.001
#define DEFAULT_PATH "./datasets/Wiki-Vote.txt" //Default path if no path argument
#define DEFAULT_THREADS 4                       //Default if no threads argument
#define DEFAULT_NODES 8298                      

void uniform(double *x, int n);
bool checkConv(double x, double y, double e);

typedef struct
{
    int outDeg;
    int inDeg;
    int *fromId;
    int iters;
   
} Node;

/** The main program **/
int main(int argc, char **argv)
{    
    char *path;
    int threads = DEFAULT_THREADS; // number of threads
    int N = DEFAULT_NODES;
    double a = ALPHA;
    int tol = TOLERANCE;
    /*** Check input arguments ***/
     if (argc == 2 || argc >  5)
    {
        printf("Usage: %s FILEPATH NODES THREADS DAMPING_FACTOR(0.85) TOLERANCE(0.001)\n", argv[0]);
        exit(1);
    }
    if (argc == 1) //Default load file
        path = DEFAULT_PATH;
    if (argc > 1)
        path = strdup(argv[1]); // path of the dataset
    if (argc > 2)
        N = atoi(argv[2]); //Number of nodes
    if (argc > 3)
        threads = atoi(argv[3]); //Number of threads
    if (argc > 4)
        a = atoi(argv[4]); // Dumping factor
    if (argc > 4)
        tol = atoi(argv[5]); // Tolerance
 
    /** Declarations/Initializations **/
    Node *Nodes;
    double *rank;
    int iter;
    double  tempK;
    FILE *fgraph;
    char graph_file[1000];
    int i, j;
    int convPages = 0;
    int *iters;
    int maxiter = MAXITER;
    double aCmpt;
    aCmpt = 1 - a;
    struct timeval start, end;
    double openmp_time;
    int notZero, zeroRows;
    int from, to;

    /*** Set number of threads ***/
    omp_set_num_threads(threads);

    printf("PageRank OpenMP implementation\n");
    printf("Number of threads: %d\n", threads);

    Nodes = (Node *)malloc(N * sizeof(Node));
    rank = (double *)malloc(N* sizeof(double));

							dummyMethod1();
  #pragma omp parallel for private(i) shared(Nodes)
    for (i = 0; i < N; i++)
    {
        Nodes[i].outDeg=0;
        Nodes[i].inDeg=0;
        
        Nodes[i].fromId = (int *)calloc(1, sizeof(int));
    }
							dummyMethod2();

    sprintf(graph_file, "%s", path);

    fgraph = fopen(graph_file, "r");
    if (fgraph == NULL)
    {
        printf("ERROR: Cant open file %s\n", graph_file);
        exit(1);
    }

    while (!feof(fgraph))
    {
        if (fscanf(fgraph, "%d %d\n", &from, &to) != 2)
            continue;

        if(Nodes[to].inDeg == 0) notZero++; // Count pages with no inbound links
        Nodes[from].outDeg++;
        Nodes[to].inDeg++;
        
      /**  if ((Nodes[from].toId = (int *)realloc(Nodes[from].toId, (Nodes[from].outDeg) * sizeof(int))) == NULL)
        {
            printf("\n Error");
            exit(1);
        }**/

        if ((Nodes[to].fromId = (int *)realloc(Nodes[to].fromId, (Nodes[to].inDeg) * sizeof(int))) == NULL)
        {
            printf("\n Error reallocating memory");
            exit(1);
        }


        //Nodes[from].toId[(Nodes[from].outDeg - 1)] = to;
        Nodes[to].fromId[(Nodes[to].inDeg - 1)] = from;
    }
    printf("Total nodes = %d \n", N);

    zeroRows = N - notZero; // Number of zero inbound link pages

    gettimeofday(&start, NULL);

    /**** Start of the main algorithm ***/
    uniform(rank, N); // Initialize x

    iter = 0;

    int index;
    double sum;

    do
    { 
															dummyMethod1();
       #pragma omp parallel for private(i, tempK,j,index,sum) shared(Nodes,rank,iter,convPages)
        for (i = 0; i < N; i++)
        {

        sum = 0;
            if (Nodes[i].iters != 0)  continue; //If page i has converged, continue
         
            tempK = rank[i];
      
           if (Nodes[i].inDeg != 0) {
            for (j = 0; j < Nodes[i].inDeg; j++)
            {
                
               index = Nodes[i].fromId[j];
               
                        sum += (rank[index]) / (Nodes[index].outDeg);
            }
           }
           else { sum = 1/N;}

       
             rank[i] = aCmpt + (a * sum); // Gauss-Seidel because we save xi(k+1) at the same matrix as xi(k), (j<i -> xj(k+1), j>i -> xj(k))  )
                 
               if (checkConv(tempK,rank[i], tol) == true)
            {
                  
                Nodes[i].iters = iter +1; // Number of iterations for page i convergence
                convPages++;
            }
             
        }
															dummyMethod2();

     iter++;
   
    } while ((iter < MAXITER) && (convPages < N));

    /**** End of the main algorithm ***/
    if (convPages < N)
        printf("The PageRank algorithm did not converge after %i iterations", iter);
    gettimeofday(&end, NULL);

    /**** Printing Results ***/
    openmp_time = (double)((end.tv_usec - start.tv_usec) / 1.0e6 + end.tv_sec - start.tv_sec);
    printf("\nOpenMP PageRank wall clock time = %f seconds \n", openmp_time);

    /*** Find max page rank *****/
    int maxi = 0;
    double max = rank[0];
    sum = 0;
       /** Normalize **/
							dummyMethod3();
    for (i = 0; i < N; i++)
    {
        sum+=rank[i];
    }
							dummyMethod4();
 
							dummyMethod3();
    for (i = 0; i < N; i++)
    {
        rank[i]=rank[i]/sum;
  
    }
							dummyMethod4();

    /** Show calculated pagerank of the last 100 pages
     for (i = N-100; i < N; i++)
   {
      printf("PR[%d] = %f\n",i,rank[i]);
   }
   printf("\n"); **/
   
      printf("\n*** END ***");
    return 0;
}


/*** Column vector representing a uniform probability distribution over allnodes ***/
void uniform(double *y, int n)
{
    int i;
    double invN = 1.0 / n;
							dummyMethod1();
#pragma omp parallel for private(i) shared(y)
    for (i = 0; i < n; ++i)
        y[i] = invN;
							dummyMethod2();
}

bool checkConv(double xk, double xk1, double e)
{
    
    if (((xk1 - xk) / xk) <= e)
        return true;
    return false;
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