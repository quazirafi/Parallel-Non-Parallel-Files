//
//  main.c
//  MatMultiply(openMp)
//
//  Created by Ahmed masoud on 5/6/16.
//  Copyright © 2016 Ahmed masoud. All rights reserved.
//

# include <stdio.h>
# include <stdlib.h>
#include <time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();



int main()
{
    
    int MAT1[10][10];
    int MAT2[10][10];
    int MAT3[10][10];
    int r1,c1,r2,c2;
    int iCount,jCount,i;
    int kCount;
    clock_t t1, t2;
    printf("Enter Number of Rows For Matrix 1 :");
    scanf("%d",&r1);
    
    printf("Enter Number of Columns For Matrix 1 :");
    scanf("%d",&c1);
    
							dummyMethod3();
    for(iCount=0;iCount<r1;iCount++)
    {
        for(jCount=0;jCount<c1;jCount++)
        {
            printf("Enter Mat1[%d][%d] :",iCount,jCount);
            scanf("%d",&MAT1[iCount][jCount]);
        }
    }
							dummyMethod4();
    
    printf("\n");
    
    printf("Enter Numer of Rows For Matrix 2 :");
    scanf("%d",&r2);
    
    printf("Enter Number of Columns For Matrix 2 :");
    scanf("%d",&c2);
    
							dummyMethod3();
    for(iCount=0;iCount<r2;iCount++)
    {
        for(jCount=0;jCount<c2;jCount++)
        {
            printf("Enter Mat2[%d][%d] :",iCount,jCount);
            scanf("%d",&MAT2[iCount][jCount]);
        }
    }
							dummyMethod4();
    t1 = clock();

    if(c1!=r2)
    {
        printf("Multipication of Matrix not Possible !!!");
    }
    else
    {
        for (i=0; i<r1; i++) {
																							dummyMethod1();
#pragma omp parallel for
            for(jCount=0;jCount<c2;jCount++)
            {
                for(kCount=0;kCount<c1;kCount++)
                {
                    MAT3[i][jCount]+=MAT1[i][kCount] * MAT2[kCount][jCount];
                }
            }
																							dummyMethod2();
            
        }
    }
    printf("\n Matrix 1 \n|\t");
    
    for(iCount=0;iCount<r1;iCount++)
    {
        for(jCount=0;jCount<c1;jCount++)
        {
            printf("%d \t",MAT1[iCount][jCount]);
        }
        printf("|\n|\t");
    }
    
    printf("\n Matrix 2 \n|\t");
    
    for(iCount=0;iCount<r2;iCount++)
    {
        for(jCount=0;jCount<c2;jCount++)
        {
            printf("%d \t",MAT2[iCount][jCount]);
        }
        printf("|\n|\t");
    }
    
    printf("\n Multipication of Matrix ...\n|\t");
    
    for(iCount=0;iCount<r1;iCount++)
    {
        for(jCount=0;jCount<c2;jCount++)
        {
            printf("%d \t",MAT3[iCount][jCount]);
        }
        printf("|\n|\t");
    }
    t2 = clock();
    float diff = ((float)(t2 - t1) / 1000000.0F ) * 1000;
    printf("it took : %f\n",diff);
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