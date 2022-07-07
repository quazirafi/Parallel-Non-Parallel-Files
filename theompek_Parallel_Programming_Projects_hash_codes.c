#include "stdio.h"
#include "stdlib.h"
#include "math.h"
#include "float.h"
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define DIM 3

inline unsigned int compute_code(float x, float low, float step){

  return floor((x - low) / step);//(επιστρεφει την μεγαλυτερη(ή ιση) ακεραια τιμη μεσα στην παρενθεση)συναρτηση της βιβλιοθηκης math.h

}


/* Function that does the quantization */
void quantize(unsigned int *codes, float *X, float *low, float step, int N){

 if(N>200000)
 { 

dummyMethod1();
#pragma omp parallel for shared(codes,X,low,step,N) schedule(static)              
  for(int i=0; i<N; i++){
    for(int j=0; j<DIM; j++){
      codes[i*DIM + j] = compute_code(X[i*DIM + j], low[j], step); 
    }
  }
dummyMethod2();

}
else{
	dummyMethod3();
	for(int i=0; i<N; i++){
    for(int j=0; j<DIM; j++){
      codes[i*DIM + j] = compute_code(X[i*DIM + j], low[j], step); 
    }
  }
	dummyMethod4();
}

}





float max_range(float *x){//βρισκει το μεγιστο απο εναν πινακα τυπου float

  float max = -FLT_MAX;//(float Max)
			dummyMethod3();
  for(int i=0; i<DIM; i++){
    if(max<x[i]){
      max = x[i];
    }
  }
			dummyMethod4();

  return max;

}

void compute_hash_codes(unsigned int *codes, float *X, int N,int nbins, float *min,float *max){
  
  float range[DIM];
  float qstep;

			dummyMethod3();
  for(int i=0; i<DIM; i++){
    range[i] = fabs(max[i] - min[i]); // The range of the data(Το εύρος των δεδομένων)
    range[i] += 0.01*range[i]; // Add somthing small to avoid having points exactly at the boundaries (προσθετουμε κατι μικρο για να αποφυγουμε τα ορια)
  }
			dummyMethod4();

  qstep = max_range(range) / nbins; // The quantization step (Το βήμα κβαντισμού)
  
  quantize(codes, X, min, qstep, N); // Function that does the quantization(Λειτουργία που κάνει το κβαντισμού)

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