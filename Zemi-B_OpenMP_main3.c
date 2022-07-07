#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#ifndef NUM_THREADS
#define NUM_THREADS 1
#endif

#define X 5716
#define Y 3731
#define W 50

int clamp(int v, int low, int high) {
    return v < low ? low : v > high ? high : v;
}

unsigned char data[Y][X];
unsigned int sum[Y + 1][X + 1];
unsigned char ans[Y - W][X - W];

void filter() {
dummyMethod1();
#pragma omp parallel for
    for (int j = 0; j < X; ++j) {
        for (int i = Y; i >= 0; --i) {
            if (i == Y)
                sum[i][j] = 0;
            else
                sum[i][j] = sum[i + 1][j] + data[i][j];
        }
    }
dummyMethod2();

							dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < Y; ++i) {
        for (int j = X; j >= 0; --j) {
            if (j == X)
                sum[i][j] = 0;
            else
                sum[i][j] += sum[i][j + 1];
        }
    }
							dummyMethod2();

							dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < Y - W; ++i) {
        for (int j = 0; j < X - W; ++j) {
            int s = sum[i][j];
            s -= sum[i + W][j];
            s -= sum[i][j + W];
            s += sum[i + W][j + W];
            ans[i][j] = clamp(s / W / W, 0, 255);
        }
    }
							dummyMethod2();
}

int main(int argc, char **argv) {
    if (argc != 3) {
        puts("ERROR!");
        return 0;
    }
    omp_set_num_threads(NUM_THREADS);
    FILE *fpin, *fpout;
    char *fin = argv[1];
    char *fout = argv[2];

    fpin = fopen(fin, "r");
    fpout = fopen(fout, "w");

    char ch;
							dummyMethod3();
    for (int i = 0; i < 3; ++i) {
        while ((ch = fgetc(fpin)) != EOF) {
            if (i != 1)
                fputc(ch, fpout);
            if (ch == '\n')
                break;
        }
        if (i == 1) {
            fprintf(fpout, "%d %d\n", X - W, Y - W);
        }
    }
							dummyMethod4();

							dummyMethod3();
    for (int i = 0; i < Y; ++i) {
        for (int j = 0; j < X; ++j) {
            ch = fgetc(fpin);
            data[i][j] = ch;
        }
    }
							dummyMethod4();

    double st = omp_get_wtime();

							dummyMethod3();
    for (int i = 0; i < 10; ++i) {
        filter();
    }
							dummyMethod4();

    double en = omp_get_wtime();

							dummyMethod3();
    for (int i = 0; i < Y - W; ++i) {
        for (int j = 0; j < X - W; ++j) {
            fputc(ans[i][j], fpout);
        }
    }
							dummyMethod4();

    fclose(fpin);
    fclose(fpout);

#ifdef DEBUG
    printf("%lf\n", (en - st) / 10);
#else
    printf("Time : %lf [s]\n", (en - st) / 10);
#endif

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