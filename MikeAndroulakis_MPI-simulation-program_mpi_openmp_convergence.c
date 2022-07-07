#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef _OPENMP
#include "omp.h"
#endif

#define NXPROB      1280                 /* x dimension of problem grid */
#define NYPROB      1024                 /* y dimension of problem grid */
#define STEPS       500                /* number of time steps */
#define NTAG        0                  /* north message tag */
#define STAG        1                  /*  south message tag */
#define WTAG        2                  /* north message tag */
#define ETAG        3 					/*  east message tag */


struct Parms {
        float cx;
        float cy;
} parms = {0.1, 0.1};


static inline void update ( int start_x, int end_x,int start_y, int end_y,int ny, float *u1, float *u2 )
{
        int b, c;
        #pragma parallel omp num_threads(4)
        for ( b = start_x; b <= end_x; b++ ) {
																	dummyMethod1();
        	#pragma parallel omp for schedule(static,1)
        	for ( c = start_y; c <= end_y; c++ ) {
            	*( u2+b*ny+c ) = *( u1+b*ny+c )  +
                 parms.cx * ( *( u1+ ( b+1 ) *ny+c ) + *( u1+ ( b-1 ) *ny+c ) - 2.0 * *( u1+b*ny+c ) ) +
                 parms.cy * ( *( u1+b*ny+c+1 ) + *( u1+b*ny+c-1 ) - 2.0 * *( u1+b*ny+c ) );
                }
																	dummyMethod2();
        }
}

static inline void inidat(int nx, int ny, float *u) {
        int b, c;

        for (b = 0; b <= nx-1; b++)
                for (c = 0; c <= ny-1; c++)
                        *(u+b*ny+c) = (float)(b * (nx - b - 1) * c * (ny - c - 1));
}

static inline void prtdat(int nx, int ny, float *u1, char *fnam) {
        int b, c;
        FILE *fp;

        fp = fopen(fnam, "w");
        for (c = ny-1; c >= 0; c--) {
                for (b = 0; b <= nx-1; b++) {
                        fprintf(fp, "%6.1f", *(u1+b*ny+c));
                        if (b != nx-1)
                                fprintf(fp, " ");
                        else
                                fprintf(fp, "\n");
                }
        }
        fclose(fp);
}

static inline int diff_between_elements(int a_bound,int b_bound,float u[2][a_bound][b_bound]){
	int converg_i,converg_j;
	int local_result;
	int result=1;
	dummyMethod1();
	#pragma omp parallel for private(vongerg_i,converg_j,local_result) reduction(&:result)
	
	for(converg_i=1; converg_i<a_bound; converg_i++){
		local_result=1;
		for(converg_j=1; converg_j<b_bound; converg_j++){
			local_result=local_result&(fabs(u[0][converg_i][converg_j]-u[1][converg_i][converg_j]) * 100/u[1][converg_i][converg_j])<=5;
		}
		result=result&local_result;

	}
	dummyMethod2();
	return result;
}

int main (int argc, char *argv[]){
        int taskid,             /* this task's unique id */
            numtasks,         /* number of tasks */
 		    north, south,west,east, /* neighbor tasks */
 		    rc=0,     /* misc */
            i,x,y,dimensions[2],periods[2],data_dimensions[2],new_old,send_convergence,receive_convergence,
            a,b,c;   /* dimension variables */
        MPI_Datatype row,col; /* datatypes */
        
        MPI_Comm cartesian; /*cartesian communicator */
        double start,end,time; /* timers */
        MPI_Request north_receive[2],south_receive[2],west_receive[2],east_receive[2],
                    north_send[2],south_send[2],west_send[2],east_send[2]; /* request variables */
                    
        MPI_Init(&argc,&argv);
        MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
        MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
        if ((NYPROB*NXPROB)%numtasks!=0) {
                MPI_Abort(MPI_COMM_WORLD,rc);
                exit(-1);
        } /* initialaation */       
        dimensions[0]=dimensions[1]=0;
        MPI_Dims_create(numtasks,2,dimensions);
        
        periods[0]=periods[1]=0;
        MPI_Cart_create(MPI_COMM_WORLD,2,dimensions,periods,1,&cartesian);
        MPI_Barrier(cartesian);  /* wait for all */
        MPI_Cart_shift(cartesian,0,1,&north,&south);
        MPI_Cart_shift(cartesian,1,1,&west,&east); /* create cartesian grid ang get neighbhors */
        
        data_dimensions[0]=data_dimensions[1]=0;
        MPI_Dims_create(NXPROB*NYPROB/numtasks,2,data_dimensions);
        x=data_dimensions[0]+2;
        y=data_dimensions[0]+2;
        float (*data)[x][y]=calloc(2,sizeof(*data));
        for (a=0; a<2; a++)
                for (b=0; b<x; b++)
                        for (c=0; c<y; c++)
                                data[a][b][c] = 0.0;
            
        inidat(x,y,&data[0][0][0]); /* get table dimensions */
        MPI_Barrier(cartesian); /* wait for all */
        MPI_Type_contiguous(x,MPI_FLOAT,&row);
        MPI_Type_commit(&row);
        MPI_Type_vector(y,1,x,MPI_FLOAT,&col);
        MPI_Type_commit(&col); /* make datatypes */
        MPI_Send_init(&data[0][1][0],1,row,north,STAG,cartesian,&north_send[0]);
        MPI_Recv_init(&data[0][0][0],1,row,north,NTAG,cartesian,&north_receive[0]);
        MPI_Send_init(&data[0][x-2][0],1,row,south,NTAG,cartesian,&south_send[0]);
        MPI_Recv_init(&data[0][x-1][0],1,row,south,STAG,cartesian,&south_receive[0]);
        MPI_Send_init(&data[0][0][1],1,col,west,ETAG,cartesian,&west_send[0]);
        MPI_Recv_init(&data[0][0][0],1,col,west,WTAG,cartesian,&west_receive[0]);
        MPI_Send_init(&data[0][0][y-2],1,col,east,WTAG,cartesian,&east_send[0]);
        MPI_Recv_init(&data[0][0][y-1],1,col,east,ETAG,cartesian,&east_receive[0]);
        MPI_Send_init(&data[1][1][0],1,row,north,STAG,cartesian,&north_send[1]);
        MPI_Recv_init(&data[1][0][0],1,row,north,NTAG,cartesian,&north_receive[1]);
        MPI_Send_init(&data[1][x-2][0],1,row,south,NTAG,cartesian,&south_send[1]);
        MPI_Recv_init(&data[1][x-1][0],1,row,south,STAG,cartesian,&south_receive[1]);
        MPI_Send_init(&data[1][0][1],1,col,west,ETAG,cartesian,&west_send[1]);
        MPI_Recv_init(&data[1][0][0],1, col,west,WTAG,cartesian,&west_receive[1]);
        MPI_Send_init(&data[1][0][y-2],1,col,east,WTAG,cartesian,&east_send[1]);
        MPI_Recv_init(&data[1][0][y-1],1,col,east,ETAG,cartesian,&east_receive[1]);
        /* initialaze communications,as we will always send and receive from the same table */
        start = MPI_Wtime(); /* start time */
        new_old=0;
        for(i=0; i<=STEPS; i++) {
                //First of all, we are going to make the connections by first sending data and then receiving
                MPI_Start(&north_send[new_old]);
                MPI_Start(&south_send[new_old]);
                MPI_Start(&west_send[new_old]);
                MPI_Start(&east_send[new_old]);
                MPI_Start(&north_receive[new_old]);
                MPI_Start(&south_receive[new_old]);
                MPI_Start(&west_receive[new_old]);
                MPI_Start(&east_receive[new_old]);
                update(2,x-3,2,y-3,x,&data[new_old][0][0],&data[1-new_old][0][0]);
                //And now we are going to wait for the needed borders for hallow points
                MPI_Wait(&east_receive[new_old],MPI_STATUS_IGNORE);
                MPI_Wait(&west_receive[new_old],MPI_STATUS_IGNORE);
                MPI_Wait(&north_receive[new_old],MPI_STATUS_IGNORE);
                MPI_Wait(&south_receive[new_old],MPI_STATUS_IGNORE);
                //Now that we have received the needed borders for the hallow points, we are going to update them
                update (1,x-2,1,1,x,&data[new_old][0][0],&data[1-new_old][0][0] );
                update (1,x-2,y-2,y-2,x,&data[new_old][0][0],&data[1-new_old][0][0] );
                update (1,1,1,y-2,x,&data[new_old][0][0],&data[1-new_old][0][0] );

                update (x-2,x-2,1,y-2,x,&data[new_old][0][0],&data[1-new_old][0][0] );
                //We wait for the sends finish

                MPI_Wait(&east_send[new_old],MPI_STATUS_IGNORE);
                MPI_Wait(&west_send[new_old],MPI_STATUS_IGNORE);
                MPI_Wait(&north_send[new_old],MPI_STATUS_IGNORE);
                MPI_Wait(&south_send[new_old],MPI_STATUS_IGNORE);
                //get the new table for the next iteration
                new_old=1-new_old;
                
                //we check the convergence every 5 steps
                if(i%5==0){
                	send_convergence=diff_between_elements(x-2,y-2,data);
                	MPI_Allreduce(&send_convergence,&receive_convergence,1,MPI_INT,MPI_LAND,cartesian);
                	if(receive_convergence==1){//an den yparxei diafora metaksy twn timwn
                		break;
                	}
                }
		}
		
        end= MPI_Wtime()-start;
        MPI_Reduce(&end,&time, 1,MPI_DOUBLE,MPI_MAX,0,cartesian); /* get time */
        if (taskid ==0) {
                printf("Time: %f\n",time);
        }
        MPI_Type_free(&row);
        MPI_Type_free(&col);
        free(data); /* free allocated datatypes and memory */
        MPI_Finalize();
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