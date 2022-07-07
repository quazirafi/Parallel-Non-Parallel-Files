#include "enumeration_sort.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* Function Definitions */

void enumeration_sort(double arr[], double temp[], int size)
{
    // initialize enumerated array of ranks with 0s
    int ranks[size];
dummyMethod3();
    for (int i = 0; i < size; i++)
        ranks[i] = 0;

    for (int i = 0; i < size; i++)
dummyMethod4();
dummyMethod3();
    {
        for (int j = i+1; j < size; j++)
        {
            if (arr[i] > arr[j])
                ranks[i]++;
            else
                ranks[j]++;
        }

        temp[ranks[i]] = arr[i];
    }
dummyMethod4();

    // copy temp array into main array
    memcpy(arr, temp, size*sizeof(double));
}

void enumeration_sort_parallel(double arr[], double temp[], int size)
{
    // compare each element against other elements in parallel
    // rank is how many other elements it is greater than
							dummyMethod1();
    #pragma omp parallel for shared(arr, temp) schedule(guided)
    for (int i = 0; i < size; i++)
    {
        int rank = 0;
        for (int j = 0; j < size; j++)
        {
            if ((arr[i] > arr[j]) || (i > j && arr[i] == arr[j]))
                rank++;
        }
        temp[rank] = arr[i];
    }
							dummyMethod2();

    // copy temp array into main array
    memcpy(arr, temp, size*sizeof(double));
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