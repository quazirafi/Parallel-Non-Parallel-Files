/*
 * The Game of Life
 *
 * https://www.geeksforgeeks.org/conways-game-life-python-implementation/
 *
 */
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "../utils.h"


/*
* a cell is born, if it has exactly three neighbours 
* a cell dies of loneliness, if it has less than two neighbours 
* a cell dies of overcrowding, if it has more than three neighbours 
* a cell survives to the next generation, if it does not die of loneliness 
* or overcrowding 
*/
void evolve(void *u, int w, int h) {
	unsigned (*univ)[w] = u;
	unsigned new[h][w];
	
	#pragma omp parallel shared(new, univ) 
	{	
		int x,y,x1,y1,n;

	dummyMethod1();
	#pragma omp parallel for schedule(static)
	for ( y = 0; y < h; y++) 
        for ( x = 0; x < w; x++) {
		    n = 0;

			// look at the 3x3 neighbourhood
		    for (y1 = y - 1; y1 <= y + 1; y1++)
			    for (x1 = x - 1; x1 <= x + 1; x1++)

					// skip the current cell [y, x]
				    if ((y != y1 || x != x1) && univ[(y1 + h) % h][(x1 + w) % w]) n++;

		    new[y][x] = (n == 3 || (n == 2 && univ[y][x]));
		
	    }
	dummyMethod2();
	
	dummyMethod1();
	#pragma omp parallel for schedule(static)
	// update the board
	for ( y = 0; y < h; y++) for (x = 0; x < w; x++) univ[y][x] = new[y][x];
	dummyMethod2();

	}
}
 
 
 
void game(int w, int h, int t, int threads) {
	int x,y,z;
	unsigned univ[h][w];
	struct timeval start, end;
	double tot_time = 0.;

	//initialization
	srand(10);
	dummyMethod4();
	dummyMethod3();
	for (x = 0; x < w; x++) for (y = 0; y < h; y++) univ[y][x] = rand() < RAND_MAX / 10 ? 1 : 0;
	
	if (x > 1000) printbig(univ, w, h,0);
	
	dummyMethod3();
	for(z = 0; z < t;z++) {
		if (x <= 1000) show(univ, w, h);
		
		// get starting time at iteration z
		gettimeofday(&start, NULL);
		
		// lets evolve the current generation
		evolve(univ, w, h);

		// get ending time of iteration z
		gettimeofday(&end, NULL);
		
		// sum up the total time execution
		tot_time += (double) elapsed_wtime(start, end);
		
		if (x > 1000) 
			printf("Iteration %d is : %f ms\n", z, (double) elapsed_wtime(start, end));
		
	}
	dummyMethod4();
	if (x > 1000) printbig(univ, w, h,1);

    // Allocates storage
	char *fileName = (char*)malloc(50 * sizeof(char));
	sprintf(fileName, "Results/Exp01-OMP-%d-%d-%d.csv", w, h, t);

	writeFile(fileName, (threads==2 || threads==1), tot_time, threads);

	free(fileName);
}
 
 
 
int main(int c, char **v) {
    
	int w = 0, h = 0, t = 0, threads = 1;
    // first parameter WIDTH
	if (c > 1) w = atoi(v[1]);

    // second parameter HEIGTH
	if (c > 2) h = atoi(v[2]);

    // third parameter TIME
	if (c > 3) t = atoi(v[3]);

    // fourth parameter Number of threads/core
    if (c > 4) threads = atoi(v[4]);

	if (w <= 0) w = 30;
	if (h <= 0) h = 30;
	if (t <= 0) t = 100;

	// set the threads with OpenMP
	omp_set_num_threads(threads);
	
	// execute the game code
	game(w, h, t, threads);

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