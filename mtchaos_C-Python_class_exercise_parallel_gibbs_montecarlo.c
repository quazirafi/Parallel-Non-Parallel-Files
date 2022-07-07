// J = 1,T = 2/log(sqrt(2) + 1)。トーラス状の二次元強磁性イジングモデルを熱浴法でシュミレーションして、磁化を計算する。OpenMp

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int f(int x,int L){
    if(x == -1){
        return L-1;
    }else if(x == L){
        return 0;
    }else{
        return x;
    }
}

void init_xor128(unsigned int s0, unsigned int *s) {
    int i = 0;
dummyMethod3();
    for (i = 0; i < 4; ++i){
        s0 = 1812433253U * ( s0 ^ ( s0 >> 30 ) ) + i;
        s[i] = s0;
    }
dummyMethod4();
}

unsigned int xor128(unsigned int *s) {
    unsigned int t = ( s[0] ^ ( s[0] << 11 ) );
    s[0] = s[1];
    s[1] = s[2];
    s[2] = s[3];
    s[3] = ( s[3] ^ ( s[3] >> 19 ) ) ^ ( t ^ ( t >> 8 ) );
    return s[3];
}

double ur(unsigned int *s){
    return ((double) xor128(s))/4294967296e0;
}

int main(int argc,char const * argv[]){
    
    //変数宣言
    double start = omp_get_wtime();
    int L;
    double z;
    if (argc == 1 || argc >= 3){ /* 引数なし or 引数3つ以上 */
        printf("引数に整数を1ついれてください。\n");
        return 1;
    }
    else{
        L = atoi(*++argv);
    }
    
    double T;
    double randomNum; //random number between 0 and 1
    double P;   //次の状態を選ぶための条件付き確率
    double tmp,sum;
    int sum_s = L*L;  //sum s_i
    double m;   //磁化m
    int spin[L][L]; //格子状のspinの状態
    unsigned int seed[4];
    int i,j,k,l,n;
    int s = 0;
    int mcs = (int)pow(10,5);
    unsigned int* a;
    unsigned int b;
    n = omp_get_max_threads();
    double mean_m[n];
    int points = 12;
    
    FILE *file_output;
    file_output = fopen("data_L_z_m.txt","a");
    if(file_output == NULL) {
        printf("the file can`t be opened\n");
        return -1;
    }
    
    
    printf("max threads (set): %d\n", n);
    //fprintf(file_output,"%d\n",L);
    
    //初期状態は全て１とする
							dummyMethod3();
    for(i = 0; i < L; i++){
        for(j = 0; j < L; j++){
            spin[i][j] = 1;
        }
    }
							dummyMethod4();
    
    
    for(k = 0;k < points;k++){
        
        z = 1.2 + (k*0.3)/points;
        T = 2.0/log(z + 1.0);
        m = 0.0;
        
															dummyMethod1();
        #pragma omp parallel for private(l,i,j,tmp,P,randomNum,a,b,seed) firstprivate(sum_s,spin) num_threads(n)
        for(s = 0;s < n; s++){
            
            seed[0] = (unsigned int)(s+1);
            seed[1] = (unsigned int)pow(s+1,2);
            seed[2] = (unsigned int)pow(s+1,3);
            seed[3] = (unsigned int)pow(s+1,4);
            
            
            for(l = 0;l < mcs;l++){
                for(i = 0;i < L;i++){
                    for(j = 0;j< L;j++){
                        
                        tmp = (spin[f(i+1,L)][j]+spin[f(i-1,L)][j]+spin[i][f(j+1,L)]+spin[i][f(j-1,L)])/T;
                        P = (1 + tanh(tmp))/2.0;
                        
                        randomNum = ur(seed);
                        
                        if(randomNum < P){
                            if(spin[i][j] == -1){
                                sum_s += 2;
                            }else{
                                sum_s -= 2;
                            }
                            spin[i][j] = -1 * spin[i][j];
                            
                        }
                        
                    }
                }
                if( l >= 1000){
                    m += (double)abs(sum_s)/(L*L*(mcs-1000));
                }
            }
            mean_m[s] = m;
        }
															dummyMethod2();
        
        sum = 0;
        for(i = 0;i < n;i++){
            sum += mean_m[i];
        }
        
        fprintf(file_output,"%lf %lf\n",z,sum/n);
    }
    
    fclose(file_output);
    
    double elapsed_time = omp_get_wtime() -start;
    printf("time = %lf\n",elapsed_time);
    
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