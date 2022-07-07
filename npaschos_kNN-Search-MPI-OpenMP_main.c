#include "read_data.h"
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
// #include <math.h>
#include <mpi.h>
#include "omp.h"

double calc_dist(double* array1, double* array2);
void swap(double *xp, double *yp);
void update_neighbors(double* neighbors_matrix, int* neighbors_index, double distance, int number_of_neighbors, int index);
void selectionSort(double* arr, int* neighbors_index, int n);
void swap_int(int *xp, int *yp);

void test(int** neighbors_index, int world_size, int world_rank);
 
struct timeval startwtime, endwtime;
double seq_time;

const int LEN = 60000;
const int DIM = 30;

int number_of_neighbors = 10;	//TO-DO: read from argv | atoi()

//BLOCKING == 1 -> BLOCKING IMPLEMENTATION
//BLOCKING !=1 -> NON-BLOCKING IMPLEMENTATION
int BLOCKING = 1;				//TO-DO: read from argv | atoi()

int main(int argc, char** argv){

	//MPI
	MPI_Init(NULL,NULL);
	int world_size;
	MPI_Comm_size(MPI_COMM_WORLD, &world_size);
	// Get the rank of the process
	int world_rank;
	MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);



	//read data
	double* data_x = read_data_custom(LEN/(world_size) * world_rank, LEN/(world_size) * (world_rank+1));
	//init_state
	double* data_send = read_data_custom(LEN/(world_size) * world_rank, LEN/(world_size) * (world_rank+1));
	//data proccess
	double* data_proc = read_data_custom(LEN/(world_size) * world_rank, LEN/(world_size) * (world_rank+1));
	double* tmp = NULL;

	//array to store distances
	double **neighbors_matrix = (double **)malloc(LEN/(world_size) * sizeof(double *));
	int **neighbors_index = (int **)malloc(LEN/(world_size) * sizeof(int *));

	dummyMethod3();
	for (int i=0; i<LEN/(world_size); i++){
		neighbors_matrix[i] = (double *)malloc(number_of_neighbors * sizeof(double));
		memset(neighbors_matrix[i], 0, number_of_neighbors * sizeof(double));
	}
	dummyMethod4();

	dummyMethod3();
	for (int i=0; i<LEN/(world_size); i++){
		neighbors_index[i] = (int *)malloc(number_of_neighbors * sizeof(int));
		memset(neighbors_index[i], 0, number_of_neighbors * sizeof(int));
	}
	dummyMethod4();

	MPI_Barrier(MPI_COMM_WORLD);
	printf("Counter started: %d\n", world_rank);
	if(world_rank==0){
		gettimeofday( &startwtime, NULL );
	}

	// test(neighbors_index, world_size, world_rank);

	// BLOCKING
	double dist = 0;
	int reps = LEN/world_size;
	int i=0;

	if(BLOCKING){
		if(world_rank==0)
			printf("BLOCKING\n");
			dummyMethod1();
		#pragma omp parallel for num_threads(4) default(shared) private(i)
		for(i=0; i<reps; ++i){
			for(int j=0; j<reps; ++j){
				// calc distance between data_x i and j
				dist = calc_dist(data_x+i*DIM,data_x+j*DIM);
				// update dist and index tables accordingly
				update_neighbors(neighbors_matrix[i], neighbors_index[i], dist, number_of_neighbors, world_rank*LEN/world_size+j);
			}
		}
			dummyMethod2();
		test(neighbors_index, world_size, world_rank);

		for(int rep=0; rep<world_size-1; ++rep){

			// printf("rep: %d world rank: %d proc: %d\n", rep+1, world_rank, (((rep+1) + world_rank) % 4)*LEN/world_size);
			int send_dest;
			(world_rank+1) < world_size ? (send_dest=world_rank+1) : (send_dest=0);
			int rec_from;
			(world_rank-1) >= 0 ? (rec_from=world_rank-1) : (rec_from=world_size-1);
			if(world_rank%2){
				// SEND data_send
				MPI_Send(data_send,LEN/world_size *sizeof(double),MPI_DOUBLE,send_dest,0,MPI_COMM_WORLD);
				// RECEIVE data_proc
				MPI_Recv(data_proc,LEN/world_size *sizeof(double),MPI_DOUBLE,rec_from,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			}
			else{
				// RECEIVE data_proc
				MPI_Recv(data_proc,LEN/world_size *sizeof(double),MPI_DOUBLE,rec_from,0,MPI_COMM_WORLD, MPI_STATUS_IGNORE);
				// SEND data_send
				MPI_Send(data_send,LEN/world_size *sizeof(double),MPI_DOUBLE,send_dest,0,MPI_COMM_WORLD);
			}

			// calc and update (same loop as before rep loop)
			int i=0;
			int proc = (((rep+1) + world_rank) % 4);

					dummyMethod1();
			#pragma omp parallel for num_threads(4) default(shared) private(i)
			for(i=0; i<reps; ++i){
				for(int j=0; j<reps; ++j){
					// calc distance between data_x i and data_proc j
					dist = calc_dist(data_x+i*DIM,data_proc+j*DIM);
					// update dist and index tables accordingly
					update_neighbors(neighbors_matrix[i], neighbors_index[i], dist, number_of_neighbors, proc*LEN/world_size+j);
				}
			}
					dummyMethod2();

			// test(neighbors_index, world_size, world_rank);

			// swap pointers data_send and data_proc
			tmp = data_send;
			data_send = data_proc;
			data_proc = tmp;
		}
	}

	else{// NON-BLOCKING

		double* tmpnb = (double*)malloc(LEN/world_size*DIM*sizeof(double));
		if(world_rank==0)
			printf("NON-BLOCKING\n");
		MPI_Status status;
		MPI_Request send_request, recv_request;
		
		int send_dest;
		(world_rank+1) < world_size ? (send_dest=world_rank+1) : (send_dest=0);
		int rec_from;
		(world_rank-1) >= 0 ? (rec_from=world_rank-1) : (rec_from=world_size-1);
		
		if(world_rank%2){	// might not be needed due to non-blocking technique
			// SEND data_send
			MPI_Isend(data_send,LEN/world_size *sizeof(double),MPI_DOUBLE,send_dest,0,MPI_COMM_WORLD, &send_request);
			// RECEIVE data_proc
			MPI_Irecv(data_proc,LEN/world_size *sizeof(double),MPI_DOUBLE,rec_from,MPI_ANY_TAG,MPI_COMM_WORLD, &recv_request);
		}
		else{
			// RECEIVE data_proc
			MPI_Irecv(tmpnb,LEN/world_size *sizeof(double),MPI_DOUBLE,rec_from,MPI_ANY_TAG,MPI_COMM_WORLD, &recv_request);
			// SEND data_send
			MPI_Isend(data_send,LEN/world_size *sizeof(double),MPI_DOUBLE,send_dest,0,MPI_COMM_WORLD, &send_request);
		}

			dummyMethod1();
		#pragma omp parallel for num_threads(4) default(shared) private(i)
		for(i=0; i<reps; ++i){
			for(int j=0; j<reps; ++j){
				// calc distance between data_x i and j
				dist = calc_dist(data_x+i*DIM,data_x+j*DIM);
				// update dist and index tables accordingly
				update_neighbors(neighbors_matrix[i], neighbors_index[i], dist, number_of_neighbors, world_rank*LEN/world_size+j);
			}
		}
			dummyMethod2();
		MPI_Wait(&send_request,&status);
		MPI_Wait(&recv_request,&status);

		data_send = data_proc;
		data_proc = tmpnb;

		// test(neighbors_index, world_size, world_rank);

		for(int rep=0; rep<world_size-1; ++rep){

			(world_rank+1) < world_size ? (send_dest=world_rank+1) : (send_dest=0);
			(world_rank-1) >= 0 ? (rec_from=world_rank-1) : (rec_from=world_size-1);

			if(world_rank%2){	// might not be needed due to non-blocking technique
				// SEND data_send
				MPI_Isend(data_send,LEN/world_size *sizeof(double),MPI_DOUBLE,send_dest,0,MPI_COMM_WORLD, &send_request);
				// RECEIVE data_proc
				MPI_Irecv(tmpnb,LEN/world_size *sizeof(double),MPI_DOUBLE,rec_from,MPI_ANY_TAG,MPI_COMM_WORLD, &recv_request);
			}
			else{
				// RECEIVE data_proc
				MPI_Irecv(tmpnb,LEN/world_size *sizeof(double),MPI_DOUBLE,rec_from,MPI_ANY_TAG,MPI_COMM_WORLD, &recv_request);
				// SEND data_send
				MPI_Isend(data_send,LEN/world_size *sizeof(double),MPI_DOUBLE,send_dest,0,MPI_COMM_WORLD, &send_request);
			}
			
			int proc = (((rep+1) + world_rank) % 4);
					dummyMethod1();
			#pragma omp parallel for num_threads(4) default(shared) private(i)
			for(int i=0; i<reps; ++i){
				for(int j=0; j<reps; ++j){
					// calc distance between data_x i and j
					dist = calc_dist(data_x+i*DIM,data_proc+j*DIM);
					// update dist and index tables accordingly
					update_neighbors(neighbors_matrix[i], neighbors_index[i], dist, number_of_neighbors, proc*LEN/world_size+j);
				}
			}
					dummyMethod2();
			
			MPI_Wait(&send_request,&status);
			MPI_Wait(&recv_request,&status);
			
			data_send = data_proc;
			data_proc = tmpnb;

			// test(neighbors_index, world_size, world_rank);

		}
	}

	printf("world rank: %d\n", world_rank);
	MPI_Barrier(MPI_COMM_WORLD);
	if(world_rank==0){
		gettimeofday( &endwtime, NULL );
		seq_time = (double)( ( endwtime.tv_usec - startwtime.tv_usec ) / 1.0e6 + endwtime.tv_sec - startwtime.tv_sec );
		printf( "%f\n", seq_time );
	}

	test(neighbors_index, world_size, world_rank);

	// Finalize the MPI environment.
	MPI_Finalize();



	return 0;
}

double calc_dist(double* array1, double* array2){

	double dist = 0.0;
	double tmp = 0;

	for(int i=0; i<30; ++i){	// TO-DO: replace with const int DIST = 30;
		// dist += pow(array1[i] - array2[i],2);
		// array1[i]+=1;
		// array1[i]+=1;
		tmp = array1[i] - array2[i];
		dist += tmp*tmp;
	}

	return dist;
}

void test(int** neighbors_index, int world_size, int world_rank){

	double* labels = read_labels();
	int cur_labels[DIM]; 
	int labels_freq[number_of_neighbors];
	int res = 0.0;
	int cur_label = 0.0;
	int cur_max = 0;
	int label = 0;

	for(int i=0; i<LEN/world_size; ++i){
		for(int j=0; j<number_of_neighbors; ++j){
			cur_labels[j] = (int)labels[(int)neighbors_index[i][j]] - 1;	// -1 because labels range is [1,10] and positions are [0,9]
			// printf("%d\n",cur_labels[j]);
		}
		memset(&labels_freq, 0, number_of_neighbors*sizeof(int));
		for(int j=0; j<number_of_neighbors; ++j){
			labels_freq[cur_labels[j]-1]++;		// -1 because labels range is [1,10] and positions are [0,9]
		}
		cur_max=labels_freq[0];
		label = 0;
		for(int j=0; j<number_of_neighbors; ++j){
			if(labels_freq[j] > cur_max){
				cur_max = labels_freq[j];
				label = j+1;
			}
		}
		// printf("calc: %d label: %d\n", label, (int)labels[LEN/world_size * world_rank + i]-1);
		if(label == (int)labels[LEN/world_size * world_rank + i]-1){	// -1 because labels range is [1,10] and positions are [0,9]
			++res;
		}

	}
	// res = res;
	printf("World rank: %d acc: %d/%d\n", world_rank, res, LEN/world_size);
}

void update_neighbors(double* neighbors_matrix, int* neighbors_index, double distance, int number_of_neighbors, int index){

	double tmp = 0.0;
	int index_tmp = 0;
	//check && update_neighbors
	for(int i=0; i<number_of_neighbors; i+=number_of_neighbors-1){
		// printf("distance: %f, neighbors_matrix[i]: %f, %d\n", distance, neighbors_matrix[i], distance < neighbors_matrix[i]);
		if(distance < neighbors_matrix[i]){
			tmp = neighbors_matrix[i];
			index_tmp = neighbors_index[i];
			neighbors_matrix[i] = distance;
			neighbors_index[i] = index;
			if(tmp!=0){
				neighbors_matrix[number_of_neighbors-1] = tmp;
				neighbors_index[number_of_neighbors-1] = index_tmp;
				//sort
				selectionSort(neighbors_matrix, neighbors_index, number_of_neighbors);
			}
			break;
		}
		else if(neighbors_matrix[i]==0 && distance > 0){
			neighbors_matrix[i] = distance;
			neighbors_index[i] = index;
			//sort
			selectionSort(neighbors_matrix, neighbors_index, number_of_neighbors);
			break;
		}
	}
}

void selectionSort(double* arr, int* neighbors_index, int n){
	int i, j, min_idx;

	// One by one move boundary of unsorted subarray
	for (i = 0; i < n-1; i++)
	{
		// Find the minimum element in unsorted array
		min_idx = i;
		for (j = i+1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		// Swap the found minimum element with the first element
		swap(&arr[min_idx], &arr[i]);
		swap_int(&neighbors_index[min_idx], &neighbors_index[i]);
	}
}

void swap(double *xp, double *yp){
	double temp = *xp;
	*xp = *yp;
	*yp = temp;
}

void swap_int(int *xp, int *yp){
	int temp = *xp;
	*xp = *yp;
	*yp = temp;
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