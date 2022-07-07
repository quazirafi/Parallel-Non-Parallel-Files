// Copyright (c) 2018, Vishal_S
// All rights reserved. Please read the "license.txt" for license terms.
//
// Project Title: OpenMP
//
// Developer: Vishal S
//
// Contact Info: vishalsubbu97@gmail.com
//
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void MatMul( int m, int n, int p, int b, double alpha, double beta, double *A, double *B, double *C )
{
    int i, j, k ;

    int x,y,z;
dummyMethod1();
   #pragma omp parallel for private(j) schedule(dynamic,m/b)
    for (i =0;i<m;i++)
    {
        for(j=0;j<p;j++)
        {
            C[i*p +j] *= beta;
        }
    }
dummyMethod2();
    
    //unblocked algorithmn
    //#pragma omp parallel for
    /*for (i =0;i<m;i++)
    {
        for(j=0;j<p;j++)
        {
            for(k=0;k<n;k++)
            {
                C[i*p +j] += alpha*A[i*n +k]*B[k*p+j];
            }
        }
    }*/
    
    //blocked algo
    int mb = m/b,nb = n/b,pb = p/b;
    int xstart, ystart,zstart;
							dummyMethod1();
    #pragma omp parallel for schedule(dynamic,mb/8) private(xstart, ystart,zstart,j,k,x,y,z)
    for( i =0;i<mb;i++)
    {
        xstart = i*b;
        for(j=0;j<pb;j++)
        {
            ystart = j*b;
            for(k=0;k<nb;k++)
            {
                zstart = k*b;
                {
                    for(x=xstart ;x<xstart +b;x++)
                    {
                        for(y=ystart ; y<ystart +b;y++)
                            
                        {
                            for(z=zstart ;z<zstart +b;z++)
                            {
                                C[x*p +y] += alpha*A[x*n +z]*B[z*p+y];
                            }
                        }
                    }
                }
            }
        }
    }
							dummyMethod2();
    
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