#include "main.h"
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
	
	int ver = 0;
	int tailX,tailY;
	int prevX,prevY;
	int i,j,k,step,coliziune = 0;
	
	dummyMethod1();
	#pragma omp parallel for private(i,tailX,tailY,prevY,prevX,ver) shared(world)
	for(i=0;i<num_snakes;i++)
	{
		
		/*		Initializari	*/
		ver = 0;
		tailX = snakes[i].head.line;
		tailY = snakes[i].head.col;
		prevX = tailX;
		prevY = tailY;
		snakes[i].future_head.line = snakes[i].head.line;
		snakes[i].future_head.col = snakes[i].head.col;
		snakes[i].collided_into = -1;
		snakes[i].collided = 0;
		
		/*		Parcurg serpii pentru a afla coada si casuta anterioara ei	*/
		while(ver  == 0)
		{
			ver = 1;
			
			/*		Daca pot merge in sus prin sarpe	*/
			if(world[((tailX-1)+num_lines)%num_lines][tailY] == snakes[i].encoding
			&& ((tailX-1+num_lines)%num_lines != prevX || tailY != prevY))
			{
				prevX = tailX;
				prevY = tailY;
				tailX = ((tailX-1)+num_lines)%num_lines;
				ver = 0;
			}
			
			/*		Daca pot merge in stanga prin sarpe	 */
			if(world[tailX][((tailY-1)+num_cols)%num_cols] == snakes[i].encoding
			&& (tailX != prevX || (tailY-1+num_cols)%num_cols != prevY))
			{
				prevX = tailX;
				prevY = tailY;
				tailY =((tailY-1)+num_cols)%num_cols;
				ver = 0;
			}
			
			/*		Daca pot merge in jos prin sarpe	*/
			if(world[(tailX+1)%num_lines][tailY] == snakes[i].encoding
			&& ((tailX+1)%num_lines != prevX || tailY != prevY))
			
			{
				prevX = tailX;
				prevY = tailY;
				tailX = (tailX+1)%num_lines;
				ver = 0;
			}
			
			/*		Daca pot merge in dreapta prin sarpe	*/
			if(world[tailX][(tailY+1)%num_cols] == snakes[i].encoding
			&& (tailX!= prevX || (tailY+1)%num_cols != prevY))
			{
				prevX = tailX;
				prevY = tailY;
				tailY = (tailY+1)%num_cols;
				ver = 0;
			}
		}
		
		/*	Salvez variabilele in structura	*/
		snakes[i].prev_tail.line = prevX;
		snakes[i].prev_tail.col = prevY;
		snakes[i].tail.line = tailX;
		snakes[i].tail.col = tailY;
		snakes[i].future_tail.line = prevX;
		snakes[i].future_tail.col = prevY;
	}
	dummyMethod2();


	for(step=0;step<step_count;step++)
	{
		
		/*		Calculez urmatoarea pozitie in care se va muta sarpele	*/
			dummyMethod1();
		#pragma omp parallel for
		for(i=0;i<num_snakes;i++)
		{
			if(snakes[i].direction == 'N')
				snakes[i].future_head.line = (snakes[i].head.line-1+num_lines)%num_lines;
				
			if(snakes[i].direction == 'S')
				snakes[i].future_head.line =(snakes[i].head.line+1)%num_lines;
			
			if(snakes[i].direction == 'E')
				snakes[i].future_head.col =(snakes[i].head.col+1)%num_cols;
							
			if(snakes[i].direction == 'V')
				snakes[i].future_head.col = (snakes[i].head.col-1+num_cols)%num_cols;
		}
			dummyMethod2();
		
		
		/*		Retin ce se afla in casuta in care urmeaza sa fac mutarea	*/
			dummyMethod1();
		#pragma omp parallel for
		for(i=0;i<num_snakes;i++)
			snakes[i].collided_into = world[snakes[i].future_head.line][snakes[i].future_head.col];
			dummyMethod2();
				
				
				
			dummyMethod1();
		#pragma omp parallel for
		for(i=0;i<num_snakes;i++)
		{

			/*		Daca pozitia in care urmez sa ma deplasez este ocupata	*/
			if(world[snakes[i].future_head.line][snakes[i].future_head.col] !=0)
			{
				snakes[i].collided =1;
			}
			
			/*		Efectuez mutarea : coada devine 0, capatul devine id	*/
			world[snakes[i].tail.line][snakes[i].tail.col] = 0;
			world[snakes[i].future_head.line][snakes[i].future_head.col] = snakes[i].encoding;
				
			/*		Refac coordonatele	dupa mutare		*/
			snakes[i].prev_tail.line = snakes[i].tail.line ;	
			snakes[i].prev_tail.col = snakes[i].tail.col;
			snakes[i].tail.line = snakes[i].future_tail.line;
			snakes[i].tail.col = snakes[i].future_tail.col;
					
			snakes[i].head.line = snakes[i].future_head.line;
			snakes[i].head.col = snakes[i].future_head.col;
			
						
			if(world[((snakes[i].tail.line-1)+num_lines)%num_lines][snakes[i].tail.col] == snakes[i].encoding
				&& ((snakes[i].tail.line-1+num_lines)%num_lines != snakes[i].prev_tail.line || tailY != snakes[i].tail.col))
			{
				snakes[i].future_tail.line = (snakes[i].tail.line-1+num_lines)%num_lines;
			}
								
			if(world[snakes[i].tail.line][((snakes[i].tail.col-1)+num_cols)%num_cols] == snakes[i].encoding
				&& (snakes[i].prev_tail.line != snakes[i].tail.line || (snakes[i].tail.col-1+num_cols)%num_cols != snakes[i].prev_tail.col))
			{
				snakes[i].future_tail.col = (snakes[i].tail.col-1+num_cols)%num_cols;
			}
								
			if(world[(snakes[i].tail.line+1)%num_lines][snakes[i].tail.col] == snakes[i].encoding
				&& ((snakes[i].tail.line+1)%num_lines != snakes[i].prev_tail.line || snakes[i].prev_tail.col != snakes[i].tail.col))
			{
				snakes[i].future_tail.line = (snakes[i].tail.line+1)%num_lines;
			}
								
			if(world[snakes[i].tail.line][(snakes[i].tail.col+1)%num_cols] == snakes[i].encoding
				&& (snakes[i].prev_tail.line!= snakes[i].tail.line || (snakes[i].tail.col+1)%num_cols != snakes[i].prev_tail.col))
			{
				snakes[i].future_tail.col = (snakes[i].tail.col+1)%num_cols;
			}
			
		}
			dummyMethod2();
	
		/*		Verific daca cel putin un sarpe a detectat coliziune	*/
			dummyMethod1();
		#pragma omp parallel for
		for(i=0;i<num_snakes;i++)
		{
			if(snakes[i].collided == 1)
				coliziune = 1;
		}
			dummyMethod2();
		
		/*		Daca detectez coliziune, dau toti serpii inapoi cu un pas */
		if(coliziune == 1)
		{
					dummyMethod1();
			#pragma omp parallel for
			for(j=0;j<num_snakes;j++)
			{
				
				/*	 Refac vechea coada	*/
				snakes[j].tail.line = snakes[j].prev_tail.line;
				snakes[j].tail.col = snakes[j].prev_tail.col;
				
				/*	 Marchez pe harta noua coada si capul	*/
				world[snakes[j].tail.line][snakes[j].prev_tail.col] = snakes[j].encoding;
				world[snakes[j].head.line][snakes[j].head.col] = snakes[j].collided_into;
				
				/* Aduc capul cu o pozitie inapoi	*/
				if(snakes[j].direction == 'N')
					snakes[j].head.line = (snakes[j].head.line +1)%num_lines;
				if(snakes[j].direction == 'S')
					snakes[j].head.line = (snakes[j].head.line -1+num_lines)%num_lines;
				if(snakes[j].direction == 'V')
					snakes[j].head.col = (snakes[j].head.col +1)%num_cols;
				if(snakes[j].direction == 'E')
					snakes[j].head.col = (snakes[j].head.col -1+num_cols)%num_cols;
				
			}
					dummyMethod2();
			
		}
	


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