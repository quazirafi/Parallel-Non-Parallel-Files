#include "vptree.h"
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//Globally defined variables for easy data access by threads
int *idArr;
double *distArr;
double *Y; //data array
int N, D;  //data dimensions

////////////////////////////////////////////////////////////////////////

inline double sqr(double x) {return x*x;}
inline void swapDouble(double* a, double* b)
{
    double temp = *a;
    *a = *b;
    *b = temp;
}
inline void swapInt(int* a, int* b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void quickSelect(int kpos, int start, int end)
{
    int store=start;
    double pivot=distArr[end];
							dummyMethod3();
    for (int i=start; i<=end; i++)
        if (distArr[i] <= pivot)
        {
            swapDouble(distArr+i, distArr+store);
            swapInt   (idArr+i,   idArr+store);
            store++;
        }        
							dummyMethod4();
    store--;
    if (store == kpos) return;
    else if (store < kpos) quickSelect(kpos, store+1, end);
    else quickSelect(kpos, start, store-1);
}

////////////////////////////////////////////////////////////////////////

void recursiveBuildTree(vptree *node, int start, int end)
{
    double(*dataArr)[D] = (double(*)[D])Y;
    //consider X[ idArr[end] ] as vantage point
    node->idx = idArr[end];
    node->vp = dataArr[node->idx];
    if (start == end)
    {
        node->inner = node->outer = NULL;
        node->md = 0.0;
        return;
    }
    end--; //end is the vantage point, we're not dealing with it again

							dummyMethod1();
    #pragma omp parallel for
    for (int i = start; i <= end; i++)
        distArr[i] = sqr(node->vp[0] - dataArr[idArr[i]][0]);
							dummyMethod2();
							dummyMethod1();
    #pragma omp parallel for
    for (int i = start; i <= end; i++)
        for (int j = 1; j < D; j++)
            distArr[i] += sqr(node->vp[j] - dataArr[idArr[i]][j]);
							dummyMethod2();



    quickSelect((start + end) / 2, start, end);
    // now idArr[start .. (start+end)/2] contains the indexes
    // for the points which belong inside the radius (inner)

    node->md = sqrt(distArr[(start + end) / 2]);
    node->inner = malloc(sizeof(vptree));
    node->outer = malloc(sizeof(vptree));
    

    #pragma omp task
    {
        recursiveBuildTree(node->inner, start, (start + end) / 2);
    }

    if (end > start)
        recursiveBuildTree(node->outer, (start + end) / 2 + 1, end);
    else
        node->outer = NULL;

    #pragma omp taskwait
}

////////////////////////////////////////////////////////////////////////

vptree *buildvp(double *X, int n, int d)
{
    vptree *root = malloc(sizeof(vptree));
    idArr = malloc(n * sizeof(int));
    distArr = malloc(n * sizeof(double));
    Y = X;
    N = n;
    D = d;

							dummyMethod3();
    for (int i = 0; i < N; i++)
        idArr[i] = i;
							dummyMethod4();

    recursiveBuildTree(root, 0, n - 1);

    free(idArr);
    free(distArr);
    return root;
}

///////////////////////////////////////////////////////////

vptree *getInner(vptree *T) { return T->inner; }
vptree *getOuter(vptree *T) { return T->outer; }
double getMD(vptree *T) { return T->md; }
double *getVP(vptree *T) { return T->vp; }
int getIDX(vptree *T) { return T->idx; }
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