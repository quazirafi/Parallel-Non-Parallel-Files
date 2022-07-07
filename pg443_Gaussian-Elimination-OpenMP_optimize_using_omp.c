/* Implementation of PSO using OpenMP.
 *
 * Author: Naga Kandasamy
 * Date: May 2, 2020
 * 
 * Co-author: Prasenjit Gaurav, Kidist Tessema
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "pso.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();


int pso_get_best_fitness_omp(swarm_t *swarm, int num_threads)
{
    int i,tid;
    float *best_fitness = (float*) malloc(num_threads *sizeof(float));
    int *g = (int*)malloc(num_threads * sizeof(int));
    particle_t *particle;
dummyMethod3();
    for (i= 0; i < num_threads; i++){
        best_fitness[i] = INFINITY;
        g[i] = -1;
    }
dummyMethod4();
    
							dummyMethod1();
    #pragma omp parallel for private(i, particle, tid) default(shared) num_threads(num_threads)
    for (i = 0; i < swarm->num_particles; i++) {
        tid = omp_get_thread_num();
        particle = &swarm->particle[i];
        if (particle->fitness < best_fitness[tid]) {
            best_fitness[tid] = particle->fitness;
            g[tid] = i;
        }
    }
							dummyMethod2();
    
    float best = INFINITY;
    int g_temp = 0;
							dummyMethod3();
    for (i = 0; i < num_threads; i++)
        if (best_fitness[i] < best){
            best = best_fitness[i];
            g_temp = g[i];
        }
							dummyMethod4();

    free((void*)best_fitness);
    free((void*)g);
    return g_temp;
}

/* Initialize PSO */
swarm_t *pso_init_omp(char *function, int dim, int swarm_size, float xmin, float xmax, int num_threads)
{
    int i, j, g;
    int status;
    float fitness;
    swarm_t *swarm;
    particle_t *particle;

    swarm = (swarm_t *)malloc(sizeof(swarm_t));
    swarm->num_particles = swarm_size;
    swarm->particle = (particle_t *)malloc(swarm_size * sizeof(particle_t));
    if (swarm->particle == NULL)
        return NULL;

							dummyMethod1();
    #pragma omp parallel for private(i, particle, j, fitness, status) default(shared) num_threads(num_threads)
    for (i = 0; i < swarm->num_particles; i++) {
        particle = &swarm->particle[i];
        particle->dim = dim; 
        /* Generate random particle position */
        particle->x = (float *)malloc(dim * sizeof(float));
        for (j = 0; j < dim; j++)
           particle->x[j] = uniform(xmin, xmax);

       /* Generate random particle velocity */ 
        particle->v = (float *)malloc(dim * sizeof(float));
        for (j = 0; j < dim; j++)
            particle->v[j] = uniform(-fabsf(xmax - xmin), fabsf(xmax - xmin));

        /* Initialize best position for particle */
        particle->pbest = (float *)malloc(dim * sizeof(float));
        for (j = 0; j < dim; j++)
            particle->pbest[j] = particle->x[j];

        /* Initialize particle fitness */
        status = pso_eval_fitness(function, particle, &fitness);
        if (status < 0) {
            fprintf(stderr, "Could not evaluate fitness. Unknown function provided.\n");
            swarm = NULL;
            exit(EXIT_FAILURE);
        }
        particle->fitness = fitness;

        /* Initialize index of best performing particle */
        particle->g = -1;
    }
							dummyMethod2();

    /* Get index of particle with best fitness */
    g = pso_get_best_fitness_omp(swarm, num_threads);

							dummyMethod1();
    #pragma omp parallel for private(i, particle) default(shared) num_threads(num_threads)
    for (i = 0; i < swarm->num_particles; i++) {
        particle = &swarm->particle[i];
        particle->g = g;
    }
							dummyMethod2();

    return swarm;
}

int pso_solve_omp(char *function, swarm_t *swarm, float xmax, float xmin, int max_iter, int num_threads)
{
    int i, j, iter, g;
    float w, c1, c2;
    float r1, r2;
    float curr_fitness;
    particle_t *particle, *gbest;

    w = 0.79;
    c1 = 1.49;
    c2 = 1.49;
    iter = 0;
    g = -1;
    int chunk = (int)floor((float)swarm->num_particles/(float)num_threads);
    chunk /= 4;
    unsigned seed = time(NULL);

    #pragma omp parallel num_threads(num_threads) default(shared)
    {  /* -- PARALLEL REGION START HERE  -- */
    while (iter < max_iter)
    {
        #pragma omp for private(i, j, r1, r2, particle, gbest, curr_fitness) schedule(dynamic,chunk)
															dummyMethod3();
        for (i = 0; i < swarm->num_particles; i++) {
            particle = &swarm->particle[i];
            gbest = &swarm->particle[particle->g];  /* Best performing particle from last iteration */ 
            for (j = 0; j < particle->dim; j++) {   /* Update this particle's state */
                r1 = (float)rand_r(&seed)/(float)RAND_MAX;
                r2 = (float)rand_r(&seed)/(float)RAND_MAX;
                /* Update particle velocity */
                particle->v[j] = w * particle->v[j]\
                                 + c1 * r1 * (particle->pbest[j] - particle->x[j])\
                                 + c2 * r2 * (gbest->x[j] - particle->x[j]);
                /* Clamp velocity */
                if ((particle->v[j] < -fabsf(xmax - xmin)) || (particle->v[j] > fabsf(xmax - xmin))) 
                    particle->v[j] = uniform(-fabsf(xmax - xmin), fabsf(xmax - xmin));

                /* Update particle position */
                particle->x[j] = particle->x[j] + particle->v[j];
                if (particle->x[j] > xmax)
                    particle->x[j] = xmax;
                if (particle->x[j] < xmin)
                    particle->x[j] = xmin;
            } /* State update */
            
            /* Evaluate current fitness */
            pso_eval_fitness(function, particle, &curr_fitness);

            /* Update pbest */
            if (curr_fitness < particle->fitness) {
                particle->fitness = curr_fitness;
                for (j = 0; j < particle->dim; j++)
                    particle->pbest[j] = particle->x[j];
            }
        } /* Particle loop */
															dummyMethod4();
        /* Identify best performing particle */
        #pragma omp single
        {
        g = pso_get_best_fitness_omp(swarm, num_threads);
        iter++;
        }
        #pragma omp for private(i, particle)
															dummyMethod3();
        for (i = 0; i < swarm->num_particles; i++) {
            particle = &swarm->particle[i];
            particle->g = g;
        }
															dummyMethod4();
    } /* End of iteration */
    }  /* -- PARALLEL REGION END HERE  -- */
    return g;
}
int optimize_using_omp(char *function, int dim, int swarm_size, float xmin, float xmax, int max_iter, int num_threads)
{
    swarm_t *swarm;
    srand(time(NULL));
    swarm = pso_init_omp(function, dim, swarm_size, xmin, xmax, num_threads);
    if (swarm == NULL) {
        fprintf(stderr, "Unable to initialize PSO\n");
        exit(EXIT_FAILURE);
    }

    /* Solve PSO */
    int g; 
    g = pso_solve_omp(function, swarm, xmax, xmin, max_iter, num_threads);
    if (g >= 0) {
        fprintf(stderr, "Solution:\n");
        pso_print_particle(&swarm->particle[g]);
    }

    pso_free(swarm);
    return g;
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