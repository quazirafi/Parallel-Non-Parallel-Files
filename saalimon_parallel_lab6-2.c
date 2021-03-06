#include "omp.h"
#include<stdio.h>
#include<stdlib.h>
#include<time.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int main(int argc, char** argv){
    int i,j,k;
    i = 0;
    j = 1;
    int rowA,rowB,colA,colB, p;
    float* matA;
    float* matB;
    float* matC;
    float* matBt;
    float num;
    time_t start, end;
    double cpu_time_used;
    FILE *fp;
    printf("Enter number of rank:");
    scanf("%d",&p);
    omp_set_num_threads(p);
    fp = fopen(argv[1], "r");
    if (fp) {
        fscanf(fp,"%d %d\n",&rowA,&colA);
        matA =(float*)  malloc(colA*rowA*sizeof(float));
dummyMethod3();
        for(i = 0 ; i < rowA ; i++){
            for(j = 0 ; j < colA ; j++){
                fscanf(fp,"%f ",&num);
                matA[i*colA+j] = num;
            }
        }            
dummyMethod4();
        fclose(fp);
    }
    fp = fopen(argv[2], "r");
    if (fp) {
        fscanf(fp,"%d %d\n",&rowB,&colB);
        matB =(float*)  malloc(colB*rowB*sizeof(float));
															dummyMethod3();
        for(i = 0; i < rowB ; i++){
            for(j = 0 ; j < colB ; j++){
                fscanf(fp,"%f ",&num);
                matB[i*colB+j] = num;
            }
        }
															dummyMethod4();
        fclose(fp);
    }
    time(&start);
    matBt =(float*)  malloc(colB*rowB*sizeof(float));
    matC =(float*)  malloc(colB*rowA*sizeof(float));
							dummyMethod3();
    for(i=0;i<rowB;i++){ //n = rowB
        for(j=0;j<colB;j++){ //p = colB
            matBt[i + j * rowB] = matB[i * colB + j];
        }
    }
							dummyMethod4();
															dummyMethod1();
    #pragma omp parallel for private(i,j,k)
        for ( i = 0; i < rowA; ++i)
        {
            for ( j = 0; j < colB; ++j)
            {
                matC[i * colB + j] = 0;
                for ( k = 0; k < rowB; ++k)
                {
                    matC[i * colB + j] += matA[i * rowB + k] * matBt[k + j * rowB];
                } 
            }
        }
															dummyMethod2();
    
    // for ( i = 0; i < rowA; ++i)
    // {
    //     for ( j = 0; j < colB; ++j)
    //     {
    //         printf("%.0f ",matC[i * colB + j]);
    //     }
    //     printf("\n");
    // }
    time(&end);
    cpu_time_used = difftime(end,start);
    printf("%lf \n",cpu_time_used);
    fp = fopen(argv[3], "w");
    if (fp) {
        fprintf(fp,"%d %d\n",rowA,colB);
															dummyMethod3();
        for(i = 0; i < rowA ; i++){
            for(j = 0 ; j < colB ; j++){
                fprintf(fp,"%.1f ",matC[i*colB+j]);  
            }
            fprintf(fp,"\n");
        }
															dummyMethod4();
        fclose(fp);
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