/* Model of a forest fire - a 2D rectangular grid of trees is initialized
   with one random tree caught on fire. At each time step, trees that are not
   on fire yet check their neighbors to the north, east, south, and west, and
   if any of them are on fire, the tree catches fire with some percent chance.
   The model runs for a certain number of time steps, which can be controlled
   by the user. At the end of the simulation, the program outputs the total
   percentage of trees burned. Tree data can also be output at each time step
   if a filename is provided by the user.

   All processes are responsible for running the
   simulation and outputting data. The rows of the forest are split up as
   evenly as possible among the processes, with the remainder split evenly among
   the first few processes. At each time step, processes must each send one row 
   of data to their top neighbor and one row of data to their bottom neighbor to
   communicate at the boundaries between process' rows. Code that should only be
   executed by one process are performed by a single "boss" process.
   */

/* Author: Aaron Weeden, Shodor, 2015 */

/* Naming convention:
   ALL_CAPS for constants
   CamelCase for globals and functions
   lowerCase for locals
   */
#include "omp.h"
#include <mpi.h> /* MPI_Init(), MPI_Finalize(), etc. */
#include <stdbool.h> /* bool type */
#include <stdio.h> /* printf() */
#include <stdlib.h> /* atoi(), exit(), EXIT_FAILURE, malloc(), free(),
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();
                       random() */
#include <string.h> /* strcpy() */
#include <unistd.h> /* getopt() */

/* Declare which MPI process is the boss */
#define BOSS 0

/* Define descriptions of command line options */
#define N_ROWS_DESCR \
  "The forest has this many rows of trees (positive integer)"
#define N_COLS_DESCR \
  "The forest has this many columns of trees (positive integer)"
#define BURN_PROB_DESCR \
  "Chance of catching fire if next to burning tree (positive integer [0..100])"
#define N_MAX_BURN_STEPS_DESCR \
  "A burning tree stops burning after this many time steps (positive integer bigger than 1)"
#define N_STEPS_DESCR \
  "Run for this many time steps (positive integer)"
#define RAND_SEED_DESCR \
  "Seed value for the random number generator (positive integer)"
#define OUTPUT_FILENAME_DESCR \
  "Filename to output tree data at each time step (file must not already exist)"
#define IS_RAND_FIRST_TREE_DESCR \
  "Start the first on a random first tree as opposed to the middle tree"

/* Define default values for simulation parameters - each of these parameters
   can also be changed later via user input */
#define N_ROWS_DEFAULT 21
#define N_COLS_DEFAULT N_ROWS_DEFAULT
#define BURN_PROB_DEFAULT 100
#define N_MAX_BURN_STEPS_DEFAULT 2
#define N_STEPS_DEFAULT N_ROWS_DEFAULT
#define RAND_SEED_DEFAULT 1
#define DEFAULT_IS_OUTPUTTING_EACH_STEP false
#define DEFAULT_IS_RAND_FIRST_TREE false

/* Define characters used on the command line to change the values of input
   parameters */
#define N_ROWS_CHAR 'r'
#define N_COLS_CHAR 'c'
#define BURN_PROB_CHAR 'b'
#define N_MAX_BURN_STEPS_CHAR 'm'
#define N_STEPS_CHAR 't'
#define RAND_SEED_CHAR 's'
#define OUTPUT_FILENAME_CHAR 'o'
#define IS_RAND_FIRST_TREE_CHAR 'f'

/* Define options string used by getopt() - a colon after the character means
   the parameter's value is specified by the user */
const char GETOPT_STRING[] = {
  N_ROWS_CHAR, ':',
  N_COLS_CHAR, ':',
  BURN_PROB_CHAR, ':',
  N_MAX_BURN_STEPS_CHAR, ':',
  N_STEPS_CHAR, ':',
  RAND_SEED_CHAR, ':',
  OUTPUT_FILENAME_CHAR, ':',
  IS_RAND_FIRST_TREE_CHAR
};

/* Define a mapping from the row and column of a given tree in a forest with
   boundaries to the index of that tree in a 1D array that includes
   boundaries */
#define TREE_MAP(row, col, nColsPlusBounds) ((row) * (nColsPlusBounds) + (col))

/* Define a mapping from the row and column of a given tree in a forest with
   boundaries to the index of that tree in a 1D array that does not include
   boundaries */
#define NEW_TREE_MAP(row, col, nCols) ((row - 1) * (nCols) + (col - 1))

/* Declare global parameters */
int NRows = N_ROWS_DEFAULT;
int NCols = N_COLS_DEFAULT;
int BurnProb = BURN_PROB_DEFAULT;
int NMaxBurnSteps = N_MAX_BURN_STEPS_DEFAULT;
int NSteps = N_STEPS_DEFAULT;
int RandSeed = RAND_SEED_DEFAULT;
bool IsOutputtingEachStep = DEFAULT_IS_OUTPUTTING_EACH_STEP;
bool IsRandFirstTree = DEFAULT_IS_RAND_FIRST_TREE;
char *OutputFilename;

/* Declare other needed global variables */
bool AreParamsValid = true; /* Do the model parameters have valid values? */
int NTrees; /* Total number of trees in the forest */
int NRowsPlusBounds; /* Number of rows of trees plus the boundary rows */
int NColsPlusBounds; /* Number of columns of trees plus the boundary columns */
int NTreesPlusBounds; /* Total number of trees plus the boundaries */
int MiddleRow; /* The tree in the middle is here. If an even number of rows,
                  this tree is just below the middle */
int MiddleCol; /* The tree in the middle is here. If an even number of cols,
                  this tree is just to the right of the middle */
int CurStep; /* The current time step */
int NBurnedTrees; /* The total number of burned trees */
char ExeName[32]; /* The name of the program executable */
int NMaxBurnStepsDigits; /* The number of digits in the max burn steps; used for
                            outputting tree data */
int *Trees; /* 1D tree array, contains a boundary around the outside of the
               forest so the same neighbor checking algorithm can be used on
               all cells */
int *NewTrees; /* Copy of 1D tree array - used so that we don't update the
                  forest too soon as we are deciding which new trees
                  should burn -- does not contain boundary */
MPI_File OutputFile; /* For outputting tree data to a file using MPI */
int BytesPerRow; /* How many bytes of information in each row? Used for
                    outputting to a file */
int OutputFileOffset = 0; /* Byte in the output file to write to next */
int MyRank; /* MPI rank of the given process executing this code */
int Procs; /* Total number of MPI processes */
int *SendBuf; /* Buffer for sending messages using MPI */
int *RecvBuf; /* Buffer for receiving messages using MPI */
int NRowsBefore; /* How many rows are above the current process'? */
int NRowsAfter; /* How many rows are below the current process'? */
bool IsMiddleRowMine; /* Is the current process responsible for the middle
                         row? */

/* DECLARE FUNCTIONS */

/* Prints out a description of an integer command line option

   @param optChar The character used to specify the option
   @param optDescr The description of the option
   @param optDefault The default value of the option
   */
void DescribeOptionInt(const char optChar, const char *optDescr,
    const int optDefault) {
  fprintf(stderr, "-%c : \n\t%s\n\tdefault: %d\n", optChar, optDescr,
      optDefault);
}

/* Prints out a description of a string command line option

   @param optChar The character used to specify the option
   @param optDescr The description of the option
   */
void DescribeOptionNoDefault(const char optChar, const char *optDescr) {
  fprintf(stderr, "-%c : \n\t%s\n", optChar, optDescr);
}

/* Print an error message

   @param errorMsg Buffer containing the message
   */
void PrintError(const char *errorMsg) {
  if (MyRank == BOSS) {
    fprintf(stderr, "%s", errorMsg);
  }
  AreParamsValid = false;
}

/* Display to the user what options are available for running the program and
   exit the program in failure

   @param errorMsg The error message to print
   */
void PrintUsageAndExit() {
  if (MyRank == BOSS) {
    fprintf(stderr, "Usage: ");
    fprintf(stderr, "%s [OPTIONS]\n", ExeName);
    fprintf(stderr, "Where OPTIONS can be any of the following:\n");
    DescribeOptionInt(N_ROWS_CHAR, N_ROWS_DESCR, N_ROWS_DEFAULT);
    DescribeOptionInt(N_COLS_CHAR, N_COLS_DESCR, N_COLS_DEFAULT);
    DescribeOptionInt(BURN_PROB_CHAR, BURN_PROB_DESCR, BURN_PROB_DEFAULT);
    DescribeOptionInt(N_MAX_BURN_STEPS_CHAR, N_MAX_BURN_STEPS_DESCR,
        N_MAX_BURN_STEPS_DEFAULT);
    DescribeOptionInt(N_STEPS_CHAR, N_STEPS_DESCR, N_STEPS_DEFAULT);
    DescribeOptionInt(RAND_SEED_CHAR, RAND_SEED_DESCR, RAND_SEED_DEFAULT);
    DescribeOptionNoDefault(OUTPUT_FILENAME_CHAR, OUTPUT_FILENAME_DESCR);
    DescribeOptionNoDefault(IS_RAND_FIRST_TREE_CHAR,
        IS_RAND_FIRST_TREE_DESCR);
  }
  MPI_Finalize();
  exit(EXIT_FAILURE);
}

/* Assert that a user's input value is an integer. If it is not, print
   a usage message and an error message and exit the program.

   @param param The user's input value
   @param optChar The character used to specify the user's input value
   */
void AssertInteger(int param, const char optChar) {
  char errorStr[64];

  /* Get the user's input value, assume floating point */
  const float floatParam = atof(optarg);

  /* Make sure positive and integer */
  if (floatParam != param) {
    sprintf(errorStr, "ERROR: value for -%c must be an integer\n",
        optChar);
    PrintError(errorStr);
  }
}

/* Assert that a user's input value is a positive integer. If it is not, print
   a usage message and an error message and exit the program.

   @param param The user's input value
   @param optChar The character used the specify the user's input value
   */
void AssertPositiveInteger(int param, const char optChar) {
  char errorStr[64];

  /* Get the user's input value, assume floating point */
  const float floatParam = atof(optarg);

  /* Make sure positive and integer */
  if (param < 1 || floatParam != param) {
    sprintf(errorStr, "ERROR: value for -%c must be positive integer\n",
        optChar);
    PrintError(errorStr);
  }
}

/* Assert that a user's input value is bigger than a value. If it is
   not, print a usage message and an error message and exit the program.

   @param param The user's input value
   @param low The value the parameter needs to be bigger than
   @param optChar The character used the specify the user's input value
   */
void AssertBigger(int param, const int val, const char optChar) {
  char errorStr[64];

  if (param <= val) {
    sprintf(errorStr,
        "ERROR: value for -%c must be bigger than %d\n", optChar, val);
    PrintError(errorStr);
  }
}

/* Assert that a user's input value is between two values, inclusive. If it is
   not, print a usage message and an error message and exit the program.

   @param param The user's input value
   @param low The lowest value the parameter can be
   @param high The highest value the parameter can be
   @param optChar The character used the specify the user's input value
   */
void AssertBetweenInclusive(int param, const int low, const int high,
    const char optChar) {
  char errorStr[64];

  if (param < low || param > high) {
    sprintf(errorStr,
        "ERROR: value for -%c must be between %d and %d, inclusive\n",
        optChar, low, high);
    PrintError(errorStr);
  }
}

/* Exit if a file already exists */
void AssertFileDNE(const char *filename) {
  char errorStr[64];

  if (access(filename, F_OK) != -1) {
    sprintf(errorStr,
        "ERROR: File '%s' already exists\n", filename);
    PrintError(errorStr);
  }
}


/* Allow the user to change simulation parameters via the command line

   @param argc The number of command line arguments to parse
   @param argv The array of command line arguments to parse
   */
void GetUserOptions(const int argc, char **argv) {
  char c; /* Loop control variable */

  /* Loop over argv, setting parameter values given */
  while ((c = getopt(argc, argv, GETOPT_STRING)) != -1) {
    switch(c) {
      case N_ROWS_CHAR:
        NRows = atoi(optarg);
        AssertPositiveInteger(NRows, N_ROWS_CHAR);
        break;
      case N_COLS_CHAR:
        NCols = atoi(optarg);
        AssertPositiveInteger(NCols, N_COLS_CHAR);
        break;
      case BURN_PROB_CHAR:
        BurnProb = atoi(optarg);
        AssertInteger(BurnProb, BURN_PROB_CHAR);
        AssertBetweenInclusive(BurnProb, 0, 100, BURN_PROB_CHAR);
        break;
      case N_MAX_BURN_STEPS_CHAR:
        NMaxBurnSteps = atoi(optarg);
        AssertPositiveInteger(NMaxBurnSteps, N_MAX_BURN_STEPS_CHAR);
        AssertBigger(NMaxBurnSteps, 1, N_MAX_BURN_STEPS_CHAR);
        break;
      case N_STEPS_CHAR:
        NSteps = atoi(optarg);
        AssertPositiveInteger(NSteps, N_STEPS_CHAR);
        break;
      case RAND_SEED_CHAR:
        RandSeed = atoi(optarg);
        AssertPositiveInteger(RandSeed, RAND_SEED_CHAR);
        break;
      case OUTPUT_FILENAME_CHAR:
        IsOutputtingEachStep = true;
        OutputFilename = optarg;
        break;
      case IS_RAND_FIRST_TREE_CHAR:
        IsRandFirstTree = true;
        break;
      case '?':
      default:
        PrintError("ERROR: illegal option\n");
        PrintUsageAndExit();
    }
  }

  if (IsOutputtingEachStep) {
    /* Make sure the output file does not exist (DNE) */
    if (MyRank == BOSS) { /* There would be a race condition if one process
                             checks if the file exists, sees that it does not
                             exist (DNE), and creates the file, then another
                             process checks if the file exists and sees that it 
                             does exist, even though it DNE initially */
      AssertFileDNE(OutputFilename);
    }
  }

  if (Procs > NRows) {
    PrintError("ERROR: The number of processes cannot be greater than the number of rows\n");
  }
}

/* Calculate the number of rows for which each process is responsible */
void DistributeRows() {
  const int evenSplit = NRows / Procs; /* If the number of rows is divided
                                          evenly with no remainder, this is
                                          the result */
  const int remainder = NRows % Procs; /* The remainder of that division is
                                          this result */

  /* All processes have at least an even split of the forest */
  NRows = evenSplit;

  /* The remainder is split up evenly among the first few processes; each
     process gets one extra row */
  if (MyRank < remainder) {
    NRows++;
    NRowsBefore =
      (evenSplit + 1) * (MyRank); /* The processes that have one more than an
                                     even split of rows are between
                                     [0..MyRank]. */
    NRowsAfter =
      (evenSplit + 1) * (remainder - MyRank - 1) + /* The processes that have
                                                      one more than an
                                                      even split of rows are
                                                      between
                                                      (MyRank..remainder]. */
      (evenSplit    ) * (Procs - remainder); /* The processes that have an
                                                even split of rows are
                                                between [remainder..Procs) */
  }
  else {
    NRowsBefore =
      (evenSplit + 1) * (remainder) + /* The processes that have one more than
                                         an even split of rows are between
                                         [0..remainder]. */
      (evenSplit    ) * (MyRank - remainder); /* The processes that have an
                                                 even split of rows are
                                                 between
                                                 [remainder..MyRank] */
    NRowsAfter =
      (evenSplit    ) * (Procs - MyRank - 1); /* The processes that have an
                                                 even split of rows are
                                                 between [MyRank..Procs) */
  }

  /* Determine whether the current process is responsible for the middle row */
  IsMiddleRowMine = (!IsRandFirstTree && MiddleRow >= NRowsBefore &&
      MiddleRow < NRowsBefore + NRows);

  /* If the current process is responsible for the middle row, indicate which
     row that is relative to the process' first row */
  if (IsMiddleRowMine) {
    MiddleRow -= NRowsBefore;
  }
}

/* Allocate dynamic memory */
void AllocateMemory() {
  Trees    = (int*)malloc(NTreesPlusBounds * sizeof(int));
  NewTrees = (int*)malloc(          NTrees * sizeof(int));

  /* The send and receive buffers are single rows with boundary columns */
  SendBuf = (int*)malloc(NColsPlusBounds * sizeof(int));
  RecvBuf = (int*)malloc(NColsPlusBounds * sizeof(int));
}

/* Generate a random integer between [min..max)

   @param min Smallest integer to generate
   @param max 1 more than the biggest integer to generate
   @return random integer
   */
int RandBetween(const int min, const int max) {
  return min + (random() % (max - min));
}

/* Light a random tree on fire, set all other trees to be not burning */
void InitData() {
  int row;
  int col;
  int rank;
  bool amIChosen;

  /* Set all trees as having burned for 0 time steps */
			dummyMethod1();
#pragma omp parallel for private(col)
  for (row = 1; row < NRows + 1; row++) {
    for (col = 1; col < NCols + 1; col++) {
      Trees[         TREE_MAP(row, col, NColsPlusBounds)] =
        NewTrees[NEW_TREE_MAP(row, col, NCols)]           = 0;
    }
  }
			dummyMethod2();

  /* Set the boundaries as burnt out */
			dummyMethod1();
#pragma omp parallel for private(col)
  for (row = 0; row < NRowsPlusBounds; row++) {
    /* Left */
    Trees[TREE_MAP(row, 0, NColsPlusBounds)] = NMaxBurnSteps;

    /* Top/Bottom */
    if ((MyRank == 0 && row == 0) ||
        (MyRank == Procs - 1 && row == NRows + 1)) {
      for (col = 1; col < NCols + 1; col++) {
        Trees[TREE_MAP(row, col, NColsPlusBounds)] = NMaxBurnSteps;
      }
    }

    /* Right */
    Trees[TREE_MAP(row, NCols + 1, NColsPlusBounds)] = NMaxBurnSteps;
  }
			dummyMethod2();

  if (IsRandFirstTree) {
    /* The boss chooses a random process to light a random tree on fire */
    if (MyRank == BOSS) {
      rank = RandBetween(0, Procs);
    }

    /* The boss broadcasts the rank of the chosen process */
    MPI_Bcast(&rank, 1, MPI_INT, BOSS, MPI_COMM_WORLD);

    /* The chosen process sets a random tree as having burned for 1 time step */
    amIChosen = (rank == MyRank);
  }
  else {
    amIChosen = IsMiddleRowMine;
  }

  if (amIChosen) {
    if (IsRandFirstTree) {
      /* Light a random tree on fire */
      row = RandBetween(1, NRows + 1);
      col = RandBetween(1, NCols + 1);
    }
    else {
      /* Light the middle tree on fire */
      row = MiddleRow + 1;
      col = MiddleCol + 1;
    }
    Trees[         TREE_MAP(row, col, NColsPlusBounds)] =
      NewTrees[NEW_TREE_MAP(row, col, NCols)]           = 1;
    NBurnedTrees++;
  }
}

/* Write a buffer of a certain length to the output file

   @param buf The buffer
   @param whoWrites The rank of the process who writes to the file
   */
void WriteToFile(char *buf, const int whoWrites) {
  const int len = strlen(buf);

  if (MyRank == whoWrites) {
    MPI_File_write_at(OutputFile, OutputFileOffset, buf, len, MPI_CHAR,
        MPI_STATUS_IGNORE);
  }

  OutputFileOffset += len * sizeof(char);
}

/* Output tree data for the current time step */
void OutputData() {
  int row;
  int col;
  char buf[64];

  /* Write the header for the current time step */
  sprintf(buf, "Time step %d\n", CurStep);
  WriteToFile(buf, BOSS);

  /* Adjust the offset to take into account the tree data for all processes
     whose ranks are less than the current process' */
  OutputFileOffset += NRowsBefore * BytesPerRow;

			dummyMethod3();
  for (row = 1; row < NRows + 1; row++) {
    for (col = 1; col < NCols + 1; col++) {
      sprintf(buf, "%*d ",
          NMaxBurnStepsDigits, Trees[TREE_MAP(row, col, NColsPlusBounds)]);
      WriteToFile(buf, MyRank);
    }
    WriteToFile("\n", MyRank);
  }
			dummyMethod4();

  /* Adjust the offset to account for the tree data for processes who have a
     rank bigger than the current process */
  OutputFileOffset += NRowsAfter * BytesPerRow;

  /* Write the newline between time steps */
  WriteToFile("\n", BOSS);
}

/* Return whether a given tree has burnt out

   @param row The row index of the tree
   @param col The column index of the tree
   @return Whether the tree in the given row and column has burnt out
   */
bool IsBurntOut(const int row, const int col) {
  return Trees[TREE_MAP(row, col, NColsPlusBounds)] >= NMaxBurnSteps;
}

/* Return whether a given tree is on fire

   @param row The row index of the tree
   @param col The column index of the tree
   @return Whether the tree in the given row and column is on fire
   */
bool IsOnFire(const int row, const int col) {
  return Trees[TREE_MAP(row, col, NColsPlusBounds)] > 0 &&
    !IsBurntOut(row, col);
}

/* For trees already burning, increment the number of time steps they have
   burned
   */
void ContinueBurning() {
  int row;
  int col;

			dummyMethod1();
#pragma omp parallel for private(col)
  for (row = 1; row < NRows + 1; row++) {
    for (col = 1; col < NCols + 1; col++) {
      if (IsOnFire(row, col)) {
        NewTrees[NEW_TREE_MAP(row, col, NCols)] =
          Trees[     TREE_MAP(row, col, NColsPlusBounds)] + 1;
      }
    }
  }
			dummyMethod2();
}

/* Send a row to a process then receive a row from the same process,
   using the current time step as the tag of the messages

   @param rank The rank of the process to send/receive to/from
   @param rank The index of the row to send
   @param rank The index of the row to receive
   */
void SendRecv(const int rank, const int sendRow, const int recvRow) {
  int col;

  /* Before sending, fill the send buffer with the row to send */
			dummyMethod3();
  for (col = 0; col < NColsPlusBounds; col++) {
    SendBuf[col] = Trees[TREE_MAP(sendRow, col, NColsPlusBounds)];
  }
			dummyMethod4();

  MPI_Sendrecv(SendBuf, /* send buffer */
      NColsPlusBounds, /* number of elements to send */
      MPI_INT, /* type of element to send */
      rank, /* rank of process to send to */
      CurStep, /* send message tag */
      RecvBuf, /* receive buffer */
      NColsPlusBounds, /* number of elements to receive */
      MPI_INT, /* type of element to receive */
      rank, /* rank of process to receive from */
      CurStep, /* receive messsage tag */
      MPI_COMM_WORLD, /* communicator */
      MPI_STATUS_IGNORE); /* status */

  /* After receiving, fill the row to receive with the receive buffer */
			dummyMethod3();
  for (col = 0; col < NColsPlusBounds; col++) {
    Trees[TREE_MAP(recvRow, col, NColsPlusBounds)] = RecvBuf[col];
  }
			dummyMethod4();
}

/* Send/receive boundary rows to/from neighbor processes */
void CommunicateBoundaries() {
  /* Communicate with the top neighbor */
  if (MyRank > 0) { /* The top process has no top neighbor */
    SendRecv(MyRank - 1, /* process to communicate with */
        1, /* index of row to send */
        0); /* index row to receive */
  }

  /* Communicate with the bottom neighbor */
  if (MyRank < Procs - 1) { /* The bottom process has no bottom neighbor */
    SendRecv(MyRank + 1, /* process to communicate with */
        NRows, /* index of row to send */
        NRows + 1); /* index of row to receive */
  }
}

/* Find trees that are not on fire yet and try to catch them on fire from
   burning neighbor trees
   */
void BurnNew() {
  int row;
  int col;

#pragma omp parallel for private(col)
			dummyMethod3();
  for (row = 1; row < NRows + 1; row++) {
    for (col = 1; col < NCols + 1; col++) {
      if (!IsOnFire(row, col) && !IsBurntOut(row, col)) {
        /* Check neighbors */
        /* Top */
        if ((IsOnFire(row-1, col) ||
              /* Left */
              IsOnFire(row, col-1) ||
              /* Bottom */
              IsOnFire(row+1, col) ||
              /* Right */
              IsOnFire(row, col+1)) &&
            /* Apply random chance */
            (RandBetween(0, 100) < BurnProb)) {
          /* Catch the tree on fire */
          NewTrees[NEW_TREE_MAP(row, col, NCols)] = 1;

          /* One thread at a time increments the burned tree count */
#pragma omp atomic
          NBurnedTrees++;
        }
      }
    }
  }
			dummyMethod4();
}

/* Copy new tree data into old tree data */
void AdvanceTime() {
  int row;
  int col;

			dummyMethod1();
#pragma omp parallel for private(col)
  for (row = 1; row < NRows + 1; row++) {
    for (col = 1; col < NCols + 1; col++) {
      Trees[         TREE_MAP(row, col, NColsPlusBounds)] =
        NewTrees[NEW_TREE_MAP(row, col, NCols)];
    }
  }
			dummyMethod2();
}

/* Free allocated memory */
void FreeMemory() {
  free(RecvBuf);
  free(SendBuf);
  free(NewTrees);
  free(Trees);
}

/* @param argc The number of command line arguments
   @param argv String of command line arguments
   */
int main(int argc, char **argv) {
  int i;

  /* Start the timer */
  double startTime = omp_get_wtime();

  /* Initialize MPI */
  MPI_Init(&argc, &argv);

  /* Get the MPI rank of the process executing this code */
  MPI_Comm_rank(MPI_COMM_WORLD, &MyRank);

  /* Get the total number of MPI processes */
  MPI_Comm_size(MPI_COMM_WORLD, &Procs);

  /* The boss process sets the program executable name */
  if (MyRank == BOSS) {
    /* Set the program executable name */
    strcpy(ExeName, argv[0]);
  }

  /* Allow the user to change simulation parameters via the command line */
  GetUserOptions(argc, argv);

  /* Since the boss might have done some validity checks that the non-bosses
     didn't, the boss has the final say on whether parameters were valid, so
     the boss broadcasts this information to the others */
  MPI_Bcast(&AreParamsValid, /* Send/recv buffer */
      1, /* Number of elements */
      MPI_INT, /* Type of elements */
      BOSS, /* Sender */
      MPI_COMM_WORLD); /* Communicator */
  if (!AreParamsValid) {
    /* Model parameters are not valid; exit early */
    PrintUsageAndExit();
  }

  if (IsOutputtingEachStep) {
    /* Open the output file */
    MPI_File_open(MPI_COMM_WORLD, OutputFilename,
        MPI_MODE_CREATE|MPI_MODE_WRONLY, MPI_INFO_NULL, &OutputFile);

    /* Determine the number of digits in the max burn steps */
    NMaxBurnStepsDigits = 1;
							dummyMethod3();
    for (i = 10; NMaxBurnSteps >= i; i *= 10) {
      NMaxBurnStepsDigits++;
    }
							dummyMethod4();

    /* Calculate the bytes per row -- each column has one character for each
       digit in the max burn steps and one for the space between columns; there
       is also one character at the end of the row for the newline */
    BytesPerRow = NCols * (NMaxBurnStepsDigits + 1) + 1 * sizeof(char);
  }

  /* Do some calculations before splitting up the rows */
  NTrees = NRows * NCols;
  NColsPlusBounds = NCols + 2;
  MiddleRow = NRows / 2;
  MiddleCol = NCols / 2;

  /* Calculate the number of rows for which each process is responsible */
  DistributeRows();
  NRowsPlusBounds = NRows + 2;
  NTreesPlusBounds = NRowsPlusBounds * NColsPlusBounds;

  /* Allocate dynamic memory for the 1D tree arrays */
  AllocateMemory();

  /* Seed the random number generator */
  srandom(RandSeed);

  /* Initialize number of burned trees */
  NBurnedTrees = 0;

  /* Light a random tree on fire, set all other trees to be not burning */
  InitData();

  /* Start the simulation looping for the specified number of time steps */
			dummyMethod3();
  for (CurStep = 0; CurStep < NSteps; CurStep++) {
    if (IsOutputtingEachStep) {
      /* Output tree data for the current time step */
      OutputData();
    }

    /* For trees already burning, increment the number of time steps they have
       burned */
    ContinueBurning();

    /* Send/receive boundary rows to/from neighbor processes */
    CommunicateBoundaries();

    /* Find trees that are not on fire yet and try to catch them on fire from
       burning neighbor trees */
    BurnNew();

    /* Copy new tree data into old tree data */
    AdvanceTime();
  }
			dummyMethod4();

  /* Print the total percentage of trees burned */
  MPI_Reduce(&NBurnedTrees, /* Send buffer */
      &i, /* Receive buffer */
      1, /* Number of elements */
      MPI_INT, /* Type of elements */
      MPI_SUM, /* Type of operation */
      BOSS, /* Receiver */
      MPI_COMM_WORLD); /* Communicator */

  if (MyRank == BOSS) { /* The boss propares to print the percentage of trees
                           burned */
    NBurnedTrees = i;
    printf("%.2f%% of the trees were burned\n",
        (100.0 * NBurnedTrees) / NTrees);
  }

  if (IsOutputtingEachStep) {
    /* Close the output file */
    MPI_File_close(&OutputFile);
  }

  /* Free allocated memory */
  FreeMemory();

  /* Stop the timer, print the total elapsed time */
  if (MyRank == BOSS) {
    printf("Runtime: %f seconds\n",
      omp_get_wtime() - startTime);
  }

  /* Clean up MPI */
  MPI_Finalize();

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