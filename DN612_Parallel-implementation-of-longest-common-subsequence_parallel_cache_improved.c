#include<stdio.h>
#include<math.h>
#include "omp.h"
#include<time.h>
#include<string.h>
#include<stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// Function to find min and max
#define min(x, y) (((x) < (y)) ? (x) : (y))
#define max(x, y) (((x) >= (y)) ? (x) : (y))

// Using the MONOTONIC clock 
#define CLK CLOCK_MONOTONIC

// Function to compute the difference between two points in time 
struct timespec diff(struct timespec start, struct timespec end);
 
// Function to computes the difference between two time instances
struct timespec diff(struct timespec start, struct timespec end)
{
    struct timespec temp;
    if((end.tv_nsec-start.tv_nsec)<0)
    {
        temp.tv_sec = end.tv_sec-start.tv_sec-1;
        temp.tv_nsec = 1000000000+end.tv_nsec-start.tv_nsec;
    }
    else
    {
        temp.tv_sec = end.tv_sec-start.tv_sec;
        temp.tv_nsec = end.tv_nsec-start.tv_nsec;
    }
    return temp;
}

/* ................main function starts........................*/

int main(int argc, char* argv[])
{
    struct timespec start_e2e, end_e2e, start_alg, end_alg, e2e, alg;

    // Start end2end time for code
    clock_gettime(CLK, &start_e2e);

    // Check if enough command-line arguments are taken in. 
    if(argc < 3)
    {
        printf( "Usage: %s n p \n", argv[0] );
        return -1;
    }

    // size of input strings
    int n=atoi(argv[1]);
    int m=n-2;

    // number of processors 
    int p=atoi(argv[2]);

    char *problem_name = "lcs";
    char *approach_name = "cache2";
    FILE* outputFile;
    char outputFileName[50];        
    //sprintf(outputFileName,"output/%s_%s_%s_%s_output.txt",problem_name,approach_name,argv[1],argv[2]);

    /********* Code specific variable declarations start *********/

    char letters[26] ={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char *X, *Y;
    X = (char *)malloc(sizeof(char)*m);
    Y = (char *)malloc(sizeof(char)*n);
    int i,j,k,x;
    int *a[3];
    a[0] = (int *)malloc(sizeof(int)*(m));
    a[1] = (int *)malloc(sizeof(int)*(m));
    a[2] = (int *)malloc(sizeof(int)*(m));
    
							dummyMethod3();
    for (i=0;i<m;i++)
    {
        X[i]=letters[rand() % 26];
        //printf("%c",X[i]);
    }
							dummyMethod4();
    //printf("\n");
							dummyMethod3();
    for (i=0;i<n;i++)
    {
        Y[i]=letters[rand() % 26];
        //printf("%c",Y[i]);
    }
							dummyMethod4();
    //printf("\n");

    //always make X the smaller string so rows <= columns in score matrix
    if(m>n)
    {
        char *temp;
        temp = (char *)malloc(sizeof(char)*m);
        strcpy(temp,X);
        strcpy(X,Y);
        strcpy(Y,temp);
        m=strlen(X);     
        n=strlen(Y);
    }


    /********* Code specific variable declarations end *********/
    
    // Set number of threads
    omp_set_num_threads(p);

    // Start algo timer
    clock_gettime(CLK, &start_alg); 

    /*-------------- Core algorithm starts here --------------------*/

    //growing region
    for (i = 0; i < m; i++)
    {
															dummyMethod1();
        #pragma omp parallel for private(j,k,x)
        for (j = 0; j <= i; j++)
        {
            k=i-j;
            x=i%3;
            
            // first row first column
            if(k==0 && j==0)
            {
                if(X[k]==Y[j])
                    a[x][j]=1;
                
                else
                    a[x][j]=0;
            }

            // first row
            else if (k==0)
            {
                if (X[k]==Y[j])
                    a[x][j] = 1;
                
                else
                    a[x][j] = a[(i-1)%3][j-1];
            }

            // first column
            else if (j==0)
            {
                if (X[k]==Y[j])
                    a[x][j] = 1;

                else
                    a[x][j] = a[(i-1)%3][j];
            }

            // somewhere in middle or last
            else 
            {
                if (X[k]==Y[j])
                    a[x][j]=a[(i-2)%3][j-1]+1;
                
                else
                    a[x][j] = max(a[(i-1)%3][j],a[(i-1)%3][j-1]);
            }
        }
															dummyMethod2();
    }

    // stable region
    for (i = 1; i < n-m; i++)
    {
															dummyMethod1();
        #pragma omp parallel for private(j,k,x)
        for (j = i; j < i+m; j++)
        {
            k=(m+i-1-j);
            x=(m-1+i)%3;

            // first row
            if (k==0)
            {
                if (X[k]==Y[j])
                    a[x][j-i] = 1;

                else
                    a[x][j-i] = a[(m-1+i-1)%3][j-i];
            }

            // somewhere in middle or last
            else 
            {
                if (X[k]==Y[j])
                {
                    if(i==1)
                        a[x][j-i]=a[(m-1+i-2)%3][j]+1;
                    else
                        a[x][j-i]=a[(m-1+i-2)%3][j+1]+1;
                }
                
                else
                     a[x][j-i] = max(a[(m-1+i-1)%3][j-i+1],a[(m-1+i-1)%3][j-i]);
            }
        }
															dummyMethod2();
    }


    // shrinking region
    int ind=-1;
    for (i = n-m; i < n; i++)
    {
        ind+=1;
															dummyMethod1();
        #pragma omp parallel for private(j,k,x)
        for (j = i; j < n; j++)
        {
            k=(m+i-1-j);
            x=(n-1+ind)%3;
            
            // first row
            if (k==0)
            {
                if (X[k]==Y[j])
                    a[x][j-i] = 1;

                else
                    a[x][j-i] = a[(n-1+ind-1)%3][j-i];
            }

            // somewhere in middle or last
            else 
            {
                if (X[k]==Y[j])
                    a[x][j-i]=a[(n-1+ind-2)%3][j-i+1]+1;

                else
                    a[x][j-i] = max(a[(n-1+ind-1)%3][j-i+1],a[(n-1+ind-1)%3][j-i]);
            }
        }
															dummyMethod2();
    }

     printf("The length of LCS is %d \n", a[(n+m-2)%3][0]);

    /*-------------- Core algorithm ends here --------------------*/

    // End algo timer
    clock_gettime(CLK, &end_alg);

    // End end2end time for code
    clock_gettime(CLK, &end_e2e);

    e2e = diff(start_e2e, end_e2e);
    alg = diff(start_alg, end_alg);
    //printf("%s,%s,%d,%d,%d,%ld,%d,%ld\n", problem_name, approach_name, n, p, e2e.tv_sec, e2e.tv_nsec, alg.tv_sec, alg.tv_nsec);

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