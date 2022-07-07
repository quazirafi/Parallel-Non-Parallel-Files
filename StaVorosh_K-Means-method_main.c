#include "header.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

int main(void)
{
	struct Points *Field; 
	struct Cluster *Clusters;
	int Width, Height;
	int NumOfPoints;
	int NumOfClusters;
	Field = Init(&Height,&Width,&NumOfPoints);
	Clusters = Calculate(Field, Height, Width, &NumOfClusters, NumOfPoints);
	Output_Data(Clusters, Field, NumOfClusters);
	return 0;
}
	
	
	
struct Points* Init(int *Height, int *Width, int *Num)
{

	int i;
	int NumOfPoints;
	struct Points *Field;
	//double x, y;

	FILE *fi;
	
	/*printf("Enter Height: ");
	scanf("%lf",Height);
	printf("Enter Width: ");
	scanf("%lf",Width);
	printf("Enter number of points: ");
	scanf("%d",&NumOfPoints);*/
	
	fi = fopen("input.txt","r");
	
	fscanf(fi, "%d %d %d", Height, Width, &NumOfPoints);
	
	Field = (struct Points*)malloc(NumOfPoints*sizeof(struct Points));
	
	dummyMethod3();
	for(i=0;i<NumOfPoints;i++)
		fscanf(fi,"%lf %lf", &Field[i].x, &Field[i].y);
	dummyMethod4();

	*Num = NumOfPoints;
	fclose(fi);
	return Field;
}

double Dist(double Point_x, double Point_y, double Cluster_x, double Cluster_y)
{
	return sqrt((Cluster_x - Point_x)*(Cluster_x - Point_x) + (Cluster_y - Point_y)*(Cluster_y - Point_y));
}

struct Cluster* Calculate(struct Points* Field, int Height, int Width, int* Num, int NumOfPoints)
{
	struct Cluster *Clusters;
	int i,j,k,NumOfClusters;
	int n;
	double Min;
	/*int Min_x;
	int Min_y;
	int Max_x;
	int Max_y;*/
	double New_Cluster_X;
	double New_Cluster_Y;
	int Min_cluster;
	double Distance;
	double Point_X, Point_Y;
	int Flag = 1;
	int New_Flag;
	
	
	printf("Enter number of clusters: ");
	scanf("%d",&NumOfClusters);
	
	Clusters = (struct Cluster*)malloc(NumOfClusters * sizeof(struct Cluster));
	Init_Clusters(Clusters, NumOfClusters);
	
	srand(time(NULL));
	
	dummyMethod3();
	for(i = 0; i< NumOfClusters; i++)
	{
		Clusters[i].x = (double)(rand()%Width);
		Clusters[i].y = (double)(rand()%Height);
	}
	dummyMethod4();

	dummyMethod1();
	#pragma omp parallel for private(i, Min)
	for(i = 0;i<NumOfPoints;i++)
	{
		Min = (double)(Height + Width);
		for(k = 0; k<NumOfClusters; k++)
		{
			Distance = Dist(Field[i].x,Field[i].y,Clusters[k].x,Clusters[k].y);
			if(Distance < Min)
			{
				Min = Distance;
				Min_cluster = k;
			}
		}
		Field[i].cluster = Min_cluster;
		Clusters[Min_cluster] = AddIndex(Clusters[Min_cluster], i);
	}
	dummyMethod2();
	
	while(Flag == 1)
	{
		Flag = 0;
			dummyMethod1();
		#pragma omp parallel for private(k)
		for(k=0; k<NumOfClusters; k++)
		{
			n = GetClusterNumOfPoints(Clusters[k]);
			New_Cluster_X = 0;
			New_Cluster_Y = 0;
			
			/*for(i = 0; i < n; i++)
			{
				Point_X = GetX(Field, Clusters[k],i);
				Point_Y = GetY(Field, Clusters[k],i);
				New_Cluster_X = (i*New_Cluster_X + Point_X)/(i+1);//vot on obhod perepolneniya
				New_Cluster_Y = (i*New_Cluster_Y + Point_Y)/(i+1);
			}*/
			#pragma omp parallel for private(i) reduction(+:New_Cluster_X, New_Cluster_Y)
			for(i = 0; i < n; i++)
			{
				New_Cluster_X += GetX(Field, Clusters[k],i)/n;
				New_Cluster_Y += GetY(Field, Clusters[k],i)/n;
			}
			Clusters[k].x = New_Cluster_X;
			Clusters[k].y = New_Cluster_Y;
		}
			dummyMethod2();
		Clear_Points(Clusters, NumOfClusters);
			dummyMethod1();
		#pragma omp parallel for private(i, Min)
		for(i = 0;i<NumOfPoints;i++)
		{
			Min = (double)(Height + Width);
			for(k = 0; k<NumOfClusters; k++)
			{
				Distance = Dist(Field[i].x,Field[i].y,Clusters[k].x,Clusters[k].y);
				if(Distance < Min)
				{
					Min = Distance;
					Min_cluster = k;
				}
			}
			if(Field[i].cluster != Min_cluster)
				Flag = 1;
			Field[i].cluster = Min_cluster;
			Clusters[Min_cluster] = AddIndex(Clusters[Min_cluster], i);
		}
			dummyMethod2();
	}
	*Num = NumOfClusters;
	return Clusters;
}
	
struct Cluster AddIndex(struct Cluster Cluster, int i)
{
	struct Indexes *Index;
	struct Indexes *root;
	root = Cluster.root;
	if(!(root))
		Cluster.root = CreatePoint(i);
	else
	{
		Index = CreatePoint(i);
		while(GoNext(root))
			root = GoNext(root);
		root->Next_Point = Index;
	}
	return Cluster;
}

struct Indexes* CreatePoint(int i)
{
	struct Indexes* point;
	point = (struct Indexes*)malloc(sizeof(struct Indexes));
	point->Index = i;
	point->Next_Point = NULL;
	return point;
}
	
	
struct Indexes* GoNext(struct Indexes *root)
{
	return root->Next_Point;
}

double GetX(struct Points *Field, struct Cluster Cluster, int i)
{
	int j = 0;
	struct Indexes *root;
	root = Cluster.root;
	while(j<i)
	{
		root = GoNext(root);
		j++;
	}
	return Field[root->Index].x;
}

double GetY(struct Points *Field, struct Cluster Cluster, int i)
{
	int j = 0;
	struct Indexes *root;
	root = Cluster.root;
	while(j<i)
	{
		root = GoNext(root);
		j++;
	}
	return Field[root->Index].y;
}

void Output_Data(struct Cluster* Clusters, struct Points* Field, int NumOfClusters)
{
	int i;
	double x, y;
	struct Indexes *root;
	
	FILE *fo;
	fo = fopen("output.txt","w");
	dummyMethod3();
	for(i=0;i<NumOfClusters;i++)
	{
		root = Clusters[i].root;
		fprintf(fo,"%d Cluster: Center x = %lf y = %lf\n", i+1, Clusters[i].x, Clusters[i].y);
		while(root)
		{
			fprintf(fo,"%lf %lf\n", Field[root->Index].x, Field[root->Index].y);
			root = GoNext(root);
		}
		fprintf(fo,"\n\n");
	}
	dummyMethod4();
	fclose(fo);
	return;
}

void Clear_Points(struct Cluster *Clusters, int NumOfClusters)
{	
	int i;
	struct Indexes *tmp, *root;
	
	dummyMethod1();
	#pragma omp parallel for private(i)
	for(i=0;i<NumOfClusters;i++)
	{
		root = Clusters[i].root;
		while(root)
		{
			tmp = root;
			root = GoNext(root);
			free(tmp);
		}
		Clusters[i].root = NULL;
	}
	dummyMethod2();
	
	return;
}

void Init_Clusters(struct Cluster* Clusters, int NumOfClusters)
{
	int i;
	
	dummyMethod1();
	#pragma omp parallel for private(i)
	for(i=0;i<NumOfClusters;i++)
	{
		Clusters[i].x = -1;
		Clusters[i].y = -1;
		Clusters[i].root = NULL;
	}
	dummyMethod2();
	return;
}

int GetClusterNumOfPoints(struct Cluster Cluster)
{
	int n=0;
	struct Indexes *root;
	root = Cluster.root;
	while(root)
	{
		n++;
		root = GoNext(root);
	}
	return n;
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