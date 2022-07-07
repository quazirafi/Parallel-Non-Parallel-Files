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

int clamp(int v, int low, int high) {
    return v < low ? low : v > high ? high : v;
}

unsigned char data[Y][X];
unsigned char ans[Y][X];

int dx[] = {0, 1, -1, 0, 0};
int dy[] = {0, 0, 0, 1, -1};

void filter() {
dummyMethod1();
#pragma omp parallel for
    for (int i = 0; i < Y; ++i) {
        for (int j = 0; j < X; ++j) {
            int s = 0;
            for (int k = 0; k < 5; ++k) {
                s += data[(i + dx[k] + Y) % Y][(j + dy[k] + X) % X];
            }
            ans[i][j] = clamp(s / 5, 0, 255);
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
            fputc(ch, fpout);
            if (ch == '\n')
                break;
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
    for (int i = 0; i < Y; ++i) {
        for (int j = 0; j < X; ++j) {
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