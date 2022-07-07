/*
 * Simplified simulation of fire extinguishing
 *
 * Computacion Paralela, Grado en Informatica (Universidad de Valladolid)
 * 2018/2019
 *
 * v1.4
 *
 * (c) 2019 Arturo Gonzalez Escribano
 */
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include<float.h>
#include<cputils.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define RADIUS_TYPE_1		3
#define RADIUS_TYPE_2_3		9
#define THRESHOLD	0.1f

/* Structure to store data of an extinguishing team */
typedef struct {
	int x,y;
	int type;
	int target;
} Team;

/* Structure to store data of a fire focal point */
typedef struct {
	int x,y;
	int start;
	int heat;
	int active; // States: 0 Not yet activated; 1 Active; 2 Deactivated by a team
} FocalPoint;


/* Macro function to simplify accessing with two coordinates to a flattened array */
#define accessMat( arr, exp1, exp2 )	arr[ (exp1) * columns + (exp2) ]


/*
 * Function: Print usage line in stderr
 */
void show_usage( char *program_name ) {
	fprintf(stderr,"Usage: %s <config_file> | <command_line_args>\n", program_name );
	fprintf(stderr,"\t<config_file> ::= -f <file_name>\n");
	fprintf(stderr,"\t<command_line_args> ::= <rows> <columns> <maxIter> <numTeams> [ <teamX> <teamY> <teamType> ... ] <numFocalPoints> [ <focalX> <focalY> <focalStart> <focalTemperature> ... ]\n");
	fprintf(stderr,"\n");
}

#ifdef DEBUG
/* 
 * Function: Print the current state of the simulation 
 */
void print_status( int iteration, int rows, int columns, float *surface, int num_teams, Team *teams, int num_focal, FocalPoint *focal, float global_residual ) {
	/* 
	 * You don't need to optimize this function, it is only for pretty printing and debugging purposes.
	 * It is not compiled in the production versions of the program.
	 * Thus, it is never used when measuring times in the leaderboard
	 */
	int i,j;

	printf("Iteration: %d\n", iteration );
	printf("+");
	for( j=0; j<columns; j++ ) printf("---");
	printf("+\n");
	for( i=0; i<rows; i++ ) {
		printf("|");
		for( j=0; j<columns; j++ ) {
			char symbol;
			if ( accessMat( surface, i, j ) >= 1000 ) symbol = '*';
			else if ( accessMat( surface, i, j ) >= 100 ) symbol = '0' + (int)(accessMat( surface, i, j )/100);
			else if ( accessMat( surface, i, j ) >= 50 ) symbol = '+';
			else if ( accessMat( surface, i, j ) >= 25 ) symbol = '.';
			else symbol = '0';

			int t;
			int flag_team = 0;
			for( t=0; t<num_teams; t++ ) 
				if ( teams[t].x == i && teams[t].y == j ) { flag_team = 1; break; }
			if ( flag_team ) printf("[%c]", symbol );
			else {
				int f;
				int flag_focal = 0;
				for( f=0; f<num_focal; f++ ) 
					if ( focal[f].x == i && focal[f].y == j && focal[f].active == 1 ) { flag_focal = 1; break; }
				if ( flag_focal ) printf("(%c)", symbol );
				else printf(" %c ", symbol );
			}
		}
		printf("|\n");
	}
	printf("+");
	for( j=0; j<columns; j++ ) printf("---");
	printf("+\n");
	printf("Global residual: %f\n\n", global_residual);
}
#endif



/*
 * MAIN PROGRAM
 */
int main(int argc, char *argv[]) {
	int i,j,t;

	// Simulation data
	int rows, columns, max_iter;
	float *surface, *surfaceCopy;
	int num_teams, num_focal;
	Team *teams;
	FocalPoint *focal;

	/* 1. Read simulation arguments */
	/* 1.1. Check minimum number of arguments */
	if (argc<2) {
		fprintf(stderr,"-- Error in arguments: No arguments\n");
		show_usage( argv[0] );
		exit( EXIT_FAILURE );
	}

	int read_from_file = ! strcmp( argv[1], "-f" );
	/* 1.2. Read configuration from file */
	if ( read_from_file ) {
		/* 1.2.1. Open file */
		if (argc<3) {
			fprintf(stderr,"-- Error in arguments: file-name argument missing\n");
			show_usage( argv[0] );
			exit( EXIT_FAILURE );
		}
		FILE *args = cp_abrir_fichero( argv[2] );
		if ( args == NULL ) {
			fprintf(stderr,"-- Error in file: not found: %s\n", argv[1]);
			exit( EXIT_FAILURE );
		}	

		/* 1.2.2. Read surface and maximum number of iterations */
		int ok;
		ok = fscanf(args, "%d %d %d", &rows, &columns, &max_iter);
		if ( ok != 3 ) {
			fprintf(stderr,"-- Error in file: reading rows, columns, max_iter from file: %s\n", argv[1]);
			exit( EXIT_FAILURE );
		}

		surface = (float *)malloc( sizeof(float) * (size_t)rows * (size_t)columns );
		surfaceCopy = (float *)malloc( sizeof(float) * (size_t)rows * (size_t)columns );

		if ( surface == NULL || surfaceCopy == NULL ) {
			fprintf(stderr,"-- Error allocating: surface structures\n");
			exit( EXIT_FAILURE );
		}

		/* 1.2.3. Teams information */
		ok = fscanf(args, "%d", &num_teams );
		if ( ok != 1 ) {
			fprintf(stderr,"-- Error file, reading num_teams from file: %s\n", argv[1]);
			exit( EXIT_FAILURE );
		}
		teams = (Team *)malloc( sizeof(Team) * (size_t)num_teams );
		if ( teams == NULL ) {
			fprintf(stderr,"-- Error allocating: %d teams\n", num_teams );
			exit( EXIT_FAILURE );
		}
			dummyMethod3();
		for( i=0; i<num_teams; i++ ) {
			ok = fscanf(args, "%d %d %d", &teams[i].x, &teams[i].y, &teams[i].type);
			if ( ok != 3 ) {
				fprintf(stderr,"-- Error in file: reading team %d from file: %s\n", i, argv[1]);
				exit( EXIT_FAILURE );
			}
		}
			dummyMethod4();

		/* 1.2.4. Focal points information */
		ok = fscanf(args, "%d", &num_focal );
		if ( ok != 1 ) {
			fprintf(stderr,"-- Error in file: reading num_focal from file: %s\n", argv[1]);
			exit( EXIT_FAILURE );
		}
		focal = (FocalPoint *)malloc( sizeof(FocalPoint) * (size_t)num_focal );
		if ( focal == NULL ) {
			fprintf(stderr,"-- Error allocating: %d focal points\n", num_focal );
			exit( EXIT_FAILURE );
		}
			dummyMethod3();
		for( i=0; i<num_focal; i++ ) {
			ok = fscanf(args, "%d %d %d %d", &focal[i].x, &focal[i].y, &focal[i].start, &focal[i].heat);
			if ( ok != 4 ) {
				fprintf(stderr,"-- Error in file: reading focal point %d from file: %s\n", i, argv[1]);
				exit( EXIT_FAILURE );
			}
			focal[i].active = 0;
		}
			dummyMethod4();
	}
	/* 1.3. Read configuration from arguments */
	else {
		/* 1.3.1. Check minimum number of arguments */
		if (argc<6) {
			fprintf(stderr, "-- Error in arguments: not enough arguments when reading configuration from the command line\n");
			show_usage( argv[0] );
			exit( EXIT_FAILURE );
		}

		/* 1.3.2. Surface and maximum number of iterations */
		rows = atoi( argv[1] );
		columns = atoi( argv[2] );
		max_iter = atoi( argv[3] );

		surface = (float *)malloc( sizeof(float) * (size_t)rows * (size_t)columns );
		surfaceCopy = (float *)malloc( sizeof(float) * (size_t)rows * (size_t)columns );

		/* 1.3.3. Teams information */
		num_teams = atoi( argv[4] );
		teams = (Team *)malloc( sizeof(Team) * (size_t)num_teams );
		if ( teams == NULL ) {
			fprintf(stderr,"-- Error allocating: %d teams\n", num_teams );
			exit( EXIT_FAILURE );
		}
		if ( argc < num_teams*3 + 5 ) {
			fprintf(stderr,"-- Error in arguments: not enough arguments for %d teams\n", num_teams );
			exit( EXIT_FAILURE );
		}
			dummyMethod3();
		for( i=0; i<num_teams; i++ ) {
			teams[i].x = atoi( argv[5+i*3] );
			teams[i].y = atoi( argv[6+i*3] );
			teams[i].type = atoi( argv[7+i*3] );
		}
			dummyMethod4();

		/* 1.3.4. Focal points information */
		int focal_args = 5 + i*3;
		if ( argc < focal_args+1 ) {
			fprintf(stderr,"-- Error in arguments: not enough arguments for the number of focal points\n");
			show_usage( argv[0] );
			exit( EXIT_FAILURE );
		}
		num_focal = atoi( argv[focal_args] );
		focal = (FocalPoint *)malloc( sizeof(FocalPoint) * (size_t)num_focal );
		if ( teams == NULL ) {
			fprintf(stderr,"-- Error allocating: %d focal points\n", num_focal );
			exit( EXIT_FAILURE );
		}
		if ( argc < focal_args + 1 + num_focal*4 ) {
			fprintf(stderr,"-- Error in arguments: not enough arguments for %d focal points\n", num_focal );
			exit( EXIT_FAILURE );
		}
			dummyMethod3();
		for( i=0; i<num_focal; i++ ) {
			focal[i].x = atoi( argv[focal_args+i*4+1] );
			focal[i].y = atoi( argv[focal_args+i*4+2] );
			focal[i].start = atoi( argv[focal_args+i*4+3] );
			focal[i].heat = atoi( argv[focal_args+i*4+4] );
			focal[i].active = 0;
		}
			dummyMethod4();

		/* 1.3.5. Sanity check: No extra arguments at the end of line */
		if ( argc > focal_args+i*4+1 ) {
			fprintf(stderr,"-- Error in arguments: extra arguments at the end of the command line\n");
			show_usage( argv[0] );
			exit( EXIT_FAILURE );
		}
	}


#ifdef DEBUG
	/* 1.4. Print arguments */
	printf("Arguments, Rows: %d, Columns: %d, max_iter: %d\n", rows, columns, max_iter);
	printf("Arguments, Teams: %d, Focal points: %d\n", num_teams, num_focal );
	for( i=0; i<num_teams; i++ ) {
		printf("\tTeam %d, position (%d,%d), type: %d\n", i, teams[i].x, teams[i].y, teams[i].type );
	}
	for( i=0; i<num_focal; i++ ) {
		printf("\tFocal_point %d, position (%d,%d), start time: %d, temperature: %d\n", i, 
		focal[i].x,
		focal[i].y,
		focal[i].start,
		focal[i].heat );
	}
#endif // DEBUG

	/* 2. Start global timer */
	double ttotal = cp_Wtime();

/*
 *
 * START HERE: DO NOT CHANGE THE CODE ABOVE THIS POINT
 *
 */
	#ifdef TIEMPO
	double tiempoParalelo= 0.0;		/*cambio*/
	double tParaleloSuma1= 0.0;
	double tParaleloSuma2= 0.0;
	double tParaleloSuma3= 0.0;
	double tParaleloSuma4= 0.0;
	double tParaleloSuma5= 0.0;
	double tParaleloSuma6= 0.0;
	double tParaleloSuma7= 0.0;
	double tParaleloSuma8= 0.0;
	#endif

	#ifdef TIEMPO
	tiempoParalelo = cp_Wtime();		/*cambio*/
	#endif
	/* 3. Initialize surface */
	dummyMethod1();
	#pragma omp parallel for default(none) private(i,j) shared(surface,rows,columns)		/*cambio*/
	for( i=0; i<rows; i++ )
		for( j=0; j<columns; j++ )
			accessMat( surface, i, j ) = 0.0;
	dummyMethod2();

	#ifdef TIEMPO
	tParaleloSuma1 = (cp_Wtime() - tiempoParalelo);		/*cambio*/
	#endif

	/* 4. Simulation */
	int iter;
	int flag_stability = 0;
	int first_activation = 0;
	for( iter=0; iter<max_iter && ! flag_stability; iter++ ) {

		#ifdef TIEMPO
		tiempoParalelo = cp_Wtime();		/*cambio*/
		#endif
		/* 4.1. Activate focal points */
		int num_deactivated = 0;
		for( i=0; i<num_focal; i++ ) {
			if ( focal[i].start == iter ) {
				focal[i].active = 1;
				if ( ! first_activation ) first_activation = 1;
			}
			// Count focal points already deactivated by a team
			if ( focal[i].active == 2 ){
				num_deactivated++;
			}
		}

		if ( ! first_activation )continue;		/*cambio*/
		#ifdef TIEMPO
		tParaleloSuma2 = tParaleloSuma2 + (cp_Wtime() - tiempoParalelo);		/*cambio*/
		#endif

		

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/* 4.2. Propagate heat (10 steps per each team movement) */
		float global_residual = 0.0f;
		float residual_temporal = 0.0f;
		int step;
		for( step=0; step<10; step++ )	{

			#ifdef TIEMPO
			tiempoParalelo = cp_Wtime();		/*cambio*/
			#endif
			/* 4.2.1. Update heat on active focal points */
			for( i=0; i<num_focal; i++ ) {

				if ( focal[i].active != 1 ) continue;
				int x = focal[i].x;
				int y = focal[i].y;
				if(step%2==0){		/*cambio*/
					accessMat( surface, x, y ) = focal[i].heat;
				}else{
					accessMat( surfaceCopy, x, y ) = focal[i].heat;

				}
			}
			#ifdef TIEMPO
			tParaleloSuma3 = tParaleloSuma3 + (cp_Wtime() - tiempoParalelo);		/*cambio*/


			tiempoParalelo = cp_Wtime();		/*cambio*/
			#endif

			#pragma omp parallel default(none) shared(step,rows,columns,surface,surfaceCopy,residual_temporal,num_deactivated,num_focal) private(i,j) reduction(max:global_residual)		/*cambio*/
			{
			
			/*2 segundos de 28*/
			/* 4.2.2. Copy values of the surface in ancillary structure (Skip borders) */
			#pragma omp for		/*cambio*/
			for( i=1; i<rows-1; i++ ){
				for( j=1; j<columns-1; j++ ){
					if(step%2==0){		/*cambio*/
					accessMat( surfaceCopy, i, j ) = (
						accessMat( surface, i-1, j ) +
						accessMat( surface, i+1, j ) +
						accessMat( surface, i, j-1 ) +
						accessMat( surface, i, j+1 ) ) / 4;
					}else{
					accessMat( surface, i, j ) = (
						accessMat( surfaceCopy, i-1, j ) +
						accessMat( surfaceCopy, i+1, j ) +
						accessMat( surfaceCopy, i, j-1 ) +
						accessMat( surfaceCopy, i, j+1 ) ) / 4;

					}
				}
			}

			/*8 segundos de 28*/
			/* 4.2.3. Update surface values (skip borders) */
			
			/*14 segundos de 24*/
			/* 4.2.4. Compute the maximum residual difference (absolute value) */
			if( num_deactivated == num_focal){ /*Solo nos interesa cuando el calor empieza a bajar*/
				if(global_residual < THRESHOLD){
					#pragma omp for			/*cambio*/
					for( i=1; i<rows-1; i++ ){
						for( j=1; j<columns-1; j++ ){
							if(step%2==0){		/*cambio*/
								residual_temporal = accessMat( surfaceCopy, i, j ) - accessMat( surface, i, j);
							}else{
								residual_temporal = accessMat( surface, i, j ) - accessMat( surfaceCopy, i, j);
							}
							if ( residual_temporal > global_residual ) {
								global_residual = residual_temporal ;
							}
						}
					}
				}
			}
			}

			#ifdef TIEMPO
			tParaleloSuma6 = tParaleloSuma6 + (cp_Wtime() - tiempoParalelo);		/*cambio*/
			#endif
		}


//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		/* If the global residual is lower than THRESHOLD, we have reached enough stability, stop simulation at the end of this iteration */
		if( num_deactivated == num_focal && global_residual < THRESHOLD ) flag_stability = 1;



		#ifdef TIEMPO
		tiempoParalelo = cp_Wtime();		/*cambio*/
		#endif
		/* 4.3. Move teams */
		if ( num_deactivated != num_focal ){
					dummyMethod1();
			#pragma omp parallel for private(t,j)
			for( t=0; t<num_teams; t++ ) {
				/* 4.3.1. Choose nearest focal point */
				float distance = FLT_MAX;
				int target = -1;
				for( j=0; j<num_focal; j++ ) {
					if ( focal[j].active != 1 ) continue; // Skip non-active focal points
					float dx = focal[j].x - teams[t].x;
					float dy = focal[j].y - teams[t].y;
					float local_distance = dx*dx + dy*dy;		/*cambio*/
					if ( local_distance < distance ) {
						distance = local_distance;
						target = j;
					}
				}
				/* 4.3.2. Annotate target for the next stage */
				teams[t].target = target;

				/* 4.3.3. No active focal point to choose, no movement */
				if ( target == -1 ) continue; 

				/* 4.3.4. Move in the focal point direction */
				if ( teams[t].type == 1 ) { 
					// Type 1: Can move in diagonal
					if ( focal[target].x < teams[t].x ) teams[t].x--;
					else if ( focal[target].x > teams[t].x ) teams[t].x++;		/*cambio*/
					if ( focal[target].y < teams[t].y ) teams[t].y--;
					else if ( focal[target].y > teams[t].y ) teams[t].y++;		/*cambio*/
				}
				else if ( teams[t].type == 2 ) { 
					// Type 2: First in horizontal direction, then in vertical direction
					if ( focal[target].y < teams[t].y ) teams[t].y--;
					else if ( focal[target].y > teams[t].y ) teams[t].y++;
					else if ( focal[target].x < teams[t].x ) teams[t].x--;
					else if ( focal[target].x > teams[t].x ) teams[t].x++;
				}
				else {
					// Type 3: First in vertical direction, then in horizontal direction
					if ( focal[target].x < teams[t].x ) teams[t].x--;
					else if ( focal[target].x > teams[t].x ) teams[t].x++;
					else if ( focal[target].y < teams[t].y ) teams[t].y--;
					else if ( focal[target].y > teams[t].y ) teams[t].y++;
				}
			}
					dummyMethod2();
		}
		#ifdef TIEMPO
		tParaleloSuma7 = tParaleloSuma7 + (cp_Wtime() - tiempoParalelo);		/*cambio*/

		
//***********************************************************/////

		tiempoParalelo = cp_Wtime();		/*cambio*/
		#endif
		/* 4.4. Team actions */
		#pragma omp parallel for default(none) private(t,i,j) shared(teams,focal,rows,columns,surface,num_teams)		/*cambio*/
		for( t=0; t<num_teams; t++ ) {
			/* 4.4.1. Deactivate the target focal point when it is reached */
			int target = teams[t].target;

			if ( target != -1 && focal[target].x == teams[t].x && focal[target].y == teams[t].y 
				&& focal[target].active == 1 )
				focal[target].active = 2;

			/* 4.4.2. Reduce heat in a circle around the team */
			int radius;
			// Influence area of fixed radius depending on type
			if ( teams[t].type == 1 ) radius = RADIUS_TYPE_1;
			else radius = RADIUS_TYPE_2_3;
			for( i=teams[t].x-radius; i<=teams[t].x+radius; i++ ) {
				for( j=teams[t].y-radius; j<=teams[t].y+radius; j++ ) {
					if ( i<1 || i>=rows-1 || j<1 || j>=columns-1 ) continue; // Out of the heated surface
					int dx = teams[t].x - i;
					int dy = teams[t].y - j;
					int distance = dx*dx + dy*dy;		/*cambio*/
					if ( distance <= radius*radius ) {
						#pragma omp atomic		/*cambio*/
						accessMat( surface, i, j ) = accessMat( surface, i, j ) * ( 0.75); // Team efficiency factor
					}
				}
			}
		}
		#ifdef TIEMPO
		tParaleloSuma8 = tParaleloSuma8 + (cp_Wtime() - tiempoParalelo);		/*cambio*/
		#endif
//***********************************************************/////
		

#ifdef DEBUG
		/* 4.5. DEBUG: Print the current state of the simulation at the end of each iteration */
		print_status( iter, rows, columns, surface, num_teams, teams, num_focal, focal, global_residual );
#endif // DEBUG
	}
	#ifdef TIEMPO		/*cambio*/
	printf("\n");
	printf("Tiempo inicializar tabla: %lf \n",tParaleloSuma1);
	printf("Tiempo activar focos: %lf \n",tParaleloSuma2);
	printf("Tiempo actualizar calor focos: %lf \n",tParaleloSuma3);
	printf("\n");
	printf("Tiempo copiar, actualizar y computar: %lf \n",tParaleloSuma6);
	printf("\n");
	printf("Tiempo mover equipos: %lf \n",tParaleloSuma7);
	printf("Tiempo accion de los equipos: %lf \n",tParaleloSuma8);
	printf("Tiempo total: %lf \n",(tParaleloSuma1+tParaleloSuma2+tParaleloSuma3+tParaleloSuma4+tParaleloSuma5+tParaleloSuma6+tParaleloSuma7+tParaleloSuma8));
	#endif

/*
 *
 * STOP HERE: DO NOT CHANGE THE CODE BELOW THIS POINT
 *
 */

	/* 5. Stop global time */
	ttotal = cp_Wtime() - ttotal;

	/* 6. Output for leaderboard */
	printf("\n");
	/* 6.1. Total computation time */
	printf("Time: %lf\n", ttotal );
	/* 6.2. Results: Number of iterations, position of teams, residual heat on the focal points */
	printf("Result: %d", iter);
	/*
	for (i=0; i<num_teams; i++)
		printf(" %d %d", teams[i].x, teams[i].y );
	*/
	for (i=0; i<num_focal; i++)
		printf(" %.6f", accessMat( surface, focal[i].x, focal[i].y ) );
	printf("\n");

	/* 7. Free resources */	
	free( teams );
	free( focal );
	free( surface );
	free( surfaceCopy );

	/* 8. End */
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