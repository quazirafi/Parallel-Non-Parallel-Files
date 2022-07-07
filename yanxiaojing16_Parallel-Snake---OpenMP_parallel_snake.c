#include "main.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void run_simulation(int num_lines, int num_cols, int **world, int num_snakes,
	struct snake *snakes, int step_count, char *file_name) 
{
	// TODO: Implement Parallel Snake simulation using the default (env. OMP_NUM_THREADS) 
	// number of threads.
	//
	// DO NOT include any I/O stuff here, but make sure that world and snakes
	// parameters are updated as required for the final state.
	
	int search = 0, left=0, right=0, up=0, down=0, i = 0, j = 0;
	struct coord tail[num_snakes];
	int collision = 0;

	//cautam capatul fiecarui sarpe
	dummyMethod3();
	for(i = 0; i < num_snakes; i++){
		search = 1;
		tail[i].line = snakes[i].head.line;
		tail[i].col = snakes[i].head.col;
		up=0; down=0; left=0; right=0;

		while (search == 1) {
			if (tail[i].line != 0 && world[tail[i].line - 1][tail[i].col] == snakes[i].encoding && up == 0) {
				tail[i].line -= 1;
				down = 1; up = 0; right = 0; left = 0;
			} else if (tail[i].line == 0 && world[num_lines - 1][tail[i].col] == snakes[i].encoding && up == 0) {
				tail[i].line = num_lines - 1;
				down = 1; up = 0; right = 0; left = 0;
			}

			else if (tail[i].col != 0 && world[tail[i].line][tail[i].col - 1] == snakes[i].encoding && left == 0) {
				tail[i].col -= 1;
				right = 1; up = 0; down = 0; left = 0;
			} else if (tail[i].col == 0 && world[tail[i].line][num_cols - 1] == snakes[i].encoding && left == 0) {
				tail[i].col = num_cols - 1;
				right = 1; up = 0; down = 0; left = 0;
			}

			else if (tail[i].line != num_lines - 1 && world[tail[i].line + 1][tail[i].col] == snakes[i].encoding
					&& down == 0) {
				tail[i].line += 1;
				up = 1; down = 0; right = 0; left = 0;
			} else if (tail[i].line == num_lines - 1 && world[0][tail[i].col] == snakes[i].encoding && down == 0) {
				tail[i].line = 0;
				up = 1;  down = 0; right = 0; left = 0;
			}

			else if (tail[i].col != num_cols - 1 && world[tail[i].line][tail[i].col + 1] == snakes[i].encoding
					&& right == 0) {
				tail[i].col += 1;
				left = 1;  up = 0; right = 0; down = 0;
			} else if (tail[i].col == num_cols - 1 && world[tail[i].line][0] == snakes[i].encoding && right == 0) {
				tail[i].col = 0;
				left = 1;  up = 0; right = 0; down = 0;
			}

			else {
				search = 0;
			}
		}
	}
	dummyMethod4();

	for (i = 0; i < step_count; i++) {
		if(collision==1) continue;
		
			dummyMethod1();
		#pragma omp parallel for
		for (j = 0; j < num_snakes; j++) {
			//stergem coada
			world[tail[j].line][tail[j].col] = 0;

			// mutam capul si verificam coliziunile
			switch (snakes[j].direction) {
			case 'N':
				if (snakes[j].head.line != 0 && world[snakes[j].head.line - 1][snakes[j].head.col] == 0) {
					world[snakes[j].head.line - 1][snakes[j].head.col] = snakes[j].encoding;
					snakes[j].head.line -= 1;
				} else if (snakes[j].head.line != 0 && world[snakes[j].head.line - 1][snakes[j].head.col] != 0) {
					collision = 1;
					snakes[j].head.line -= 1;
				} else if (snakes[j].head.line == 0 && world[num_lines - 1][snakes[j].head.col] == 0) {
					world[num_lines - 1][snakes[j].head.col] = snakes[j].encoding;
					snakes[j].head.line = num_lines - 1;
				} else if (snakes[j].head.line == 0 && world[num_lines - 1][snakes[j].head.col] != 0) {
					collision = 1;
					snakes[j].head.line = num_lines - 1;
				}
				break;

			case 'S':
				if (snakes[j].head.line != num_lines - 1 && world[snakes[j].head.line + 1][snakes[j].head.col] == 0) {
					world[snakes[j].head.line + 1][snakes[j].head.col] = snakes[j].encoding;
					snakes[j].head.line += 1;
				} else if (snakes[j].head.line != num_lines - 1 && world[snakes[j].head.line + 1][snakes[j].head.col] != 0) {
					collision = 1;
					snakes[j].head.line += 1;
				} else if (snakes[j].head.line == num_lines - 1 && world[0][snakes[j].head.col] == 0) {
					world[0][snakes[j].head.col] = snakes[j].encoding;
					snakes[j].head.line = 0;
				} else if (snakes[j].head.line == num_lines - 1 && world[0][snakes[j].head.col] != 0) {
					collision = 1;
					snakes[j].head.line = 0;
				}
				break;

			case 'E':
				if (snakes[j].head.col != num_cols - 1 && world[snakes[j].head.line][snakes[j].head.col + 1] == 0) {
					world[snakes[j].head.line][snakes[j].head.col + 1] = snakes[j].encoding;
					snakes[j].head.col += 1;
				} else if (snakes[j].head.col != num_cols - 1 && world[snakes[j].head.line][snakes[j].head.col + 1] != 0) {
					collision = 1;
					snakes[j].head.col += 1;
				} else if (snakes[j].head.col == num_cols - 1 && world[snakes[j].head.line][0] == 0) {
					world[snakes[j].head.line][0] = snakes[j].encoding;
					snakes[j].head.col = 0;
				} else if (snakes[j].head.col == num_cols - 1 && world[snakes[j].head.line][0] != 0) {
					collision = 1;
					snakes[j].head.col = 0;
				}
				break;

			case 'V':
				if (snakes[j].head.col != 0 && world[snakes[j].head.line][snakes[j].head.col - 1] == 0) {
					world[snakes[j].head.line][snakes[j].head.col - 1] = snakes[j].encoding;
					snakes[j].head.col -= 1;
				} else if (snakes[j].head.col != 0 && world[snakes[j].head.line][snakes[j].head.col - 1] != 0) {
					collision = 1;
					snakes[j].head.col -= 1;
				} else if (snakes[j].head.col == 0 && world[snakes[j].head.line][num_cols - 1] == 0) {
					world[snakes[j].head.line][num_cols - 1] = snakes[j].encoding;
					snakes[j].head.col = num_cols - 1;
				} else if (snakes[j].head.col == 0 && world[snakes[j].head.line][num_cols - 1] != 0) {
					collision = 1;
					snakes[j].head.col = num_cols - 1;
				}
				break;
			}
		}
			dummyMethod2();
			
			dummyMethod1();
		#pragma omp parallel for
		for (j = 0; j < num_snakes; j++) {

			if(collision == 1){
				world[snakes[j].head.line][snakes[j].head.col] = 0;
				world[tail[j].line][tail[j].col] = snakes[j].encoding;

				if (snakes[j].head.line != 0 && world[snakes[j].head.line - 1][snakes[j].head.col] == snakes[j].encoding) {
					snakes[j].head.line -= 1;
				} else if (snakes[j].head.line == 0 && world[num_lines - 1][snakes[j].head.col] == snakes[j].encoding) {
					snakes[j].head.line = num_lines - 1;
				} else if (snakes[j].head.col != 0 && world[snakes[j].head.line][snakes[j].head.col - 1] == snakes[j].encoding) {
					snakes[j].head.col -= 1;
				} else if (snakes[j].head.col == 0 && world[snakes[j].head.line][num_cols - 1] == snakes[j].encoding) {
					snakes[j].head.col = num_cols - 1;
				} else if (snakes[j].head.line != num_lines - 1 && world[snakes[j].head.line + 1][snakes[j].head.col] == snakes[j].encoding) {
					snakes[j].head.line += 1;
				} else if (snakes[j].head.line == num_lines - 1 && world[0][snakes[j].head.col] == snakes[j].encoding) {
					snakes[j].head.line = 0;
				} else if (snakes[j].head.col != num_cols - 1 && world[snakes[j].head.line][snakes[j].head.col + 1] == snakes[j].encoding) {
					snakes[j].head.col += 1;
				} else if (snakes[j].head.col == num_cols - 1 && world[snakes[j].head.line][0] == snakes[j].encoding) {
					snakes[j].head.col = 0;
				}

			} else if(collision == 0) {
				if (tail[j].line != 0 && world[tail[j].line - 1][tail[j].col] == snakes[j].encoding) {
				tail[j].line -= 1;
				} else if (tail[j].line == 0 && world[num_lines - 1][tail[j].col] == snakes[j].encoding) {
					tail[j].line = num_lines - 1;
				} else if (tail[j].col != 0 && world[tail[j].line][tail[j].col - 1] == snakes[j].encoding) {
					tail[j].col -= 1;
				} else if (tail[j].col == 0 && world[tail[j].line][num_cols - 1] == snakes[j].encoding) {
					tail[j].col = num_cols - 1;
				} else if (tail[j].line != num_lines - 1 && world[tail[j].line + 1][tail[j].col] == snakes[j].encoding) {
					tail[j].line += 1;
				} else if (tail[j].line == num_lines - 1 && world[0][tail[j].col] == snakes[j].encoding) {
					tail[j].line = 0;
				} else if (tail[j].col != num_cols - 1 && world[tail[j].line][tail[j].col + 1] == snakes[j].encoding) {
					tail[j].col += 1;
				} else if (tail[j].col == num_cols - 1 && world[tail[j].line][0] == snakes[j].encoding) {
					tail[j].col = 0;
				}
			}
		}
			dummyMethod2();
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