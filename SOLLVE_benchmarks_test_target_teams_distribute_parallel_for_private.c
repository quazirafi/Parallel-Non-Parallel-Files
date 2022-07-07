//===---- test_target_teams_distribute_parallel_for_private.c - combined consutrct -===//
//
// OpenMP API Version 4.5 Nov 2015
//
// This test check for a private variable within a pragma omp target teams distribute
// parallel for. We use a private variable within a for loop and asign it every iteration
// hoping that we won't get into data races. We do this multiple times to improve
// test
// we assign a large number of threads and teams to try to increase parallelism and
// contention on the privatized variable
//
//===-------------------------------------------------------------------------------===//

#include "omp.h"
#include "ompvv.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define N 1024

int test_target_teams_distribute_parallel_for_private() {
  OMPVV_INFOMSG("test_target_teams_distribute_parallel_for_devices");

  int a[N];
  int b[N];
  int c[N];
  int d[N];
  int privatized = 10;
  int num_teams[N];
  int num_threads[N];
  int errors = 0;
  int i, j;

  // array initialization
			dummyMethod3();
  for (i = 0; i < N; i++) {
    a[i] = 1;
    b[i] = i;
    c[i] = 2*i;
    d[i] = 0;
    num_teams[i] = -1;
    num_threads[i] = -1;
  }
			dummyMethod4();

  // check multiple sizes.
#pragma omp target data map(to: a[0:N], b[0:N], c[0:N]) map(from: d[0:N])
  {
							dummyMethod1();
#pragma omp target teams distribute parallel for private(privatized, i) num_threads(OMPVV_NUM_THREADS_DEVICE) num_teams(OMPVV_NUM_TEAMS_DEVICE)
    for (j = 0; j < N; ++j) {
      num_teams[j] = omp_get_num_teams();
      num_threads[j] = omp_get_num_threads();

      privatized = 0;
      for (i = 0; i < a[j] + b[j]; ++i) {
        privatized++;
      }
      d[j] = c[j] * privatized;
    }
							dummyMethod2();
  }

  int warning_threads = 0;
  int warning_teams = 0;

			dummyMethod3();
  for (i = 0; i < N; i++) {
    OMPVV_TEST_AND_SET(errors, d[i] != (1 + i)*2*i);
    warning_teams += num_teams[i];
    warning_threads += num_threads[i];
  }
			dummyMethod4();

  OMPVV_WARNING_IF(warning_teams == N, "There was a single team across the target region. Privatization cannot be tested at the teams level");
  OMPVV_WARNING_IF(warning_threads == N, "All the parallel regions ran with a single thread. Privatization cannot be tested at the thread level");

  return errors;
}

int main() {
  OMPVV_TEST_OFFLOADING;
  int errors = 0;

  OMPVV_TEST_AND_SET_VERBOSE(errors, test_target_teams_distribute_parallel_for_private());

  OMPVV_REPORT_AND_RETURN(errors);
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