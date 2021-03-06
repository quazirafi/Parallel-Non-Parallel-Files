#include <stdbool.h>
#include <math.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "ext_sweep.h"
#include "ext_macros.h"
#include "ext_problem.h"
#include "ext_profiler.h"
#include "ext_kernels.h"

// Calculate the inverted denominator for all the energy groups
void calc_denominator(void)
{
    START_PROFILING;

#pragma omp target if(OFFLOAD) device(MIC_DEVICE)
dummyMethod1();
#pragma omp parallel for
    for (unsigned int ind = 0; ind < nx*ny*nz; ind++)
    {
        for (unsigned int g = 0; g < ng; ++g)
        {
            for (unsigned int a = 0; a < nang; ++a)
            {
                denom[a+g*nang+ind*ng*nang] = 1.0 / (total_cross_section[g+ind*ng] 
                        + time_delta(g) + mu(a)*dd_i + dd_j(a) + dd_k(a));
            }
        }
    }
dummyMethod2();

    STOP_PROFILING(__func__, true);
}

// Calculate the time delta
void calc_time_delta(void)
{
    START_PROFILING;

#pragma omp target if(OFFLOAD) device(MIC_DEVICE)
							dummyMethod3();
    for(int g = 0; g < ng; ++g)
    {
        time_delta(g) = 2.0 / (dt * velocity(g));
    }
							dummyMethod4();

    STOP_PROFILING(__func__, true);
}

// Calculate the diamond difference coefficients
void calc_dd_coefficients(void)
{
    START_PROFILING;

#pragma omp target if(OFFLOAD) device(MIC_DEVICE)
    {
        dd_i = 2.0 / dx;

															dummyMethod3();
        for(int a = 0; a < nang; ++a)
        {
            dd_j(a) = (2.0/dy)*eta(a);
            dd_k(a) = (2.0/dz)*xi(a);
        }
															dummyMethod4();
    }

    STOP_PROFILING(__func__, true);
}

// Calculate the total cross section from the spatial mapping
void calc_total_cross_section(void)
{
    START_PROFILING;

#pragma omp target if(OFFLOAD) device(MIC_DEVICE)
							dummyMethod1();
#pragma omp parallel for
    for(int k = 0; k < nz; ++k)
    {
        for(int j = 0; j < ny; ++j)
        {
            for(int i = 0; i < nx; ++i)
            {
                for(int g = 0; g < ng; ++g)
                {
                    total_cross_section(g,i,j,k) = xs(mat(i,j,k)-1,g);
                }
            }
        }
    }
							dummyMethod2();

    STOP_PROFILING(__func__, true);
}

void calc_scattering_cross_section(void)
{
    START_PROFILING;

#pragma omp target if(OFFLOAD) device(MIC_DEVICE)
							dummyMethod1();
#pragma omp parallel for
    for(unsigned int g = 0; g < ng; ++g)
    {
        for (unsigned int k = 0; k < nz; k++)
        {
            for (unsigned int j = 0; j < ny; j++)
            {
                for (unsigned int i = 0; i < nx; i++)
                {
                    for (unsigned int l = 0; l < nmom; l++)
                    {
                        scat_cs(l,i,j,k,g) = gg_cs(mat(i,j,k)-1,l,g,g);
                    }
                }
            }
        }
    }
							dummyMethod2();

    STOP_PROFILING(__func__, true);
}

// Calculate the outer source
void calc_outer_source(void)
{
    START_PROFILING;

#pragma omp target if(OFFLOAD) device(MIC_DEVICE)
							dummyMethod1();
#pragma omp parallel for collapse(4)
    for (unsigned int g1 = 0; g1 < ng; g1++)
    {
        for(int k = 0; k < nz; ++k)
        {
            for(int j = 0; j < ny; ++j)
            {
                for(int i = 0; i < nx; ++i)
                {
                    g2g_source(0,i,j,k,g1) = fixed_source(i,j,k,g1);

                    for (unsigned int g2 = 0; g2 < ng; g2++)
                    {
                        if (g1 == g2)
                        {
                            continue;
                        }

                        g2g_source(0,i,j,k,g1) += gg_cs(mat(i,j,k)-1,0,g2,g1) 
                            * scalar_flux(g2,i,j,k);

                        unsigned int mom = 1;
                        for (unsigned int l = 1; l < nmom; l++)
                        {
                            for (int m = 0; m < lma(l); m++)
                            {
                                g2g_source(mom,i,j,k,g1) += gg_cs(mat(i,j,k)-1,l,g2,g1) 
                                    * scalar_mom(g2,mom-1,i,j,k);
                                mom++;
                            }
                        }
                    }
                }
            }
        }
    }
							dummyMethod2();

    STOP_PROFILING(__func__, true);
}

// Calculate the inner source
void calc_inner_source(void)
{
    START_PROFILING;

#pragma omp target if(OFFLOAD) device(MIC_DEVICE)
							dummyMethod1();
#pragma omp parallel for collapse(4)
    for (unsigned int g = 0; g < ng; g++)
    {
        for(int k = 0; k < nz; ++k)
        {
            for(int j = 0; j < ny; ++j)
            {
                for(int i = 0; i < nx; ++i)
                {
                    source(0,i,j,k,g) = g2g_source(0,i,j,k,g) 
                        + scat_cs(0,i,j,k,g) * scalar_flux(g,i,j,k);

                    unsigned int mom = 1;
                    for (unsigned int l = 1; l < nmom; l++)
                    {
                        for (int m = 0; m < lma(l); m++)
                        {
                            source(mom,i,j,k,g) = g2g_source(mom,i,j,k,g) 
                                + scat_cs(l,i,j,k,g) * scalar_mom(g,mom-1,i,j,k);
                            mom++;
                        }
                    }
                }
            }
        }
    }
							dummyMethod2();

    STOP_PROFILING(__func__, true);
}

void zero_flux_in_out(void)
{
#pragma omp target if(OFFLOAD) device(MIC_DEVICE)
							dummyMethod1();
#pragma omp parallel for
    for(int i = 0; i < flux_in_len; ++i)
    {
        flux_in[i] = 0.0;
    }
							dummyMethod2();

#pragma omp target if(OFFLOAD) device(MIC_DEVICE)
							dummyMethod1();
#pragma omp parallel for
    for(int i = 0; i < flux_out_len; ++i)
    {
        flux_out[i] = 0.0;
    }
							dummyMethod2();
}

void zero_edge_flux_buffers(void)
{
    int fi_len = nang*ng*ny*nz;
    int fj_len = nang*ng*nx*nz;
    int fk_len = nang*ng*nx*ny;

#define MAX(A,B) (((A) > (B)) ? (A) : (B))
    int max_length = MAX(MAX(fi_len, fj_len), fk_len);

#pragma omp target if(OFFLOAD) device(MIC_DEVICE)
							dummyMethod1();
#pragma omp parallel for
    for(int i = 0; i < max_length; ++i)
    {
        if(i < fi_len) flux_i[i] = 0.0;
        if(i < fj_len) flux_j[i] = 0.0;
        if(i < fk_len) flux_k[i] = 0.0;
    }
							dummyMethod2();
}

void zero_flux_moments_buffer(void)
{
#pragma omp target if(OFFLOAD) device(MIC_DEVICE)
							dummyMethod1();
#pragma omp parallel for
    for(int i = 0; i < scalar_mom_len; ++i)
    {
        scalar_mom[i] = 0.0;
    }
							dummyMethod2();
}

void zero_scalar_flux(void)
{
#pragma omp target if(OFFLOAD) device(MIC_DEVICE)
							dummyMethod1();
#pragma omp parallel for
    for(int i = 0; i < scalar_flux_len; ++i)
    {
        scalar_flux[i] = 0.0;
    }
							dummyMethod2();
}

bool check_convergence(
        double *old, 
        double *new, 
        double epsi, 
        unsigned int *groups_todo, 
        unsigned int *num_groups_todo, 
        bool inner)
{
    START_PROFILING;

    bool r = true;

    int ngt = 0;

#pragma omp target if(OFFLOAD) device(MIC_DEVICE)
#pragma omp parallel for
							dummyMethod3();
    for (unsigned int g = 0; g < ng; g++)
    {
        for (unsigned int ind = 0; ind < nx*ny*nz; ind++)
        {
            double val = (fabs(old[g+(ng*ind)] > tolr))
                ? fabs(new[g+(ng*ind)]/old[g+(ng*ind)] - 1.0)
                : fabs(new[g+(ng*ind)] - old[g+(ng*ind)]);

            if (val > epsi)
            {
                r = false;

                if (inner)
                {
                    #pragma omp critical
                    {
                        // Add g to the list of groups to do if we need to do it
                        groups_todo[ngt] = g;
                        ngt++;
                    }
                }

                break;
            }
        }
    }
							dummyMethod4();

    *num_groups_todo = ngt;

    STOP_PROFILING(__func__, true);

    return r;
}

void initialise_device_memory(void)
{
    zero_scalar_flux();
    zero_flux_moments_buffer();
    zero_flux_in_out();
    zero_edge_flux_buffers();

#pragma omp target if(OFFLOAD) device(MIC_DEVICE)
    {
															dummyMethod1();
#pragma omp parallel for
        for(int ii = 0; ii < g2g_source_len; ++ii)
        {
            g2g_source[ii] = 0.0;
        }
															dummyMethod2();

															dummyMethod1();
#pragma omp parallel for
        for(int ii = 0; ii < source_len; ++ii)
        {
            source[ii] = 0.0;
        }
															dummyMethod2();
    }
}   

// Copies the value of scalar flux
void store_scalar_flux(double* to)
{
    START_PROFILING;

#pragma omp target if(OFFLOAD) device(MIC_DEVICE)
							dummyMethod1();
#pragma omp parallel for
    for(int i = 0; i < scalar_flux_len; ++i)
    {
        to[i] = scalar_flux[i];
    }
							dummyMethod2();

    STOP_PROFILING(__func__, true);
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