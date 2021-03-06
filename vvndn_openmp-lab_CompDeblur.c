//OpenMP version.  Edit and submit only this file.
/* Enter your details below
 * Name : Vivian Doan
 * UCLA ID: 904914594
 * Email id: doanpvivian@gmail.com
 * Input: Old files
 */

// Comments
/* 
Optimizations:
- eliminated dead code
	-> before eliminating dead code I loop unrolled almost all of OMP_GaussianBlur and used #pragma omp parallel for for a number of loops
- loop unrolled part of OMP_Deblur, added a #pragma omp parallel for num_threads(16) private (x, y) for the section with no data dependencies
- code motion/common subexpressions
	-> Instead of calling the index function every time, I found the pattern of incrementation and would increment by +-1 for x, +-xMax for y, and += xMax * yMax for z
	-> I would calculate the Index once, and then add or subtract to change the indexing, which would reduce the amount of expensive calculations

Test runs with this code yielded the following times (on server 08, around 6pm June 8th):

Sequential took 13.389080 time units
OpenMP took 1.324546 time units
This resulted in a 10.108430x speed-up

Sequential took 10.136733 time units
OpenMP took 0.825088 time units
This resulted in a 12.285639x speed-up

Sequential took 14.186149 time units
OpenMP took 0.977146 time units
This resulted in a 14.517942x speed-up

Sequential took 12.662985 time units
OpenMP took 0.887367 time units
This resulted in a 14.270290x speed-up

Sequential took 12.611306 time units
OpenMP took 0.842738 time units
This resulted in a 14.964682x speed-up

Sequential took 10.944801 time units
OpenMP took 0.795510 time units
This resulted in a 13.758220x speed-up

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
  // commented out pow function and replaced with x * x;
  return x*x;
  //return pow(x, 2.0);
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
  	// changed (2*stepCount) to stepCount + stepCount
  	//double lambda = (Ksigma * Ksigma) / (double)(2 * stepCount);
  	double lambda = (Ksigma * Ksigma) / (double)(stepCount + stepCount);
	double nu = (1.0 + 2.0*lambda - sqrt(1.0 + 4.0*lambda))/(2.0*lambda);
	int x, y, z, step;
	double boundryScale = 1.0 / (1.0 - nu);
	double postScale = pow(nu / lambda, (double)(3 * stepCount));
	int xyMax = xMax * yMax;

	for(step = 0; step < stepCount; step++)
	{
			dummyMethod1();
		#pragma omp parallel for num_threads(16) private (x)
		for(z = 0; z < zMax; z++)
		{
			
			for(y = 0; y < yMax; y += 16)
			{
				// loop unrolling
				int ind = Index(0, y, z);
				u[ind] *= boundryScale;
				u[ind + xMax] *= boundryScale;
				u[ind + xMax + xMax] *= boundryScale;
				u[ind + xMax + xMax + xMax] *= boundryScale;
				u[ind + xMax + xMax + xMax + xMax] *= boundryScale;
				u[ind + xMax + xMax + xMax + xMax + xMax] *= boundryScale;
				u[ind + xMax + xMax + xMax + xMax + xMax + xMax] *= boundryScale;
				u[ind + xMax + xMax + xMax + xMax + xMax + xMax + xMax] *= boundryScale;
				
				int temp = ind + xMax + xMax + xMax + xMax + xMax + xMax + xMax + xMax;
				u[temp] *= boundryScale;
				u[temp + xMax] *= boundryScale;
				u[temp + xMax + xMax] *= boundryScale;
				u[temp + xMax + xMax + xMax] *= boundryScale;
				u[temp + xMax + xMax + xMax + xMax] *= boundryScale;
				u[temp + xMax + xMax + xMax + xMax + xMax] *= boundryScale;
				u[temp + xMax + xMax + xMax + xMax + xMax + xMax] *= boundryScale;
				u[temp + xMax + xMax + xMax + xMax + xMax + xMax + xMax] *= boundryScale;
				
				for(x = 1; x < xMax; x++)
				{
					int xyzInd = Index(x, y, z);
					u[xyzInd] += u[xyzInd - 1] * nu;
					u[xyzInd + xMax] += u[xyzInd + xMax - 1] * nu;
					u[xyzInd + xMax + xMax] += u[xyzInd + xMax + xMax - 1] * nu;
					u[xyzInd + xMax + xMax + xMax] += u[xyzInd + xMax + xMax + xMax - 1] * nu;
					u[xyzInd + xMax + xMax + xMax + xMax] += u[xyzInd + xMax + xMax + xMax + xMax - 1] * nu;
					u[xyzInd + xMax + xMax + xMax + xMax + xMax] += u[xyzInd + xMax + xMax + xMax + xMax + xMax - 1] * nu;
					u[xyzInd + xMax + xMax + xMax + xMax + xMax + xMax] += u[xyzInd + xMax + xMax + xMax + xMax + xMax + xMax - 1] * nu;
					u[xyzInd + xMax + xMax + xMax + xMax + xMax + xMax + xMax] += u[xyzInd + xMax + xMax + xMax + xMax + xMax + xMax + xMax - 1] * nu;

					temp = xyzInd + xMax + xMax + xMax + xMax + xMax + xMax + xMax + xMax;
					u[temp] += u[temp - 1] * nu;
					u[temp + xMax] += u[temp + xMax - 1] * nu;
					u[temp + xMax + xMax] += u[temp + xMax + xMax - 1] * nu;
					u[temp + xMax + xMax + xMax] += u[temp + xMax + xMax + xMax - 1] * nu;
					u[temp + xMax + xMax + xMax + xMax] += u[temp + xMax + xMax + xMax + xMax - 1] * nu;
					u[temp + xMax + xMax + xMax + xMax + xMax] += u[temp + xMax + xMax + xMax + xMax + xMax - 1] * nu;
					u[temp + xMax + xMax + xMax + xMax + xMax + xMax] += u[temp + xMax + xMax + xMax + xMax + xMax + xMax - 1] * nu;
					u[temp + xMax + xMax + xMax + xMax + xMax + xMax + xMax] += u[temp + xMax + xMax + xMax + xMax + xMax + xMax + xMax - 1] * nu;
				}

				// beginning of 3rd loop
				u[ind] *= boundryScale;
				u[ind + xMax] *= boundryScale;
				u[ind + xMax + xMax] *= boundryScale;
				u[ind + xMax + xMax + xMax] *= boundryScale;
				u[ind + xMax + xMax + xMax + xMax] *= boundryScale;
				u[ind + xMax + xMax + xMax + xMax + xMax] *= boundryScale;
				u[ind + xMax + xMax + xMax + xMax + xMax + xMax] *= boundryScale;
				u[ind + xMax + xMax + xMax + xMax + xMax + xMax + xMax] *= boundryScale;

				temp = ind + xMax + xMax + xMax + xMax + xMax + xMax + xMax + xMax;
				u[temp] *= boundryScale;
				u[temp + xMax] *= boundryScale;
				u[temp + xMax + xMax] *= boundryScale;
				u[temp + xMax + xMax + xMax] *= boundryScale;
				u[temp + xMax + xMax + xMax + xMax] *= boundryScale;
				u[temp + xMax + xMax + xMax + xMax + xMax] *= boundryScale;
				u[temp + xMax + xMax + xMax + xMax + xMax + xMax] *= boundryScale;
				u[temp + xMax + xMax + xMax + xMax + xMax + xMax + xMax] *= boundryScale;

				for(x = xMax - 2; x >= 0; x--)
				{
					int xyzInd = Index(x, y, z);
					u[xyzInd] += u[xyzInd + 1] * nu;
					u[xyzInd + xMax] += u[xyzInd + xMax + 1] * nu;
					u[xyzInd + xMax + xMax] += u[xyzInd + xMax + xMax + 1] * nu;
					u[xyzInd + xMax + xMax + xMax] += u[xyzInd + xMax + xMax + xMax + 1] * nu;
					u[xyzInd + xMax + xMax + xMax + xMax] += u[xyzInd + xMax + xMax + xMax + xMax + 1] * nu;
					u[xyzInd + xMax + xMax + xMax + xMax + xMax] += u[xyzInd + xMax + xMax + xMax + xMax + xMax + 1] * nu;
					u[xyzInd + xMax + xMax + xMax + xMax + xMax + xMax] += u[xyzInd + xMax + xMax + xMax + xMax + xMax + xMax + 1] * nu;
					u[xyzInd + xMax + xMax + xMax + xMax + xMax + xMax + xMax] += u[xyzInd + xMax + xMax + xMax + xMax + xMax + xMax + xMax + 1] * nu;

					temp = xyzInd + xMax + xMax + xMax + xMax + xMax + xMax + xMax + xMax;
					u[temp] += u[temp + 1] * nu;
					u[temp + xMax] += u[temp + xMax + 1] * nu;
					u[temp + xMax + xMax] += u[temp + xMax + xMax + 1] * nu;
					u[temp + xMax + xMax + xMax] += u[temp + xMax + xMax + xMax + 1] * nu;
					u[temp + xMax + xMax + xMax + xMax] += u[temp + xMax + xMax + xMax + xMax + 1] * nu;
					u[temp + xMax + xMax + xMax + xMax + xMax] += u[temp + xMax + xMax + xMax + xMax + xMax + 1] * nu;
					u[temp + xMax + xMax + xMax + xMax + xMax + xMax] += u[temp + xMax + xMax + xMax + xMax + xMax + xMax + 1] * nu;
					u[temp + xMax + xMax + xMax + xMax + xMax + xMax + xMax] += u[temp + xMax + xMax + xMax + xMax + xMax + xMax + xMax + 1] * nu;
				}
			}
		}
			dummyMethod2();
			dummyMethod1();
		#pragma omp parallel for num_threads(16) private (x)
		for(z = 0; z < zMax; z++)
		{
			for(x = 0; x < xMax; x += 16)
			{
				int ind = Index(x, 0, z);
				u[ind] *= boundryScale;
				u[ind + 1] *= boundryScale;
				u[ind + 2] *= boundryScale;
				u[ind + 3] *= boundryScale;
				u[ind + 4] *= boundryScale;
				u[ind + 5] *= boundryScale;
				u[ind + 6] *= boundryScale;
				u[ind + 7] *= boundryScale;

				u[ind + 8] *= boundryScale;
				u[ind + 9] *= boundryScale;
				u[ind + 10] *= boundryScale;
				u[ind + 11] *= boundryScale;
				u[ind + 12] *= boundryScale;
				u[ind + 13] *= boundryScale;
				u[ind + 14] *= boundryScale;
				u[ind + 15] *= boundryScale;
			}
		}
			dummyMethod2();
			dummyMethod1();
		#pragma omp parallel for num_threads(16) private (x, y)
		for(z = 0; z < zMax; z++)
		{
			for(y = 1; y < yMax; y++)
			{
				for(x = 0; x < xMax; x += 16)
				{
					int xyzInd = Index(x, y, z);
					u[xyzInd] += u[xyzInd - xMax] * nu;
					u[xyzInd + 1] += u[xyzInd + 1 - xMax] * nu;
					u[xyzInd + 2] += u[xyzInd + 2 - xMax] * nu;
					u[xyzInd + 3] += u[xyzInd + 3 - xMax] * nu;
					u[xyzInd + 4] += u[xyzInd + 4 - xMax] * nu;
					u[xyzInd + 5] += u[xyzInd + 5 - xMax] * nu;
					u[xyzInd + 6] += u[xyzInd + 6 - xMax] * nu;
					u[xyzInd + 7] += u[xyzInd + 7 - xMax] * nu;

					u[xyzInd + 8] += u[xyzInd + 8 - xMax] * nu;
					u[xyzInd + 9] += u[xyzInd + 9 - xMax] * nu;
					u[xyzInd + 10] += u[xyzInd + 10 - xMax] * nu;
					u[xyzInd + 11] += u[xyzInd + 11 - xMax] * nu;
					u[xyzInd + 12] += u[xyzInd + 12 - xMax] * nu;
					u[xyzInd + 13] += u[xyzInd + 13 - xMax] * nu;
					u[xyzInd + 14] += u[xyzInd + 14 - xMax] * nu;
					u[xyzInd + 15] += u[xyzInd + 15 - xMax] * nu;
				}
			}
		}
			dummyMethod2();
		int yval = yMax - 1;
			dummyMethod1();
		#pragma omp parallel for num_threads(16) private (x)
		for(z = 0; z < zMax; z++)
		{
			for(x = 0; x < xMax; x += 16)
			{
				int ind = Index(x, yval, z);
				u[ind] *= boundryScale;
				u[ind + 1] *= boundryScale;
				u[ind + 2] *= boundryScale;
				u[ind + 3] *= boundryScale;
				u[ind + 4] *= boundryScale;
				u[ind + 5] *= boundryScale;
				u[ind + 6] *= boundryScale;
				u[ind + 7] *= boundryScale;

				u[ind + 8] *= boundryScale;
				u[ind + 9] *= boundryScale;
				u[ind + 10] *= boundryScale;
				u[ind + 11] *= boundryScale;
				u[ind + 12] *= boundryScale;
				u[ind + 13] *= boundryScale;
				u[ind + 14] *= boundryScale;
				u[ind + 15] *= boundryScale;
			}
		}
			dummyMethod2();
		for(z = 0; z < zMax; z++)
		{
			for(y = yMax - 2; y >= 0; y--)
			{
				for(x = 0; x < xMax; x += 16)
				{
					int xyzInd = Index(x, y, z);
					u[xyzInd] += u[xyzInd + xMax] * nu;
					u[xyzInd + 1] += u[xyzInd + 1 + xMax] * nu;
					u[xyzInd + 2] += u[xyzInd + 2 + xMax] * nu;
					u[xyzInd + 3] += u[xyzInd + 3 + xMax] * nu;
					u[xyzInd + 4] += u[xyzInd + 4 + xMax] * nu;
					u[xyzInd + 5] += u[xyzInd + 5 + xMax] * nu;
					u[xyzInd + 6] += u[xyzInd + 6 + xMax] * nu;
					u[xyzInd + 7] += u[xyzInd + 7 + xMax] * nu;

					u[xyzInd + 8] += u[xyzInd + 8 + xMax] * nu;
					u[xyzInd + 9] += u[xyzInd + 9 + xMax] * nu;
					u[xyzInd + 10] += u[xyzInd + 10 + xMax] * nu;
					u[xyzInd + 11] += u[xyzInd + 11 + xMax] * nu;
					u[xyzInd + 12] += u[xyzInd + 12 + xMax] * nu;
					u[xyzInd + 13] += u[xyzInd + 13 + xMax] * nu;
					u[xyzInd + 14] += u[xyzInd + 14 + xMax] * nu;
					u[xyzInd + 15] += u[xyzInd + 15 + xMax] * nu;
				}
			}
		}
			dummyMethod1();
		#pragma omp parallel for num_threads(16) private (x)
		for(y = 0; y < yMax; y++)
		{
			for(x = 0; x < xMax; x += 16)
			{
				int ind = Index(x, y, 0);
				u[ind] *= boundryScale;
				u[ind + 1] *= boundryScale;
				u[ind + 2] *= boundryScale;
				u[ind + 3] *= boundryScale;
				u[ind + 4] *= boundryScale;
				u[ind + 5] *= boundryScale;
				u[ind + 6] *= boundryScale;
				u[ind + 7] *= boundryScale;

				u[ind + 8] *= boundryScale;
				u[ind + 9] *= boundryScale;
				u[ind + 10] *= boundryScale;
				u[ind + 11] *= boundryScale;
				u[ind + 12] *= boundryScale;
				u[ind + 13] *= boundryScale;
				u[ind + 14] *= boundryScale;
				u[ind + 15] *= boundryScale;
			}
		}
			dummyMethod2();
		for(z = 1; z < zMax; z++)
		{
			for(y = 0; y < yMax; y++)
			{
				for(x = 0; x < xMax; x += 16)
				{
					int xyzInd = Index(x, y, z);
					u[xyzInd] = u[xyzInd - xyMax] * nu;
					u[xyzInd + 1] = u[xyzInd + 1 - xyMax] * nu;
					u[xyzInd + 2] = u[xyzInd + 2 - xyMax] * nu;
					u[xyzInd + 3] = u[xyzInd + 3 - xyMax] * nu;
					u[xyzInd + 4] = u[xyzInd + 4 - xyMax] * nu;
					u[xyzInd + 5] = u[xyzInd + 5 - xyMax] * nu;
					u[xyzInd + 6] = u[xyzInd + 6 - xyMax] * nu;
					u[xyzInd + 7] = u[xyzInd + 7 - xyMax] * nu;

					u[xyzInd + 8] = u[xyzInd + 8 - xyMax] * nu;
					u[xyzInd + 9] = u[xyzInd + 9 - xyMax] * nu;
					u[xyzInd + 10] = u[xyzInd + 10 - xyMax] * nu;
					u[xyzInd + 11] = u[xyzInd + 11 - xyMax] * nu;
					u[xyzInd + 12] = u[xyzInd + 12 - xyMax] * nu;
					u[xyzInd + 13] = u[xyzInd + 13 - xyMax] * nu;
					u[xyzInd + 14] = u[xyzInd + 14 - xyMax] * nu;
					u[xyzInd + 15] = u[xyzInd + 15 - xyMax] * nu;
				}
			}
		}
		int zval = zMax - 1;
			dummyMethod1();
		#pragma omp parallel for num_threads(16) private (x)
		for(y = 0; y < yMax; y++)
		{	
			for(x = 0; x < xMax; x += 16)
			{
				int ind = Index(x, y, zval);
				u[ind] *= boundryScale;
				u[ind + 1] *= boundryScale;
				u[ind + 2] *= boundryScale;
				u[ind + 3] *= boundryScale;
				u[ind + 4] *= boundryScale;
				u[ind + 5] *= boundryScale;
				u[ind + 6] *= boundryScale;
				u[ind + 7] *= boundryScale;

				u[ind + 8] *= boundryScale;
				u[ind + 9] *= boundryScale;
				u[ind + 10] *= boundryScale;
				u[ind + 11] *= boundryScale;
				u[ind + 12] *= boundryScale;
				u[ind + 13] *= boundryScale;
				u[ind + 14] *= boundryScale;
				u[ind + 15] *= boundryScale;
			}
		}
			dummyMethod2();
		for(z = zMax - 2; z >= 0; z--)
		{
			for(y = 0; y < yMax; y++)
			{
				for(x = 0; x < xMax; x += 16)
				{
					int xyzInd = Index(x, y, z);
					u[xyzInd] += u[xyzInd + xyMax] * nu;
					u[xyzInd + 1] += u[xyzInd + 1 + xyMax] * nu;
					u[xyzInd + 2] += u[xyzInd + 2 + xyMax] * nu;
					u[xyzInd + 3] += u[xyzInd + 3 + xyMax] * nu;
					u[xyzInd + 4] += u[xyzInd + 4 + xyMax] * nu;
					u[xyzInd + 5] += u[xyzInd + 5 + xyMax] * nu;
					u[xyzInd + 6] += u[xyzInd + 6 + xyMax] * nu;
					u[xyzInd + 7] += u[xyzInd + 7 + xyMax] * nu;

					u[xyzInd + 8] += u[xyzInd + 8 + xyMax] * nu;
					u[xyzInd + 9] += u[xyzInd + 9 + xyMax] * nu;
					u[xyzInd + 10] += u[xyzInd + 10 + xyMax] * nu;
					u[xyzInd + 11] += u[xyzInd + 11 + xyMax] * nu;
					u[xyzInd + 12] += u[xyzInd + 12 + xyMax] * nu;
					u[xyzInd + 13] += u[xyzInd + 13 + xyMax] * nu;
					u[xyzInd + 14] += u[xyzInd + 14 + xyMax] * nu;
					u[xyzInd + 15] += u[xyzInd + 15 + xyMax] * nu;
				}
			}
		}
	}
	dummyMethod1();
	#pragma omp parallel for num_threads(16) private (x, y)
	for(z = 0; z < zMax; z++)
	{
		for(y = 0; y < yMax; y++)
		{
			for(x = 0; x < xMax; x += 16)
			{
				int ind = Index(x, y, z);
				u[ind] *= postScale;
				u[ind + 1] *= postScale;
				u[ind + 2] *= postScale;
				u[ind + 3] *= postScale;
				u[ind + 4] *= postScale;
				u[ind + 5] *= postScale;
				u[ind + 6] *= postScale;
				u[ind + 7] *= postScale;
				u[ind + 8] *= postScale;
				u[ind + 9] *= postScale;
				u[ind + 10] *= postScale;
				u[ind + 11] *= postScale;
				u[ind + 12] *= postScale;
				u[ind + 13] *= postScale;
				u[ind + 14] *= postScale;
				u[ind + 15] *= postScale;
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
	int xyMax = xMax * yMax;

	for(iteration = 0; iteration < maxIterations && converged != fullyConverged; iteration++)
	{
			dummyMethod1();
		#pragma omp parallel for num_threads(16) private (x, y)
		for(z = 1; z < zMax - 1; z++)
		{
			for(y = 1; y < yMax - 1; y++)
			{
				for(x = 1; x < xMax - 1; x += 2)
				{
					// code motion to avoid calculating xyzInd on every iteration
					int xyzInd = Index(x, y, z);
					int xyz_xmin = xyzInd - 1;
					int xyz_xplu = xyzInd + 1;
					int xyz_ymin = xyzInd - xMax;
					int xyz_yplu = xyzInd + xMax;
					int xyz_zmin = xyzInd - xyMax;
					int xyz_zplu = xyzInd + xyMax;
					double uInd = u[xyzInd];
					g[xyzInd] = 1.0 / sqrt(epsilon + 
						SQR(uInd - u[xyz_xplu]) + 
						SQR(uInd - u[xyz_xmin]) + 
						SQR(uInd - u[xyz_yplu]) + 
						SQR(uInd - u[xyz_ymin]) + 
						SQR(uInd - u[xyz_zplu]) + 
						SQR(uInd - u[xyz_zmin]));
					
					double uInd1 = u[xyzInd + 1];
					g[xyzInd + 1] = 1.0 / sqrt(epsilon + 
						SQR(uInd1 - u[xyz_xplu + 1]) + 
						SQR(uInd1 - u[xyz_xmin + 1]) + 
						SQR(uInd1 - u[xyz_yplu + 1]) + 
						SQR(uInd1 - u[xyz_ymin + 1]) + 
						SQR(uInd1 - u[xyz_zplu + 1]) + 
						SQR(uInd1 - u[xyz_zmin + 1]));
				}
			}
		}
			dummyMethod2();
		memcpy(conv, u, sizeof(double) * xMax * yMax * zMax);
		OMP_GaussianBlur(conv, Ksigma, 3);
			dummyMethod1();
		#pragma omp parallel for num_threads(16) private (x, y)
		for(z = 0; z < zMax; z++)
		{
			for(y = 0; y < yMax; y++)
			{
				for(x = 0; x < xMax; x++)
				{
					// more code motion, avoid calculating index of xyz 
					int xyzInd = Index(x, y, z);
					double r = conv[xyzInd] * f[xyzInd] / sigma2;
					r = (r * (2.38944 + r * (0.950037 + r))) / (4.65314 + r * (2.57541 + r * (1.48937 + r)));
					conv[xyzInd] -= f[xyzInd] * r;
				}
			}
		}
			dummyMethod2();
		OMP_GaussianBlur(conv, Ksigma, 3);
		converged = 0;
		//#pragma omp parallel for num_threads(16) private (x, y) reduction(+:converged)
		for(z = 1; z < zMax - 1; z++)
		{
			for(y = 1; y < yMax - 1; y++)
			{
				for(x = 1; x < xMax - 1; x++)
				{
					// more code motion
					int xyzInd = Index(x, y, z);
					int xyz_xmin = xyzInd - 1;
					int xyz_xplu = xyzInd + 1;
					int xyz_ymin = xyzInd - xMax;
					int xyz_yplu = xyzInd + xMax;
					int xyz_zmin = xyzInd - xyMax;
					int xyz_zplu = xyzInd + xyMax;

					double g_xmin = g[xyz_xmin];
					double g_xplu = g[xyz_xplu];
					double g_ymin = g[xyz_ymin];
					double g_yplu = g[xyz_yplu];
					double g_zmin = g[xyz_zmin];
					double g_zplu = g[xyz_zplu];

					double oldVal = u[xyzInd];
					double newVal = (oldVal + dt * ( 
						u[xyz_xmin] * g_xmin + 
						u[xyz_xplu] * g_xplu + 
						u[xyz_ymin] * g_ymin + 
						u[xyz_yplu] * g_yplu + 
						u[xyz_zmin] * g_zmin + 
						u[xyz_zplu] * g_zplu - gamma * conv[xyzInd])) /
						(1.0 + dt * (g_xplu + g_xmin + g_yplu + g_ymin + g_zplu + g_zmin));
					if(fabs(oldVal - newVal) < epsilon)
					{
						converged++;
					}
					u[xyzInd] = newVal;
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