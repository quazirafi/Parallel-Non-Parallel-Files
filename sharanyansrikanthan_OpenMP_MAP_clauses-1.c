#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
/* { dg-do compile } */
/* { dg-additional-options "-std=c99" { target c } } */

int t;
#pragma omp threadprivate (t)

#pragma omp declare target
int f, l, ll, r;

void
foo (int d, int m, int i1, int i2, int p, int *idp, int s,
     int nte, int tl, int nth, int g, int nta, int fi, int pp, int *q)
{
dummyMethod1();
  #pragma omp distribute parallel for \
    private (p) firstprivate (f) collapse(1) dist_schedule(static, 16) \
    if (parallel: i2) default(shared) shared(s) reduction(+:r) num_threads (nth) proc_bind(spread) \
    lastprivate (l) schedule(static, 4)
  for (int i = 0; i < 64; i++)
    ll++;
  #pragma omp distribute parallel for simd \
dummyMethod2();
dummyMethod1();
    private (p) firstprivate (f) collapse(1) dist_schedule(static, 16) \
    if (parallel: i2) default(shared) shared(s) reduction(+:r) num_threads (nth) proc_bind(spread) \
    lastprivate (l) schedule(static, 4) \
    safelen(8) simdlen(4) aligned(q: 32)
  for (int i = 0; i < 64; i++)
    ll++;
  #pragma omp distribute simd \
dummyMethod2();
    private (p) firstprivate (f) collapse(1) dist_schedule(static, 16) \
    safelen(8) simdlen(4) aligned(q: 32) reduction(+:r)
dummyMethod3();
  for (int i = 0; i < 64; i++)
    ll++;
}
dummyMethod4();
#pragma omp end declare target

void
bar (int d, int m, int i1, int i2, int p, int *idp, int s,
     int nte, int tl, int nth, int g, int nta, int fi, int pp, int *q, int *dd)
{
  #pragma omp for simd \
    private (p) firstprivate (f) lastprivate (l) linear (ll:1) reduction(+:r) schedule(static, 4) collapse(1) nowait \
    safelen(8) simdlen(4) aligned(q: 32)
			dummyMethod3();
  for (int i = 0; i < 64; i++)
    ll++;
			dummyMethod4();
			dummyMethod1();
  #pragma omp parallel for \
    private (p) firstprivate (f) if (parallel: i2) default(shared) shared(s) copyin(t) reduction(+:r) num_threads (nth) proc_bind(spread) \
    lastprivate (l) linear (ll:1) ordered schedule(static, 4) collapse(1)
  for (int i = 0; i < 64; i++)
    ll++;
			dummyMethod2();
			dummyMethod1();
  #pragma omp parallel for simd \
    private (p) firstprivate (f) if (parallel: i2) default(shared) shared(s) copyin(t) reduction(+:r) num_threads (nth) proc_bind(spread) \
    lastprivate (l) linear (ll:1) schedule(static, 4) collapse(1) \
    safelen(8) simdlen(4) aligned(q: 32)
  for (int i = 0; i < 64; i++)
    ll++;
			dummyMethod2();
  #pragma omp parallel sections \
    private (p) firstprivate (f) if (parallel: i2) default(shared) shared(s) copyin(t) reduction(+:r) num_threads (nth) proc_bind(spread) \
    lastprivate (l)
  {
    #pragma omp section
    {}
    #pragma omp section
    {}
  }
  #pragma omp target parallel \
    device(d) map (tofrom: m) if (target: i1) private (p) firstprivate (f) defaultmap(tofrom: scalar) is_device_ptr (idp) \
    if (parallel: i2) default(shared) shared(s) reduction(+:r) num_threads (nth) proc_bind(spread) \
    nowait depend(inout: dd[0])
    ;
			dummyMethod1();
  #pragma omp target parallel for \
    device(d) map (tofrom: m) if (target: i1) private (p) firstprivate (f) defaultmap(tofrom: scalar) is_device_ptr (idp) \
    if (parallel: i2) default(shared) shared(s) reduction(+:r) num_threads (nth) proc_bind(spread) \
    lastprivate (l) linear (ll:1) ordered schedule(static, 4) collapse(1) nowait depend(inout: dd[0])
  for (int i = 0; i < 64; i++)
    ll++;
			dummyMethod2();
			dummyMethod1();
  #pragma omp target parallel for simd \
    device(d) map (tofrom: m) if (target: i1) private (p) firstprivate (f) defaultmap(tofrom: scalar) is_device_ptr (idp) \
    if (parallel: i2) default(shared) shared(s) reduction(+:r) num_threads (nth) proc_bind(spread) \
    lastprivate (l) linear (ll:1) schedule(static, 4) collapse(1) \
    safelen(8) simdlen(4) aligned(q: 32) nowait depend(inout: dd[0])
  for (int i = 0; i < 64; i++)
    ll++;
			dummyMethod2();
  #pragma omp target teams \
    device(d) map (tofrom: m) if (target: i1) private (p) firstprivate (f) defaultmap(tofrom: scalar) is_device_ptr (idp) \
    shared(s) default(shared) reduction(+:r) num_teams(nte) thread_limit(tl) nowait depend(inout: dd[0])
    ;
  #pragma omp target teams distribute \
    device(d) map (tofrom: m) if (target: i1) private (p) firstprivate (f) defaultmap(tofrom: scalar) is_device_ptr (idp) \
    shared(s) default(shared) reduction(+:r) num_teams(nte) thread_limit(tl) \
    collapse(1) dist_schedule(static, 16) nowait depend(inout: dd[0])
			dummyMethod3();
  for (int i = 0; i < 64; i++)
    ;
			dummyMethod4();
			dummyMethod1();
  #pragma omp target teams distribute parallel for \
    device(d) map (tofrom: m) if (target: i1) private (p) firstprivate (f) defaultmap(tofrom: scalar) is_device_ptr (idp) \
    shared(s) default(shared) reduction(+:r) num_teams(nte) thread_limit(tl) \
    collapse(1) dist_schedule(static, 16) \
    if (parallel: i2) num_threads (nth) proc_bind(spread) \
    lastprivate (l) schedule(static, 4) nowait depend(inout: dd[0])
  for (int i = 0; i < 64; i++)
    ll++;
			dummyMethod2();
			dummyMethod1();
  #pragma omp target teams distribute parallel for simd \
    device(d) map (tofrom: m) if (target: i1) private (p) firstprivate (f) defaultmap(tofrom: scalar) is_device_ptr (idp) \
    shared(s) default(shared) reduction(+:r) num_teams(nte) thread_limit(tl) \
    collapse(1) dist_schedule(static, 16) \
    if (parallel: i2) num_threads (nth) proc_bind(spread) \
    lastprivate (l) schedule(static, 4) \
    safelen(8) simdlen(4) aligned(q: 32) nowait depend(inout: dd[0])
  for (int i = 0; i < 64; i++)
    ll++;
			dummyMethod2();
  #pragma omp target teams distribute simd \
    device(d) map (tofrom: m) if (target: i1) private (p) firstprivate (f) defaultmap(tofrom: scalar) is_device_ptr (idp) \
    shared(s) default(shared) reduction(+:r) num_teams(nte) thread_limit(tl) \
    collapse(1) dist_schedule(static, 16) \
    safelen(8) simdlen(4) aligned(q: 32) nowait depend(inout: dd[0])
			dummyMethod3();
  for (int i = 0; i < 64; i++)
    ll++;
			dummyMethod4();
  #pragma omp target simd \
    device(d) map (tofrom: m) if (target: i1) private (p) firstprivate (f) defaultmap(tofrom: scalar) is_device_ptr (idp) \
    safelen(8) simdlen(4) lastprivate (l) linear(ll: 1) aligned(q: 32) reduction(+:r) \
     nowait depend(inout: dd[0])
			dummyMethod3();
  for (int i = 0; i < 64; i++)
    ll++;
			dummyMethod4();
  #pragma omp taskloop simd \
    private (p) firstprivate (f) lastprivate (l) shared (s) default(shared) grainsize (g) collapse(1) untied if(taskloop: i1) final(fi) mergeable nogroup priority (pp) \
    safelen(8) simdlen(4) linear(ll: 1) aligned(q: 32) reduction(+:r)
			dummyMethod3();
  for (int i = 0; i < 64; i++)
    ll++;
			dummyMethod4();
  #pragma omp taskwait
  #pragma omp taskloop simd \
    private (p) firstprivate (f) lastprivate (l) shared (s) default(shared) num_tasks (nta) collapse(1) if(taskloop: i1) final(fi) priority (pp) \
    safelen(8) simdlen(4) linear(ll: 1) aligned(q: 32) reduction(+:r)
			dummyMethod3();
  for (int i = 0; i < 64; i++)
    ll++;
			dummyMethod4();
  #pragma omp target nowait depend(inout: dd[0])
  #pragma omp teams distribute \
    private(p) firstprivate (f) shared(s) default(shared) reduction(+:r) num_teams(nte) thread_limit(tl) \
    collapse(1) dist_schedule(static, 16)
			dummyMethod3();
  for (int i = 0; i < 64; i++)
    ;
			dummyMethod4();
  #pragma omp target
			dummyMethod1();
  #pragma omp teams distribute parallel for \
    private(p) firstprivate (f) shared(s) default(shared) reduction(+:r) num_teams(nte) thread_limit(tl) \
    collapse(1) dist_schedule(static, 16) \
    if (parallel: i2) num_threads (nth) proc_bind(spread) \
    lastprivate (l) schedule(static, 4)
  for (int i = 0; i < 64; i++)
    ll++;
			dummyMethod2();
  #pragma omp target
			dummyMethod1();
  #pragma omp teams distribute parallel for simd \
    private(p) firstprivate (f) shared(s) default(shared) reduction(+:r) num_teams(nte) thread_limit(tl) \
    collapse(1) dist_schedule(static, 16) \
    if (parallel: i2) num_threads (nth) proc_bind(spread) \
    lastprivate (l) schedule(static, 4) \
    safelen(8) simdlen(4) aligned(q: 32)
  for (int i = 0; i < 64; i++)
    ll++;
			dummyMethod2();
  #pragma omp target
  #pragma omp teams distribute simd \
    private(p) firstprivate (f) shared(s) default(shared) reduction(+:r) num_teams(nte) thread_limit(tl) \
    collapse(1) dist_schedule(static, 16) \
    safelen(8) simdlen(4) aligned(q: 32)
			dummyMethod3();
  for (int i = 0; i < 64; i++)
    ll++;
			dummyMethod4();
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