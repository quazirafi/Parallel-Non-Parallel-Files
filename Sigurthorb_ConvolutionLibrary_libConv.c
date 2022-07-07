#include "libConv.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include "omp.h"
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void Convolution(unsigned char* paddedInput, unsigned char* output, int height, int width, int channels, float* kernel, int kSize) {
    int row, col, ch, krow, kcol;
    unsigned char ucValue = 0;
    double dValueKernel = 0;
    double dAgg[] = {0.0, 0.0, 0.0, 0.0};
    
    unsigned char ucAgg = 0;
    int chunkSize = width;
    int numThreads = 1;

#ifdef _OPENMP
    numThreads = omp_get_max_threads();
    chunkSize = ceil((double)width/numThreads);
#endif
    int kHalf = kSize/2;
    int paddedInputHeight = height + kHalf * 2;
    int paddedInputWidth = width + kHalf * 2;

							dummyMethod1();
#pragma omp parallel for private(col, row, ch, krow, kcol, ucValue, dValueKernel, dAgg, ucAgg) collapse(2) schedule(dynamic, chunkSize)
    for(row = kHalf; row < paddedInputHeight - kHalf; row++)
    {
        for(col = kHalf; col < paddedInputWidth - kHalf; col++)
        {
            for (krow = 0; krow < kSize; krow++)
            {
                for(kcol = 0; kcol < kSize; kcol++)
                {
                    for (ch = 0; ch < channels; ch++)
                    {
                        ucValue = paddedInput[((row - kHalf + krow) * paddedInputWidth * channels) + ((col - kHalf + kcol) * channels) + ch];
                        dValueKernel = kernel[krow * kSize + kcol];
                        dAgg[ch] += ucValue * dValueKernel;
                    }
                }
            }

            for (ch = 0; ch < channels; ch++)
            {
                ucAgg = dAgg[ch];
                if (dAgg[ch] - ucAgg >= 0.5)
                {
                    ucAgg += 1;
                }

                output[((row - kHalf) * width * channels) + ((col - kHalf) * channels) + ch] = ucAgg;
                dAgg[ch] = 0.0;
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