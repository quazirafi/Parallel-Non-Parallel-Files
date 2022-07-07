#include"pqsort.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void merge(void *base1, int bnum1, void *base2, int bnum2, size_t bsize,
           int (*compare)(const void*, const void*)){
     unsigned char *t, *c1, *c2;
     int nr, ns, nt;

     c1 = (unsigned char*)base1;
     c2 = (unsigned char*)base2;
     t  = (unsigned char*)malloc(bsize*(bnum1+bnum2));
     nr = 0; ns=0; nt=0;
     while(nr < bnum1 && ns < bnum2){
          if(compare(&c1[nr*bsize], &c2[ns*bsize]) < 0){
               memcpy(&t[nt*bsize], &c1[nr*bsize], bsize);
               nr++;
          }
          else{
               memcpy(&t[nt*bsize], &c2[ns*bsize], bsize);
               ns++;
          }
          nt++;
     }
     if(nr < bnum1) memcpy(&t[nt*bsize], &c1[nr*bsize], bsize*(bnum1-nr));
     else           memcpy(&t[nt*bsize], &c2[ns*bsize], bsize*(bnum2-ns));
     memcpy(base1, &t[0],           bsize*bnum1);
     memcpy(base2, &t[bsize*bnum1], bsize*bnum2);
     free(t);
     return;
};

void pqsort(void *base, int num, size_t size,
            int (*compare)(const void*, const void*)){
     int i, fb, sb;
     int threads;
     int *bidx, *bnum;
     int aid, bid;
     int thread_lg;
     threads = 1;
     threads = omp_get_num_procs();
     thread_lg = (int)pow(2, (int)log2((int)threads));
     bidx = (int*)malloc(sizeof(int)*(thread_lg+1));
     bnum = (int*)malloc(sizeof(int)*(thread_lg));

									dummyMethod4();
									dummyMethod3();
     for(i=0;i<thread_lg;i++) bidx[i] = i * (int)num / thread_lg;
     bidx[thread_lg] = (int)num;
									dummyMethod4();
									dummyMethod3();
     for(i=0;i<thread_lg;i++) bnum[i] = bidx[i+1] - bidx[i];

									dummyMethod1();
     #pragma omp parallel for
     for(i=0;i<thread_lg;i++){
          qsort((void*)(base+size*bidx[i]), bnum[i], size, compare);
     }
									dummyMethod2();

     // bitonic sort
     for(fb=1; fb<=(int)log2(thread_lg);fb++){
          for(sb=fb-1;sb>=0;sb--){
																													dummyMethod1();
               #pragma omp parallel for private(aid, bid)
               for(i=0;i<thread_lg;i++){
                    aid = i^(1<<sb);
                    bid = i;
                    if(((i>>fb)&1)^((i>>sb)&1)){
                         merge((void*)(base+size*bidx[aid]), bnum[aid],
                               (void*)(base+size*bidx[bid]), bnum[bid],
                               size, compare);
                    }
               }
																													dummyMethod2();
          }
     }
     free(bidx); free(bnum);
     return;
};

void* pqsort_thread_wrapper(void* args){
     qsort_args* qs_args;
     qs_args = (qsort_args*)args;
     pqsort(qs_args->base, qs_args->num, qs_args->bsize, qs_args->compare);
     return NULL;
}

pthread_t pqsort_thread(qsort_args* args){
     int status;
     pthread_t thread;
     status = pthread_create(&thread, NULL, pqsort_thread_wrapper,
                             (void*)args);
     if(status != 0){
          printf("ERR : pthread_create\n");
          exit(1);
     }
     return thread;
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