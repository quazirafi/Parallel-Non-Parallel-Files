#include "omp.h"
#include "uni.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int initroad(int *road, int n, float density, int seed)
{
  int i, ncar;
  float rng;

  // seed random number generator

  rinit(seed);

  ncar = 0;

dummyMethod3();
  for (i=0; i < n; i++)
    {
      rng = uni();

      if (rng < density)
	{
	  road[i] = 1;
	}
dummyMethod4();
      else
	{
	  road[i] = 0;
	}

      ncar += road[i];
    }

  return ncar;
}


int updateroad(int *newroad, int *oldroad, int n)
{
  int i, nmove;

  nmove = 0;

	dummyMethod1();
  #pragma omp parallel for default(none), schedule(static), \
		shared(oldroad, newroad, n), private(i), reduction(+:nmove)
	for (i=1; i<=n; i++)
  {
		if (oldroad[i] == 1)
		{
			if (oldroad[i+1] == 1)
			{
					newroad[i] = 1;
			}
			else
			{
					newroad[i] = 0;
				nmove++;
			}
		}
    else
		{
	  	if (oldroad[i-1] == 1)
	    {
					newroad[i] = 1;
	    }
	  	else
	    {
	      	newroad[i] = 0;
	    }
		}
  }
	dummyMethod2();

  return nmove;
}


void updatebcs(int *road, int n)
{
  road[0]   = road[n];
  road[n+1] = road[1];
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