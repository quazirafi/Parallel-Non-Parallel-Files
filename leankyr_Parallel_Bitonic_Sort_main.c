#include"header.h"
#include<sys/time.h>
#include<string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char** argv){ 

    FILE *fp;
    omp_set_dynamic(0);
    omp_set_num_threads(4);
    struct timeval startwtime, endwtime;

    if(argc != 5){
        printf("Usage: filename size d toll\n");
        return 0;
    }
        
    char filename[256];
    strcpy(filename,argv[1]);
    unsigned int sz = atoi(argv[2]);
    float d = atof(argv[3]);
    float toll = atof(argv[4]);
    //-------------------------------------//
    //------Open Dataset From File---------//
    //------------------------------------//

    if((fp = fopen(filename,"r")) == NULL){
    fprintf(stderr,"[Error] Cannot open the file\n");
        exit(1);
        }
    //-------------------------------------//    
    //-------------INITIALIZE A------------//
    //------------------------------------//
    matrix A; // A is the graph
    A.size = sz;
    A.elements = memAlloc(sz);
    
    char line[1000];
    unsigned int i;
    int node1, node2;

    //SET MATRIX TO 0 

    setToZero(&A,sz);
    
    //Update A if there is an edge between nodes    

    while(!feof(fp)){
        fgets(line,sizeof(line), fp);
        if(strncmp(line, "#",1 ) != 0){
            if(sscanf(line,"%d\t%d\n",&node1,&node2)){  
                A.elements[node1][node2]= 1;
            }
        }
    }

    //printf("Our input to the system:\n");
    // matrixDisplay(&A);
    //------------------------------------// 
    //--------Initialize vector P---------//
    //------------------------------------//
    
    vector P;
    vector_init(&P, sz);
       
    //-------------------------------------//    
    //----------- Initliaze Out_link-------// 
    //-------------------------------------//
    //How many edged leave from node i

    vector out_link;
    vector_init(&out_link, sz);

    countOutlinks(&A, &out_link , sz); 
    

    //printf("The out nodes for each i node are:\n\n");
    //    vector_display(&out_link);
    // Give initial values to vector P
									dummyMethod3();
     for(i = 0;i < sz; i ++){
     P.elements[i] = 1.0/sz;
     }
									dummyMethod4();
    vector_normalize(&P);     
    //printf("The vector P is:  \n\n");
    //vector_display(&P); 

    //----------------------------------------------------//
    //-- Stochastiphy matrix A and deal with dungling nodes--/
    //----------------------------------------------------//
    stochastiphyMatrix(&A, &out_link, sz);
    
    //matrixDisplay(&A);

    //------------------------------------//
    //----- PAGERANK IMPLEMENTAION--------//
    //------------------------------------//

    matrixTranspose(&A); 

    int loop = 1;
    int k = 0 ; //num of loops 
    vector P_new;
    vector_init(&P_new,sz);

    // Create M matrix 
    createMatrixM(&A,d);
    //matrixDisplay(&A);
    gettimeofday (&startwtime, NULL);
    
    while(loop){

															dummyMethod1();
        #pragma omp parallel for schedule(static) num_threads(8)
        for(i = 0; i < sz ; i++){
            P_new.elements[i] = 0;
        }
															dummyMethod2();
        //calc new Probs 
        Power_Method(&P_new,&A,&P);
        //gaussSiedel(&P_new,&A,&P);
        //vector_display(&P_new);
        float error = 0.0;
        
															dummyMethod1();
        #pragma omp parallel for schedule(static) num_threads(8)
        for(i=0; i < sz ; i++){
            error = error + fabs(P_new.elements[i] - P.elements[i]);
        }
															dummyMethod2();
    
        if (error < toll)loop = 0;
    
    //update P
															dummyMethod1();
        #pragma omp parallel for schedule(static) num_threads(8)
        for(i = 0; i < sz ; i++){
            P.elements[i] = P_new.elements[i];
            } 
															dummyMethod2();
        k += 1;
        //printf("error is: %f at iteration %d\n",error,k);
    }

    gettimeofday (&endwtime, NULL);
    double exec_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6 
    + endwtime.tv_sec - startwtime.tv_sec);
    printf("k is: %d\n" , k);
    printf(" execution time = %lf\n", exec_time);

    //--------------------------------------------//
    //-----------Display Final Pagerank----------//
    //-------------------------------------------//
    
    vector_normalize(&P);
    //vector_display(&P);

    //------------------------------------------//
    //---------Freeing Memory-------------------//
    //------------------------------------------//

    matrix_free(&A);
    vector_free(&out_link);
    vector_free(&P);
    vector_free(&P_new);
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