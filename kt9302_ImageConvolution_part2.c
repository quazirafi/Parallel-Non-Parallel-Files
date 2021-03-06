#define KERNX 3 //this is the x-size of the kernel. It will always be odd.
#define KERNY 3 //this is the y-size of the kernel. It will always be odd.
#include <emmintrin.h> /* where intrinsics are defined */
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
int conv2D(float* in, float* out, int data_size_X, int data_size_Y,
           float* kernel)
{
    // the x coordinate of the kernel's center
    int kern_cent_X = (KERNX - 1)/2;
    // the y coordinate of the kernel's center
    int kern_cent_Y = (KERNY - 1)/2;
    //int data_size_X = data_size_X+kern_cent_X*2;
    //int newY = data_size_Y+kern_cent_Y*2;
    float copy[KERNX*KERNY];

dummyMethod3();
    for (int c = 0; c < KERNX*KERNY; c++) {
        copy[c ] = kernel[c ];
    }
dummyMethod4();
    kernel = copy;//put kernel on cache
							dummyMethod3();
    for (int x=0;x<kern_cent_X;x++){
        for (int y=0;y<kern_cent_Y;y++){
            for(int j = -y; j <= kern_cent_Y; j++){
                for(int i = -x; i <= kern_cent_X; i++){
                    out[x+y*data_size_X] +=
                    kernel[(kern_cent_X-i)+(kern_cent_Y-j)*KERNX] * in[(x+i) + (y+j)*data_size_X];

                }
            }
        }
        for (int y=data_size_Y-kern_cent_Y;y<data_size_Y;y++){
            for(int j = -kern_cent_Y; j<=data_size_Y-1-y; j++){
                for(int i = -x; i <= kern_cent_X; i++){
                    out[x+y*data_size_X] +=
                    kernel[(kern_cent_X-i)+(kern_cent_Y-j)*KERNX] * in[(x+i) + (y+j)*data_size_X];

                }
            }
        }
    }
							dummyMethod4();
							dummyMethod3();
    for (int x=data_size_X-kern_cent_X;x<data_size_X;x++){
        for (int y=0;y<kern_cent_Y;y++){
        for(int j = -y; j <= kern_cent_Y; j++){
            for(int i = -kern_cent_X; i <= data_size_X-1-x; i++){
                out[x+y*data_size_X] +=
                kernel[(kern_cent_X-i)+(kern_cent_Y-j)*KERNX] * in[(x+i) + (y+j)*data_size_X];

            }
        }
        }
        for (int y=data_size_Y-kern_cent_Y;y<data_size_Y;y++){
            for(int j = -kern_cent_Y; j<=data_size_Y-1-y; j++){
                for(int i = -kern_cent_X; i <= data_size_X-1-x; i++){
                    out[x+y*data_size_X] +=
                    kernel[(kern_cent_X-i)+(kern_cent_Y-j)*KERNX] * in[(x+i) + (y+j)*data_size_X];

                }
            }
        }
    } //for 4 corners;
							dummyMethod4();
   
							dummyMethod3();
    for (int x=kern_cent_X;x<data_size_X-kern_cent_X;x++){
        for (int y=0;y<kern_cent_Y;y++){
            for(int j = -y; j <= kern_cent_Y; j++){
                for(int i = -kern_cent_X; i <= kern_cent_X; i++){
                    out[x+y*data_size_X] +=
                    kernel[(kern_cent_X-i)+(kern_cent_Y-j)*KERNX] * in[(x+i) + (y+j)*data_size_X];
                }
            }
        }
    }
							dummyMethod4();
  
							dummyMethod3();
    for (int x=kern_cent_X;x<data_size_X-kern_cent_X;x++){
        for (int y=data_size_Y-kern_cent_Y;y<data_size_Y;y++){
            for(int j = -kern_cent_Y; j <= data_size_Y-1-y; j++){
                for(int i = -kern_cent_X; i <= kern_cent_X; i++){
                    out[x+y*data_size_X] +=
                    kernel[(kern_cent_X-i)+(kern_cent_Y-j)*KERNX] * in[(x+i) + (y+j)*data_size_X];

                }
            }
        }
    }
							dummyMethod4();
  
							dummyMethod3();
    for (int y=kern_cent_Y;y<data_size_Y-kern_cent_Y;y++){
        for (int x=0;x<kern_cent_X;x++){
            for(int j = -kern_cent_Y; j <= kern_cent_Y; j++){
                for(int i = -x; i <= kern_cent_X; i++){
                    out[x+y*data_size_X] +=
                    kernel[(kern_cent_X-i)+(kern_cent_Y-j)*KERNX] * in[(x+i) + (y+j)*data_size_X];

                }
            }
        }
    }
							dummyMethod4();

							dummyMethod3();
    for (int y=kern_cent_Y;y<data_size_Y-kern_cent_Y;y++){
        for (int x=data_size_X-kern_cent_X;x<data_size_X;x++){
            for(int j = -kern_cent_Y; j <= kern_cent_Y; j++){
                for(int i = -kern_cent_X; i <= data_size_X-1-x; i++){
                    out[x+y*data_size_X] +=
                    kernel[(kern_cent_X-i)+(kern_cent_Y-j)*KERNX] * in[(x+i) + (y+j)*data_size_X];

                }
            }
        }
    }//4 strips
							dummyMethod4();
							dummyMethod1();
    #pragma omp parallel for 
    for(int y = kern_cent_Y; y < data_size_Y-kern_cent_Y; y++){
        int x = kern_cent_X;
        int offset = y*data_size_X;
        for(x = kern_cent_X; x < (data_size_X-kern_cent_X)/12*12-12; x+=12){
            int outpos = x+offset;
            __m128 result1 = _mm_set1_ps(0);
            __m128 result2 = _mm_set1_ps(0);
            __m128 result3 = _mm_set1_ps(0);
            for(int j = -kern_cent_Y; j <= kern_cent_Y; j++){
                int temp  = (y+j)*data_size_X; // Y reference
                int temp1 =(kern_cent_Y-j)*KERNX;
                for(int i = -kern_cent_X; i <= kern_cent_X; i++){
                    int kerpos = (kern_cent_X-i)+temp1;
                    int ref=(x+i)+temp;
                    __m128 kerval1 = _mm_set1_ps(kernel[kerpos]);
                    __m128 inval1 = _mm_loadu_ps(in+ref);
                    __m128 kerval2 = _mm_set1_ps(kernel[kerpos]);
                    __m128 inval2 = _mm_loadu_ps(in+ref+4);
                    __m128 kerval3 = _mm_set1_ps(kernel[kerpos]);
                    __m128 inval3 = _mm_loadu_ps(in+ref+8);
                    result1 =  _mm_add_ps(_mm_mul_ps(inval1,kerval1),result1);
                    result2 =  _mm_add_ps(_mm_mul_ps(inval2,kerval2),result2);
                    result3 =  _mm_add_ps(_mm_mul_ps(inval3,kerval3),result3);
				}
			}
            _mm_storeu_ps(out+outpos, result1);
            _mm_storeu_ps(out+outpos+4, result2);
            _mm_storeu_ps(out+outpos+8, result3);
		}
        for (;x<data_size_X-kern_cent_X; x++){
            
            for(int i = -kern_cent_X; i <= kern_cent_X; i++){
				for(int j = -kern_cent_Y; j <= kern_cent_Y; j++){
                    out[x+y*data_size_X] +=
                    kernel[(kern_cent_X-i)+(kern_cent_Y-j)*KERNX] * in[(x+i) + (y+j)*data_size_X];
				}
			}
            
        }
	}
							dummyMethod2();
    
    return 1;
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