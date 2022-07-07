// Prueba-Valgrind
// Código ~equivalente~ al planteado en proy-ENSA 2015
// Código ~equivalente~ al planteado en proy-ENSA 2016
//

#define VAR_STACK
#define COD2016
#define no_COD2015

#if defined (COD2016)
#define MAX_RECURS 10
#elif defined (COD2015)
#define MAX_RECURS 15
#endif

#define MAX_X   4000
#define MAX_Y   3000

#include <png.h>
#include <string.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "img_ng.h"
#include "readpng.h"
#include "write_png.h"

extern uchar * FichImagen1;
extern int Silent;
static tImagen * RGBaGris(tImagen *im, tImagen *Resul);

/* VARIABLES GLOBALES A ESTE MODULO */
tImagen *Original;

void leeImagenOriginal_ng(char *nomImagen)
{

#define PROGNAME "PruVG"

  int rc;
  char * filename = nomImagen;
  tImagen ImLeida;
  unsigned char bg_red=0, bg_green=0, bg_blue=0;
  FILE * infile;
  unsigned char *image_data;
  ulg ancho, alto, rowbytes;
  int channels;

  double LUT_exponent;               /* just the lookup table */
  double CRT_exponent = 2.2;         /* just the monitor */
  double default_display_exponent;   /* whole display system */
  double display_exponent;   /* whole display system */
  char * p;

  LUT_exponent = 1.0;   /* assume no LUT:  most PCs */

  default_display_exponent = LUT_exponent * CRT_exponent;

  if ((p = getenv("SCREEN_GAMMA")) != NULL)
    display_exponent = atof(p);
  else
    display_exponent = default_display_exponent;

  if (!(infile = fopen(filename, "rb"))) {
    fprintf(stderr, PROGNAME ":  can't open PNG file [%s]\n", filename);
  } else {
    if ((rc = readpng_init(infile, &ancho, &alto)) != 0) {
      switch (rc) {
      case 1:
	fprintf(stderr, PROGNAME
		":  [%s] is not a PNG file: incorrect signature\n",
		filename);
	break;
      case 2:
	fprintf(stderr, PROGNAME
		":  [%s] has bad IHDR (libpng longjmp)\n", filename);
	break;
      case 4:
	fprintf(stderr, PROGNAME ":  insufficient memory\n");
	break;
      default:
	fprintf(stderr, PROGNAME
		":  unknown readpng_init() error\n");
	break;
      }
    } else {
      ImLeida.height = alto;
      ImLeida.width = ancho;
      ImLeida.maxHeight = MAX_Y;
      ImLeida.maxWidth = MAX_X;
      ImLeida.offWidth = 0;
      ImLeida.offImg = 0;
      ImLeida.modificada = 0;

      if (readpng_get_bgcolor(&bg_red, &bg_green, &bg_blue) > 1) {
	readpng_cleanup(TRUE);
	fprintf(stderr, PROGNAME
		":  libpng error while checking for background color\n");
      }

      image_data = readpng_get_image(display_exponent, &channels, &rowbytes);

      /*
	if (!Silent)
	fprintf(stderr, PROGNAME
	      ":  rowbytes=%ld, channels=%d\n", rowbytes, channels);
      */

      ImLeida.channels = channels;
      ImLeida.rowbytes = rowbytes;
      ImLeida.imagen = image_data;

      readpng_cleanup(FALSE);
      fclose(infile);

      if (!image_data) {
	fprintf(stderr, PROGNAME ":  unable to decode PNG image\n");
	Original = NULL;
      } else {
	Original = malloc(sizeof(tImagen));
	*Original = ImLeida;
      }
    }
  }

  return;
}

void escribeImagenOriginal_ng(tImagen * Im, char *nomImagen)
{

  (void) writeImage(nomImagen, Im->width, Im->height, Im->channels, Im->imagen);

  return;

}

static tImagen * RGBaGris(tImagen *im, tImagen *Resul)
{
  uchar *im1, *im2;
  uchar r, g, b;
  int v, i;
  int h, w;

  w = im->width;
  h = im->height;
  im1 = im->imagen;
  im2 = Resul->imagen;

			dummyMethod3();
  for(i=0; i<h*w; i++) {
    r = *im1; g= *(im1+1); b= *(im1+2);
    v = (r+g+b) / 3;

    if (v < 0)
      v = 0;
    else if (v > 255)
      v = 255;

    *im2++ = v;
    im1 += im->channels;
  }
			dummyMethod4();

  return Resul;
}

int ejecutaPPAL(void)
{
#if defined (COD2016)
  mFiltro_t MF0 = {10, {2, 2, 2,  0, 10, 0, -2, -2, -2}};
  mFiltro_t MF01 = {15, {2, 2, 2,  0, 15, 0, -2, -2, -2}};
  mFiltro_t MF1 = {15, {3, 3, 3,  0, 15, 0, -3, -3, -3}};
#elif defined (COD2015)
  mFiltro_t MF1 = {18, 10, 1};
#endif

  int nFiltrados = 0;
  int nCambios = 95000;
  tImagen *im, *ImGris; // Para convertir la original a 8bits
  int h, w;

  struct timeval tv_start, tv_end;
  float tiempo_trans;

  im = Original;
  w = im->width;
  h = im->height;

  ImGris=malloc(sizeof(tImagen));
  *ImGris = *im;

  ImGris->rowbytes = im->width;
  ImGris->channels = 1;
  ImGris->imagen = malloc(h*w);

  ImGris = RGBaGris(Original, ImGris);        // ImN1: 8b

  escribeImagenOriginal_ng(ImGris, "Im2_Gray.png");

  gettimeofday(&tv_start, NULL);

  nFiltrados = filtRec(ImGris, &MF1, nCambios, nFiltrados);

  gettimeofday(&tv_end, NULL);

  escribeImagenOriginal_ng(ImGris, "Im3_Final.png");

  tiempo_trans=(tv_end.tv_sec - tv_start.tv_sec) * 10000 +
    (tv_end.tv_usec - tv_start.tv_usec)/100; //en 1/10 milisegundos
  printf("Llamada a filtRec: %.1f ms\n", tiempo_trans/10);

  free(ImGris->imagen);
  free(ImGris);
  ImGris = NULL;

  free(Original->imagen);
  free(Original);
  Original = NULL;

  return nFiltrados;
}

#ifdef VAR_STACK // implementación recursiva con variables en pila

int filtRec(tImagen *im_in, mFiltro_t *MF, int nCambios, int nFiltrados)
{

  int nC, nF = nFiltrados;
  int w = im_in->width;
  int h = im_in->height;

  tImagen I;
  uchar Ipix[h*w];

  tImagen *imFiltrada = &I;
  imFiltrada->imagen = Ipix;

  fprintf(stdout, "filtRec, nF=%d\n", nFiltrados);

  Filtro(im_in, imFiltrada, MF);

  if (++nF < MAX_RECURS) {
    nC = Comp(im_in, imFiltrada);
    if (nC >= nCambios)
      nF = filtRec(imFiltrada, MF, nCambios, nF);
  }

  memcpy(im_in->imagen, imFiltrada->imagen, w*h);
  return nF;
}

#else // VAR_HEAP implementación recursiva con variables en heap

int filtRec(tImagen *im_in, mFiltro_t *MF, int nCambios, int nFiltrados)
{

  int nC, nF = nFiltrados;
  int w = im_in->width;
  int h = im_in->height;

  tImagen *I;
  uchar *Ipix;
  tImagen *imFiltrada;

  I = malloc(sizeof(tImagen));
  Ipix = malloc(w*h*sizeof(unsigned char));

  imFiltrada = I;
  imFiltrada->imagen = Ipix;

  fprintf(stdout, "filtRec, nF=%d\n", nFiltrados);

  Filtro(im_in, imFiltrada, MF);

  if (++nF < MAX_RECURS) {
    nC = Comp(im_in, imFiltrada);
    if (nC >= nCambios)
      nF = filtRec(imFiltrada, MF, nCambios, nF);
  }

  memcpy(im_in->imagen, imFiltrada->imagen, w*h);

  free(imFiltrada->imagen);
  free(imFiltrada);

  return nF;
}

#endif

void Filtro(tImagen *im_i, tImagen *im_o, mFiltro_t *MF)
{

  int w = im_i->width;
  int h = im_i->height;
  int i, j;
  uchar * dirima;

  dirima = im_o->imagen;
  *im_o = *im_i;
  im_o->imagen = dirima;

			dummyMethod1();
  #pragma omp parallel for
  for (i=0; i<h; i++)
    for (j=0; j<w; j++)
      *(im_o->imagen+i*w+j) = FilPixel(im_i, i, j, MF);
			dummyMethod2();

  return;
}

uchar FilPixel(tImagen *im_ima, int i, int j, mFiltro_t *MF)
{
  uchar pixf;
  //uchar subimg[1];
  uchar subimg[9];

  SubMatriz(im_ima, subimg, i, j);
  pixf = valorPixel(subimg, MF);

  return pixf;
}

void SubMatriz(tImagen *im, uchar *subimg, int i, int j)
{
  int w = im->width;
  int h = im->height;
  int ii, jj;
  uchar pix, *so=subimg, *si=im->imagen;

  if ((i==0) || (j==0) || (i==(h-1)) || (j==(w-1))) {
    pix = *(im->imagen + i*w + j);
							dummyMethod3();
    for (ii=0; ii<9; ii++)
      *so++ = pix;
							dummyMethod4();
  } else {
    si += (i-1)*w+(j-1);
    jj = w-3;

    *so++ = *si++;
    *so++ = *si++;
    *so++ = *si++;
    si += jj;
    *so++ = *si++;
    *so++ = *si++;
    *so++ = *si++;
    si += jj;
    *so++ = *si++;
    *so++ = *si++;
    *so++ = *si++;
  }

  return;
}

uchar valorPixel(uchar *s_img, mFiltro_t *MF)
{
  uchar pix;
  int K = MF->K;

#if defined (COD2016)
  int p=0, *co = &(MF->nucleo[0]);
  uchar *s = &s_img[0];

  p += *s++ * *co++;
  p += *s++ * *co++;
  p += *s++ * *co++;

  p += *s++ * *co++;
  p += *s++ * *co++;
  p += *s++ * *co++;

  p += *s++ * *co++;
  p += *s++ * *co++;
  p += *s++ * *co++;

  p /= K;

#elif defined (COD2015)
  int p, b=MF->B, c=MF->C;
  uchar *q;

  p  = *s_img++;
  p += *s_img++;
  p += *s_img++;
  p += *s_img++;

  q = s_img++;

  p += *s_img++;
  p += *s_img++;
  p += *s_img++;
  p += *s_img++;

  p *= b;
  p += *q * c;

  p /= MF->K;
#endif

  if (p > 255)
    pix = (uchar) 255;
  else if (p < 0)
    pix = (uchar) 0;
  else
    pix = (uchar) p;

  return pix;
}

int Comp(tImagen *i1, tImagen *i2)
{
  int w = i1->width;
  int h = i1->height;
  int i, j, desp;
  int difes;

  difes = 0;
			dummyMethod1();
  #pragma omp parallel for reduction(+:difes)
  for (i=0; i<h; i++) {
    for (j=0; j<w; j++) {
      desp = i*w + j;
      difes += abs(*(i1->imagen + desp) - *(i2->imagen + desp));
    }
    //fprintf(stdout, "difes(i=%d): %d\n", i, difes);
  }
			dummyMethod2();
  return difes;
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