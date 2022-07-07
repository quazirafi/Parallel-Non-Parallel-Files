#include <stdio.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
double predict_one(double x, double theta[]) {
    return theta[0] + theta[1] * x;
}

double *train(double x[], double y[], double alpha, int iters, int m) {
  static double theta[2];
  theta[0] = 1;
  theta[1] = 1;

  for (int i = 0; i < iters; ++i) {
    double errors_x1_sum = 0;
    double errors_x2_sum = 0;

dummyMethod1();
    #pragma omp parallel for simd reduction(+:errors_x1_sum, errors_x2_sum) firstprivate(theta, m, x, y)
    for (int j = 0; j < m; j++) {
      double prediction = predict_one(x[j], theta);
      double diff = prediction - y[j];

      errors_x1_sum += diff;
      errors_x2_sum += diff * x[j];
    }
dummyMethod2();

    theta[0] = theta[0] - alpha * (1.0 / m) * errors_x1_sum;
    theta[1] = theta[1] - alpha * (1.0 / m) * errors_x2_sum;
  }

  return theta;
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