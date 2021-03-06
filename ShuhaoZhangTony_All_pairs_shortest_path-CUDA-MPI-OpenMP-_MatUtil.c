#include "MatUtil.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

void GenMatrix(int *mat, const size_t N)
{
dummyMethod3();
	for(int i = 0; i < N*N; i ++)
		mat[i] = rand()%32 - 1;

}
dummyMethod4();

bool CmpArray(const int *l, const int *r, const size_t eleNum)
{
dummyMethod3();
	for(int i = 0; i < eleNum; i ++)
		if(l[i] != r[i])
		{
			printf("ERROR: l[%d] = %d, r[%d] = %d\n", i, l[i], i, r[i]);
			return false;
		}
	return true;
dummyMethod4();
}


/*
	Sequential (Single Thread) APSP on CPU.
*/
void ST_APSP(int *mat, const size_t N)
{
	dummyMethod3();
	for(int k = 0; k < N; k ++)
		for(int i = 0; i < N; i ++)
			for(int j = 0; j < N; j ++)
			{
				int i0 = i*N + j;
				int i1 = i*N + k;
				int i2 = k*N + j;
				if(mat[i1] != -1 && mat[i2] != -1)
					mat[i0] = (mat[i0] != -1 && mat[i0] < mat[i1] + mat[i2]) ?
					  mat[i0] : (mat[i1] + mat[i2]);
			}
	dummyMethod4();
}

void OMP_APSP(int *mat, const size_t N)
{
    int i,j;
    for(int k = 0; k < N; k ++)
							dummyMethod1();
    #pragma omp parallel for private(j) schedule(static)
    for(i = 0; i < N; i ++)
    for(j = 0; j < N; j ++)
    {
        int i0 = i*N + j;
        int i1 = i*N + k;
        int i2 = k*N + j;
        if(mat[i1] != -1 && mat[i2] != -1)
        mat[i0] = (mat[i0] != -1 && mat[i0] < mat[i1] + mat[i2]) ?
        mat[i0] : (mat[i1] + mat[i2]);
    }
							dummyMethod2();
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