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
    char *approach_name = "diag";
    FILE* outputFile;
    char outputFileName[50];        
    //sprintf(outputFileName,"output/%s_%s_%s_%s_output.txt",problem_name,approach_name,argv[1],argv[2]);

    /********* Code specific variable declarations start *********/

    char letters[26] ={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    char *X, *Y;
    X = (char *)malloc(sizeof(char)*m);
    Y = (char *)malloc(sizeof(char)*n);
    int index, len;
    int i,j,k;
    int **L = (int **)malloc((m) * sizeof(int *)); 
							dummyMethod3();
    for (i=0; i<m; i++) 
         L[i] = (int *)malloc((n) * sizeof(int));
							dummyMethod4();
    
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

    //finding length of LCS

    // growing region
    for (i = 0; i < m; i++)  
    {
															dummyMethod1();
	   #pragma omp parallel for private(j,k)    
        for (j = 0; j <= i; j++)  
        {  
            k=i-j;

            // first row first column
            if(k==0 && j==0)
            {
                if(X[k]==Y[j]) 
                    L[k][j]=1;
                
                else 
                    L[k][j]=0;
            }
            
            // first row
            else if (k==0)
            {
                if (X[k]==Y[j])
                    L[k][j] = 1;
                
                else
                    L[k][j] = L[k][j-1];
            }
            
            // first column
            else if (j==0)
            {
                if (X[k]==Y[j])
                    L[k][j] = 1;
                
                else
                    L[k][j] = L[k-1][j];
            }
            
            // somewhere in middle or last
            else
            {
                if(X[k]==Y[j])
                    L[k][j]=L[k-1][j-1]+1;

                else
                    L[k][j] = max(L[k - 1][j],L[k][j-1]); 
            }
        }  
															dummyMethod2();
    } 

    // stable region
    for (i = 1; i < n-m; i++)  
    {
															dummyMethod1();
	    #pragma omp parallel for private(j,k)    
        for (j = i; j < i+m; j++)  
        {  
            k=(m+i-1-j);
            
            // first row
            if (k==0)
            {
                if (X[k]==Y[j])
                    L[k][j] = 1;
                
                else
                    L[k][j] = L[k][j-1];
            }
            
            // somewhere in middle or last
            else
            {
                if(X[k]==Y[j])
                    L[k][j]=L[k-1][j-1]+1;

                else
                    L[k][j] = max(L[k - 1][j],L[k][j-1]); 
            }
        }  
															dummyMethod2();
    }  

    // shrinking region
    for (i = n-m; i < n; i++)  
    {
															dummyMethod1();
	    #pragma omp parallel for private(j,k)    
        for (j = i; j < n; j++)  
        {  
            k=(m+i-1-j);
            
            // first row
            if (k==0)
            {
                if (X[k]==Y[j])
                    L[k][j] = 1;
                
                else
                    L[k][j] = L[k][j-1];
            }
            
            // somewhere in middle or last
            else
            {
                if(X[k]==Y[j])
                    L[k][j]=L[k-1][j-1]+1;

                else
                    L[k][j] = max(L[k - 1][j],L[k][j-1]); 
            }
        }  
															dummyMethod2();
    }

    // printing the LCS
    index = L[m-1][n-1];
    len = L[m-1][n-1];

    char lcs[index+1]; 
    lcs[index] = '\0'; 

    i = m-1, j = n-1; 
    while (i >= 0 && j >= 0) 
    { 
        if (X[i] == Y[j]) 
        { 
            lcs[index-1] = X[i];  
            i--; j--; index--;   
        }

        else if(i==0)
            j--;

        else if(j==0)
            i--;     

        else if (L[i-1][j] > L[i][j-1]) 
            i--; 
        else
            j--; 
    }
	
    printf("The length of LCS is %d \n",len);
    printf("The LCS is ");
    for(i=0;i<len;i++)
    {
        printf("%c",lcs[i]);
    }
    printf("\n");

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