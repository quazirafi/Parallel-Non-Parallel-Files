#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//include header file 
#include "Accessor_c.h"

int main(){
   
    int * x = (int *)malloc(sizeof(int)*10);
    int * y = (int *)malloc(sizeof(int)*10);
    int * z = (int *)malloc(sizeof(int)*10);

    // declare a struct on the format accessor_<ACCESS_MODE>_<TYPE>
    accessor_read_int ac_x;
    accessor_read_int ac_y;
    accessor_write_int ac_z;

    // set accessor struct data members
    ac_x.data = x;
    ac_x.len = 10;

    ac_y.data = y;
    ac_y.len = 10;

    ac_z.data = z;
    ac_z.len = 10;

dummyMethod1();
#pragma omp target teams distribute parallel for 
    for (int i=0; i< 10; i++){
        // access the "data" member of the accessor struct
        ac_z.data[i] = ac_x.data[i] + ac_y.data[i];
    }
dummyMethod2();

    // free dynamic data
    free(x);
    free(y);
    free(z);

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