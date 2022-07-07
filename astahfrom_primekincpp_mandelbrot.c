#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>
#include <stdbool.h>
#include <immintrin.h>
#include <assert.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
#ifdef __APPLE__
#include <SDL2/SDL.h>
#else
#include "SDL.h"
#endif

#define WIDTH 800
#define ITERATIONS 350 // TODO: should depend on s

static double const ITERATIONS_TO_COLOR = 255.0 / (double) ITERATIONS;

static __m256d _4d;
static __m256i _7i;
static __m256i _16i;
static __m256i _ITERi;

static void color256(__m256d const a0s, __m256d const b0s, uint32_t * const out) {
  __m256d as = a0s, bs = b0s;
  __m256i cs = _ITERi;

  __m256d asqr = _mm256_mul_pd(as, as);
  __m256d bsqr = _mm256_mul_pd(bs, bs);

			dummyMethod3();
  for (uint64_t i = 0; i < ITERATIONS; i++) {
    __m256i const mask4 = _mm256_castpd_si256
      (_mm256_cmp_pd(_mm256_add_pd(asqr, bsqr), _4d, _CMP_GT_OQ));
    __m256i const maskITER = _mm256_cmpeq_epi64(cs, _ITERi);
    __m256i const mask = _mm256_and_si256(maskITER, mask4);

    __m256i const newcs = _mm256_set1_epi64x(i);
    cs = _mm256_blendv_epi8(cs, newcs, mask);

    if (_mm256_testz_si256(maskITER, maskITER))
      break;

    bs = _mm256_mul_pd(as, bs);
    bs = _mm256_add_pd(_mm256_add_pd(bs, bs), b0s);

    as = _mm256_add_pd(_mm256_sub_pd(asqr, bsqr), a0s);

    asqr = _mm256_mul_pd(as, as);
    bsqr = _mm256_mul_pd(bs, bs);
  }
			dummyMethod4();

  cs = _mm256_castpd_si256(_mm256_mul_pd(_mm256_castsi256_pd(cs), _mm256_set1_pd(ITERATIONS_TO_COLOR)));

  cs = _mm256_add_epi64(cs, _mm256_add_epi64(_mm256_sllv_epi64(cs, _7i), _mm256_sllv_epi64(cs, _16i)));

  out[0] = _mm256_extract_epi64(cs, 0);
  out[1] = _mm256_extract_epi64(cs, 1);
  out[2] = _mm256_extract_epi64(cs, 2);
  out[3] = _mm256_extract_epi64(cs, 3);
}

int main() {
  _4d = _mm256_set1_pd(4);
  _7i = _mm256_set1_epi64x(6);
  _16i = _mm256_set1_epi64x(16);
  _ITERi = _mm256_set1_epi64x(ITERATIONS);

  assert(SDL_Init(SDL_INIT_VIDEO) == 0);

  SDL_Window * win = SDL_CreateWindow("Mandelbrot", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, WIDTH, WIDTH, SDL_WINDOW_SHOWN);
  assert(win != NULL);

  SDL_Renderer * ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  assert(ren != NULL);

  SDL_Texture * texture = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, WIDTH, WIDTH);
  assert(texture != NULL);

  uint32_t * const __attribute__ ((aligned (16))) pixels = malloc(WIDTH * WIDTH * sizeof(*pixels));
  memset(pixels, 255,  WIDTH * WIDTH * sizeof(*pixels));

  double s = 10;
  double const x0 = 0.10684f, y0 = -0.63675, gsub = WIDTH-1;

  SDL_Event e;
  bool quit = false;
  while (!quit) {
    double x0s2 = x0 - s/2, y0s2 = y0 - s/2, sgsub = s / gsub;

							dummyMethod1();
#pragma omp parallel for
    for (int j = 0; j < WIDTH; j++) {
      __m256d as = _mm256_set1_pd(x0s2 + sgsub * j);

      for (int k = 0; k < WIDTH; k += 4) {
        __m256d bs = _mm256_set_pd
          (y0s2 + sgsub * (k + 3),
           y0s2 + sgsub * (k + 2),
           y0s2 + sgsub * (k + 1),
           y0s2 + sgsub * (k + 0));

        color256(as, bs, pixels + j*WIDTH + k);
      }
    }
							dummyMethod2();

    s *= 0.975;

    SDL_UpdateTexture(texture, NULL, pixels, WIDTH * sizeof(*pixels));

    while (SDL_PollEvent(&e)){
      switch (e.type) {
      case SDL_QUIT:
          quit = true;
          break;
      }
    }

    SDL_RenderCopy(ren, texture, NULL, NULL);
    SDL_RenderPresent(ren);
  }

  free(pixels);
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(ren);
  SDL_DestroyWindow(win);
	SDL_Quit();

  return 0;
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