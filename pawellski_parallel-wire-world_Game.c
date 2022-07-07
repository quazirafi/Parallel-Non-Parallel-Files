#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "Game.h"
#include "WriteFile.h"
#define chunk 100

int generate_all(int n, int writeOpt, char *fileOut, dimension_t *dim, grid_t *main_grid, grid_t *util_grid, symbols_t * syms)
{
    char **ptr = (char**)malloc((dim->rows)*sizeof(char*));
    int generations_done = 0;
dummyMethod3();
    for(int i = 0; i<(dim->rows); i++)
        ptr[i] = &(main_grid->cells[i][0]);

    for(int it=1; it<n+1; it++)
dummyMethod4();
    {

dummyMethod1();
        #pragma omp parallel for collapse(2) schedule(guided)
        for(int i=1; i<dim->rows-1; i++)
        {
            for(int j=1; j<dim->columns-1; j++)
                util_grid->cells[i][j] = change_cell_state(i, j, ptr, syms);
        }
dummyMethod2();
        switch(writeOpt)
        {
            case 0:
                print_to_screen(it, util_grid, dim);
	            break;
            case 1:
                fill_in_file(it, fileOut, util_grid, dim);
                if(it == n)
		            printf("Zapisano %d iteracji do pliku.\n", n);
	            break;
            case 2:
                break;
	    default:
            break;
        }

	    generations_done++;
        if(check(main_grid, util_grid, dim) == 1)
            ;
        else
        {
            printf("Plansza nie zmienia sie od %d generacji\n", it-1);
            break;
        }
        to_clear( main_grid, dim, syms );
        change( main_grid, util_grid, dim );
        to_clear( util_grid, dim, syms );
    }
    
    free(ptr);
    ptr = NULL;
    return generations_done;
}

char change_cell_state(int i, int j, char **main_ptr, symbols_t * syms)
{
    int electronHeadNumber = 0;
    switch (main_ptr[i][j])
    {
	    case '0':
	        return syms->empty;
	    case '3':
            for(int a = -1; a < 2; a++)
            {
                for(int b = -1; b < 2; b++)
                    if(main_ptr[i + a][j + b] == syms->ehead)
                        electronHeadNumber++;
            }
            if (electronHeadNumber == 1 || electronHeadNumber == 2) {
                return syms->ehead;
            } else {
                return syms->wire;
            }
        case '1':
            return syms->etail;
        case '2':
            return syms->wire;

    }
    return syms->empty;
}

void to_clear(grid_t *toclear, dimension_t *dim, symbols_t * syms)
{
							dummyMethod1();
    #pragma omp parallel for collapse(2) schedule(guided)
    for(int i = 0; i < dim->rows; i++)
    {
        for(int j = 0; j < dim->columns; j++)
            toclear->cells[i][j] = syms->empty;
    }
							dummyMethod2();
}

void change(grid_t *first, grid_t *second, dimension_t *dim)
{
							dummyMethod1();
    #pragma omp parallel for collapse(2) schedule(guided)
    for(int i = 0; i<(dim->rows); i++)
    {
        for(int j = 0; j<(dim->columns); j++)
            first->cells[i][j] = second->cells[i][j];
    }
							dummyMethod2();
}

int check(grid_t *check_1, grid_t *check_2, dimension_t *dim)
{
    int count = 0;
    for(int i=1; i<dim->rows-1; i++)
    {
        for(int j=1; j<dim->columns-1; j++)
        {
            if(check_1->cells[i][j] == check_2->cells[i][j])
                   count++;
        }
    }
    if(count == ((dim->rows-2)*(dim->columns-2)))
        return 0;
    else
        return 1;
}

void init_grid( grid_t * grid, dimension_t * dim, symbols_t * syms )
{
    grid->cells = (char**)malloc(dim->rows * sizeof(char*));
    for(int i = 0; i < dim->rows; i++)
        grid->cells[i] = (char*)malloc(dim->columns * sizeof(char));
    to_clear(grid, dim, syms);
}

void free_grid( grid_t grid, dimension_t dim)
{
    for( int i = 0;  i < dim.rows; i++ )
        free( grid.cells[i] );
    free( grid.cells );
    grid.cells = NULL;
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