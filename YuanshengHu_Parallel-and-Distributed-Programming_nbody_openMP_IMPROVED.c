// Compile with:
//     
//
// To specify the number of bodies in the world, the program optionally accepts
// an integer as its first command line argument.

#include <time.h>
#include <sys/times.h>
#include <math.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <X11/Xlib.h>
#include <unistd.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define WIDTH 1024
#define HEIGHT 768

// default number of bodies
#define DEF_NUM_BODIES 200
// gravitational constant
#define GRAV 10.0
// initial velocities are scaled by this value
#define V_SCALAR 20.0
// initial masses are scaled by this value
#define M_SCALAR 5.0
// radius scalar
#define R_SCALAR 3
// coefficient of restitution determines the elasticity of a collision: C_REST = [0,1]
//  if C_REST = 0 -> perfectly inelastic (particles stick together)
//  if C_REST = 1 -> perfectly elastic (no loss of speed)
#define C_REST 0.5
// set the iteration times
#define iteration_times 200
// Must set 0 if run on Pi
#define NOT_RUN_ON_PI 1

struct body {
    double x, y; // position
    double vx, vy; // velocity
    double m; // mass
    double r; // radius of the particle
};

struct world {
    struct body *bodies;
    int num_bodies;
};

clock_t total_time = 0;
//total_time.sec = 0;
//total_time.usec = 0;

int thread_count = 4;
/* This function initializes each particle's mass, velocity and position */
struct world* create_world(int num_bodies) {
    struct world *world = malloc(sizeof(struct world));

    world->num_bodies = num_bodies;
    world->bodies = malloc(sizeof(struct body)*num_bodies);

    int i = 0;
    double x;
    double y;
    double rc;

    int min_dim = (WIDTH < HEIGHT) ? WIDTH : HEIGHT;

    while (i<num_bodies) {
        x = drand48() * WIDTH;
        y = drand48() * HEIGHT;
        rc = sqrt((WIDTH/2-x)*(WIDTH/2-x) + (y-HEIGHT/2)*(y-HEIGHT/2));
        if (rc <= min_dim/2) {
            world->bodies[i].x = x;
            world->bodies[i].y = y;

            world->bodies[i].vx = V_SCALAR * (y-HEIGHT/2) / rc;
            world->bodies[i].vy = V_SCALAR * (WIDTH/2-x) / rc;

            world->bodies[i].m = (1 / (0.025 + drand48())) * M_SCALAR;
            world->bodies[i].r = sqrt(world->bodies[i].m / M_PI) * R_SCALAR;
            i++;
        }
    }
    return world;
}

// set the foreground color given RGB values between 0..255.
void set_color(Display *disp, GC gc, int r, int g, int b){
  unsigned long int p ;

  if (r < 0) r = 0; else if (r > 255) r = 255;
  if (g < 0) g = 0; else if (g > 255) g = 255;
  if (b < 0) b = 0; else if (b > 255) b = 255;

  p = (r << 16) | (g  << 8) | (b) ;

  XSetForeground(disp, gc, p) ;
}


/* This function updates the screen with the new positions of each particle */
void draw_world(Display *disp, Pixmap back_buf, GC gc, struct world *world) {
    int i;
    double x, y, r, r2;

    // we turn off aliasing for faster draws
    set_color(disp, gc, 255, 255, 255);
    XFillRectangle(disp, back_buf, gc, 0, 0, WIDTH, HEIGHT);

							dummyMethod3();
    for (i = 0; i < world->num_bodies; i++) {
        r = world->bodies[i].r;
        x = world->bodies[i].x - r;
        y = world->bodies[i].y - r;
        r2 = r + r;

        // draw body
        set_color(disp, gc, 255*7/10, 255*7/10, 255*7/10);
        XFillArc(disp, back_buf, gc, x, y, r2, r2, 0, 360*64); 
        set_color(disp, gc, 0, 0, 0);
        XDrawArc(disp, back_buf, gc, x, y, r2, r2, 0, 360*64); 
    }
							dummyMethod4();
}

void collision_step(struct world *world) {
    int a, b;
    double r, x, y, vx, vy;

    // Impose screen boundaries by reversing direction if body is off screen
							dummyMethod3();
    for (a = 0; a < world->num_bodies; a++) {
        r = world->bodies[a].r;
        x = world->bodies[a].x;
        y = world->bodies[a].y;
        vx = world->bodies[a].vx;
        vy = world->bodies[a].vy;

        if (x-r < 0) { // left edge
            if (vx < 0) { world->bodies[a].vx = -C_REST * vx; }
            world->bodies[a].x = r;
        } else if (x+r > WIDTH) { // right edge
            if (vx > 0) { world->bodies[a].vx = -C_REST * vx; }
            world->bodies[a].x = WIDTH - r;
        }

        if (y-r < 0) { // bottom edge
            if (vy < 0) { world->bodies[a].vy = -C_REST * vy; }
            world->bodies[a].y = r;
        } else if (y+r > HEIGHT) { // top edge
            if (vy > 0) { world->bodies[a].vy = -C_REST * vy; }
            world->bodies[a].y = HEIGHT - r;
        }
    }
							dummyMethod4();
}

void position_step(struct world *world, double time_res) {
    int i, j;
    double d, d_cubed, diff_x, diff_y;

    /* The forces array stores the x and y components of the total force acting
     * on each body. The forces are index like this:
     *     F on body i in the x dir = F_x[i]
     *     F on body i in the y dir = F_y[i] */
    double *force_x = (double*)malloc(sizeof(double) * world->num_bodies);
	double *force_y = (double*)malloc(sizeof(double) * world->num_bodies);
    // initialize all forces to zero
    force_x = memset(force_x, 0, sizeof(double) * world->num_bodies);
	force_y = memset(force_y, 0, sizeof(double) * world->num_bodies);

    /* Compute the net force on each body */
    double **loc_forces_x = (double**)malloc(sizeof(double*)*thread_count);
    double **loc_forces_y = (double**)malloc(sizeof(double*)*thread_count);
							dummyMethod1();
    #pragma omp parallel for num_threads(thread_count) \
           default(none) shared(thread_count,loc_forces_x,loc_forces_y,world) private(i)
    for (i = 0; i < thread_count; i++) {
       loc_forces_x[omp_get_thread_num()] = (double*)malloc(sizeof(double)*world->num_bodies);
       loc_forces_y[omp_get_thread_num()] = (double*)malloc(sizeof(double)*world->num_bodies);
    }
							dummyMethod2();
							dummyMethod1();
    #pragma omp parallel for num_threads(thread_count) \
           default(none) shared(world,thread_count,loc_forces_x,loc_forces_y) private(diff_x,diff_y,d,d_cubed,i,j) schedule(static,1)
    for (i = 0; i < world->num_bodies; i++) {
        int my_rank = omp_get_thread_num();
        for (j = i+1; j < world->num_bodies; j++) {
            diff_x = world->bodies[j].x - world->bodies[i].x;
            diff_y = world->bodies[j].y - world->bodies[i].y;
            d = sqrt((diff_x * diff_x) + (diff_y * diff_y));

			if (d < 25) {
                d = 25;
            }
            d_cubed = d * d * d;
            // Add force due to j to total force on i
            loc_forces_x[my_rank][i] += GRAV * (world->bodies[i].m * world->bodies[j].m/ d_cubed) * diff_x;
            loc_forces_y[my_rank][i] += GRAV * (world->bodies[i].m * world->bodies[j].m/ d_cubed) * diff_y;
            loc_forces_x[my_rank][j] -= GRAV * (world->bodies[i].m * world->bodies[j].m/ d_cubed) * diff_x;
            loc_forces_y[my_rank][j] -= GRAV * (world->bodies[i].m * world->bodies[j].m/ d_cubed) * diff_y;
        }
    }
							dummyMethod2();
    int thread;
							dummyMethod1();
    #pragma omp parallel for num_threads(thread_count) \
              default(none) shared(force_x,force_y,thread_count,world,loc_forces_x,loc_forces_y) private(i,thread) schedule(static,world->num_bodies/thread_count)
    for (i = 0; i < world->num_bodies; i++) {
        for(thread = 0 ; thread < thread_count; thread++){
            force_x[i] += loc_forces_x[thread][i];
            force_y[i] += loc_forces_y[thread][i];
        }             
    }
							dummyMethod2();
    // Update the velocity and position of each body
							dummyMethod1();
    #pragma omp parallel for num_threads(thread_count) \
           default(none) shared(world,force_x,force_y,time_res,thread_count) private(i) schedule(static,world->num_bodies/thread_count)
    for (i = 0; i < world->num_bodies; i++) {
        // Update velocities
        world->bodies[i].vx += force_x[i] * time_res / world->bodies[i].m;
        world->bodies[i].vy += force_y[i] * time_res / world->bodies[i].m;		
		
        // Update positions
        world->bodies[i].x += world->bodies[i].vx * time_res;
        world->bodies[i].y += world->bodies[i].vy * time_res;
    }	
							dummyMethod2();
}

void step_world(struct world *world, double time_res) {
	
	struct tms ttt;
	clock_t start, end;
	start = times(&ttt);
    position_step(world, time_res);
	end = times(&ttt);
	total_time += end - start;

    collision_step(world);
}


/* Main method runs initialize() and update() */
int main(int argc, char **argv) {
	//total_time.tv_sec = 0;
	//total_time.tv_usec = 0;
    /* get num bodies from the command line */
    int num_bodies;
    num_bodies = (argc == 2) ? atoi(argv[1]) : DEF_NUM_BODIES;
    thread_count = (argc == 3) ? atoi(argv[2]) : 4;
    printf("Universe has %d bodies.\n", num_bodies);

    /* set up the universe */
    time_t cur_time;
    time(&cur_time);
    srand48((long)cur_time); // seed the RNG used in create_world
    struct world *world = create_world(num_bodies);

    /* set up graphics using Xlib */
#if NOT_RUN_ON_PI
    Display *disp = XOpenDisplay(NULL);
    int scr = DefaultScreen(disp);
    Window win = XCreateSimpleWindow(
            disp,
            RootWindow(disp, scr),
            0, 0,
            WIDTH, HEIGHT,
            0,
            BlackPixel(disp, scr), WhitePixel(disp, scr));
    XStoreName(disp, win, "N-Body Simulator");

    Pixmap back_buf = XCreatePixmap(disp, RootWindow(disp, scr),
            WIDTH, HEIGHT, DefaultDepth(disp, scr));
    GC gc = XCreateGC(disp, back_buf, 0, 0);

    // Make sure we're only looking for messages about closing the window
    Atom del_window = XInternAtom(disp, "WM_DELETE_WINDOW", 0);
    XSetWMProtocols(disp, win, &del_window, 1);

    XSelectInput(disp, win, StructureNotifyMask);
    XMapWindow(disp, win);
    XEvent event;
    // wait until window is mapped
    while (1) {
        XNextEvent(disp, &event);
        if (event.type == MapNotify) {
            break;
        }
    }
#endif

    struct timespec delay={0, 1000000000 / 60}; // for 60 FPS
    struct timespec remaining;
	double delta_t = 0.1;
	int ii;
	
							dummyMethod3();
    for(ii = 0; ii < iteration_times; ii++){
        // check if the window has been closed
#if NOT_RUN_ON_PI	
        if (XCheckTypedEvent(disp, ClientMessage, &event)) {
            break;
        }

        // we first draw to the back buffer then copy it to the front (`win`)
        draw_world(disp, back_buf, gc, world);
        XCopyArea(disp, back_buf, win, gc, 0, 0, WIDTH, HEIGHT, 0, 0);
#endif

        step_world(world, delta_t);

		//if you want to watch the process in 60 FPS
        //nanosleep(&delay, &remaining);
    }
							dummyMethod4();

//	printf("Total Time = %f\n", (double)total_time.tv_sec + (double)total_time.tv_usec/1000000);
	printf("Nbody Position Calculation Time = :%lf s\n",(double)total_time / (sysconf(_SC_CLK_TCK)));

#if NOT_RUN_ON_PI	
    XFreeGC(disp, gc);
    XFreePixmap(disp, back_buf);
    XDestroyWindow(disp, win);
    XCloseDisplay(disp);
#endif

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