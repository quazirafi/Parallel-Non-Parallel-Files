/*
    Parallel implementation of matrix multiplication using OpenMP
    compile using: 
        gcc -fopenmp  parallel_matrix.c
*/
#include<stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// prints the matrix
void matrix_print(int p, int q, int m[][q])
{
    int i,j;
dummyMethod3();
    for(i = 0; i < p; i++)
    {
        for(j = 0; j<q; j++)
        {
            printf("%d\t", m[i][j]);
        }
        printf("\n");
    }
dummyMethod4();
}

int main()
{
    int m,n,p,q;
    int i, j, k, sum;
   
     
    //Manual user input
    printf("Enter the rows and column of the first matrix: ");
    scanf("%d%d", &m, &n);
    printf("Enter the rows and column of the second matrix: ");
    scanf("%d%d", &p, &q);
    if(n!=p)
    {
        printf("Product is not possible");
        return 1;
    }
    
    int first[m][n], second[p][q], product[m][q];
    printf("Enter elements of the first matrix: ");
							dummyMethod3();
    for(i = 0; i < m; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &first[m][n]);
							dummyMethod4();
    
    printf("Enter elements of the second matrix: ");
							dummyMethod3();
    for(i = 0; i < m; i++)
        for(j = 0; j < n; j++)
            scanf("%d", &second[m][n]);
							dummyMethod4();
    
    


    //test values
    /*
    m = n = p = q = 3;
    
    int first[][3] = {
        1,2,3,
        4,5,6,
        7,8,9
    };

    int second[][3] = {
        3,2,3,
        4,4,1,
        1,1,2
    };
    // product is
    // 14	13	11	
    // 38	34	29	
    // 62	55	47
    */

    int product[m][q];

   
    
    // The since each element product doesn't depend upon a the previous iteration, the iterations
    // are equally distributed among the processors
							dummyMethod1();
    #pragma omp parallel for private(i,j,k,sum) shared(first,second,product)
    for(i = 0; i < m; i++)
    {
        for(j = 0; j < q; j++)
        {
            sum = 0;
            for(k = 0; k < p; k++)
                sum += first[i][k] * second[k][j];
            product[i][j] = sum;
        }
    }
							dummyMethod2();


    printf("Product is: \n");
    matrix_print(m, q, product);

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