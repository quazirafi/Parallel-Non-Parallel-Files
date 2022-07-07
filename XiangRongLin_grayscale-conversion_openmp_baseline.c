#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
void convert_baseline(unsigned char *img, int width, int height, int channels, int threads, unsigned char *result)
{
dummyMethod1();
#pragma omp parallel for collapse(2)
    for (int x = 0; x < width; x++)
    {
        for (int y = 0; y < height; y++)
        {
            result[y * width + x] =
                0.2126 * img[(y * width + x) * channels]        // red
                + 0.7152 * img[(y * width + x) * channels + 1]  // green
                + 0.0722 * img[(y * width + x) * channels + 2]; // blue
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