#include <sys/time.h>
#include <time.h>
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
static unsigned long long current_time_ns() {
#ifdef __MACH__
    clock_serv_t cclock;
    mach_timespec_t mts;
    host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
    clock_get_time(cclock, &mts);
    mach_port_deallocate(mach_task_self(), cclock);
    unsigned long long s = 1000000000ULL * (unsigned long long)mts.tv_sec;
    return (unsigned long long)mts.tv_nsec + s;
#else
    struct timespec t ={0,0};
    clock_gettime(CLOCK_MONOTONIC, &t);
    unsigned long long s = 1000000000ULL * (unsigned long long)t.tv_sec;
    return (((unsigned long long)t.tv_nsec)) + s;
#endif
}
#include <stdio.h>
#include <time.h>
#include <assert.h>
#include <stdlib.h> 
#include <math.h> 
#include <sys/time.h>
#include <string.h>

#define STR_SIZE (256)
#define MAX_PD	(3.0e6)
/* required precision in degrees	*/
#define PRECISION	0.001
#define SPEC_HEAT_SI 1.75e6
#define K_SI 100
/* capacitance fitting factor	*/
#define FACTOR_CHIP	0.5


/* chip parameters	*/
float t_chip = 0.0005;
float chip_height = 0.016; float chip_width = 0.016; 
/* ambient temperature, assuming no package at all	*/
float amb_temp = 80.0;

void fatal(char *s)
{
    fprintf(stderr, "Error: %s\n", s);
}

void readinput(float *vect, int grid_rows, int grid_cols, int layers, char *file) {
    int i,j,k;
    FILE *fp;
    char str[STR_SIZE];
    float val;

    if( (fp  = fopen(file, "r" )) ==0 )
      fatal( "The file was not opened" );


							dummyMethod3();
    for (i=0; i <= grid_rows-1; i++) 
      for (j=0; j <= grid_cols-1; j++)
        for (k=0; k <= layers-1; k++)
          {
            if (fgets(str, STR_SIZE, fp) == NULL) fatal("Error reading file\n");
            if (feof(fp))
              fatal("not enough lines in file");
            if ((sscanf(str, "%f", &val) != 1))
              fatal("invalid file format");
            vect[i*grid_cols+j+k*grid_rows*grid_cols] = val;
          }
							dummyMethod4();

    fclose(fp);	

}


void writeoutput(float *vect, int grid_rows, int grid_cols, int layers, char *file) {

    int i,j,k, index=0;
    FILE *fp;
    char str[STR_SIZE];

    if( (fp = fopen(file, "w" )) == 0 )
      printf( "The file was not opened\n" );

							dummyMethod3();
    for (i=0; i < grid_rows; i++) 
      for (j=0; j < grid_cols; j++)
        for (k=0; k < layers; k++)
          {
            sprintf(str, "%d\t%g\n", index, vect[i*grid_cols+j+k*grid_rows*grid_cols]);
            fputs(str,fp);
            index++;
          }
							dummyMethod4();

    fclose(fp);	
}



void computeTempCPU(float *pIn, float* tIn, float *tOut, 
        int nx, int ny, int nz, float Cap, 
        float Rx, float Ry, float Rz, 
        float dt, int numiter) 
{   float ce, cw, cn, cs, ct, cb, cc;
    float stepDivCap = dt / Cap;
    ce = cw =stepDivCap/ Rx;
    cn = cs =stepDivCap/ Ry;
    ct = cb =stepDivCap/ Rz;

    cc = 1.0 - (2.0*ce + 2.0*cn + 3.0*ct);

    int c,w,e,n,s,b,t;
    int x,y,z;
    int i = 0;
    do{
															dummyMethod3();
        for(z = 0; z < nz; z++)
            for(y = 0; y < ny; y++)
                for(x = 0; x < nx; x++)
                {
                    c = x + y * nx + z * nx * ny;

                    w = (x == 0) ? c      : c - 1;
                    e = (x == nx - 1) ? c : c + 1;
                    n = (y == 0) ? c      : c - nx;
                    s = (y == ny - 1) ? c : c + nx;
                    b = (z == 0) ? c      : c - nx * ny;
                    t = (z == nz - 1) ? c : c + nx * ny;


                    tOut[c] = tIn[c]*cc + tIn[n]*cn + tIn[s]*cs + tIn[e]*ce + tIn[w]*cw + tIn[t]*ct + tIn[b]*cb + (dt/Cap) * pIn[c] + ct*amb_temp;
                }
															dummyMethod4();
        float *temp = tIn;
        tIn = tOut;
        tOut = temp; 
        i++;
    }
    while(i < numiter);

}

float accuracy(float *arr1, float *arr2, int len)
{
    float err = 0.0; 
    int i;
							dummyMethod3();
    for(i = 0; i < len; i++)
    {
        err += (arr1[i]-arr2[i]) * (arr1[i]-arr2[i]);
    }
							dummyMethod4();

    return (float)sqrt(err/len);


}
void computeTempOMP(float *pIn, float* tIn, float *tOut, 
        int nx, int ny, int nz, float Cap, 
        float Rx, float Ry, float Rz, 
        float dt, int numiter) 
{  

    float ce, cw, cn, cs, ct, cb, cc;

    float stepDivCap = dt / Cap;
    ce = cw =stepDivCap/ Rx;
    cn = cs =stepDivCap/ Ry;
    ct = cb =stepDivCap/ Rz;

    cc = 1.0 - (2.0*ce + 2.0*cn + 3.0*ct);


    {
        int count = 0;
        float *tIn_t = tIn;
        float *tOut_t = tOut;

        do {
            int z; 
 { const unsigned long long parallel_for_start = current_time_ns();
dummyMethod1();
#pragma omp parallel for
for (z = 0; z < nz; z++) {
                int y;
                for (y = 0; y < ny; y++) {
                    int x;
                    for (x = 0; x < nx; x++) {
                        int c, w, e, n, s, b, t;
                        c =  x + y * nx + z * nx * ny;
                        w = (x == 0)    ? c : c - 1;
                        e = (x == nx-1) ? c : c + 1;
                        n = (y == 0)    ? c : c - nx;
                        s = (y == ny-1) ? c : c + nx;
                        b = (z == 0)    ? c : c - nx * ny;
                        t = (z == nz-1) ? c : c + nx * ny;
                        tOut_t[c] = cc * tIn_t[c] + cw * tIn_t[w] + ce * tIn_t[e]
                            + cs * tIn_t[s] + cn * tIn_t[n] + cb * tIn_t[b] + ct * tIn_t[t]+(dt/Cap) * pIn[c] + ct*amb_temp;
                    }
                }
            } ; 
dummyMethod2();
const unsigned long long parallel_for_end = current_time_ns();
printf("pragma157_omp_parallel %llu ns\n", parallel_for_end - parallel_for_start); } 

            float *t = tIn_t;
            tIn_t = tOut_t;
            tOut_t = t; 
            count++;
        } while (count < numiter);
    } 
    return; 
} 

void usage(int argc, char **argv)
{
    fprintf(stderr, "Usage: %s <rows/cols> <layers> <iterations> <powerFile> <tempFile> <outputFile>\n", argv[0]);
    fprintf(stderr, "\t<rows/cols>  - number of rows/cols in the grid (positive integer)\n");
    fprintf(stderr, "\t<layers>  - number of layers in the grid (positive integer)\n");

    fprintf(stderr, "\t<iteration> - number of iterations\n");
    fprintf(stderr, "\t<powerFile>  - name of the file containing the initial power values of each cell\n");
    fprintf(stderr, "\t<tempFile>  - name of the file containing the initial temperature values of each cell\n");
    fprintf(stderr, "\t<outputFile - output file\n");
    exit(1);
}



int main(int argc, char** argv)
{
    if (argc != 7)
    {
        usage(argc,argv);
    }

    char *pfile, *tfile, *ofile;// *testFile;
    int iterations = atoi(argv[3]);

    pfile = argv[4];
    tfile = argv[5];
    ofile = argv[6];
    //testFile = argv[7];
    int numCols = atoi(argv[1]);
    int numRows = atoi(argv[1]);
    int layers = atoi(argv[2]);

    /* calculating parameters*/

    float dx = chip_height/numRows;
    float dy = chip_width/numCols;
    float dz = t_chip/layers;

    float Cap = FACTOR_CHIP * SPEC_HEAT_SI * t_chip * dx * dy;
    float Rx = dy / (2.0 * K_SI * t_chip * dx);
    float Ry = dx / (2.0 * K_SI * t_chip * dy);
    float Rz = dz / (K_SI * dx * dy);

    // cout << Rx << " " << Ry << " " << Rz << endl;
    float max_slope = MAX_PD / (FACTOR_CHIP * t_chip * SPEC_HEAT_SI);
    float dt = PRECISION / max_slope;


    float *powerIn, *tempOut, *tempIn, *tempCopy;// *pCopy;
    //    float *d_powerIn, *d_tempIn, *d_tempOut;
    int size = numCols * numRows * layers;

    powerIn = (float*)calloc(size, sizeof(float));
    tempCopy = (float*)malloc(size * sizeof(float));
    tempIn = (float*)calloc(size,sizeof(float));
    tempOut = (float*)calloc(size, sizeof(float));
    //pCopy = (float*)calloc(size,sizeof(float));
    float* answer = (float*)calloc(size, sizeof(float));

    // outCopy = (float*)calloc(size, sizeof(float));
    readinput(powerIn,numRows, numCols, layers,pfile);
    readinput(tempIn, numRows, numCols, layers, tfile);

    memcpy(tempCopy,tempIn, size * sizeof(float));

const unsigned long long full_program_start = current_time_ns();
{
    struct timeval start, stop;
    float time;
    gettimeofday(&start,NULL);
    computeTempOMP(powerIn, tempIn, tempOut, numCols, numRows, layers, Cap, Rx, Ry, Rz, dt,iterations);
    gettimeofday(&stop,NULL);
    time = (stop.tv_usec-start.tv_usec)*1.0e-6 + stop.tv_sec - start.tv_sec;
    computeTempCPU(powerIn, tempCopy, answer, numCols, numRows, layers, Cap, Rx, Ry, Rz, dt,iterations);

    float acc = accuracy(tempOut,answer,numRows*numCols*layers);
    printf("Time: %.3f (s)\n",time);
    printf("Accuracy: %e\n",acc);
    } ; 
const unsigned long long full_program_end = current_time_ns();
printf("full_program %llu ns\n", full_program_end - full_program_start);

    writeoutput(tempOut,numRows, numCols, layers, ofile);
    free(tempIn);
    free(tempOut); free(powerIn);
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