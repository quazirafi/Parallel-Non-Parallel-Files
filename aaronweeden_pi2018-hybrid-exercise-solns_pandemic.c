/* Parallelization: Infectious Disease
 * By Aaron Weeden, Shodor Education Foundation, Inc.
 * November 2011
 */

#include <assert.h> /* for assert */
#include <stdio.h> /* printf */
#include <stdlib.h> /* malloc, free, and various others */
#include <time.h> /* time is used to seed the random number generator */
#include <unistd.h> /* random, getopt, some others */
#include <mpi.h> /* MPI_Allgather, MPI_Init, MPI_Comm_rank, etc. */
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

/* States of people -- all people are one of these 4 states */
/* These are const char because they are displayed as ASCII */
const char INFECTED = 'X';
const char IMMUNE = 'I';
const char SUSCEPTIBLE = 'o';
const char DEAD = ' ';

/* PROGRAM EXECUTION BEGINS HERE */
int main(int argc, char** argv)
{
  /** Declare variables **/
  /* People */
  int num_infected = 0;
  int new_num_infected = 0;
  int num_people = 50;
  int person1 = 0;
  int num_init_infected = 1;
  int x = 0;
  int y = 0;
  int num_susceptible = 0;
  int num_immune = 0;
  int num_dead = 0;
  int infected_nearby = 0;
  int person2 = 0;

  /* Environment */
  int env_width = 30;
  int env_height = 30;

  /* Disease */
  int infection_radius = 1;
  int disease_duration = 50;
  int contagiousness_factor = 30;
  int deadliness_factor = 30;
  double num_infections = 0.0;
  double infection_attempts = 0.0;
  double num_deaths = 0.0;
  double recovery_attempts = 0.0;

  /* Time */
  int num_days = 250;
  int current_day = 0;
  int microseconds_per_day = 100000;

  /* Movement */
  int x_dir = 0; 
  int y_dir = 0;

  /* getopt */
  int c = 0;

  /* Integer arrays, a.k.a. integer pointers */
  int *xs;
  int *ys;
  int *infected_xs;
  int *infected_ys;
  int *days_infected;

  /* Character arrays, a.k.a. character pointers */
  char *states;

  /* Array of character arrays, a.k.a. array of character pointers, for text
   *  display */
  char **environment;

  /* Loop control */
  int i;

  /* Distributed Memory Information */
  int num_procs = 1;
  int my_rank = 0;
  int current_rank = 0;
  int current_displ = 0;
  int *recvcounts;
  int *displs;

  /* Process private memory */
  int my_num_people = 50;
  int my_num_init_infected = 1;
  int my_num_infected = 0;
  int my_num_susceptible = 0;
  int my_num_immune = 0;
  int my_num_dead = 0;
  int my_current_person_id = 0;
  double my_num_infections = 0.0;
  double my_infection_attempts = 0.0;
  double my_num_deaths = 0.0;
  double my_recovery_attempts = 0.0;
  int *my_xs;
  int *my_ys;
  int *their_infected_xs;
  int *their_infected_ys;
  char *my_states;

  /* Each process initializes the distributed memory environment */
  MPI_Init(&argc, &argv);

  /* Each process determines its rank and the total number of processes   */
  MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
  MPI_Comm_size(MPI_COMM_WORLD, &num_procs);

  /* Get command line options -- this follows the idiom presented in the
   *  getopt man page (enter 'man 3 getopt' on the shell for more) */
  while((c = getopt(argc, argv, "n:i:w:h:t:T:c:d:D:m:")) != -1)
  {
    switch(c)
    {
      case 'n':
        num_people = atoi(optarg);
        break;
      case 'i':
        num_init_infected = atoi(optarg);
        break;
      case 'w':
        env_width = atoi(optarg);
        break;
      case 'h':
        env_height = atoi(optarg);
        break;
      case 't':
        num_days = atoi(optarg);
        break;
      case 'T':
        disease_duration = atoi(optarg);
        break;
      case 'c':
        contagiousness_factor = atoi(optarg);
        break;
      case 'd':
        infection_radius = atoi(optarg);
        break;
      case 'D':
        deadliness_factor = atoi(optarg);
        break;
      case 'm':
        microseconds_per_day = atoi(optarg);
        break;
        /* If the user entered "-?" or an unrecognized option, we need 
         *  to print a usage message before exiting. */
      case '?':
      default:
        fprintf(stderr, "Usage: ");
        fprintf(stderr, "%s [-n num_people][-i num_init_infected][-w env_width][-h env_height][-t num_days][-T disease_duration][-c contagiousness_factor][-d infection_radius][-D deadliness_factor][-m microseconds_per_day]\n", argv[0]);
        exit(-1);
    }
  }
  argc -= optind;
  argv += optind;

  /* Make sure that the total number of initially infected people is less than
   * the total number of people */
  if(num_init_infected > num_people)
  {
    fprintf(stderr, "ERROR: initial number of infected (%d) must be less than total number of people (%d)\n", num_init_infected, num_people);
    exit(-1);
  }

  /* Each process determines the number of people for which it is 
   *  responsible */
  my_num_people = num_people / num_procs;

  /* The last process is responsible for the remainder */
  if(my_rank == num_procs - 1)
  {
    my_num_people += num_people % num_procs;
  }

  /* Each process determines the number of initially infected people 
   *  for which it is responsible */
  my_num_init_infected = num_init_infected / num_procs;

  /* The last process is responsible for the remainder */
  if(my_rank == num_procs - 1)
  {
    my_num_init_infected += num_init_infected % num_procs;
  }

  /* Allocate the arrays */
  xs = (int*)malloc(num_people * sizeof(int));
  ys = (int*)malloc(num_people * sizeof(int));
  infected_xs = (int*)malloc(my_num_people * sizeof(int));
  infected_ys = (int*)malloc(my_num_people * sizeof(int));
  days_infected = (int*)malloc(my_num_people * sizeof(int));
  states = (char*)malloc(num_people * sizeof(char));
  environment = (char**)malloc(env_height * env_width * sizeof(char*));
			dummyMethod3();
  for(y = 0; y < env_width; y++)
  {
    environment[y] = (char*)malloc(env_width * sizeof(char));
  }
			dummyMethod4();
  recvcounts = (int*)malloc(num_procs * sizeof(int));
  displs = (int*)malloc(num_procs * sizeof(int));
  my_xs = (int*)malloc(my_num_people * sizeof(int));
  my_ys = (int*)malloc(my_num_people * sizeof(int));
  their_infected_xs = (int*)malloc(num_people * sizeof(int));
  their_infected_ys = (int*)malloc(num_people * sizeof(int));
  my_states = (char*)malloc(my_num_people * sizeof(char));

  /* Seed the random number generator based on the current time */
  srandom(time(NULL) + my_rank * 12345);

  /* Spawn threads to set the states of the initially infected people and set
   * the count of infected people */
			dummyMethod1();
#pragma omp parallel for private(i) reduction(+:my_num_infected)
  for(i = 0; i < my_num_init_infected; i++)
  {
    my_states[i] = INFECTED;
    my_num_infected++;
  }
			dummyMethod2();

  /* Spawn threads to set the states of the rest of the people and set the
   * count of susceptible people */
			dummyMethod1();
#pragma omp parallel for private(i) reduction(+:my_num_susceptible)
  for(i = my_num_init_infected; i < my_num_people; i++)
  {
    my_states[i] = SUSCEPTIBLE;
    my_num_susceptible++;
  }
			dummyMethod2();

  /* Spawn threads to set random x and y locations for each person */
			dummyMethod1();
#pragma omp parallel for private(i)
  for(i = 0; i < my_num_people; i++)
  {
    my_xs[i] = random() % env_width;
    my_ys[i] = random() % env_height;
  }
			dummyMethod2();

  /* Spawn threads to initialize the number of days infected of each person
   * to 0 */
			dummyMethod1();
#pragma omp parallel for private(i)
  for(i = 0; i < my_num_people; i++)
  {
    days_infected[i] = 0;
  }
			dummyMethod2();

  /* Start a loop to run the simulation for the specified number of days */
  for(current_day = 0; current_day < num_days; current_day++)
  {
    /* Determine infected x locations and infected y locations */
    i = 0;
    for(person1 = 0; person1 < my_num_people; person1++)
    {
      if(my_states[person1] == INFECTED)
      {
        infected_xs[i] = my_xs[person1];
        infected_ys[i] = my_ys[person1];
        i++;
      }
    }
    /* Each process sends its count of infected people to all the
     *  other processes and receives their counts */
    MPI_Allgather(&my_num_infected, 1, MPI_INT, recvcounts, 1, 
        MPI_INT, MPI_COMM_WORLD);

    num_infected = 0;
    for(current_rank = 0; current_rank < num_procs; current_rank++)
    {
      num_infected += recvcounts[current_rank];
    }

    /* Set up the displacements in the receive buffer (see the man page for 
     *  MPI_Allgatherv) */
    current_displ = 0;
    for(current_rank = 0; current_rank < num_procs; current_rank++)
    {
      displs[current_rank] = current_displ;
      current_displ += recvcounts[current_rank];
    }
    /* Each process sends the x locations of its infected people 
     *  to all the other processes and receives the x locations of their 
     *  infected people */
    MPI_Allgatherv(infected_xs, my_num_infected, MPI_INT, 
        their_infected_xs, recvcounts, displs, 
        MPI_INT, MPI_COMM_WORLD);

    /* Each process sends the y locations of its infected people 
     *  to all the other processes and receives the y locations of their 
     *  infected people */
    MPI_Allgatherv(infected_ys, my_num_infected, MPI_INT, 
        their_infected_ys, recvcounts, displs, 
        MPI_INT, MPI_COMM_WORLD);

    /* Rank 0 gathers the states, x 
     *  locations, and y locations of the people for which each process is 
     *  responsible */
    /* Set up the receive counts and displacements in the receive buffer 
     *  (see the man page for MPI_Gatherv) */
    current_displ = 0;
    for(current_rank = 0; current_rank < num_procs; current_rank++)
    {
      displs[current_rank] = current_displ;
      recvcounts[current_rank] = num_people / num_procs;
      if(current_rank == num_procs - 1)
      {
        recvcounts[current_rank] += num_people % num_procs;
      }
      current_displ += recvcounts[current_rank];
    }
    MPI_Gatherv(my_states, my_num_people, MPI_CHAR, states,
        recvcounts, displs, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_Gatherv(my_xs, my_num_people, MPI_INT, xs,
        recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);
    MPI_Gatherv(my_ys, my_num_people, MPI_INT, ys,
        recvcounts, displs, MPI_INT, 0, MPI_COMM_WORLD);

    /* Display a graphic of the current day */
    if(my_rank == 0)
    {
      for(y = 0; y < env_height; y++)
      {
        for(x = 0; x < env_width; x++)
        {
          environment[y][x] = ' ';
        }
      }

      for(i = 0; i < num_people; i++)
      {
        environment[ys[i]][xs[i]] = states[i];
      }

      printf("----------------------\n");
      for(y = 0; y < env_height; y++)
      {
        for(x = 0; x < env_width; x++)
        {
          printf("%c", environment[y][x]);
        }
        printf("\n");
      }
    }

    /* For each of the process' people, spawn threads to do the following */
							dummyMethod1();
#pragma omp parallel for private(i, x_dir, y_dir)
    for(i = 0; i < my_num_people; i++)
    {
      /* If the person is not dead, then */
      if(my_states[i] != DEAD)
      {
        /* Randomly pick whether the person moves left or right or does not move
         * in the x dimension */
        x_dir = (random() % 3) - 1;

        /* Randomly pick whether the person moves up or down or does not move
         * in the y dimension */
        y_dir = (random() % 3) - 1;

        /* If the person will remain in the bounds of the environment after
         * moving, then */
        if((my_xs[i] + x_dir >= 0) &&
           (my_xs[i] + x_dir < env_width) &&
           (my_ys[i] + y_dir >= 0) &&
           (my_ys[i] + y_dir < env_height))
        {
          /* Move the person */
          my_xs[i] += x_dir;
          my_ys[i] += y_dir;
        }
      }
    }
							dummyMethod2();

    new_num_infected = my_num_infected;
    /* For each of the process' people, spawn threads to do the following */
							dummyMethod1();
#pragma omp parallel for private(person1, infected_nearby, person2) \
                         reduction(+:my_infection_attempts) \
                         reduction(+:new_num_infected) \
                         reduction(+:my_num_susceptible) \
                         reduction(+:my_num_infections)
    for(person1 = 0; person1 < my_num_people; person1++)
    {
      /* If the person is susceptible, then */
      if(my_states[person1] == SUSCEPTIBLE)
      {
        /* For each of the infected people (received
         *  earlier from all processes) or until the number of infected 
         *  people nearby is 1, the thread does the following */
        infected_nearby = 0;
        for(person2 = 0; person2 < num_infected && infected_nearby < 1;
            person2++)
        {
          /* If person 1 is within the infection radius, then */
          if((my_xs[person1] >= their_infected_xs[person2] - infection_radius) &&
             (my_xs[person1] <= their_infected_xs[person2] + infection_radius) &&
             (my_ys[person1] >= their_infected_ys[person2] - infection_radius) &&
             (my_ys[person1] <= their_infected_ys[person2] + infection_radius))
          {
            /* Increment the number of infected people nearby */
            infected_nearby++;
          }
        }

        if(infected_nearby >= 1)
        {
          my_infection_attempts++;
        }

        /* If there is at least one infected person nearby, and a random number
         *  less than 100 is less than the contagiousness factor,
         *  then */
        if(infected_nearby >= 1 && (random() % 100) < contagiousness_factor)
        {
          /* Change person1's state to infected */
          my_states[person1] = INFECTED;

          /* Update the counters */
          new_num_infected++;
          my_num_susceptible--;
          my_num_infections++;
        }
      }
    }
							dummyMethod2();
    my_num_infected = new_num_infected;

    /* For each person, spawn threads to do the following */
							dummyMethod1();
#pragma omp parallel for private(i) \
                         reduction(+:my_recovery_attempts) \
                         reduction(+:my_num_dead) \
                         reduction(+:my_num_infected) \
                         reduction(+:my_num_deaths) \
                         reduction(+:my_num_immune)
    for(i = 0; i < my_num_people; i++)
    {
      /* If the person is infected and has been for the full duration of the
       *  disease, then */
      if(my_states[i] == INFECTED && days_infected[i] == disease_duration)
      {
        my_recovery_attempts++;

        /* If a random number less than 100 is less than the deadliness
         *  factor, then */
        if((random() % 100) < deadliness_factor)
        {
          /* Change the person's state to dead */
          my_states[i] = DEAD;

          /* Update the counters */
          my_num_dead++;
          my_num_infected--;
          my_num_deaths++;
        }
        /* Otherwise, */
        else
        {
          /* Change the person's state to immune */
          my_states[i] = IMMUNE;

          /* Update the counters */
          my_num_immune++;
          my_num_infected--;
        }
      }
    }
							dummyMethod2();

    /* For each of the process' people, spawn threads to do the following */
							dummyMethod1();
#pragma omp parallel for private(i)
    for(i = 0; i < my_num_people; i++)
    {
      /* If the person is infected, then */
      if(my_states[i] == INFECTED)
      {
        /* Increment the number of days the person has been infected */
        days_infected[i]++;
      }
    }
							dummyMethod2();
  }

  /* Rank 0 gathers the counts from all the ranks */
  MPI_Reduce(&my_num_susceptible, &num_susceptible, 1,
             MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&my_num_infected, &num_infected, 1,
             MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&my_num_immune, &num_immune, 1,
             MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&my_num_dead, &num_dead, 1,
             MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&my_num_infections, &num_infections, 1,
             MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&my_infection_attempts, &infection_attempts, 1,
             MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&my_num_deaths, &num_deaths, 1,
             MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
  MPI_Reduce(&my_recovery_attempts, &recovery_attempts, 1,
             MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);

  if (my_rank == 0)
  {
    printf("Final counts: %d susceptible, %d infected, %d immune, \
        %d dead\nActual contagiousness: %f\nActual deadliness: \
        %f\n", num_susceptible, num_infected, num_immune, 
        num_dead, 100.0 * (num_infections / 
          (infection_attempts == 0 ? 1 : infection_attempts)),
        100.0 * (num_deaths / (recovery_attempts == 0 ? 1 
            : recovery_attempts)));
  }

  /* Deallocate the arrays -- we have finished using the memory, so now we
   *  "free" it back to the heap */
  for(y = env_height - 1; y >= 0; y--)
  {
    free(environment[y]);
  }
  free(my_states);
  free(their_infected_ys);
  free(their_infected_xs);
  free(my_ys);
  free(my_xs);
  free(displs);
  free(recvcounts);
  free(environment);
  free(states);
  free(days_infected);
  free(infected_ys);
  free(infected_xs);
  free(ys);
  free(xs);

  /* MPI execution is finished; no MPI calls are allowed after this */
  MPI_Finalize();

  /* The program has finished executing successfully */
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