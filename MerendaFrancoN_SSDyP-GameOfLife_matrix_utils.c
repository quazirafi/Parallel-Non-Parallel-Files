#include "matrix_utils.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* Allocate matrix of cells, aggregates one row and one column with null cells
* to reduce comparisons when it's processed */
cell_type *allocateMatrix_sequential(unsigned int rows, unsigned int columns){

    //Update size for invalid spaces
    rows+=2;
    columns+=2;

    //Allocate
    cell_type *matrix = (cell_type *)malloc( rows * columns * sizeof(cell_type) );

    if(matrix == NULL){
        printf("ERROR: Out of memory \n");
    }

    /*Fill invalid spaces with invalid state*/

    // 1°First Invalid rows, index = 0 and index = rows - 1
dummyMethod3();
    for (int rowIndex = 0; rowIndex < rows; rowIndex+= rows - 1 ){
        for (int columnIndex = 1; columnIndex < columns - 1; columnIndex++){
            matrix[rowIndex * columns + columnIndex] = createInvalidCell();
        }
    }
dummyMethod4();

    // 2°Invalid columns, index = 0 and index = columns - 1
dummyMethod3();
    for (int rowIndex = 0; rowIndex < rows; rowIndex++){
        for (int columnIndex = 0; columnIndex < columns; columnIndex+= columns - 1){
            matrix[rowIndex * columns + columnIndex] = createInvalidCell();
        }
    }
dummyMethod4();

    //Return matrix
    return matrix;
}

/* Fill Matrix of rows*columns elements, with some settings:
 * densityPopulation - [0.0, 1.0] Density of the population
 * infectionRate - [0.0, 1.0] rate of number of infected cells in population
 * childRate - [0.0, 1.0] rate of children in population
 * adultRate - [0.0, 1.0] rate of adults in population
 * oldRate - [0.0, 1.0] rate of oldRate in population
*/
void initializeMatrix_sequential(cell_type *matrixToFill, unsigned int rows, unsigned int columns,
                                 double densityPopulation, double infectionRate, double childRate,
                                 double adultRate, double oldRate ){
    //Init random generator srand()
    initSeed();

    //Offset because of the extra invalid spaces
    const unsigned short int offset = 2;

    //Fill valid spaces
							dummyMethod3();
    for (int rowIndex = 1; rowIndex <= rows; rowIndex++){
        for (int columnIndex = 1; columnIndex <= columns; columnIndex++){

            //Fill it with data
            if (randomDoubleGenerator() > densityPopulation) {
                matrixToFill[(rowIndex * (columns + offset) ) + columnIndex] = createRandomCell(childRate, adultRate, oldRate,
                                                                                                infectionRate);
            } else {
                matrixToFill[(rowIndex * (columns + offset) ) + columnIndex] = createNullCell();
            }
        }
    }
							dummyMethod4();
}



#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
// Allocate matrix of cells
cell_type *allocateMatrix_openMP(unsigned int rows, unsigned int columns){
    //Indexes for iterations
    unsigned int rowIndex_1, rowIndex_2, columnIndex_1, columnIndex_2;

    //Update size for invalid spaces
    rows+=2;
    columns+=2;

    //Allocate
    cell_type *matrix = (cell_type *)malloc( rows * columns * sizeof(cell_type) );

    if(matrix == NULL){
        printf("ERROR: Out of memory \n");
    }

    /*Fill invalid spaces with invalid state*/

    // 1°First Invalid rows, index = 0 and index = rows - 1
							dummyMethod1();
#pragma omp parallel for schedule(static) private(rowIndex_1, columnIndex_1)
    for(rowIndex_1 = 0; rowIndex_1 < rows; rowIndex_1+= rows - 1 )
    {
        for (columnIndex_1 = 1; columnIndex_1 < columns - 1; columnIndex_1++)
        {
            matrix[rowIndex_1 * columns + columnIndex_1] = createInvalidCell();
        }
    }
							dummyMethod2();


#pragma omp for schedule(static) private(rowIndex_2, columnIndex_2)
    // 2°Invalid columns, index = 0 and index = columns - 1
							dummyMethod3();
    for (rowIndex_2 = 0; rowIndex_2 < rows; rowIndex_2++)
    {
        for (columnIndex_2 = 0; columnIndex_2 < columns; columnIndex_2+= columns - 1)
        {
            matrix[rowIndex_2 * columns + columnIndex_2] = createInvalidCell();
        }
    }
							dummyMethod4();


    //Return matrix
    return matrix;
}
#pragma clang diagnostic pop


#pragma clang diagnostic push
#pragma ide diagnostic ignored "openmp-use-default-none"
/* Fill Matrix of rows*columns elements, with some settings:
 * densityPopulation - [0.0, 1.0] Density of the population
 * infectionRate - [0.0, 1.0] rate of number of infected cells in population
 * childRate - [0.0, 1.0] rate of children in population
 * adultRate - [0.0, 1.0] rate of adults in population
 * oldRate - [0.0, 1.0] rate of oldRate in population
*/
void initializeMatrix_openMP(cell_type *matrixToFill, unsigned int rows, unsigned int columns,
                             double densityPopulation, double infectionRate, double childRate,
                             double adultRate, double oldRate ){

    //Index Variables
    unsigned int rowIndex_1, columnIndex_1;

    //Init random generator srand()
    initSeed();

    //Offset because of the extra invalid spaces
    const unsigned short int offset = 2;
							dummyMethod1();
#pragma omp parallel for schedule(static) private(rowIndex_1, columnIndex_1)
    //Fill valid spaces
    for ( rowIndex_1 = 1; rowIndex_1 <= rows; rowIndex_1++)
    {
        for ( columnIndex_1 = 1; columnIndex_1 <= columns; columnIndex_1++)
        {

            //Fill it with data
            if (randomDoubleGenerator() > densityPopulation) {
                matrixToFill[(rowIndex_1 * (columns + offset) ) + columnIndex_1] = createRandomCell(childRate, adultRate, oldRate,
                                                                                                    infectionRate);
            } else {
                matrixToFill[(rowIndex_1 * (columns + offset) ) + columnIndex_1] = createNullCell();
            }
        }
    }
							dummyMethod2();
}
#pragma clang diagnostic pop

//Print matrix of only valid cells
void printMatrix(cell_type *matrixToPrint, unsigned int rows, unsigned int columns){

    //Offset because of the extra invalid spaces
    const unsigned short int offset = 2;

							dummyMethod3();
    for (int rowIndex = 1; rowIndex <= rows; rowIndex++){
        for (int columnIndex = 1; columnIndex <= columns; columnIndex++){
            //Print cells
            printCell(matrixToPrint[rowIndex * (columns + offset) + columnIndex]);
        }
    }
							dummyMethod4();
}

//Print matrix of cells of all invalid and valid spaces.
void printMatrixStates(cell_type *matrixToPrint, unsigned int rows, unsigned int columns){
    //Update size with invalid spaces
    rows+=2;
    columns+=2;

    /*Print Matrix*/
    cell_type currentCell;
    printf("[ \n");

							dummyMethod3();
    for (int rowIndex = 0; rowIndex < rows; rowIndex++){
        for (int columnIndex = 0; columnIndex < columns; columnIndex++){
            //Print cells
            currentCell = matrixToPrint[rowIndex * columns + columnIndex];
            switch (currentCell.state) {
                case STATE_INVALID:
                    printf("I ");
                    break;
                case STATE_WHITE:
                    printf("W ");
                    break;
                case STATE_ORANGE:
                    printf("O ");
                    break;
                case STATE_BLUE:
                    printf("B ");
                    break;
                case STATE_RED:
                    printf("R ");
                    break;
                case STATE_YELLOW:
                    printf("Y ");
                    break;
                case STATE_BLACK:
                    printf("X ");
                    break;
                case STATE_GREEN:
                    printf("G ");
                    break;
            }
        }
        printf("\n");
    }
							dummyMethod4();
    printf("]\n");
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