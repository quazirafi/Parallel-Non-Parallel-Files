//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Maeneka Grewal
 * UCLA ID: 204901948
 * Email id: maeneka@g.ucla.edu
 * Input: New Files
 */

#include <math.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int OMP_xMax;
#define xMax OMP_xMax
int OMP_yMax;
#define yMax OMP_yMax
int OMP_zMax;
#define zMax OMP_zMax

int OMP_Index(int x, int y, int z)
{
    return ((z * yMax + y) * xMax + x);
}
#define Index(x, y, z) OMP_Index(x, y, z)

double OMP_SQR(double x)
{
    return pow(x, 2.0);
}
#define SQR(x) OMP_SQR(x)

double* OMP_conv;
double* OMP_g;

void OMP_Initialize(int xM, int yM, int zM)
{
    xMax = xM;
    yMax = yM;
    zMax = zM;
    assert(OMP_conv = (double*)malloc(sizeof(double) * xMax * yMax * zMax));
    assert(OMP_g = (double*)malloc(sizeof(double) * xMax * yMax * zMax));
}
void OMP_Finish()
{
    free(OMP_conv);
    free(OMP_g);
}
void OMP_GaussianBlur(double *u, double Ksigma, int stepCount)
{
    double lambda = (Ksigma * Ksigma) / (double)(2 * stepCount);
    double nu = (1.0 + 2.0*lambda - sqrt(1.0 + 4.0*lambda))/(2.0*lambda);
    int x, y, z, step;
    double boundryScale = 1.0 / (1.0 - nu);
    double postScale = pow(nu / lambda, (double)(3 * stepCount));
    
    //1. move z to outer for loop
    //2. consolidate z to outer for loop for all
    //3. consolidate y to middle for loop for all
    for(step = 0; step < stepCount; step++)
    {
															dummyMethod1();
        #pragma omp parallel for private(x,y,z) shared (xMax, yMax, zMax) num_threads(16)
        for(z = 0; z < zMax; z++)
        {
            for(y = 0; y < yMax; y++)
            {
                u[Index(0, y, z)] *= boundryScale;
                for(x = 1; x < xMax; x++)
                {
                    u[Index(x, y, z)] += u[Index(x - 1, y, z)] * nu;
                }
                u[Index(0, y, z)] *= boundryScale;
                for(x = xMax - 2; x >= 0; x--)
                {
                    u[Index(x, y, z)] += u[Index(x + 1, y, z)] * nu;
                }
            }
            /*for(y = 0; y < yMax; y++)
            {
                for(x = 1; x < xMax; x++)
                {
                    u[Index(x, y, z)] += u[Index(x - 1, y, z)] * nu;
                }
            }*/
            /*for(y = 0; y < yMax; y++) //CANNOT MOVE TO Y LOOP? nvm just have to keep in order
            {
                u[Index(0, y, z)] *= boundryScale;
            }*/
            /*for(y = 0; y < yMax; y++) //CANNOT MOVE TO Y LOOP?
            {
                for(x = xMax - 2; x >= 0; x--)
                {
                    u[Index(x, y, z)] += u[Index(x + 1, y, z)] * nu;
                }
            }*/
            for(x = 0; x < xMax; x++)
            {
                u[Index(x, 0, z)] *= boundryScale;
                for(y = 1; y < yMax; y++)
                {
                    u[Index(x, y, z)] += u[Index(x, y - 1, z)] * nu;
                }
                u[Index(x, yMax - 1, z)] *= boundryScale;
                for(y = yMax - 2; y >= 0; y--)
                {
                    u[Index(x, y, z)] += u[Index(x, y + 1, z)] * nu;
                }
            }
            /*for(x = 0; x < xMax; x++)
            {
                for(y = 1; y < yMax; y++)
                {
                    u[Index(x, y, z)] += u[Index(x, y - 1, z)] * nu;
                }
            }*/
            /*for(x = 0; x < xMax; x++)
            {
                u[Index(x, yMax - 1, z)] *= boundryScale;
            }*/
            /*for(x = 0; x < xMax; x++)
            {
                for(y = yMax - 2; y >= 0; y--)
                {
                    u[Index(x, y, z)] += u[Index(x, y + 1, z)] * nu;
                }
            }*/
        }
															dummyMethod2();
        
        /*for(z = 0; z < zMax; z++)
        {
            
        }*/
        /*for(z = 0; z < zMax; z++)
        {
            for(y = 0; y < yMax; y++)
            {
                u[Index(0, y, z)] *= boundryScale;
            }
        }*/
        /*for(z = 0; z < zMax; z++)
        {
            for(x = xMax - 2; x >= 0; x--)
            {
                for(y = 0; y < yMax; y++)
                {
                    u[Index(x, y, z)] += u[Index(x + 1, y, z)] * nu;
                }
            }
        }*/
        /*for(z = 0; z < zMax; z++)
        {
            for(x = 0; x < xMax; x++)
            {
                u[Index(x, 0, z)] *= boundryScale;
            }
        }*/
        /*for(z = 0; z < zMax; z++)
        {
            for(x = 0; x < xMax; x++)
            {
                for(y = 1; y < yMax; y++)
                {
                    u[Index(x, y, z)] += u[Index(x, y - 1, z)] * nu;
                }
            }
        }*/
        /*for(z = 0; z < zMax; z++)
        {
            for(x = 0; x < xMax; x++)
            {
                u[Index(x, yMax - 1, z)] *= boundryScale;
            }
        }*/
        /*for(z = 0; z < zMax; z++)
        {
            for(x = 0; x < xMax; x++)
            {
                for(y = yMax - 2; y >= 0; y--)
                {
                    u[Index(x, y, z)] += u[Index(x, y + 1, z)] * nu;
                }
            }
        }*/
															dummyMethod1();
#pragma omp parallel for shared(xMax, yMax, zMax) private(x,y) num_threads(16)
        for(y = 0; y < yMax; y++)
        {
            for(x = 0; x < xMax; x++)
            {
                u[Index(x, y, 0)] *= boundryScale;

                u[Index(x, y, zMax - 1)] *= boundryScale;
                
            }
        }
															dummyMethod2();
        
        for(z = 1; z < zMax; z++)
        {
            for(y = 0; y < yMax; y++)
            {
                for(x = 0; x < xMax; x++)
                {
                    u[Index(x, y, z)] = u[Index(x, y, z - 1)] * nu;
                }
            }
        }
        /*for(y = 0; y < yMax; y++)
        {
            for(x = 0; x < xMax; x++)
            {
                u[Index(x, y, zMax - 1)] *= boundryScale;
            }
        }*/
        for(z = zMax - 2; z >= 0; z--)
        {
            for(y = 0; y < yMax; y++)
            {
                for(x = 0; x < xMax; x++)
                {
                    u[Index(x, y, z)] += u[Index(x, y, z + 1)] * nu;
                }
            }
        }
    }
    
							dummyMethod1();
#pragma omp parallel for shared(xMax, yMax, zMax, postScale, u) private(x,y,z) num_threads(16)
    for(z = 0; z < zMax; z++) // CANNOT PUT IN MAIN Z LOOP???
    {
        for(x = 0; x < xMax; x++)
        {
            for(y = 0; y < yMax; y++)
            {
                u[Index(x, y, z)] *= postScale;
            }
        }
    }
							dummyMethod2();
}
void OMP_Deblur(double* u, const double* f, int maxIterations, double dt, double gamma, double sigma, double Ksigma)
{
    double epsilon = 1.0e-7;
    double sigma2 = SQR(sigma);
    int x, y, z, iteration;
    int converged = 0;
    int lastConverged = 0;
    int fullyConverged = (xMax - 1) * (yMax - 1) * (zMax - 1);
    double* conv = OMP_conv;
    double* g = OMP_g;
    
    for(iteration = 0; iteration < maxIterations && converged != fullyConverged; iteration++)
    {
															dummyMethod1();
#pragma omp parallel for private(x,y,z) num_threads(16)
        for(z = 1; z < zMax - 1; z++)
        {
            for(y = 1; y < yMax - 1; y++)
            {
                for(x = 1; x < xMax - 1; x++)
                {
                    g[Index(x, y, z)] = 1.0 / sqrt(epsilon +
                                                   SQR(u[Index(x, y, z)] - u[Index(x + 1, y, z)]) +
                                                   SQR(u[Index(x, y, z)] - u[Index(x - 1, y, z)]) +
                                                   SQR(u[Index(x, y, z)] - u[Index(x, y + 1, z)]) +
                                                   SQR(u[Index(x, y, z)] - u[Index(x, y - 1, z)]) +
                                                   SQR(u[Index(x, y, z)] - u[Index(x, y, z + 1)]) +
                                                   SQR(u[Index(x, y, z)] - u[Index(x, y, z - 1)]));
                }
            }
        }
															dummyMethod2();
        memcpy(conv, u, sizeof(double) * xMax * yMax * zMax);
        OMP_GaussianBlur(conv, Ksigma, 3);
															dummyMethod1();
        #pragma omp parallel for private(x,y,z) num_threads(16) //shared(xMax, yMax, zMax)
        for(z = 0; z < zMax; z++)
        {
            for(y = 0; y < yMax; y++)
            {
                for(x = 0; x < xMax; x++)
                {
                    double r = conv[Index(x, y, z)] * f[Index(x, y, z)] / sigma2;
                    r = (r * (2.38944 + r * (0.950037 + r))) / (4.65314 + r * (2.57541 + r * (1.48937 + r)));
                    conv[Index(x, y, z)] -= f[Index(x, y, z)] * r;
                }
            }
        }
															dummyMethod2();
        OMP_GaussianBlur(conv, Ksigma, 3);
        converged = 0;

        for(z = 1; z < zMax - 1; z++)
        {
            for(y = 1; y < yMax - 1; y++)
            {
                for(x = 1; x < xMax - 1; x++)
                {
                    double oldVal = u[Index(x, y, z)];
                    double newVal = (u[Index(x, y, z)] + dt * (
                                                               u[Index(x - 1, y, z)] * g[Index(x - 1, y, z)] +
                                                               u[Index(x + 1, y, z)] * g[Index(x + 1, y, z)] +
                                                               u[Index(x, y - 1, z)] * g[Index(x, y - 1, z)] +
                                                               u[Index(x, y + 1, z)] * g[Index(x, y + 1, z)] +
                                                               u[Index(x, y, z - 1)] * g[Index(x, y, z - 1)] +
                                                               u[Index(x, y, z + 1)] * g[Index(x, y, z + 1)] - gamma * conv[Index(x, y, z)])) /
                    (1.0 + dt * (g[Index(x + 1, y, z)] + g[Index(x - 1, y, z)] + g[Index(x, y + 1, z)] + g[Index(x, y - 1, z)] + g[Index(x, y, z + 1)] + g[Index(x, y, z - 1)]));
                    if(fabs(oldVal - newVal) < epsilon)
                    {
                        converged++;
                    }
                    u[Index(x, y, z)] = newVal;
                }
            }
        }
        if(converged > lastConverged)
        {
            printf("%d pixels have converged on iteration %d\n", converged, iteration);
            lastConverged = converged;
        }
    }
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