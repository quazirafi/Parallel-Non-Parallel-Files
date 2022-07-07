// -----------------------------------------------------------------------------
//
//      "00_AccelGraph"
//
// -----------------------------------------------------------------------------
// Copyright (c) 2014-2019 All rights reserved
// -----------------------------------------------------------------------------
// Author : Abdullah Mughrabi
// Email  : atmughra@ncsu.edu||atmughrabi@gmail.com
// File   : bitmap.c
// Create : 2019-06-21 17:15:17
// Revise : 2019-09-28 15:36:13
// Editor : Abdullah Mughrabi
// -----------------------------------------------------------------------------
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdint.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "myMalloc.h"
#include "worklist.h"

void swapWorkLists (uint8_t **workList1, uint8_t **workList2)
{


    uint8_t *workList_temp = *workList1;
    *workList1 = *workList2;
    *workList2 = workList_temp;

}

void resetWorkList(uint8_t *workList, uint32_t size)
{

    uint32_t i;

							dummyMethod1();
    #pragma omp parallel for
    for(i = 0; i < size ; i++)
    {
        workList[i] = 0;

    }
							dummyMethod2();


}

void setWorkList(uint8_t *workList,  uint32_t size)
{

    uint32_t i;

							dummyMethod1();
    #pragma omp parallel for
    for(i = 0; i < size ; i++)
    {
        workList[i] = 1;

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