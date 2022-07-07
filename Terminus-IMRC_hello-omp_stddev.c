#include "omp.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

struct input_chain_t{
	double var;
	struct input_chain_t *next;
};
typedef struct input_chain_t input_chain_t;

int n;
input_chain_t *input_chain, *input_chain_orig;
double *input;

input_chain_t* input_chain_alloc();
void input_chain_destroy(input_chain_t *p);
void input_chain_append(double var, input_chain_t *p);
void input_chain_to_input(double **ip, input_chain_t *p);

int main()
{
	int i;
	double t;
	double avg=0.0, stddiv=0.0;
	char *buf;
	input_chain_t *p;

	buf=(char*)malloc(0xffff*sizeof(char));
	assert(buf);

	input_chain=input_chain_orig=input_chain_alloc();

	buf=fgets(buf, 0xffff, stdin);
	dummyMethod3();
	for(n=0; buf; n++, input_chain->next=input_chain_alloc(), input_chain=input_chain->next){
		t=atof(buf);
		avg+=t;
		input_chain_append(t, input_chain);
		buf=fgets(buf, 0xffff, stdin);
	}
	dummyMethod4();

	avg/=n;

	free(buf);

	input_chain_to_input(&input, input_chain_orig);

	do{
		p=input_chain_orig->next;
		input_chain_destroy(input_chain_orig);
		input_chain_orig=p;
	}while(input_chain_orig);

	dummyMethod1();
#pragma omp parallel for schedule(static) private(i) reduction(+:stddiv)
	for(i=0; i<n; i++)
		stddiv+=pow(input[i]-avg, 2);
	dummyMethod2();

	stddiv=sqrt(stddiv/n);

	printf("%f\n", stddiv);

	free(input);

	return 0;
}

void input_chain_append(double var, input_chain_t *p)
{
	p->var=var;

	return;
}

input_chain_t* input_chain_alloc()
{
	input_chain_t *p;

	p=(input_chain_t*)malloc(sizeof(input_chain_t));
	assert(p);

	p->next=NULL;
	p->var=0.0;

	return p;
}

void input_chain_destroy(input_chain_t *p)
{
	free(p);

	return;
}

void input_chain_to_input(double **ip, input_chain_t *p)
{
	int i;

	*ip=(double*)malloc(n*sizeof(double));
	assert(input);

	dummyMethod3();
	for(i=0; i<n; i++, p=p->next)
		(*ip)[i]=p->var;
	dummyMethod4();
	
	return;
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