/***********************************************************
 *  Copyright Univ. of Texas M.D. Anderson Cancer Center
 *  1992.
 *
 *	main program for Monte Carlo simulation of photon
 *	distribution in multi-layered turbid media.
 *
 ****/

/****
 *	THINKCPROFILER is defined to generate profiler calls in
 *	Think C. If 1, remember to turn on "Generate profiler
 *	calls" in the options menu.
 ****/
#define THINKCPROFILER 0

/* GNU cc does not support difftime() and CLOCKS_PER_SEC.*/
#define GNUCC 0

/* the number of photons in a batch */
#define NUM_PHOTONS_PER_BATCH 102400

#if THINKCPROFILER
#include <profile.h>
#include <console.h>
#include "omp.h"
#include <limits.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#endif
#include <sys/time.h>
#include <time.h>
#include "mcml.h"

/*	Declare before they are used in main(). */
FILE *GetFile(char *);
short ReadNumRuns(FILE* );
void ReadParm(FILE* , InputStruct * );
void CheckParm(FILE* , InputStruct * );
void InitOutputData(InputStruct, OutStruct *);
void FreeData(InputStruct, OutStruct *);
double Rspecular(LayerStruct * );
void LaunchPhoton(double, LayerStruct *, PhotonStruct *);
void DoOneRun(short NumRuns, InputStruct *In_Ptr, int num_threads);
void SumScaleResult(InputStruct, OutStruct *);
void WriteResult(InputStruct, OutStruct, char *);
void collect(OutStruct *Out_Ptr, tmpOutStruct *cl_OUTstruct);

static double dtime()
{
    double tseconds = 0.0;
    struct timeval mytime;
    gettimeofday(&mytime,(struct timezone *) 0);
    tseconds = (double) (mytime.tv_sec + (double)mytime.tv_usec * 1.0e-6);
    return (tseconds) ;
}

// Collect Function
void collect(OutStruct *Out_Ptr, tmpOutStruct *cl_OUTstruct)
{
    int i;
    if (cl_OUTstruct->Rd_valid)
        Out_Ptr->Rd_ra[cl_OUTstruct->Rdra.x][cl_OUTstruct->Rdra.y]+=cl_OUTstruct->Rdra.w;
    if (cl_OUTstruct->Tt_valid)
        Out_Ptr->Tt_ra[cl_OUTstruct->Ttra.x][cl_OUTstruct->Ttra.y]+=cl_OUTstruct->Ttra.w;
							dummyMethod3();
    for (i=0; i<cl_OUTstruct->total_steps; i++) {
//        if (item == 43752 && (i == 702 || i == 703))
//            printf("i = %d, x = %d, y = %d, w = %E\n", i, cl_OUTstruct->data[i].x, cl_OUTstruct->data[i].y, cl_OUTstruct->data[i].w);
        Out_Ptr->A_rz[cl_OUTstruct->data[i].x][cl_OUTstruct->data[i].y]+=cl_OUTstruct->data[i].w;
    }
							dummyMethod4();
}

/***********************************************************
 *	If F = 0, reset the clock and return 0.
 *
 *	If F = 1, pass the user time to Msg and print Msg on
 *	screen, return the real time since F=0.
 *
 *	If F = 2, same as F=1 except no printing.
 *
 *	Note that clock() and time() return user time and real
 *	time respectively.
 *	User time is whatever the system allocates to the
 *	running of the program;
 *	real time is wall-clock time.  In a time-shared system,
 *	they need not be the same.
 *
 *	clock() only hold 16 bit integer, which is about 32768
 *	clock ticks.
 ****/
time_t PunchTime(char F, char *Msg)
{
#if GNUCC
    return(0);
#else
    static clock_t ut0;	/* user time reference. */
    static time_t  rt0;	/* real time reference. */
    double secs;
    char s[STRLEN];

    if(F==0) {
        ut0 = clock();
        rt0 = time(NULL);
        return(0);
    } else if(F==1)  {
        secs = (clock() - ut0)/(double)CLOCKS_PER_SEC;
        if (secs<0) secs=0;	/* clock() can overflow. */
        sprintf(s, "User time: %8.0lf sec = %8.2lf hr.  %s\n",
                secs, secs/3600.0, Msg);
        puts(s);
        strcpy(Msg, s);
        return(difftime(time(NULL), rt0));
    } else if(F==2) return(difftime(time(NULL), rt0));
    else return(0);
#endif
}

/***********************************************************
 *	Print the current time and the estimated finishing time.
 *
 *	P1 is the number of computed photon packets.
 *	Pt is the total number of photon packets.
 ****/
void PredictDoneTime(long P1, long Pt)
{
    time_t now, done_time;
    struct tm *date;
    char s[80];

    now = time(NULL);
    date = localtime(&now);
    strftime(s, 80, "%H:%M %x", date);
    printf("Now %s, ", s);

    done_time = now +
                (time_t) (PunchTime(2,"")/(double)P1*(Pt-P1));
    date = localtime(&done_time);
    strftime(s, 80, "%H:%M %x", date);
    printf("End %s\n", s);
}

/***********************************************************
 *	Report time and write results.
 ****/
void ReportResult(InputStruct In_Parm, OutStruct Out_Parm)
{
    char time_report[STRLEN];

    strcpy(time_report, " Simulation time of this run.");
    PunchTime(1, time_report);

    SumScaleResult(In_Parm, &Out_Parm);
    WriteResult(In_Parm, Out_Parm, time_report);
}

/***********************************************************
 *	Get the file name of the input data file from the
 *	argument to the command line.
 ****/
void GetFnameFromArgv(int argc,
                      char * argv[],
                      char * input_filename)
{
    if(argc>=2) {			/* filename in command line */
        strcpy(input_filename, argv[1]);
    } else
        input_filename[0] = '\0';
}


/***********************************************************
 *	Execute Monte Carlo simulation for one independent run.
 ****/
void DoOneRun(short NumRuns, InputStruct *In_Ptr, int num_threads)
{
    int i, j;
    long i_photon;
    double t_0, t_1, t_2, t_3, t_4, t_5,  t_mem_set= 0.0, t_collect = 0.0, t_kernel = 0.0;

    // time 0
    t_0 = dtime();
    /* index to photon. register for speed.*/
    OutStruct out_parm;		/* distribution of photons.*/
    PhotonStruct photon;
    long num_photons = In_Ptr->num_photons, photon_rep=10;

    //Initial parallel version OutStruct
    tmpOutStruct* tmpOut_Ptr;
    tmpOut_Ptr = (tmpOutStruct *)malloc(sizeof(tmpOutStruct) * NUM_PHOTONS_PER_BATCH);

    //Initial random seed for rand_r()
    unsigned int *rand_seed;
    rand_seed = (unsigned int *)malloc(sizeof(unsigned int) * num_threads);
							dummyMethod3();
    for (i = 0 ; i < num_threads ; i++ ) {
        rand_seed[i] = (unsigned int) (time(NULL) ^ i);
    }
							dummyMethod4();
//    for (i = 0 ; i <num_threads; i++)
//        printf ("===========>%f", (double)rand_r(&rand_seed[i])/ RAND_MAX );

#if THINKCPROFILER
    InitProfile(200,200);
    cecho2file("prof.rpt",0, stdout);
#endif

    InitOutputData(*In_Ptr, &out_parm);
    //Rspecular only one time
    out_parm.Rsp = Rspecular(In_Ptr->layerspecs);
    i_photon = num_photons;
    PunchTime(0, "");
    // time 1
    t_1 = dtime();
    for( i=0 ; i<num_photons/NUM_PHOTONS_PER_BATCH ; i++) {
        // time 2
        t_2 = dtime();
        memset(tmpOut_Ptr, 0, sizeof(tmpOutStruct) * NUM_PHOTONS_PER_BATCH);
        // time 3
        t_3 = dtime();
        t_mem_set += t_3 - t_2;
															dummyMethod1();
        #pragma omp parallel for private(photon)
        for(j=0 ; j<NUM_PHOTONS_PER_BATCH; j++) {
            /*if(num_photons - i_photon == photon_rep) {
                printf("%ld photons & %hd runs left, ", i_photon, NumRuns);
                PredictDoneTime(num_photons - i_photon, num_photons);
                photon_rep *= 10;
            }*/
            LaunchPhoton(out_parm.Rsp, In_Ptr->layerspecs, &photon);
            do    HopDropSpin(In_Ptr, &photon, &tmpOut_Ptr[j], &rand_seed[omp_get_thread_num()]);
            while (!photon.dead);
        }
															dummyMethod2();
#if THINKCPROFILER
        exit(0);
#endif
        // time 4
        t_4 = dtime();
        t_kernel += t_4 - t_3;
        for (j=0; j<NUM_PHOTONS_PER_BATCH; j++)
            collect(&out_parm, &tmpOut_Ptr[j]);
        // time 5
        t_5 = dtime();
        t_collect += t_5 - t_4;
    }
    printf("Initial time    : %3.3f (s)\n", t_1 - t_0 );
    printf("Kernel  time    : %3.3f (s)\n", t_kernel );
    printf("Collection time : %3.3f (s)\n", t_collect );

    printf("Memset time     : %3.3f (s)\n", t_mem_set);

    ReportResult(*In_Ptr, out_parm);
    FreeData(*In_Ptr, &out_parm);
    free(tmpOut_Ptr);
}

/***********************************************************
 *	The argument to the command line is filename, if any.
 *	Macintosh does not support command line.
 ****/
char main(int argc, char *argv[])
{
    char input_filename[STRLEN];
    FILE *input_file_ptr;
    short num_runs;	/* number of independent runs. */
    InputStruct in_parm;
    int i, num_threads;

    ShowVersion("Version 1.2, 1993");
    GetFnameFromArgv(argc, argv, input_filename);
    input_file_ptr = GetFile(input_filename);
    CheckParm(input_file_ptr, &in_parm);

    //Set the number of threads
    num_runs = ReadNumRuns(input_file_ptr);
    printf("Input the number of threads : ");
    scanf("%d", &num_threads);
    omp_set_num_threads(num_threads);

    #pragma omp parallel
    #pragma omp master
    {
        printf("%d threads start... \n", omp_get_num_threads());
    }
//    while(num_runs--)  {
    for( i=0; i<num_runs--; i++) {
        ReadParm(input_file_ptr, &in_parm);
        DoOneRun(num_runs, &in_parm, num_threads);
    }

    fclose(input_file_ptr);
    return(0);
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