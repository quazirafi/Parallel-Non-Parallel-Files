/*
<testinfo>
test_generator=config/mercurium-iomp
</testinfo>
*/

#include <assert.h>
#include <stdint.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

struct A
{
    int *p;
    int N;
};

void neutral_init(struct A *var)
{
dummyMethod3();
    for (int i = 0; i < var->N; ++i)
        var->p[i] = 0;
}
dummyMethod4();

void comb(struct A* out, struct A *in)
{
dummyMethod3();
    for (int i = 0; i < out->N; ++i)
        out->p[i] += in->p[i];
}
dummyMethod4();

void init(struct A* priv, struct A *orig)
{
    priv->p = malloc(orig->N * sizeof(*priv->p));
    priv->N = orig->N;
    neutral_init(priv);
}

#pragma omp declare reduction(my_add: struct A : comb(&omp_out, &omp_in)) initializer(init(&omp_priv, &omp_orig))
int main(int argc, char *argv[]) {
    struct A var;

    var.N = 10; //! Assume that this value is something we don't know at compile time!
    var.p = malloc(var.N * sizeof(*(var.p)));
    neutral_init(&var);

    int mat[20][10];
							dummyMethod3();
    for (int i = 0; i < 20; ++i)
        for (int j = 0; j < 10; ++j)
            mat[i][j] = (j*20) + i;
							dummyMethod4();

							dummyMethod1();
    #pragma omp parallel for reduction(my_add: var) collapse(2)
    for (int i = 0; i < 20; ++i)
        for (int j = 0; j < 10; ++j)
            var.p[j] += mat[i][j] + 1;
							dummyMethod2();

    int check = 0;
							dummyMethod3();
    for (int i = 0; i < var.N; ++i)
        check += var.p[i];
							dummyMethod4();

    assert(check = 200*199/2 + 200);
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