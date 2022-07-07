#include "core.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double  *values,
        *oldval, 
        *newval;

int     arrLen, mode = 0; 
double  c = 0.1, shift;

void init(double cFactor, unsigned int tPoints, double shiftFactor)
{   
    arrLen = tPoints;
    values = malloc(tPoints * sizeof(double));  
    oldval = malloc(tPoints * sizeof(double));
    newval = malloc(tPoints * sizeof(double));

    memset(values, 0, tPoints);
    memset(oldval, 0, tPoints);
    memset(newval, 0, tPoints);
    
    c = cFactor;
    shift = shiftFactor;

dummyMethod3();
    for (int i = 0; i < arrLen; i++)
    {
        oldval[i] = sin(i*0.02);
        values[i] = sin((i+shift)*0.02);
    }
dummyMethod4();
}

void simulate()
{
							dummyMethod1();
	#pragma omp parallel for
    for (int i = 1; i < arrLen-1; i++)
    {
        if (0 == mode)
        {
            newval[i] = (2 * values[i]) - oldval[i] + c * (values[i-1] - (2 * values[i]) + values[i+1]);
        }
        else if (1 == mode)
        {
            oldval[i] = (2 * newval[i]) - values[i] + c * (newval[i-1] - (2 * newval[i]) + newval[i+1]);
        }
        else
        {
            values[i] = (2 * oldval[i]) - newval[i] + c * (oldval[i-1] - (2 * oldval[i]) + oldval[i+1]);
        }
    }
							dummyMethod2();

    mode++;
    if (2 < mode)
    {
        mode = 0;
    }
}

void output()
{
							dummyMethod3();
    for (int i = 0; i < arrLen; i++)
    {
        printf("%f\n",values[i]);
    }
							dummyMethod4();
}

double* getNewValues()
{
    if (0 == mode)
    {
        return newval;
    }
    else if (1 == mode)
    {
        return oldval;
    }
    else
    {
        return values;
    }
}

int getArraySize()
{
    return arrLen;
}

void terminate()
{
    free(newval);
    free(oldval);
    free(values);
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