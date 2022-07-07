#include "Life.h"
#include "Defaults.h"
#include <math.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

// Default parameters for the simulation
const int     DEFAULT_SIZE = 120;
const int     DEFAULT_GENS = 1000;
const double     INIT_PROB = 0.25;

// Cells become DEAD with more than UPPER_THRESH
// or fewer than LOWER_THRESH neighbors
const int UPPER_THRESH = 3;
const int LOWER_THRESH = 2;

// Cells with exactly SPAWN_THRESH neighbors become ALIVE
const int SPAWN_THRESH = 3;

/*
	init_env()
		Initialize runtime environment.
*/
int init (struct life_t * life, int * c, char *** v) {
	int argc          = *c;
	char ** argv      = *v;
	life->rank        = 0;
	life->size        = 1;
	life->ncols       = DEFAULT_SIZE;
	life->nrows       = DEFAULT_SIZE;
	life->generations = DEFAULT_GENS;
	life->infile      = NULL;
	life->outfile     = NULL;

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &life->rank);
	MPI_Comm_size(MPI_COMM_WORLD, &life->size);

	int sqr = sqrt(life->size);
	int dims[2]={sqr,sqr},
	periods[2]={1,1}, reorder=0;


// MPI Cart Creation for the communication between the processes
	MPI_Cart_create(MPI_COMM_WORLD, 2, dims, periods, reorder, &life->comm);
	MPI_Cart_coords(life->comm, life->rank, 2, life->coords);

//MPI Datatypes In Order to send Rows and Cols
	MPI_Type_vector(life->ncols, 1, 1, MPI_INT, &life->row);
	MPI_Type_commit(&life->row);

	MPI_Type_vector(life->nrows, 1, life->ncols+2, MPI_INT, &life->col);
	MPI_Type_commit(&life->col);


	seed_random(life->rank);

	parse_args(life, argc, argv);

	init_grids(life);


}

/*
	eval_rules()
		Evaluate the rules of Life for each cell; count
		neighbors and update current state accordingly.
*/
int eval_rules (struct life_t * life) {
	int neighbors;

	int ncols = life->ncols;
	int nrows = life->nrows;

	int ** grid      = life->grid;
	int ** next_grid = life->next_grid;
	int changes = 0;
	int i,j,k,l;
					dummyMethod1();
	#pragma omp parallel for private(neighbors, j, k, l) reduction(+: changes) collapse(2) num_threads(2)
	// {
			for (i = 1; i <= ncols; i++) {
				for (j = 1; j <= nrows; j++) {
					neighbors = 0;

					// count neighbors
					for (k = i-1; k <= i+1; k++) {
						for (l = j-1; l <= j+1; l++) {
							if (!(k == i && l == j) && grid[k][l] != DEAD)
								neighbors++;
						}
					}

					// update state
					if (neighbors < LOWER_THRESH || neighbors > UPPER_THRESH)
						next_grid[i][j] = DEAD;
					else if (grid[i][j] != DEAD || neighbors == SPAWN_THRESH)
						next_grid[i][j] = grid[i][j]+1;
					else
						next_grid[i][j] = grid[i][j];

					if(next_grid[i][j] != grid[i][j])
						changes++;
				}
			}
					dummyMethod2();
	//  }
	return changes;
}

/*
	copy_bounds()
		Copies sides, top, and bottom to their respective locations.
		All boundaries are considered periodic.

		In the MPI model, processes are aligned As Cartesian System.
		All Sides are sent to neighboring processes.
*/
void copy_bounds (struct life_t * life) {
	int i,j;

	int rank  = life->rank;
	int size  = life->size;
	int ncols = life->ncols;
	int nrows = life->nrows;
	int * coords = life->coords;
	int ** grid = life->grid;

	MPI_Status status;

	// Some MPIs deadlock if a single process tries to communicate
	// with itself
	if (size != 1) {
		// copy sides to neighboring processes
		int sqr = sqrt(size);
		int i, j;
		int neighbor;
		int neighcoord[2];
		MPI_Request send_requests[8];
		MPI_Request recv_request[8];
			dummyMethod3();
		for (i = coords[0]-1; (i<=coords[0]+1 ); i++ )
		{
			for (j = coords[1]-1; (j<=coords[1]+1 ); j++)
			{
				if(!(i == coords[0]) || !(j== coords[1]))
				{

					neighcoord[0] = i;
					neighcoord[1] = j;
					MPI_Cart_rank(life->comm, neighcoord, &neighbor);

					if(coords[0] == neighcoord[0] )
					{
						if (coords[1] == neighcoord[1]+1)
						{ /* Send and Receive from process' Right*/
							MPI_Isend(&grid[1][1], 1, life->col, neighbor, RIGHT , life->comm,&send_requests[0] );
							MPI_Irecv(&grid[1][0], 1, life->col, neighbor,LEFT, life->comm, &recv_request[0]);
						}
						else
						{ /* Send and Receive from process' Left*/
							MPI_Isend(&grid[1][ncols], 1, life->col, neighbor, LEFT , life->comm,&send_requests[1] );
							MPI_Irecv(&grid[1][ncols+1], 1, life->col, neighbor,RIGHT, life->comm, &recv_request[1]);
						}
					}
					else if ( coords[0] == neighcoord[0]+1 )
					{
							if ( coords[1] == neighcoord[1]+1 )
							{/* Send and Receive from process' Upleft*/
								MPI_Isend(&grid[1][1], 1, MPI_INT, neighbor, UPLEFT , life->comm,&send_requests[2] );
								MPI_Irecv(&grid[0][0], 1, MPI_INT, neighbor,DOWNRIGHT, life->comm, &recv_request[2]);
							}
							else if ( coords[1] == neighcoord[1])
							{/* Send and Receive from process' Up*/
								MPI_Isend(&grid[1][1], 1, life->row, neighbor, UP , life->comm,&send_requests[3] );
								MPI_Irecv(&grid[0][1], 1, life->row, neighbor, DOWN, life->comm, &recv_request[3]);
							}
							else
							{/* Send and Receive from process' UpRight*/
								MPI_Isend(&grid[1][ncols], 1, MPI_INT, neighbor, UPRIGHT , life->comm,&send_requests[4] );
								MPI_Irecv(&grid[0][ncols+1], 1, MPI_INT, neighbor, DOWNLEFT, life->comm, &recv_request[4]);
							}
						}
					else if( coords[0] == neighcoord[0]-1 )
					{
							if ( coords[1] == neighcoord[1]+1)
							{/* Send and Receive from process' DownLeft*/
								MPI_Isend(&grid[nrows][ncols], 1, MPI_INT, neighbor, DOWNLEFT , life->comm,&send_requests[5] );
								MPI_Irecv(&grid[nrows+1][ncols+1], 1, MPI_INT, neighbor, UPRIGHT, life->comm, &recv_request[5]);
							}
							else if ( coords[1] == neighcoord[1] )
							{/* Send and Receive from process' Down*/
								MPI_Isend(&grid[nrows][1], 1, life->row, neighbor, DOWN , life->comm,&send_requests[6] );
								MPI_Irecv(&grid[nrows+1][1], 1, life->row, neighbor, UP, life->comm, &recv_request[6]);
							}
							else
							{/* Send and Receive from process' DownRight*/
								MPI_Isend(&grid[nrows][ncols], 1, MPI_INT, neighbor, DOWNRIGHT , life->comm,&send_requests[7] );
								MPI_Irecv(&grid[nrows+1][ncols+1], 1, MPI_INT, neighbor, UPLEFT, life->comm, &recv_request[7]);
							}
						}
				}
		 }
		}
			dummyMethod4();

		MPI_Waitall(8, recv_request, MPI_STATUSES_IGNORE);
			dummyMethod3();
		for( i = 0; i < 8 ; i++)
		{
		 	MPI_Request_free(&send_requests[i]);
			// MPI_Request_free(&recv_request[i]);
		}
			dummyMethod4();
	}

	// Copy sides locally to maintain periodic boundaries
	// when there's only one process
	if (size == 1) {
			dummyMethod3();
		for (j = 0; j < nrows+2; j++) {
			grid[ncols+1][j] = grid[1][j];
			grid[0][j] = grid[ncols][j];
		}
			dummyMethod4();

		// copy corners
		grid[0][0]             = grid[0][nrows];
		grid[0][nrows+1]       = grid[0][1];
		grid[ncols+1][0]       = grid[ncols+1][nrows];
		grid[ncols+1][nrows+1] = grid[ncols+1][1];

		// copy top and bottom
			dummyMethod3();
		for (i = 1; i <= ncols; i++) {
			grid[i][0]       = grid[i][nrows];
			grid[i][nrows+1] = grid[i][1];
		}
			dummyMethod4();
	}
}

/*
	update_grid()
		Copies temporary values from next_grid into grid.
*/
void update_grid (struct life_t * life) {
	int ncols = life->ncols;
	int nrows = life->nrows;
	int ** grid      = life->grid;
	int ** next_grid = life->next_grid;

	life->grid = next_grid;
	life->next_grid = grid;
}


/*
	// allocate_grids()
		Allocates memory for a 2D array of integers.
*/
void allocate_grids (struct life_t * life) {
	int i,j;
	int ncols = life->ncols;
	int nrows = life->nrows;

	life->grid      = (int **) malloc(sizeof(int *) * (ncols+2));
	life->next_grid = (int **) malloc(sizeof(int *) * (ncols+2));

	life->grid[0] = malloc(sizeof(int)*(ncols+2)*(nrows+2));
	life->next_grid[0] = malloc(sizeof(int)*(ncols+2)*(nrows+2));
	//Allocation in continuous spots
	dummyMethod3();
	for ( i = 1; i < ncols+2; i++ ){
		life->grid[i] = &life->grid[0][(i * (ncols+2))];
		life->next_grid[i] = &life->next_grid[0][(i * (ncols+2))];
	}
	dummyMethod4();

}

/*
	init_grids()
		Initialize cells based on input file, otherwise all cells
		are DEAD.
*/
void init_grids (struct life_t * life) {
	FILE * fd;
	int i,j;
	char * file;
	if (life->infile != NULL) {
		file = malloc(strlen(life->outfile)+life->rank%10+2);
		sprintf(file, "%s%d", life->infile, life->rank);

		if ((fd = fopen(file, "r")) == NULL) {
			perror("Failed to open file for input");
			exit(EXIT_FAILURE);
		}

		if (fscanf(fd, "%d %d\n", &life->ncols, &life->nrows) == EOF) {
			printf("File must at least define grid dimensions!\nExiting.\n");
			exit(EXIT_FAILURE);
		}

	}

	allocate_grids(life);

	dummyMethod3();
	for (i = 0; i < life->ncols+2; i++) {
		for (j = 0; j < life->nrows+2; j++) {
			life->grid[i][j]      = DEAD;
			life->next_grid[i][j] = DEAD;
		}
	}
	dummyMethod4();

	if (life->infile != NULL) {
		while (fscanf(fd, "%d %d\n", &i, &j) != EOF) {
			life->grid[i][j]      = ALIVE;
			life->next_grid[i][j] = ALIVE;
		}

		fclose(fd);

		free(file);
	} else {
		randomize_grid(life, INIT_PROB);
	}
}

/*
	write_grid()
		Dumps the current state of life.grid to life.outfile.
*/
void write_grid (struct life_t * life) {
	FILE * fd;
	int i,j;
	int ncols   = life->ncols;
	int nrows   = life->nrows;
	int ** grid = life->grid;

	if (life->outfile != NULL) {
		char * file = malloc(strlen(life->outfile)+life->rank%10+2);
		sprintf(file, "%s%d", life->outfile, life->rank);
		if ((fd = fopen(file, "w")) == NULL) {
			perror("Failed to open file for output");
			exit(EXIT_FAILURE);
		}

		fprintf(fd, "%d %d\n", ncols, nrows);

			dummyMethod3();
		for (i = 1; i <= ncols; i++) {
			for (j = 1; j <= nrows; j++) {
				fprintf(fd, "%d ", grid[i][j]);
			}
			fprintf(fd, "\n");
		}
			dummyMethod4();
		fprintf(fd, "END \n");
		fclose(fd);
		free(file);
	}
}

/*
	free_grids()
		Frees memory used by an array that was allocated
		with allocate_grids().
*/
void free_grids (struct life_t * life) {
	int i;
	int ncols = life->ncols;

	// for (i = 0; i < ncols+2; i++) {
	// 	free(life->grid[i]);
	// 	free(life->next_grid[i]);
	// }
	free(life->grid[0]);
	free(life->next_grid[0]);
	free(life->grid);
	free(life->next_grid);
}

/*
	rand_double()
		Generate a random double between 0 and 1.
*/
double rand_double() {
	return (double)random()/(double)RAND_MAX;
}

/*
	randomize_grid()
		Initialize a Life grid. Each cell has a [prob] chance
		of starting alive.
*/
void randomize_grid (struct life_t * life, double prob) {
	int i,j;
	int ncols = life->ncols;
	int nrows = life->nrows;

	dummyMethod3();
	for (i = 1; i <= ncols; i++) {
		for (j = 1; j <= nrows; j++) {
			if (rand_double() < prob)
				life->grid[i][j] = ALIVE;
		}
	}
	dummyMethod4();
}

/*
	seed_random()
		Seed the random number generator based on the
		process's rank and time. Multiplier is arbitrary.
*/
void seed_random (int rank) {
	srandom(time(NULL) + 100*rank);
}

/*
	cleanup()
		Prepare process for a clean termination.
*/
void cleanup (struct life_t * life) {
	write_grid(life);
	free_grids(life);

	MPI_Type_free(&life->col);
	MPI_Type_free(&life->row);
	MPI_Finalize();
}

/*
	usage()
		Describes Life's command line option
*/
void usage () {
	printf("\nUsage: Life [options]\n");
	printf("  -c|--columns number   Number of columns in grid. Default: %d\n", DEFAULT_SIZE);
	printf("  -r|--rows number      Number of rows in grid. Default: %d\n", DEFAULT_SIZE);
	printf("  -g|--gens number      Number of generations to run. Default: %d\n", DEFAULT_GENS);
	//printf("  -i|--input filename   Input file. See README for format. Default: none.\n");
	printf("  -o|--output filename  Output file. Default: none.\n");
	printf("  -h|--help             This help page.\n");
	printf("\nSee README for more information.\n\n");

	exit(EXIT_FAILURE);
}

/*
	parse_args()
		Make command line arguments useful
*/
void parse_args (struct life_t * life, int argc, char ** argv) {
	int opt       = 0;
	int opt_index = 0;
	int i;

	dummyMethod3();
	for (;;) {
		opt = getopt_long(argc, argv, opts, long_opts, &opt_index);

		if (opt == -1) break;

		switch (opt) {
			case 'c':
				life->ncols = strtol(optarg, (char**) NULL, 10);
				break;
			case 'r':
				life->nrows = strtol(optarg, (char**) NULL, 10);
				break;
			case 'g':
				life->generations = strtol(optarg, (char**) NULL, 10);
				break;
			case 'i':
				life->infile = optarg;
				break;
			case 'o':
				life->outfile = optarg;
				break;
			case 'h':
			case '?':
				usage();
				break;

			default:
				break;
		}
	}
	dummyMethod4();

	// Backwards compatible argument parsing
	if (optind == 1) {
		if (argc > 1)
			life->nrows       = strtol(argv[1], (char**) NULL, 10);
		if (argc > 2)
			life->ncols       = strtol(argv[2], (char**) NULL, 10);
		if (argc > 3)
			life->generations = strtol(argv[3], (char**) NULL, 10);
	}
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