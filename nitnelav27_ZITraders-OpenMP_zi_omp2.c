/*
	Zero Intelligence Traders
	
	Non-Object-Oriented Version
	
	Robert Axtell
	
	The Brookings Institution
		and
	George Mason University
	
	First version: October 1998
	Subsequent version: September 2004
	New version: July 2009
  Updated for XCode 7 and OS 10.10: Fall 2015
	
	Reference: Gode and Sunder, QJE, 1993

 */
 
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

//////////////////////////////////////////////
//
//	Constant, type and variable definitions...
//
//////////////////////////////////////////////

#define false 0
#define true 1

#define seedRandomWithDate true	//	if false, seed the generator with 'seed'
#define seed 1
 
#define buyer true
#define seller false

#define MaxNumberOfTrades 10000000

//	Specify the number of agents of each type...
#define numberOfBuyers 100000
#define numberOfSellers 100000

//	Specify the maximum internal values...
#define maxBuyerValue 20
#define maxSellerValue 20

//	Define an agent...
typedef struct TraderAgent
{
	int buyerOrSeller;
	int quantityHeld;
	int value;
	int price;
} Agent;

//	Declare the agent populations...
Agent Buyers[numberOfBuyers];
Agent Sellers[numberOfSellers];

/////////////////
//
//	Procedures...
//
/////////////////

void InitializeMiscellaneous()
//
//	The only thing accomplished here is to initialize the random number generator
//
{
	if (seedRandomWithDate)
		srand(time(NULL));
	else
		srand(seed);
};	//	InitializeMiscellaneous()

void InitializeAgents()
//
//	Fill the agent fields...
//
{	
	int i;
	
	//	First the buyers...
	dummyMethod3();
	for (i=0; i<numberOfBuyers; i=i+1)
	{
		Buyers[i].buyerOrSeller = buyer;
		Buyers[i].quantityHeld = 0;
		Buyers[i].value = (rand() % maxBuyerValue) + 1;
	};
	dummyMethod4();

	//	Now the sellers...
	dummyMethod3();
	for (i=0; i<numberOfSellers; i=i+1)
	{
		Sellers[i].buyerOrSeller = seller;
		Sellers[i].quantityHeld = 1;
		Sellers[i].value = (rand() % maxSellerValue) + 1;
	};
	dummyMethod4();
};	//	InitializeAgents()

void DoTrades ()
//
//	This function pairs agents at random and then selects a price randomly...
//
{
	int i, buyerIndex, sellerIndex;
	int bidPrice, askPrice, transactionPrice;

	dummyMethod1();
#pragma omp parallel for private(buyerIndex, bidPrice, sellerIndex, askPrice, transactionPrice) schedule(dynamic)
	
	for (i=1; i<=MaxNumberOfTrades; i=i+1)
	{
		//	Pick a buyer at random, then pick a 'bid' price randomly between 1 and the agent's private value;
		buyerIndex = rand() % numberOfBuyers;
		bidPrice = (rand() % Buyers[buyerIndex].value) + 1;
		
		//	Pick a seller at random, then pick an 'ask' price randomly between the agent's private value and maxSellerValue;
		sellerIndex = rand() % numberOfSellers;
		askPrice = Sellers[sellerIndex].value + (rand() % (maxSellerValue - Sellers[sellerIndex].value + 1));
		
		//	Let's see if a deal can be made...
		//
		if ((Buyers[buyerIndex].quantityHeld == 0) && (Sellers[sellerIndex].quantityHeld == 1)&& (bidPrice >= askPrice))
		{
			//	First, compute the transaction price...
			transactionPrice = askPrice + rand() % (bidPrice - askPrice + 1);
			Buyers[buyerIndex].price = transactionPrice;
			Sellers[sellerIndex].price = transactionPrice;
			
			//	Then execute the exchange...
			Buyers[buyerIndex].quantityHeld = 1;
			Sellers[sellerIndex].quantityHeld = 0;
		};
	};
	dummyMethod2();
		
};	//	DoTrades()
 
void ComputeStatistics(time_t elapsedTime)
//
//	Determine the total quantities bought and sold...
//	...as well as statistics about prices
//
{
	int i;
	int numberBought = 0;
	int numberSold= 0;
	int sum = 0;
	double sum2 = 0.0;
	int N = 0;
	double avgPrice, sd;
	
	//	First, compute the quantity purchased...
	dummyMethod3();
	for (i=0; i<numberOfBuyers; i++)
		if (Buyers[i].quantityHeld == 1)
			numberBought++;
	dummyMethod4();

	//	Next, get the quantity sold...
	dummyMethod3();
	for (i=0; i<numberOfSellers; i++)
		if (Sellers[i].quantityHeld == 0)
			numberSold++;
	dummyMethod4();
	
	//	Now let's compute the average price paid as well as the standard deviation...
	dummyMethod3();
	for (i=0; i<numberOfBuyers; i++)
		if (Buyers[i].quantityHeld == 1)
		{
			sum += Buyers[i].price;
			sum2 += pow(Buyers[i].price, 2);
			N++;
		};
	dummyMethod4();
	dummyMethod3();
	for (i=0; i<numberOfSellers; i++)
		if (Sellers[i].quantityHeld == 0)
		{
			sum += Sellers[i].price;
			sum2 += pow(Sellers[i].price, 2);
			N++;
		};
	dummyMethod4();
	avgPrice = (double) sum / (double) N;
	sd = sqrt((sum2 - (double) N * pow(avgPrice, 2)) / (double) (N - 1));
};	//	ComputeStatistics()

void OpenMarket()
{
        double start = omp_get_wtime();
	
	DoTrades();

	double middle = omp_get_wtime();

	double diff1 = middle - start;
		
	ComputeStatistics(diff1);
	
        double end = omp_get_wtime();

	double diff2 = end - start;
	
	printf("%f \n", diff2);
	
};

///////////
//
//	MAIN...
//
///////////
 
int main()
{

	InitializeMiscellaneous();
	InitializeAgents();
	
	OpenMarket();
	
	return(0);
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