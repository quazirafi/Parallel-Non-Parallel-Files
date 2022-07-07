#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
    int *Vector;
    int *result;
    int **matrix;
    int SZ_Vector,rows,cols;/*number of Rows of Vector And 2D of Matrix */

    void print_VC()
{
    int i;
dummyMethod3();
    for(i=0; i<SZ_Vector; i++)
    {
        if(i== SZ_Vector/2 )
           {
               printf("V = ");
               printf("|%d| \n",Vector[i]);
           }
        else
            printf("    |%d| \n",Vector[i]);
    }
dummyMethod4();
    printf("\n\n");

}
void printMX()
{
    int i,j;
							dummyMethod3();
    for(i=0;i<rows;i++)
    {
        if(i==rows/2)
            {
                printf("M = | ");
            }
        else
            printf("    | ");
        for(j=0;j<cols;j++)
            printf(" %d ",matrix[i][j]);
        printf(" |\n");
    }
							dummyMethod4();


    printf("\n\n");
}

void Vector_Input()
{
    Vector=malloc(SZ_Vector*sizeof(int));
    int i;
    printf("Enter The Elements of Vector \n");
							dummyMethod3();
    for(i=0; i<SZ_Vector; i++)
    {
        scanf("%d",&Vector[i]);
    }
							dummyMethod4();
}

void Matrix_Input()
{

    //printf("Number of ROWS And Number of COLUMNS are %d    %d  \n",rows,cols);
    int i,c,r;
    matrix=malloc(rows*sizeof(int *));
							dummyMethod3();
    for(i=0;i<rows;i++)
        matrix[i]=malloc(cols*sizeof(int));
							dummyMethod4();
    printf("Enter The Elements of Matrix \n");
    i=0;
							dummyMethod3();
    for(r=0; r<rows; r++)
    {

        for(c=0;c<cols;c++)
            scanf("%d",&matrix[r][c]);
    }
							dummyMethod4();
}
int main()
{
        while(1)
        {
            printf(" \nenter number of Rows Of The Vector\n");
            scanf("%d",&SZ_Vector);
            printf("Enter Number of ROWS And Number of COLUMNS \n");
            scanf(" %d %d",&rows,&cols);
            if(cols==SZ_Vector)
            {
                Vector_Input();
                Matrix_Input();
                result=malloc(rows*sizeof(int));
                int x;
																															dummyMethod3();
                for(x=0;x<rows;x++)
                    result[x]=0;
																															dummyMethod4();
                int i,j;
																															dummyMethod1();
                #pragma omp parallel for private(i , j) shared (matrix,Vector,result)
                for(i=0;i<rows;i++)
                {
                    for(j=0;j<cols;j++)
                        {
                            result[i]+=(matrix[i][j]*Vector[j]);
                        }
                }
																															dummyMethod2();
                print_VC();
                printMX();
                int count;
																															dummyMethod3();
                for(count=0;count<rows;count++)
                {
                  if(count== SZ_Vector/2 )
                       {
                           printf("Result_Vector = ");
                           printf("|%d| \n",result[count]);
                       }
                    else
                        printf("                |%d| \n",result[count]);
                }
																															dummyMethod4();
           }
            else
               {
                printf("Invalid Multiplication ' Number of columns of matrix must be equal the number of rows of vector \n");
                printf(",please try again \n");
               }

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