/*  ======== main.c ========
*/

#include "_fake_typedefs.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// ======== taskFxn ========
//Void taskFxn(UArg a0, UArg a1)
void test()
{
    unsigned short *imgIn;
    unsigned int *imgOut;
    unsigned int i = 0;
    unsigned int j = 0;
    unsigned int k = 0;
    unsigned int l = 0;
    unsigned int m = 0;
    unsigned short featureIn[FEATURE_SIZE*FEATURE_SIZE];
    unsigned short *imgInMSMC;
    unsigned short temp = 0;
    uint64_t start_time, end_time;
    unsigned short tid = 0;
    printf("enter taskFxn()\n");

    long long imgInPix_64 = 0;
    long long featureInPix_64 = 0;

    imgInMSMC = (unsigned short *)(MSMC_ADDR);
    /* imgInMSMC = (unsigned short *)(EDMA_TEST_ADDR); */

    imgIn     = (unsigned short *)(IMG_IN_ADDRESS);
    
    imgOut    = (unsigned int *)(IMG_OUT_ADDRESS);

    /* Some feature initializations */
    for (i=0; i < FEATURE_SIZE; i++){
															dummyMethod1();
        temp = 0;
        for(j = 0; j < FEATURE_SIZE; j++){
            temp = temp +1;
            featureIn[i*FEATURE_SIZE+j] = temp;
        }
															dummyMethod2();
    }

        // some image initialization
    for (i=0; i < IMG_ROWS; i++){
															dummyMethod1();
        temp = 0;
        for(j = 0; j < IMG_COLS; j++){
            temp = temp +1;
            // imgIn[i*IMG_COLS + j] = temp;
            imgIn[i*IMG_COLS + j] = 1;
        }
															dummyMethod2();
    }

    temp = 0;
    /* printf("testing DMA \n"); */
    
    // Task_sleep(10);

    /* edmaInitiateXfer(imgInMSMC, imgIn+m*(NUM_ROWS_MSMC)*(IMG_COLS), (unsigned int)(NUM_BYTES), (unsigned int)(NUM_ARRAY), (unsigned int)(NUM_FRAMES), */
    /*                       SRCBIDX, DSTBIDX, 1, */
    /*                       1, 1, 1); */
    /*     edmaWait4Completion(1); */

    start_time = _itoll(TSCH,TSCL);
    for (m = 0; m < (NUM_MSMC_TX); m++){
        // invalidate cache
        CACHE_wbInvAllL1d(CACHE_WAIT);
        CACHE_wbInvAllL2(CACHE_WAIT);
        //Edma data to MSMMC
        edmaInitiateXfer(imgInMSMC, imgIn+m*(NUM_ROWS_MSMC)*(IMG_COLS), (unsigned int)(NUM_BYTES), (unsigned int)(NUM_ARRAY), (unsigned int)(NUM_FRAMES),
                          SRCBIDX, DSTBIDX, 1,
                          1, 1, 1);
        edmaWait4Completion(1);

        /* for (j = 0; j < NUM_L2_TX; j++){ */
        /*     //printf("In omp create loop\n"); */
        /*     //Call kernel operation for the data in MSMC, */
        /*     img_conv(imgInMSMC+j*(NUM_ROWS_L2)*(IMG_COLS), imgOut + i*(NUM_ROWS_MSMC)*(OUTPUT_COLS) + j*(NUM_ROWS_L2)*(IMG_COLS), featureIn, NUM_ROWS_L2, OUTPUT_COLS, FEATURE_SIZE); */
        /* } */

        
#pragma omp parallel for shared(imgInMSMC, imgOut) private(i,j,k,l, temp, featureIn, imgInPix_64, featureInPix_64)
															dummyMethod3();
        for (i = 0; i < (NUM_ROWS_MSMC-FEATURE_SIZE); i++) {
            //for (i = tid*(CHUNK_SIZE); i < (tid+1)*(CHUNK_SIZE); i++){
            for (j=0; j < OUTPUT_COLS; j++) {
                for (k = 0; k < FEATURE_SIZE; k++) {
                    for (l = 0; l < FEATURE_SIZE - 1; l += 4) {
                        /* temp += ((imgInMSMC[(i+k)*(IMG_COLS) + (j+l)] * featureIn[k*(FEATURE_SIZE)+l])); */
                        //imgOut[i][j] += imgIn[i+k][j+l] * featureIn[k][l];
                        imgInPix_64 = _mem8(&imgIn[(i+k)*(IMG_COLS) + j +l]);
                        featureInPix_64 = _mem8(&featureIn[k*(FEATURE_SIZE)+l]);
                            
                        // imgInPix_64 = _mem8(imgPtr+l);
                        // featureInPix_64 = _mem8(featurePtr+l);
                        temp += _dotpsu4h(imgInPix_64, featureInPix_64);
                    }
                    temp += imgIn[(i+k)*IMG_COLS + (j) + (FEATURE_SIZE)-1] * featureIn[k*(FEATURE_SIZE) + (FEATURE_SIZE)-1];                        
                }
                imgOut[m*(NUM_ROWS_MSMC)*(OUTPUT_COLS)+i*(OUTPUT_COLS) + j] = temp;
                temp = 0;
            }
        }
															dummyMethod4();
    }
    
    end_time = _itoll(TSCH,TSCL);
    printf("exit taskFxn()\n");
    printf("cycle count:%lld\n", end_time-start_time);
}

/*
 *  ======== main ========
 */
void main()
{ 
    /* Task_Handle task; */
    /* Error_Block eb; */

    #ifdef PARAMS
    printf("NUM_ROWS_MSMC: %d, NUM_ROWS_L2: %d, NUM_TX_MSMC: %d, NUM_TX_L2: %d, NUM_ARRAY: %d\n", (NUM_ROWS_MSMC), (NUM_ROWS_L2),(NUM_MSMC_TX), (NUM_L2_TX), (NUM_ARRAY));
    #endif


    int nthreads = NTHREADS;
    
    printf("enter main()\n");

    //    int nthreads = 0;
    // unsigned int tid = 0;

    edmaClose();
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