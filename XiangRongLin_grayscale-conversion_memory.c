#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void convert_memory(unsigned char *img, int width, int height, int channels, int threads, unsigned char *result)
{
    int pixel_per_thread = (width * height) / threads;
dummyMethod1();
#pragma omp parallel for
    for (int thread = 0; thread < threads; thread++)
    {
        int end;
        if (thread + 1 == threads)
        {
            end = width * height;
        }
        else
        {
            end = pixel_per_thread * (thread + 1);
        }

        for (int i = pixel_per_thread * thread; i < end; i++)
        {
            result[i] =
                0.2126 * img[(i * channels)]    // red
                + 0.7152 * img[(i * channels) + 1]  // green
                + 0.0722 * img[(i * channels) + 2]; // blue
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