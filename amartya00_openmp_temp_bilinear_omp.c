#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define NTHREADS 8 
void bilinear_omp (unsigned int *in, unsigned int width, unsigned int height, float theta, unsigned int *out) {

    unsigned int i =0;
    unsigned int j =0;
    unsigned short chunkSize = 0;

    double itcos = 0;
    double itsin = 0;
    int it = 0;
    int jt = 0;
    double ir =0;
    double jr = 0;
    double sinTh = 0;
    double cosTh = 0;

    int si = 0;
    int sj = 0;

    sinTh = sin(theta);
    cosTh = cos(theta);

    printf("theta:%f, cosTh: %f, sinTh: %f", theta, cosTh, sinTh);

    int nthreads;
    nthreads = NTHREADS;
    omp_set_num_threads(nthreads);

    chunkSize = height/nthreads;


											dummyMethod1();
#pragma omp parallel for shared(in, out) private(i,j,jt, it, itcos, itsin, ir ,jr, si, sj) schedule(static)
      for (i = 0; i < height -1; i++){
        
        it = (i - (height)/2);
        itcos = it * cosTh;
        itsin = it * sinTh;

        for (j = 0; j < width -1; j++){
	  jt = (j - (width)/2);
	  ir = itcos - jt * sinTh;
	  jr = itsin + jt * cosTh;
            
	  /* printf("\nj:%d",j); */
	  /* printf("\nir:%f\njr:%f\n", ir, jr); */

	  ir = ir + height/2 -1;
	  jr = jr + width/2 -1;

	  /* if (ir > height -1) ir = height - 1; */
	  /* else if (ir < 0) ir = 0; */

	  /* if (jr > width -1) jr = width -1 ; */
	  /* else if (jr < 0) jr = 0; */
            
	  si = (ir);
	  sj = (jr);

	  if (si > 0 && si < height -1){
	    if(sj >0 && sj < width -1){
	      out[i * width + j] = in[si * width + sj];
	    }
	  }
	  else
	    out[i*width +j] = 0;

            
	  //             printf("\nir:%f\njr:%f\n", ir, jr);
	  // out[i * width + j] = in[si * width + sj] + in[(si+1) * width + sj] +
	  //     in[si * width + sj +1] + in[(si+1) * width + sj +1];
	  //out[i * width + j] = in[i * width +j];

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