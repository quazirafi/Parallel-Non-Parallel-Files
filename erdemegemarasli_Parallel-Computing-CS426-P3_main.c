#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int threadNumber;
    int repetitionNumber;
    int shouldPrint;
    char *fileName;

    double startTime;
    double endTime;
    double totalTime = 0;

    if (argc != 5)
    {
        printf("Please enter inputs correctly. Thus if your executable is exe\n");
        printf("./exe [no_of_threads] [no_of_repetitions] [0 or 1] [filename]\n");
        return 0;
    }
    threadNumber = atoi(argv[1]);
    repetitionNumber = atoi(argv[2]);
    shouldPrint = atoi(argv[3]);
    fileName = argv[4];

    if (threadNumber < 1)
    {
        printf("no_of_threads must be positive integer\n");
        return 0;
    }
    if (repetitionNumber < 1)
    {
        printf("no_of_repetitions must be positive integer\n");
        return 0;
    }
    if (shouldPrint != 0 && shouldPrint != 1)
    {
        printf("An argument to print on stdout must be 0 or 1\n");
        return 0;
    }
    

    //change later
    omp_set_num_threads(threadNumber);

    double **x;
    int *row_ptr;
    int *col_ind;
    double *values;

    int rowCount;
    int colCount;
    int nonZeroCount;


    FILE *file = fopen(fileName, "r");
    //Changed nonZeroCount since its false in the files
    fscanf(file, "%d %d %d\n", &rowCount, &colCount, &nonZeroCount);


    double **tempMatrix = (double **)calloc(rowCount, sizeof(double *));

							dummyMethod3();
    for (int i = 0; i < rowCount; i++)
    {
        tempMatrix[i] = (double *)calloc(colCount, sizeof(double));
    }
							dummyMethod4();


    while (!feof(file))
    {
        int rowIndex;
        int colIndex;
        double value;
        fscanf(file, "%d %d  %lf\n", &rowIndex, &colIndex, &value);
        rowIndex = rowIndex - 1;
        colIndex = colIndex - 1;
        tempMatrix[rowIndex][colIndex] = value;
    }
    fclose(file);

    nonZeroCount = 0;

							dummyMethod3();
    for (int i = 0; i < rowCount; i++)
    {
        for (int j = 0; j < colCount; j++)
        {
            if (tempMatrix[i][j] != 0){
                nonZeroCount++;
            }
        }
    }
							dummyMethod4();

    //Init vector and CSR
    x = (double **)calloc(repetitionNumber + 1, sizeof(double *));
							dummyMethod3();
    for (int i = 0; i < repetitionNumber + 1; i++)
    {
        x[i] = (double *)calloc(nonZeroCount, sizeof(double));
    }
							dummyMethod4();

    col_ind = (int *)calloc(nonZeroCount, sizeof(int));
    values = (double *)calloc(nonZeroCount, sizeof(double));
    //rowCount + 1 so that last one can point out of bound
    row_ptr = (int *)calloc(rowCount + 1, sizeof(int));

    //Init starter vector 1
							dummyMethod3();
    for (int i = 0; i < nonZeroCount; i++)
    {
        x[0][i] = 1;
    }
							dummyMethod4();

    //Init CSR properly
    int currentIndex = 0;

							dummyMethod3();
    for (int i = 0; i < rowCount; i++)
    {
        int nonZeroCountCurRow = 0;

        for (int j = 0; j < colCount; j++)
        {
            if (tempMatrix[i][j] != 0)
            {
                if (nonZeroCountCurRow == 0)
                {
                    row_ptr[i] = currentIndex;
                }
                col_ind[row_ptr[i] + nonZeroCountCurRow] = j;
                values[row_ptr[i] + nonZeroCountCurRow] = tempMatrix[i][j];
                currentIndex++;
                nonZeroCountCurRow++;
            }
        }
        if (nonZeroCountCurRow == 0)
        {
            row_ptr[i] = currentIndex;
        }
    }
							dummyMethod4();
    //Point last row outside
    row_ptr[rowCount] = nonZeroCount;

    //Print before parallel execution
    if (shouldPrint == 1)
    {
        
        printf("--------------Matrix----------------\n");

        printf("------row_ptr------------\n");
															dummyMethod3();
        for (int i = 0; i < rowCount+1; i++)
        {
            printf("row_ptr[%d]: %d\n",i, row_ptr[i]);
        }
															dummyMethod4();

        printf("------col_ind------------\n");
															dummyMethod3();
        for (int i = 0; i < nonZeroCount; i++)
        {
            printf("col_ind[%d]: %d\n",i, col_ind[i]);
        }
															dummyMethod4();

        printf("---------values---------\n");
															dummyMethod3();
        for (int i = 0; i < nonZeroCount; i++)
        {
            printf("values[%d]: %.17g\n", i, values[i]);
        }
															dummyMethod4();

    
        printf("--------------Initial Vector----------------\n");
															dummyMethod3();
        for (int i = 0; i < rowCount; i++)
        {
            printf("x[%d]: %.17g\n", i, x[0][i]);
        }
															dummyMethod4();
    }

    //Computation
    for (int k = 0; k < repetitionNumber; k++)
    {
        startTime = omp_get_wtime();
        //Parallel Section
															dummyMethod1();
        #pragma omp parallel for schedule(static)
        for (int i = 0; i < rowCount; i++) 
        {
            for (int j = row_ptr[i]; j < row_ptr[i+1]; j++)
                x[k + 1][i] += values[j] * x[k][col_ind[j]];
        }
															dummyMethod2();

        endTime = omp_get_wtime();
        
        totalTime += endTime - startTime;
    }

    

    //Print Resulting vector
    if (shouldPrint == 1)
    {
        printf("--------------Resulting Vector----------------\n");
        for (int i = 0; i < rowCount; i++)
        {
            printf("x[%d]: %.17g\n", i, x[repetitionNumber][i]);
        }
    }

    printf("Parallel work took %lf seconds.\n", totalTime);

    //-------Free memory-------
    for (int i = 0; i < rowCount; i++)
    {
        free(tempMatrix[i]);
    }
    free(tempMatrix);

    for (int i = 0; i < repetitionNumber + 1; i++)
    {
        free(x[i]);
    }
    free(x);
    free(col_ind);
    free(values);
    free(row_ptr);

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