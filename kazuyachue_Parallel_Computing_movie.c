//
// Torbert, 8 February 2016
//
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
//
#define M 640
#define N 480
//
typedef struct
{
   double x ;
   double y ;
   double z ;
   //
} triple ;
//
typedef struct
{
   int r;
   int g;
   int b;
   //
} color;
//
typedef struct
{
   triple c;
   color h;
   double r;
   //
} sphere;
//
triple e = { 0.50 , 0.50 , -1.00 } ; // the eye
triple g = { 0.00 , 1.25 , -0.50 } ; // the light
sphere a[4];
color checkerColor = {113, 78, 161};
//
double dotp( triple t , triple u )
{
   return t.x * u.x + t.y * u.y + t.z * u.z ;
}
//
void diff( triple* t , triple u , triple v ) // t = u - v
{
   t->x = u.x - v.x ;
   t->y = u.y - v.y ;
   t->z = u.z - v.z ;
}
//
void init()
{
   a[0].c.x =      0.50 ;
   a[0].c.y = -20000.00 ; // the floor
   a[0].c.z =      0.50 ;
   a[0].r   =  20000.25 ;
   a[0].h.r =    205    ; // color is Peru
   a[0].h.g =    133    ;
   a[0].h.b =     63    ;
   //
   a[1].c.x =      0.50 ;
   a[1].c.y =      0.50 ;
   a[1].c.z =      0.50 ;
   a[1].r   =      0.25 ;
   a[1].h.r =      0    ; // color is Blue
   a[1].h.g =      0    ;
   a[1].h.b =    255    ;
   //
   a[2].c.x =      1.00 ;
   a[2].c.y =      0.50 ;
   a[2].c.z =      1.00 ;
   a[2].r   =      0.25 ;
   a[2].h.r =      0    ; // color is Green
   a[2].h.g =    255    ;
   a[2].h.b =      0    ;
   //
   a[3].c.x =      0.00 ;
   a[3].c.y =      0.75 ;
   a[3].c.z =      1.25 ;
   a[3].r   =      0.50 ;
   a[3].h.r =    255    ; // color is Red
   a[3].h.g =      0    ;
   a[3].h.b =      0    ;
}
//
void drawImage(color* rgb, triple p)
{
	triple r;
	diff(&r, p, e);
	double rmag = sqrt(pow(r.x,2) + pow(r.y, 2) + pow(r.z, 2));
	r.x /= rmag; 
	r.y /= rmag; 
	r.z /= rmag;
	
	int minIndex;
	double minT = INFINITY;
	dummyMethod3();
	for(int i=0; i<4; i++)
	{
		triple vectorc = {a[i].c.x, a[i].c.y, a[i].c.z};
		triple d;
		diff(&d, e, vectorc);
		double a1 = 1.0;
		double b = 2 * dotp(d, r);
		double c = pow(d.x,2) + pow(d.y,2) + pow(d.z, 2) - pow(a[i].r,2);
		double discriminant = pow(b,2) - 4 * a1 * c;
		if(discriminant < 0) continue;
		else
		{
			double T = (-1 * b - sqrt(discriminant)) / 2*a1;
			if (T<0) T = INFINITY;
		
			if(T<minT)
			{
				minT = T;
				minIndex = i;
			}
		}
		
	}
	dummyMethod4();
	if(minT == INFINITY) //missed all spheres, light blue
	{
		rgb->r = 180   ; // red
		rgb->g = 255 ; // green
		rgb->b = 255   ; // blue
	}
	else
	{
		double xCircle = e.x + minT * r.x;
		double yCircle = e.y + minT * r.y;
		double zCircle = e.z + minT * r.z;
		triple p2 = {xCircle, yCircle, zCircle};
		
		//eliminating noise
		triple center = {a[minIndex].c.x, a[minIndex].c.y, a[minIndex].c.z};
		triple noise;
		diff(&noise, p2, center);
		triple normal = noise;
		double nmag = sqrt(pow(noise.x,2) + pow(noise.y, 2) + pow(noise.z, 2));
		noise.x /= nmag;
		noise.y /= nmag;
		noise.z /= nmag;
		
		p2.x += 0.0001 * noise.x;	
		p2.y += 0.0001 * noise.y;	
		p2.z += 0.0001 * noise.z;	
		
		triple r2;
		diff(&r2, g, p2);
		double rmag2 = sqrt(pow(r2.x,2) + pow(r2.y, 2) + pow(r2.z, 2));
		r2.x /= rmag2; 
		r2.y /= rmag2; 
		r2.z /= rmag2;
		
		//checking if there is a shadow
		int shadow = 0;
			dummyMethod3();
		for(int i=0;i<4;i++)
		{
			triple vectorc = {a[i].c.x, a[i].c.y, a[i].c.z};
			triple d;
			diff(&d, p2, vectorc);
			double a1 = 1.0;
			double b = 2 * dotp(d, r2);
			double c = pow(d.x,2) + pow(d.y,2) + pow(d.z, 2) - pow(a[i].r,2);
			double discriminant = pow(b,2) - 4 * a1 * c;
			if(discriminant < 0) continue;
			else
			{
				double T = (-1 * b - sqrt(discriminant)) / 2*a1;
				if (T>0)
				{
					shadow = 1;
					break;
				}
			}
		}
			dummyMethod4();
		
		if (minIndex == 0) //checkerboard code
		{
			int xchecker = (int)(p2.x / 0.1);
			int zchecker = (int)(p2.z / 0.1);
			if (p2.x < 0) xchecker-=1;
			if (p2.z < 0) zchecker -=1;
			int totalchecker = xchecker + zchecker;
			if (totalchecker%2 == 0)
			{
				rgb->r = a[minIndex].h.r * 0.5; // red
				rgb->g = a[minIndex].h.g * 0.5; // green
				rgb->b = a[minIndex].h.b * 0.5; // blue
			}
			else
			{
				rgb->r = checkerColor.r * 0.5; // red
				rgb->g = checkerColor.g * 0.5; // green
				rgb->b = checkerColor.b * 0.5; // blue
			}
		}
		else
		{
			rgb->r = a[minIndex].h.r * 0.5; // red
			rgb->g = a[minIndex].h.g * 0.5; // green
			rgb->b = a[minIndex].h.b * 0.5; // blue
		}

		if (shadow == 0) //lambert's law for non shadow color
		{
			double d = dotp(noise, r2);
			if (d<0.0) d=0.0;
			else
			{
				rgb->r = d * rgb->r + rgb->r; // red
				rgb->g = d * rgb->g + rgb->g; // red
  				rgb->b = d * rgb->b + rgb->b; // red

			}
		}
	}


}
//
int main(void)
{
   int rgb[N][M][3] ; // red-green-blue for each pixel
   //
   int y , x ;
   //
   FILE* fout ;
   //
   init();
   //
   char fname[50];
   sprintf(fname, "rm movie_pngs -r");
   system(fname);
   sprintf(fname, "mkdir movie_pngs");
   system(fname);
   //
   int frameCount ;
   //
   for( frameCount = 1 ; frameCount <= 100 ; frameCount++ )
   {
	a[2].c.z = 1.0 - (0.01 * frameCount);
	a[1].c.y = 0.5 + (0.01 * frameCount);
	a[3].c.x = (0.01 * frameCount);	

	for( y = 0 ; y < N ; y++ )
	{
			dummyMethod1();
		#pragma omp parallel for private(x)
		for( x = 0 ; x < M ; x++)
		{
			triple p = {x/480.0-0.15, 1.0-y/480.0, 0.0};
			color rgb2;
			drawImage(&rgb2, p);
			rgb[y][x][0] = rgb2.r;
			rgb[y][x][1] = rgb2.g;
			rgb[y][x][2] = rgb2.b;
		}
			dummyMethod2();
	}
	//
	fout = fopen( "movie.ppm" , "w" ) ;
	//
	fprintf( fout , "P3\n" ) ;
	fprintf( fout , "%d %d\n" , M , N ) ;
	fprintf( fout , "255\n" ) ;
	//
	for( y = 0 ; y < N ; y++ )
	{
		for( x = 0 ; x < M ; x++)
		{
			 fprintf( fout , "%d %d %d\n" ,
			 rgb[y][x][0] , rgb[y][x][1] , rgb[y][x][2] ) ;
		}
	}
	fclose( fout ) ;
	sprintf(fname, "convert movie.ppm ./movie_pngs/f%07d.png", frameCount);
	system(fname);
	printf("done %d/%d\n", frameCount, 100);
   }
   //
   return 0 ;
}
//
// end of file
//
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