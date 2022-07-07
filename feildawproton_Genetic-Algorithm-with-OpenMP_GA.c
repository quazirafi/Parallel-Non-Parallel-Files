#include "GA.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include <stdio.h>  //bc we want lots of io for reasons
#include <stdlib.h>
#include <math.h>  //for fabs
#include <time.h>

#include "omp.h"

//the part of the total constraint  penalty to eguality contraints
float eval_EQ_Pfunc(unsigned neq, const gaf_ptr* EQ,  unsigned ndv, const float* DV)
{
	float sum = 0;
	//equality constraints evaluated like sum(EQ^2)
dummyMethod3();
	for (unsigned q = 0; q < neq; q++)
	{
		float val = EQ[q](ndv, DV);
		float valsqrd = val * val; //better to do it this way than call the funtion (expensive) twice
		sum += valsqrd;
	}
dummyMethod4();
	return sum;
}
//the <= constraint penalty part of the total constraints
float eval_LE_Pfunc(unsigned nle, const gaf_ptr* LE, unsigned ndv, const float* DV)
{
	float sum = 0;
	//<= constraints evaluated like sum(LE + |LE|)
	dummyMethod3();
	for (unsigned l = 0; l < nle; l++)
	{
		float val = LE[l](ndv, DV);
		float eval = val + fabs(val);
		if (eval < 0)
			printf("something went wrong inside of P_LE\n");
		sum += eval;
	}
	dummyMethod4();
	return sum;
}
//the >= constraint penalty part of the total constraints
float eval_GE_Pfunc(unsigned nge, const gaf_ptr* GE, unsigned ndv, const float* DV)
{
	float sum = 0;
	//>= constraints evaluated like sum(-GE + abs(GE))
	dummyMethod3();
	for (unsigned g = 0; g < nge; g++)
	{
		float val = GE[g](ndv, DV);
		float eval = fabs(val) - val;
		if (eval < 0)
			printf("something went wrong inside of P_GE\n");
		sum += eval;
	}
	dummyMethod4();
	return sum;
}
//the penalty function
float eval_Pfunc(const FitnessFunc* FitFunc, unsigned ndv, const float* DV)
{
	if (FitFunc->ndv != ndv)
	{
		printf("The number of supplied design variables (%i) does not match the number that the fitness function was created for (%i)\n", ndv, FitFunc->ndv);
		getchar();
		return 0;
	}
	else
	{
		float EQ_part = eval_EQ_Pfunc(FitFunc->neq, FitFunc->EQ, ndv, DV);
		float LE_part = eval_LE_Pfunc(FitFunc->nle, FitFunc->LE, ndv, DV);
		float GE_part = eval_GE_Pfunc(FitFunc->nge, FitFunc->GE, ndv, DV);
		float penalty = EQ_part + LE_part + GE_part;
		return penalty;
	}
} 
float eval_Fitfunc(const FitnessFunc* FitFunc, unsigned ndv, const float* DV)
{
	float Pfunc = eval_Pfunc(FitFunc, ndv, DV);
	float Ofunc = FitFunc->ObjF(ndv, DV);
	if (FitFunc->ObjType == MIN)
	{
		float val = Ofunc + (GA_PENALTY * Pfunc);
		return val;
	}
	else
	{
		float val = Ofunc - (GA_PENALTY * Pfunc);
		return val;
	}
}

FitnessFunc* create_FitFunc(unsigned ndv, unsigned neq, unsigned nle, unsigned  nge, MinMAX ObjType, const gaf_ptr ObjF, GAbool Binary)
{
	FitnessFunc* F = malloc(sizeof(FitnessFunc));
	F->ndv = ndv;

	//eq
	F->current_neq = 0;
	F->neq = neq;
	F->EQ = calloc(F->neq, sizeof(gaf_ptr));

	//le
	F->current_nle = 0;
	F->nle = nle;
	F->LE = calloc(F->nle, sizeof(gaf_ptr));

	//ge
	F->current_nge = 0;
	F->nge = nge;
	F->GE = calloc(F->nge, sizeof(gaf_ptr));

	F->ObjType = ObjType;
	F->ObjF = ObjF;
	return F;
}
void destroy_FitFunc(FitnessFunc* FitFunc)
{
	free(FitFunc->EQ);
	free(FitFunc->LE);
	free(FitFunc->GE);
	free(FitFunc);
}
void add_eq(FitnessFunc* FitFunc, const gaf_ptr eq_f)
{
	if (FitFunc->current_neq >= FitFunc->neq)
	{
		printf("Cannot add another equality constraint to the fitness function\n");
		printf("The number of requested equality constraints is %i, and the current number of equality constraints is %i\n", FitFunc->neq, FitFunc->current_neq);
		getchar();
	}
	else
	{
		FitFunc->current_neq++;
		unsigned position = FitFunc->current_neq - 1;
		FitFunc->EQ[position] = eq_f;
	}
}
void add_le(FitnessFunc* FitFunc, const gaf_ptr le_f)
{
	if (FitFunc->current_nle >= FitFunc->nle)
	{
		printf("Cannot add another l.e. constraint to the fitness function\n");
		printf("The number of requested l.e. constraints is %i, and the current number of l.e. constraints is %i\n", FitFunc->nle, FitFunc->current_nle);
		getchar();
	}
	else
	{
		FitFunc->current_nle++;
		unsigned position = FitFunc->current_nle - 1;
		FitFunc->LE[position] = le_f;
	}
}
void add_ge(FitnessFunc* FitFunc, const gaf_ptr ge_f)
{
	if (FitFunc->current_nge >= FitFunc->nge)
	{
		printf("Cannot add another g.e. constraint to the fitness function\n");
		printf("The number of requested g.e. constraints is %i, and the current number of g.e. constraints is %i\n", FitFunc->nge, FitFunc->current_nge);
		getchar();
	}
	else
	{
		FitFunc->current_nge++;
		unsigned position = FitFunc->current_nge - 1;
		FitFunc->GE[position] = ge_f;
	}
}
GAbool check_fitfuncOK(const FitnessFunc* FitFunc)
{
	if (FitFunc->neq == FitFunc->current_neq && FitFunc->nle == FitFunc->current_nle && FitFunc->nge == FitFunc->current_nge && FitFunc->ObjF != NULL)
	{
		if (FitFunc->ObjType == MIN)
			printf("The fitness function is complete and set to minimize\n");
		else if (FitFunc->ObjType == MAX)
			printf("The fitness function is complete and set to maximize\n");
		else
			printf("The fitness function is complete and set to nonesense: %i\n", FitFunc->ObjType);  //should never get here because create_FitFunc() requires MinMAX as input
		
		return GA_TRUE;
	}
	else
	{
		printf("The fitness function is not finished being built\n");
		getchar();
		return GA_TRUE;
	}
}

float* create_Population(unsigned ndv, const float* UB, const float* LB)
{
	//population major array treated like matrix population[chromosome, v] = population[ndv*chromosome + v]
	float* Population = malloc(GA_POPULATION * ndv * sizeof(float));
#pragma omp parallel
	{
		unsigned tid = omp_get_thread_num();
		srand(time(NULL) + tid);  //only works with MSVCRT. include time.
		int p = 0;
#pragma omp for
			dummyMethod3();
		for (p = 0; p < GA_POPULATION; p++)
		{
			for (unsigned v = 0; v < ndv; v++)
			{
				float MAX = pow(2, GA_RESOLUTION) - 1.0f;
				unsigned MAXi = (unsigned)MAX;
				int rndint = rand() % (MAXi + 1);  //i assume this is a less than check!
				float rndn = (((float)rndint / (MAX)) * (UB[v] - LB[v])) + LB[v];
				Population[ndv*p + v] = rndn;
			}
		}
			dummyMethod4();
	}
	return Population;
}
void print_Population(unsigned ndv, const float* Population)
{
	dummyMethod3();
	for (unsigned p = 0; p < GA_POPULATION; p++)
	{
		printf("\nPrinting info on chrom %i: ", p);
		for (unsigned v = 0; v < ndv; v++)
		{
			float val = Population[ndv*p + v];
			printf("%f, ", val);
		}
	}
	dummyMethod4();
}
void destroy_Population(unsigned ndv, float* Population)
{
	free(Population);
}

float* calc_PopFitness(unsigned ndv, const FitnessFunc* FitFunc, const float* Population)
{
	float* Fitness = malloc(GA_POPULATION * sizeof(float));
	int p = 0;
	dummyMethod1();
#pragma omp parallel for
	for (p = 0; p < GA_POPULATION; p++)
	{
		float* DV = malloc(ndv * sizeof(float));
		for (unsigned v = 0; v < ndv; v++)
		{
			DV[v] = Population[ndv*p + v];
		}
		float Fitness_p = eval_Fitfunc(FitFunc, ndv, DV);
		free(DV);
		Fitness[p] = Fitness_p;
	}
	dummyMethod2();
	return Fitness;
}
void print_Fitness(const float* Fitness)
{
	dummyMethod3();
	for (unsigned p = 0; p < GA_POPULATION; p++)
	{
		printf("\nPrinting fitness for chromosome %i: %f", p, Fitness[p]);
	}
	dummyMethod4();
}
void destroy_Fitness(float* Fitness)
{
	free(Fitness);
}

float* crossPop_Min(unsigned ndv, const float* Fitness, const float* Population)
{
	//float* NewFitness = malloc(GA_POPULATION * sizeof(float));
	float* NewPopulation = malloc(GA_POPULATION * ndv * sizeof(float));
	//the following is done in parallel because it is somewhat heavy.  I think...  Whatever.
#pragma omp parallel
	{
		unsigned tid = omp_get_thread_num();
		srand(time(NULL) + tid);  //only works with MSVCRT. include time.
		int p = 0;
#pragma omp for
			dummyMethod3();
		for (p = 0; p < GA_POPULATION; p++)
		{
			unsigned oneDex = rand() % (GA_POPULATION); //assuming this works via less than NOT less than or equal
			unsigned twoDex = rand() % (GA_POPULATION);
			float oneVal = Fitness[oneDex];
			float twoVal = Fitness[twoDex];
			unsigned Mindex = 0;
			if (oneVal <= twoVal)
				Mindex = oneDex;
			else
				Mindex = twoDex;
			for (unsigned v = 0; v < ndv; v++)
				NewPopulation[p * ndv + v] = Population[Mindex * ndv + v];				
		}
			dummyMethod4();
	}
	return NewPopulation;
}
float* matePop(unsigned ndv, const float* CrossOverPop, const FitnessFunc* FitFunc)
{
	float* NewPopulation = malloc(GA_POPULATION * ndv * sizeof(float));
#pragma omp parallel
	{
		unsigned tid = omp_get_thread_num();
		srand(time(NULL) + tid);  //only works with MSVCRT. include time.
		int p = 0;
#pragma omp for
			dummyMethod3();
		for (p = 0; p < GA_POPULATION; p++)
		{
			unsigned oneDex = rand() % (GA_POPULATION); //assuming this works via less than NOT less than or equal
			unsigned twoDex = rand() % (GA_POPULATION);
			float* Baby1 = malloc(ndv * sizeof(float));
			for (unsigned v = 0; v < ndv; v++)
			{
				unsigned flip = rand() % 2;
				if (flip == 1)
					Baby1[v] = CrossOverPop[oneDex * ndv + v];
				else if (flip == 0)
					Baby1[v] = CrossOverPop[twoDex * ndv + v];
				else
				{
					printf("\nSomething went wrong inside of the mutation function\n");
					getchar();
				}
			}
			for (unsigned v = 0; v < ndv; v++)
				NewPopulation[p * ndv + v] = Baby1[v];
			free(Baby1);
		}
			dummyMethod4();
	}
	return NewPopulation;
}
float* mutPop(unsigned ndv, const float* MatePop, const float* UB, const float* LB)
{
	float* NewPop = malloc(GA_POPULATION * ndv * sizeof(float));
#pragma omp parallel
	{
		unsigned tid = omp_get_thread_num();
		srand(time(NULL) + tid);  //only works with MSVCRT. include time.
		int p = 0;
#pragma omp for
			dummyMethod3();
		for (p = 0; p < GA_POPULATION; p++)
		{
			//copy
			for (unsigned v = 0; v < ndv; v++)
			{
				NewPop[p * ndv + v] = MatePop[p * ndv + v];
				//should we mutate?
				unsigned mut = rand() & ndv;
				if (mut == v)
				{
					float MAX = pow(2, GA_RESOLUTION) - 1.0f;
					unsigned MAXi = (unsigned)MAX;
					int rndint = rand() % (MAXi + 1);  //i assume this is a less than check!
					float rndf = (((float)rndint / (MAX)) * (UB[v] - LB[v])) + LB[v];
					NewPop[p * ndv + v] = rndf;
					//printf("Mutation on chromosome %i, DV %i with value %f from thread %i\n", p, mdex, rndf, tid);
				}
			}
		}
			dummyMethod4();
	}
	return NewPop;
}

void print_minVal(unsigned iter, unsigned ndv, const float* Fitness, const float* Population)
{
	float minVal = Fitness[0];
	unsigned minDex = 0;
	dummyMethod3();
	for (unsigned p = 0; p < GA_POPULATION; p++)
	{
		if (Fitness[p] < minVal)
		{
			minVal = Fitness[p];
			minDex = p;
		}
	}
	dummyMethod4();
	printf("\nMinimum value of iteration %i is %f with: ", iter, minVal);
	dummyMethod3();
	for (unsigned v = 0; v < ndv; v++)
	{
		float val = Population[minDex * ndv + v];
		printf("%f, ", val);
	}
	dummyMethod4();
}

void optimPop_Min(unsigned ndv, const FitnessFunc* FitFunc, const float* UB, const float* LB)
{
	float* Population = create_Population(ndv, UB, LB);
	//loop here
	dummyMethod3();
	for (unsigned i = 0; i < 100; i++)
	{
		float* Fitness = calc_PopFitness(ndv, FitFunc, Population);

		print_minVal(i, ndv, Fitness, Population);

		float* CrossOverPop = crossPop_Min(ndv, Fitness, Population);
		float* MatePop = matePop(ndv, CrossOverPop, FitFunc);
		float* MutPop = mutPop(ndv, MatePop, UB, LB);

		destroy_Fitness(Fitness);
		destroy_Population(ndv, CrossOverPop);
		destroy_Population(ndv, MatePop);

		destroy_Population(ndv, Population);
		Population = MutPop;
	}
	dummyMethod4();
	//print_Population(ndv, Population);
	destroy_Population(ndv, Population);
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