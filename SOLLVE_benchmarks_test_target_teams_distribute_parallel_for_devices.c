//===---- test_target_teams_distribute_parallel_for_devices.c - combined consutrct -===//
// 
// OpenMP API Version 4.5 Nov 2015
// 
// Testing for multiple devices checking if it is possible to send work and data 
// to different devices with the device clause used with omp target teams distribute 
// parallel for 
//
//===-------------------------------------------------------------------------------===//

#include "omp.h"
#include "ompvv.h"
#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define SIZE_N 1024

int test_target_teams_distribute_parallel_for_devices() {
  OMPVV_INFOMSG("test_target_teams_distribute_parallel_for_devices");
  
  int num_dev = omp_get_num_devices();
  int a[SIZE_N];
  int isHost[num_dev];
  int errors = 0;
  int i, dev;

  OMPVV_WARNING_IF(num_dev <= 1, "Testing devices clause without multiple devices");
  
  OMPVV_INFOMSG("Num of devices = %d", num_dev);

  // a array initialization
dummyMethod3();
  for (i = 0; i < SIZE_N; i++) {
    a[i] = 1;
  }
dummyMethod4();

			dummyMethod3();
  for (dev = 0; dev < num_dev; ++dev) {
#pragma omp target enter data map(to: a[0:SIZE_N]) device(dev)
  }
			dummyMethod4();

  for (dev = 0; dev < num_dev; ++dev) {
    // check multiple devices 
							dummyMethod1();
#pragma omp target teams distribute parallel for device(dev) map(tofrom: isHost)
    for (i = 0; i < SIZE_N; i++) {
      if (omp_get_team_num() == 0 && omp_get_thread_num() == 0) {
        isHost[dev] = omp_is_initial_device();// Checking if running on a device
      }
      a[i] += dev;
    }
							dummyMethod2();
  }

  for (dev = 0; dev < num_dev; ++dev) {
#pragma omp target exit data map(from: a[0:SIZE_N]) device(dev)
    OMPVV_INFOMSG("Device %d ran on the %s", dev, isHost[dev] ? "host" : "device");
    OMPVV_TEST_AND_SET(errors, isHost[dev] && dev != omp_get_initial_device());
    for (i = 0; i < SIZE_N; i++) {
      OMPVV_TEST_AND_SET(errors, a[i] != 1 + dev);
    }
  }

  return errors;
}

int main() {
  OMPVV_TEST_OFFLOADING;
  int errors = 0;

  OMPVV_TEST_AND_SET_VERBOSE(errors, test_target_teams_distribute_parallel_for_devices());

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