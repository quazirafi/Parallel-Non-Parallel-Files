#include"header.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(int argc, char** argv){ 
    
    FILE *fp;
    struct timeval startwtime, endwtime;
    //omp_set_dynamic(0);
    int num_threads = 8;
    if(argc != 2){
        printf("Usage: filename size d toll\n");
        return 0;
    }
        
    char filename[256];
    strcpy(filename,argv[1]);
    //unsigned int sz = atoi(argv[2]);
    //float toll = atof(argv[3]);
    //float d = atof(argv[4]);
    //-------------------------------------//
    //------Open Dataset From File---------//
    //------------------------------------//

    if((fp = fopen(filename,"r")) == NULL){
    fprintf(stderr,"[Error] Cannot open the file\n");
        exit(1);
        }
    //-------------------------------------//    
    //-------Find Num Of Nodes/Edges------//
    //------------------------------------//
    int n, e;
    char ch;
    char str[100];
    ch = getc(fp);
    while(ch == '#') {
        fgets(str,100-1,fp);
        //Debug: print title of the data set
        //printf("%s",str);
        sscanf (str,"%*s %d %*s %d", &n, &e); //number of nodes
        ch = getc(fp);
      }
      ungetc(ch, fp);

    // DEBUG: Print the number of nodes and edges, skip everything else
    
    /* Compressed sparse row format: 
     *- Val vector: contains 1.0 if an edge exists in a certain row
     *- Col_ind vector: contains the column index of the
     *  corresponding value in 'val'
     *- Row_ptr vector: points to the start of each row in
     *  'col_ind'
     *  */



    printf("\nGraph data:\n\n  Nodes: %d, Edges: %d \n\n", n, e);
    float *val = calloc(e, sizeof(float));
    int *col_ind = calloc(e, sizeof(int));
    int *row_ptr = calloc(n+1, sizeof(int));
    

    //float *val = (float*) malloc(e*sizeof(float));
    //int *col_ind = (int*) malloc(e*sizeof(int));
    //int *row_ptr = (int*) malloc((n+1)*sizeof(int));


    // The first row always starts at position 0
    row_ptr[0] = 0;

    int fromnode, tonode;
    int cur_row = 0;
    int i = 0;
    int j = 0;
    // Elements for row
    int elrow = 0;
    // Cumulative numbers of elements
    int cumel = 0;

    while(!feof(fp)){

    fscanf(fp,"%d%d",&fromnode,&tonode);

    // DEBUG: print fromnode and tonode
    //printf("From: %d To: %d\n",fromnode, tonode);

    if (fromnode > cur_row) { // change the row
        cumel = cumel + elrow;
															dummyMethod3();
        for (int k = cur_row + 1; k <= fromnode; k++) {
        row_ptr[k] = cumel;
      }
															dummyMethod4();
      elrow = 0;
      cur_row = fromnode;
    }
    val[i] = 1.0;
    col_ind[i] = tonode;
    elrow++;
    i++;
    }
    row_ptr[cur_row+1] = cumel + elrow - 1;

    // DEBUG: Print vectors involved so far
    /* 
    printf("\nVal vector:\n  [ ");
    for (i=0; i<e; i++){
        printf("%f ", val[i]);
      }
    printf("]\n");
    printf("\nCol_ind vector :\n  [ ");
    for (i=0; i<e; i++){
        printf("%d ", col_ind[i]);
      }
    printf("]\n");
    int size = sizeof(row_ptr) / sizeof(int);
    printf("\nrow_ptr vector (size = %d):\n  [ ", size);
    for (i=0; i< n+1; i++){
        printf("%d ", row_ptr[i]);
      }
    printf("]\n");
    // */ 
    // Fix the stochastization

    int *out_link = (int*) malloc(n*sizeof(int));
    
							dummyMethod3();
    for(i=0; i<n; i++){
        out_link[i] =0;
    }
							dummyMethod4();

    /* DEBUG: row pointer test
    printf("\nRow_ptr:\n");
     for (i=0; i<n; i++){
          printf("%d ", row_ptr[i]);
        }
    printf("\n");
    // */

    int rowel = 0;
							dummyMethod3();
    for(i=0; i<n; i++){
        if (row_ptr[i+1] != 0) {
          rowel = row_ptr[i+1] - row_ptr[i];
          out_link[i] = rowel;
        }
    }
							dummyMethod4();

    /* DEBUG: Outlink print test
    printf("\nOutlink:\n");
    for (i=0; i<n; i++){
        printf("%d ", out_link[i]);
      }
    printf("\n");
    //  */

    int curcol = 0;
							dummyMethod3();
    for(i=0; i<n; i++){
        rowel = row_ptr[i+1] - row_ptr[i];
        for (j=0; j<rowel; j++) {
            val[curcol] = val[curcol] / out_link[i];
            curcol++;
        }
    }
							dummyMethod4();

    /* DEBUG: val print test 
    for(i=0; i<e; i++){
      printf("%f ", val[i]);
    }
    // */

    /******************* INITIALIZATION OF P, DAMPING FACTOR ************************/

    // Set the damping factor 'd'
    float d = 0.85;

    // Initialize p[] vector
    float *p = (float*) malloc(n*sizeof(float));
    
							dummyMethod3();
    for(i=0; i<n; i++){
        p[i] = 1.0/n;
    }
							dummyMethod4();

    /*************************** PageRank LOOP  **************************/

    gettimeofday (&startwtime, NULL);
    // Set the looping condition and the number of iterations 'k'
    int looping = 1;
    int k = 0;

    // Initialize new p vector
    float *p_new = (float*) malloc(n*sizeof(float));
    while (looping){

   
    // Initialize p_new as a vector of n 0.0 cells
							dummyMethod1();
    #pragma omp parallel for schedule(auto) num_threads(num_threads)
    for(i=0; i<n; i++){
      p_new[i] = 0.0;
    }
							dummyMethod2();

    int rowel = 0;
    int curcol = 0;
    // Page rank modified algorithm 
    //#pragma omp parallel for schedule(dynamic) num_threads(8)
    /*       
    for(i=0; i<n; i++){ 
      rowel = row_ptr[i+1] - row_ptr[i];
      for (j=0; j<rowel; j++ ) {
        p_new[col_ind[curcol]] = p_new[col_ind[curcol]] + val[curcol] * p[i];
        curcol++;
        
      }
    }
   // */
    
    //#pragma omp parallel for schedule(dynamic) num_threads(8)
							dummyMethod3();
    for(i=0; i<n; i++){ 
        rowel = row_ptr[i+1] - row_ptr[i];
        for(j=0; j<rowel; j++ ){
            if(p_new[i] == 0){ 
            p_new[col_ind[curcol]] = p_new[col_ind[curcol]] + val[curcol] * p[i];}  
            else{ 
            p_new[col_ind[curcol]] = p_new[col_ind[curcol]] + val[curcol] * p_new[i];}
            curcol++;
        
      }
    }
							dummyMethod4();
    // */
    /*//DEBUG: print pnew
    for (i=0; i<n; i++){
      printf("%f ", p_new[i]);
    }
    // */

    // Adjustment to manage dangling elements 
							dummyMethod1();
    #pragma omp parallel for schedule(auto) num_threads(num_threads)
    for(i=0; i<n; i++){
      p_new[i] = d * p_new[i] + (1.0 - d) / n;
    }
							dummyMethod2();

    /*DEBUG: print pnew after the damping factor multiplication
    for (i=0; i<n; i++){
      printf("%f ", p_new[i]);
    }*/
       
    // TERMINATION: check if we have to stop
    float error = 0.0;
							dummyMethod3();
    for(i=0; i<n; i++) {
      error =  error + fabs(p_new[i] - p[i]);
    }
							dummyMethod4();
    //if two consecutive instances of pagerank vector are almost identical, stop
    if (error < 0.00000000001){
      looping = 0;
    }

    // Update p[]
							dummyMethod1();
    #pragma omp parallel for schedule(auto) num_threads(num_threads)
    for (i=0; i<n;i++){
        p[i] = p_new[i];
    }
							dummyMethod2();

    // Increase the number of iterations
    k = k + 1;
    }

    /*************************** CONCLUSIONS *******************************/
    gettimeofday (&endwtime, NULL);
    vector_normalize(p,n);
    double exec_time = (double)((endwtime.tv_usec - startwtime.tv_usec)/1.0e6 
    + endwtime.tv_sec - startwtime.tv_sec);
    printf("k is: %d\n" , k);
    printf(" execution time = %lf\n", exec_time);


    // Sleep(500);

    // Print results

    printf ("\nNumber of iteration to converge: %d \n\n", k); 
     
    /* 
    printf ("Final Pagerank values:\n\n[");
    for (i=0; i<n; i++){
    printf("%.16f ", p[i]);
    if(i!=(n-1)){ printf(", "); }
    }printf("\n");
    // */
    
    
    free(p_new);
    free(p);
    free(out_link);
    free(row_ptr);
    free(col_ind);
    free(val);
     
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