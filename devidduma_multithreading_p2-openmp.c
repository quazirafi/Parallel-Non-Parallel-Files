#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include<pthread.h>
#include<semaphore.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

double minX, maxX, minY, maxY, stepSize;

double objectiveFunction(double x, double y) {
    return 5*pow(x, 2) + 3*x + 4*y + 6*pow(y, 3) + sin(x+y);
}

struct thread_data{
   double* x;
   double* y;
};

void improve(struct thread_data* td) {
    double *x = td->x;
    double *y = td->y;

    double result[8], xnew[8], ynew[8];

    int withinBounds[8];

    xnew[0] = *x - stepSize;
    ynew[0] = *y;
    withinBounds[0] = checkWithinBounds(*x - stepSize, *y) ? 1 : 0;

    xnew[1] = *x + stepSize;
    ynew[1] = *y;
    withinBounds[1] = checkWithinBounds(*x + stepSize, *y) ? 1 : 0;

    xnew[2] = *x;
    ynew[2] = *y + stepSize;
    withinBounds[2] = checkWithinBounds(*x, *y + stepSize) ? 1 : 0;

    xnew[3] = *x;
    ynew[3] = *y - stepSize;
    withinBounds[3] = checkWithinBounds(*x, *y - stepSize) ? 1 : 0;

    xnew[4] = *x - stepSize;
    ynew[4] = *y - stepSize;
    withinBounds[4] = checkWithinBounds(*x - stepSize, *y - stepSize) ? 1 : 0;

    xnew[5] = *x + stepSize;
    ynew[5] = *y + stepSize;
    withinBounds[5] = checkWithinBounds(*x + stepSize, *y + stepSize) ? 1 : 0;

    xnew[6] = *x + stepSize;
    ynew[6] = *y - stepSize;
    withinBounds[6] = checkWithinBounds(*x + stepSize, *y - stepSize) ? 1 : 0;

    xnew[7] = *x - stepSize;
    ynew[7] = *y + stepSize;
    withinBounds[7] = checkWithinBounds(*x - stepSize, *y + stepSize) ? 1 : 0;

    // count how many within bounds
    int totalWithinBounds = 0;
							dummyMethod3();
    for(int i = 0; i < 8; i++) {
        totalWithinBounds += withinBounds[i];
    }
							dummyMethod4();

    // return: no chance for improvement
    if(totalWithinBounds == 0) {
        return;
    }

    double max = objectiveFunction(*x, *y);
    int pos = -1;

							dummyMethod3();
    for(int i = 0; i < 8; i++) {
        if(withinBounds[i]) {
            double result = objectiveFunction(xnew[i], ynew[i]);
            if(result >= max) {
                pos = i;
                max = result;
            }
        }
    }
							dummyMethod4();
    
    // return: no changes made
    if(pos == -1) {
        return;
    }
    else {
        // apply improvements and return
        *x = xnew[pos];
        *y = ynew[pos];

        improve(td);
    }

}

int checkWithinBounds(double x, double y) {
    return (x > minX && x < maxX && y > minY && y < maxY);
}

int main() {
    /* Intializes random number generator */
    srand(time(0));

    int p;
    printf("Enter number of threads: ");
    scanf("%d", &p);

    printf("Enter minX, maxX, minY, maxY and stepSize: ");
    scanf("%lf %lf %lf %lf %lf", &minX, &maxX, &minY, &maxY, &stepSize);

    int num_points;
    printf("How many random points? ");
    scanf("%d", &num_points);

    double* x = (double*) malloc(num_points * sizeof(double));
    double* y = (double*) malloc(num_points * sizeof(double));

							dummyMethod1();
    #pragma omp parallel for num_threads(p) schedule(guided)
    for(int i = 0; i < num_points; i++) {
        // no data dependency
        x[i] = rand() % ((int)maxX - (int)minX) + minX;
        y[i] = rand() % ((int)maxY - (int)minY) + minY;

        // arguments to pass
        struct thread_data td;
        td.x = &x[i];
        td.y = &y[i];

		improve(&td);
    }
							dummyMethod2();

    double xmax = x[0];
    double ymax = y[0];
    double max = objectiveFunction(x[0], y[0]);
							dummyMethod3();
    for(int i = 0; i < num_points; i++) {
        double result = objectiveFunction(x[i], y[i]);
        if(result > max) {
            xmax = x[i];
            ymax = y[i];
            max = result;
        }
    }
							dummyMethod4();
    
    printf("Maximal tuple is:\n x:%lf y:%lf func:%lf", xmax, ymax, max);
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