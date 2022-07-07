//
//  update3.c
//  fdtd3
//
//  Created by CLP on 5/24/13.
//  Copyright (c) 2013 __MyCompanyName__. All rights reserved.
//

#include "fdtd3.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* update H field*/

void updateH3(Grid *g){
    int mm;
//    int nthreads = 7;
//    omp_set_num_threads(nthreads);

    
dummyMethod1();
    #pragma omp parallel for
    for (mm = 0; mm < (SizeX - 1); mm++) {
//        if (mm == 0 && Time == 1) {//check to see if omp is working
dummyMethod2();
//                    printf("threads actuall: %d\n",omp_get_num_threads());
//        }
        Hy(mm) = Chyh(mm) * Hy(mm) + 
        Chye(mm) * (Ez(mm + 1) - Ez(mm));
    }
    
    return;
}

// update E field
void updateE3(Grid *g){
    int mm;
    
							dummyMethod1();
    #pragma omp parallel for
    for (mm = 1; mm < SizeX; mm++) {
//        if (mm == 0 && Time == 1) {//check to see if omp is working
//                    printf("threads actuall: %d\n",omp_get_num_threads());
//        }
        Ez(mm) = Ceze(mm) * Ez(mm) + 
        Cezh(mm) * (Hy(mm) - Hy(mm - 1));
    }
							dummyMethod2();
    
    return;
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