#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int cmpfunction(const void* a, const void* b) {
    return ( *(int*)a - *(int*)b );
}

int sort(int* values, int start, int stop) {
    int bSize = sizeof(int);
    int pivot = values[start];
    int i = start;
    int j = stop+1;
    while (1) {
        while (values[++i] < pivot) if (i == stop) break;
        while (values[--j] >= pivot) if (j == start) break;
        if (i >= j) break;
        int tmp = values[i];
        values[i] = values[j];
        values[j] = tmp;
    }
    // place the pivot back
    int tmp = values[j];
    values[j] = pivot;
    values[start] = tmp;

    return j;
}

int getMedian(int* values, int size) {
    int middle = size / 2;
    int start = 0;
    int stop = size-1;
    int pivot = sort(values, start, stop);
    while (pivot != middle) {
        if (pivot > middle) {
            // median is in left half
            stop = pivot-1;
            pivot = sort(values, start, stop);
        } else {
            // median is in right half
            start = pivot+1;
            pivot = sort(values, start, stop);
        }
    }
    return values[pivot];
}

// read the binary file and perform binning
int readBinaryFile(const char* filename, int* grid, int histSize, int windSize) {
    printf("reading file...\n");
    FILE *dataFile = fopen(filename, "rb");
    if (!dataFile) {
        printf("Unable to open data file.");
        return -1;
    }
    while(!feof(dataFile)) {
        float x;
        float y;
        fread(&x, 1, sizeof(float), dataFile);
        fread(&y, 1, sizeof(float), dataFile);
        // get bins
        int xpos = (int) (x * (histSize - 1));
        int ypos = (int) (y * (histSize - 1));
        //
        grid[ypos * histSize + xpos] += 1;
    }
    fclose(dataFile);
    return 1;
}

// read the already written CSV histogram
int readHistogramCsvFile(const char* filename, int* grid, int histSize, int windSize) {
    printf("Reading histogram file...\n");
    char buffer[10240];
    FILE *dataFile = fopen(filename, "r");
    if (dataFile == NULL) {
         printf("Failed to open Histogram file.");
         return -1;
    }
    char* line;
    char* value;
    int col;
    int row = 0;
    while ((line = fgets(buffer, sizeof(buffer), dataFile)) != NULL) {
        // ignore the first row, which is a header.
        if (row > 0) {
            col = 0;
            value = strtok(line, ",");
            while (value != NULL) {
                // ignore first column, which is a header
                if (col > 0) {
                    int num = atol(value);
                    grid[(row-1) * histSize + (col-1)] = num;
                }
                value = strtok(NULL, ",");
                col++;
            }
        }
        row++;
    }
    printf("returning\n");
    return 1;
}

int main(int argc, char **argv) {

    if (argc != 3) {
        printf("Incorrect number of arguments: %d\n", argc);
        return -1;
    }

    int gridSize;
    int windSize;
    sscanf(argv[1], "%d", &gridSize);
    sscanf(argv[2], "%d", &windSize);

    // window size must be odd.
    if (windSize % 2 == 0) windSize++;

    // initialise the grid
    int* grid = (int*) malloc(gridSize * gridSize * sizeof(int));
    int* grid2 = (int*) malloc(gridSize * gridSize * sizeof(int));
							dummyMethod3();
    for (int i = 0; i < gridSize * gridSize; i++) {
        grid[i] = 0;
        grid2[i] = 0;
    }
							dummyMethod4();

    double binSize = 1.0 / gridSize;

    // readBinaryFile("points_noise_normal.bin", grid, gridSize, windSize);
    readHistogramCsvFile("grid-512.csv", grid, gridSize, windSize);

    // perform smoothing
							dummyMethod1();
    #pragma omp parallel for
    for (int y = 0; y < gridSize; y++) {
        for (int x = 0; x < gridSize; x++) {

            int* window = (int*) malloc(windSize * windSize * sizeof(int));

            int w_idx = 0;
            for (int dy = -windSize / 2; dy <= windSize / 2; dy++) {
                for (int dx = -windSize / 2; dx <= windSize / 2; dx++) {
                    // gather the values in the window
                    int gy, gx;
                    if (y + dy < 0) {gy = 0;}
                    else if (y + dy > gridSize - 1) {gy = gridSize - 1;}
                    else {gy = y + dy;}
                    if (x + dx < 0) {gx = 0;}
                    else if (x + dx > gridSize - 1) {gx = gridSize - 1;}
                    else {gx = x + dx;}
                    window[w_idx] = grid[gy * gridSize + gx];
                    //printf("(%d, %d): %lu, %lu\n", gx, gy, window[w_idx], grid[gy*gridSize + gx]);
                    w_idx++;
                }
            }

            int median = getMedian(window, windSize * windSize);
            grid2[y * gridSize + x] = median;

            free(window);

        }
    }
							dummyMethod2();

    // write results to csv file
    FILE *f = fopen("output.csv", "w");
    if (f == NULL) {
        return -1;
    }

    // print column headers
							dummyMethod3();
    for (int x = 0; x < gridSize-1; x++) {
        fprintf(f, "%f,", binSize * x);
    }
							dummyMethod4();
    fprintf(f, "%f\n", binSize * (gridSize-1));
    // print the columns
							dummyMethod3();
    for (int y = 0; y < gridSize; y++) {
        fprintf(f, "%f", binSize * y);
        for (int x = 0; x < gridSize-1; x++) {
            fprintf(f, "%lu,", grid2[y * gridSize + x]);
        }
        fprintf(f, "%lu\n", grid2[y * gridSize + gridSize-1]);
    }
							dummyMethod4();
    fclose(f);

    free(grid);
    free(grid2);

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