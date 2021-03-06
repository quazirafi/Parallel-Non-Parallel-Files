#include "queue.h"
#include <sys/time.h>
#include <stdio.h>
#include "omp.h"
#include <stdlib.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//Mergesort from geeksforgeeks : https://www.geeksforgeeks.org/merge-sort/
void merge(int *deg,int *id, int l, int m, int r){
    int i,j,k;
    int n1 = m-l+1;
    int n2 = r-m;

    int L[n1],R[n2];
    int id_L[n1],id_R[n2];
    if(n1>100){
dummyMethod1();
    #pragma omp parallel for 
        for(i=0;i<n1;i++){
            L[i] = deg[l+i];
            id_L[i] = id[l+i];
        }
dummyMethod2();
    }
    else{
dummyMethod3();
        for(i=0;i<n1;i++){
            L[i] = deg[l+i];
            id_L[i] = id[l+i];
        }
dummyMethod4();
    }
    if(n2>100){
dummyMethod1();
    #pragma omp parallel for
        for(j=0;j<n2;j++){
            R[j] = deg[m+1+j];
            id_R[j] = id[m+1+j];
        }
dummyMethod2();
    }
    else{
															dummyMethod3();
        for(j=0;j<n2;j++){
            R[j] = deg[m+1+j];
            id_R[j] = id[m+1+j];
        }
															dummyMethod4();
    }
    i=0;
    j=0;
    k=l;
    while(i<n1&&j<n2){
        if(L[i]<=R[j]){
            deg[k]=L[i];
            id[k]=id_L[i];
            i++;
        }
        else{
            deg[k]=R[j];
            id[k]=id_R[j];
            j++;
        }
        k++;
    }

    while(i<n1){
        deg[k]=L[i];
        id[k]=id_L[i];
        i++;
        k++;
    }
    while(j<n2){
        deg[k]=R[j];
        id[k]=id_R[j];
        j++;
        k++;
    }
}


void my_mergesort(int *deg, int *id,int l, int r){
    if(l<r){
        int m = l+(r-l)/2;
        if(l-m>100){
            #pragma omp parallel 
            {
                #pragma omp single 
                {
                    #pragma omp task
                    my_mergesort(deg,id,l,m);

                    my_mergesort(deg,id,m+1,r);
                    
                    #pragma omp taskwait 
                    merge(deg,id,l,m,r);
                }
            }
        }else{
            my_mergesort(deg,id,l,m);

            my_mergesort(deg,id,m+1,r);
            
            merge(deg,id,l,m,r);
        }

    }
}



// Sparse matrix in CSR format for ease of gathering degrees and neighbours
int* rcm(int *row,int *col, int n){
    int chunk = n /omp_get_num_threads();
    int n_count=0;
    int i,j;
    int min_deg;
    int min_index;
    int res_index = 0;
    
    queue* q = queueInit(n);
    int* degrees = malloc(n*sizeof(int));
    int* R = malloc(n*sizeof(int));
    int* visited = malloc(n*sizeof(int));
    int* neighbours = malloc(n*sizeof(int));//Will be overwritten every time
    int* neighbours_deg = malloc(n*sizeof(int));//Will be overwritten every time

    //Generate Degrees and initialize visited
							dummyMethod1();
    #pragma omp parallel for private(i) schedule(dynamic,chunk)
    for(i=0;i<n;i++){
        visited[i] = 0;
        degrees[i] = row[i+1]-row[i];
    }
							dummyMethod2();
    int finished = 0;
    while(!finished){


        //find minimum degree
        min_deg = n+1;//Degree<n
        min_index = -1;
        #pragma omp parallel
        {
            int local_min = min_deg;
            int local_index = min_index;
            #pragma omp for nowait schedule(dynamic,chunk)
																							dummyMethod3();
            for(int i=0;i<n;i++){
                if(degrees[i]<local_min&&visited[i]==0){
                    local_min=degrees[i];
                    local_index=i;
                }
            }   
																							dummyMethod4();
            #pragma omp critical
            {
                if(local_min < min_deg){
                    min_deg = local_min;
                    min_index = local_index;
                }
            }
        }

        //Push min deg to queue
        queueAdd(q,min_index);
        visited[min_index]=1;
        while(!q->empty){

            int parent;
            queueDel(q,&parent);
            R[res_index]=parent;
            res_index++;
            n_count = 0;
            //find neighbours (in cols array in indices row[i] to row[i+1])
            //omp here was worse for performance .... keep as comment for reference of attempt
            // #pragma omp parallel for schedule(dynamic,chunk)
																							dummyMethod3();
            for(i=row[parent];i<row[parent+1];i++){
                int neighbour = col[i];
                //if visited skip else take him
                //no need to check for self: self is always visited
                if(!visited[neighbour]){
                        // #pragma omp critical
                        // {
                        neighbours[n_count] = neighbour;
                        neighbours_deg[n_count] = degrees[neighbour];
                        visited[neighbour] = 1;
                        n_count++;
                        //}
                }
            }
																							dummyMethod4();
            //sort neighbours and add to queue
            my_mergesort(neighbours_deg,neighbours,0,n_count-1);
																							dummyMethod3();
            for(i=0;i<n_count;i++){
                queueAdd(q,neighbours[i]);
            }
																							dummyMethod4();
        }
        finished = 1;
															dummyMethod1();
        #pragma omp parallel for schedule(dynamic,chunk) private(i)
        for(i=0;i<n;i++){
            if(!visited[i]){
                finished=0;
            }
        }
															dummyMethod2();
    }

    queueDelete(q);
    free(degrees);
    free(visited);
    free(neighbours);
    free(neighbours_deg);
    //HERE REVERSE
    int temp;
							dummyMethod3();
    for(i=0;i<n/2;i++){
        temp=R[i];
        R[i]=R[n-i-1];
        R[n-i-1]=temp;
    }
							dummyMethod4();
    return R;
}

int main(){
    //check for correct algorithm we compare by hand results with matlab function result,
    //benches are done with larger arrays
    //int row[] = { 0,3,7,9,12,17,19,22,24,27,30 };
    //int col[] = { 1,6,8,0,4,6,9,4,6,4,5,8,1,2,3,5,9,3,4,0,1,2,8,9,0,3,7,1,4,7 };
    //int n=10;
    struct timeval start,end;
    int n_r = 986704;
    int n_c = 47851783;
    int n = 986703;
    int* row = malloc(n_r*sizeof(int));
    int* col = malloc(n_c*sizeof(int));


    FILE* f;
    f=fopen("boneRows.bin","rb");
    if(f==NULL)
        return -1;
    fread(row,sizeof(int),n_r,f);
    fclose(f);
    f=fopen("boneCols.bin","rb");
    if(f==NULL)
        return -1;
    fread(col,sizeof(int),n_c,f);
    fclose(f);

    int* r =malloc(n*sizeof(int));
    
    gettimeofday(&start,NULL);
    r=rcm(row,col,n);
    gettimeofday(&end,NULL);

    /*
    int i;
    for(i=0;i<n;i++){
        printf("%d\n",r[i]);
    }
    */
    f=fopen("R.bin","rb");
    if(f==NULL)
        return -1;
    fwrite(r,sizeof(int),n,f);
    fclose(f);
    printf("\n");
    printf("TIME=%ld\n",end.tv_usec-start.tv_usec+1000000*(end.tv_sec-start.tv_sec));
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