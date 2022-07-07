#include <stdio.h>
#include <stdlib.h>
#include "omp.h"
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#define COD_ERROR 2
#define ERROR(e) {printf("Errori: %s\n", nc_strerror(e)); exit(COD_ERROR);}
#define NX 21696
#define NY 21696
#define NKERNEL 3
#define ARCHIVO "/home/sampaxx/Escritorio/SistemasOperativosII/TP2/includes/OR_ABI-L2-CMIPF-M6C02_G16_s20191011800206_e20191011809514_c20191011809591.nc"
// //Escritorio/SistemasOperativosII/TP2/includes

#define FILE_OUT_TIMES "./tiempos_omp.txt"
#define FILE_OUT_BIN  "./imagen_filtrada.bin"
#define PATH_MAX 300

void convolucion(float *dato_entrada, float kernel[3][3], float *salida, int num_threads);

void write_to_bin(float *dato_entrada);

void write_to_nc();

void get_dir();

int main(int argc, char* argv[]) {

    /*
     * http://cortesfernando.blogspot.com/2011/10/malloc-vs-calloc.html
     */
    float *dato_salida=(float*)calloc((NX-NKERNEL+1) * (NY-NKERNEL+1), sizeof(float));
    float *dato_entrada= (float*)calloc(NX*NY, sizeof(float));
    float kernel [NKERNEL][NKERNEL]={{-1. -1, -1},
                                     {-1,  8, -1},
                                     {-1. -1, -1}};
    int nc_id, var_id, ret_value;
    size_t inicio[2]={0};
    size_t cuenta[2]={0};
    int nth;

    cuenta[0]=NX;
    cuenta[1]=NY;

    inicio[0]=0;
    inicio[1]=0;

    
    printf("leyendo archivo NC a memoria\n");
    /*
    https://www.unidata.ucar.edu/software/netcdf/docs/group__datasets.html#gaccbdb128a1640e204831256dbbc24d3e

    int nc_open 	(const char *path, int omode, int *ncidp)
    Open an existing netCDF file.
            This function opens an existing netCDF dataset for access. It determines the underlying file format automatically. Use the same call to open a netCDF classic or netCDF-4 file.
            Parameters
    path	File name for netCDF dataset to be opened. When the dataset is located on some remote server, then the path may be an OPeNDAP URL rather than a file path.
            omode	The open mode flag may include NC_WRITE (for read/write access) and NC_SHARE (see below) and NC_DISKLESS (see below).
    ncidp	Pointer to location where returned netCDF ID is to be stored.

            Open Mode
    A zero value (or NC_NOWRITE) specifies the default behavior: open the dataset with read-only access, buffering and caching accesses for efficiency.
    Here is an example using nc_open()to open an existing netCDF dataset named foo.nc for read-only, non-shared access:

     #include <netcdf.h>
    ...
    int status = NC_NOERR;
    int ncid;
    ...
    status = nc_open("foo.nc", 0, &ncid);
    if (status != NC_NOERR) handle_error(status);

    Author
    Glenn Davis, Ed Hartnett, Dennis Heimbigner
    Definition at line 635 of file dfile.c
    */


    double start_time_read= omp_get_wtime();
    ret_value= nc_open(ARCHIVO, 0, &nc_id );
    if(  ret_value != NC_NOERR){
        ERROR(ret_value);
    }
    double tiempo_de_carga= omp_get_wtime() - start_time_read;
    printf("Tiempo de carga: %f\n", tiempo_de_carga);

    //obtencion de elvarID de la variable CMI
    /*
    nc_inq_varid()
    int nc_inq_varid (int ncid, const char *name, int *varidp)
        Find the ID of a variable, from the name.
        The function nc_inq_varid returns the ID of a netCDF variable, given its name.

        Parameters
            ncid	NetCDF or group ID, from a previous call to nc_open(), nc_create(), nc_def_grp(), or associated inquiry functions such as nc_inq_ncid().
            name	Name of the variable.
            varidp	Pointer to location for returned variable ID. Ignored if NULL.

        Returns
            NC_NOERR No error.
            NC_EBADID Bad ncid.
            NC_ENOTVAR Invalid variable ID.

        Here is an example using nc_inq_varid to find out the ID of a variable named rh in an existing netCDF dataset named foo.nc:
        #include <netcdf.h>
           ...
        int  status, ncid, rh_id;
           ...
        status = nc_open("foo.nc", NC_NOWRITE, &ncid);
        if (status != NC_NOERR) handle_error(status);
           ...
        status = nc_inq_varid (ncid, "rh", &rh_id);
        if (status != NC_NOERR) handle_error(status);

        Definition at line 62 of file dvarinq.c.
    */
    if((ret_value= nc_inq_varid(nc_id, "CMI", &var_id)))
    ERROR(ret_value)

    //lectura de la matriz
    /*
             nc_get_vara_float()
             int nc_get_vara_float (int ncid, int varid, const size_t *startp, const size_t *countp, float *ip)
        Read an array of values from a variable.
        The array to be read is specified by giving a corner and a vector of edge lengths to Specify a Hyperslab.
        The data values are read into consecutive locations with the last dimension varying fastest. The netCDF dataset must be in data mode (for netCDF-4/HDF5 files, the switch to data mode will happen automatically, unless the classic model is used).
        The nc_get_vara() function will read a variable of any type, including user defined type. For this function, the type of the data in memory must match the type of the variable - no data conversion is done.
        Other nc_get_vara_ functions will convert data to the desired output type as needed.

        Parameters
            ncid	NetCDF or group ID, from a previous call to nc_open(), nc_create(), nc_def_grp(), or associated inquiry functions such as nc_inq_ncid().
            varid	Variable ID
            startp	Start vector with one element for each dimension to Specify a Hyperslab.
            countp	Count vector with one element for each dimension to Specify a Hyperslab.
            ip	Pointer where the data will be copied. Memory must be allocated by the user before this function is called.

        Returns
            NC_NOERR No error.
            NC_ENOTVAR Variable not found.
            NC_EINVALCOORDS Index exceeds dimension bound.
            NC_EEDGE Start+count exceeds dimension bound.
            NC_ERANGE One or more of the values are out of range.
            NC_EINDEFINE Operation not allowed in define mode.
            NC_EBADID Bad ncid.

        Example
        Here is an example using nc_get_vara_double() to read all the values of the variable named rh from an existing netCDF dataset named foo.nc. For simplicity in this example, we assume that we know that rh is dimensioned with time, lat, and lon, and that there are three time values, five lat values, and ten lon values.
        #include <netcdf.h>
           ...
        #define TIMES 3
        #define LATS 5
        #define LONS 10
        int  status;
        int ncid;
        int rh_id;
        static size_t start[] = {0, 0, 0};
        static size_t count[] = {TIMES, LATS, LONS};
        double rh_vals[TIMES*LATS*LONS];
           ...
        status = nc_open("foo.nc", NC_NOWRITE, &ncid);
        if (status != NC_NOERR) handle_error(status);
           ...
        status = nc_inq_varid (ncid, "rh", &rh_id);
        if (status != NC_NOERR) handle_error(status);
           ...
        status = nc_get_vara_double(ncid, rh_id, start, count, rh_vals);
        if (status != NC_NOERR) handle_error(status);

        Author
            Glenn Davis, Russ Rew, Ed Hartnett, Dennis Heimbigner, Ward Fisher
        Examples:
            pres_temp_4D_rd.c.
        Definition at line 805 of file dvarget.c.
     */
    if( (ret_value=nc_get_vara_float(nc_id, var_id, inicio, cuenta, dato_entrada)) )
    ERROR(ret_value)

    // se cierra el archivo nc y se liberan los recursos
    /*
        nc_close()
            int nc_close(int ncid)
        Close an open netCDF dataset.
        If the dataset in define mode, nc_enddef() will be called before closing. (In this case, if nc_enddef() returns an error, nc_abort() will automatically be called to restore the dataset to the consistent state before define mode was last entered.) After an open netCDF dataset is closed, its netCDF ID may be reassigned to the next netCDF dataset that is opened or created.
        Parameters
            ncid	NetCDF ID, from a previous call to nc_open() or nc_create().
        Returns
            NC_NOERR No error.
            NC_EBADID Invalid id passed.
            NC_EBADGRPID ncid did not contain the root group id of this file. (NetCDF-4 only).

        Example
        Here is an example using nc_close to finish the definitions of a new netCDF dataset named foo.nc and release its netCDF ID:
        #include <netcdf.h>
           ...
        int status = NC_NOERR;
        int ncid;
           ...
        status = nc_create("foo.nc", NC_NOCLOBBER, &ncid);
        if (status != NC_NOERR) handle_error(status);
           ...   create dimensions, variables, attributes
        status = nc_close(ncid);
        if (status != NC_NOERR) handle_error(status);

        Definition at line 1271 of file dfile.c.
    */
    if( ( ret_value=nc_close(nc_id)  )  )
    ERROR(ret_value)

    //aca se procesan los datos: se hace la convolucion
    printf("procesando...\n");
    
    double start_time= omp_get_wtime(); //https://www.openmp.org/spec-html/5.0/openmpsu160.html

    if (argv[1]!=NULL){
        nth=atoi(argv[1]);
    } else{
        nth=1;
    }
    convolucion(dato_entrada, kernel, dato_salida, nth);
    
    double tiempo= omp_get_wtime()- start_time;
    
    printf("Procesamiento terminado. Tiempo empleado: %f\n", tiempo);
    free(dato_entrada); //de que libreria es esta funcion?

    //escribir los resultados en el nc (dato_salida)
    printf("Escribiendo la salida en binario\n");
    get_dir();
    write_to_bin(dato_salida);
    free(dato_salida); //otra vez esta funcion. De que libreria es?

    //Registracion  del tiempo de ejecucion en un archivo txt
    printf("Registrando tiempo de ejecucion en archivo\n");
    FILE *tiempos_file;
    tiempos_file= fopen(FILE_OUT_TIMES, "a");
    fprintf(tiempos_file, "%f\n", tiempo); //int fprintf(FILE *stream, const char *format, ...)
    fclose(tiempos_file);

    printf("Todo listo. Saliendo\n");

    return 0;
}

/**
 * @brief Guarda el archivo de imagen pasado como parametro como un archivo binario de floats
 * @param dato_entrada Es un puntero float que sera guardado como binario
 */
void write_to_bin(float *dato_entrada) {
    int fd; //&lt;
    fd = open(FILE_OUT_BIN, O_WRONLY|O_CREAT|O_TRUNC, 0666);
    if(fd < 0){
        perror("error al crear el archivo de salida\n");
        return;
    }

    if ( ( write(fd, dato_entrada, sizeof(float)*(NX-NKERNEL+1)*(NY-NKERNEL+1))) < 0 ){
        perror("error al escribir el archivo\n");
        exit(EXIT_FAILURE);
    }

    close(fd);

}

/**
 * @brief Esta funcion hace la convolucion entre el 'kernel' y el dato_entrada
 * @param dato_entrada
 * @param kernel
 * @param salida
 * @param num_threads la cantidad de hilos a emplear en la operacion de convolucion
 */
void convolucion(float *dato_entrada, float kernel[3][3], float *salida, int num_threads) {

omp_set_num_threads(num_threads);
							dummyMethod1();
#pragma omp parallel for collapse (2) //estudiar
    for (int fil_img = 0; fil_img < (NX-NKERNEL+1); fil_img++){ //recorro las filas de la imagen
        for (int col_img=0; col_img < (NY-NKERNEL+1); col_img++){ //recorro las columnas de la imagen
            for( int fil_kernel = 0; fil_kernel < NKERNEL; fil_kernel++){ //recorro las filas del kernel
                for( int col_kernel = 0; col_kernel < NKERNEL; col_kernel++){ //recorro las columnas del kernel

                    salida[fil_img * (NX-NKERNEL+1)+col_img]+= dato_entrada[(fil_img+fil_kernel) * NX + (col_img + col_kernel)]*kernel[fil_kernel][col_kernel];
                }//columna ker
            }// fila ker
        } //columna img
    } // fila img
							dummyMethod2();

}

/**
 * @brief la funcion no devuelve dato (void) pero imprime por consola el current working directory desde donde el programa esta corriendo
 * @param sin parametros
 */
void get_dir() {
    char cwd[PATH_MAX];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Current working dir: %s\n", cwd);
    } else {
        perror("getcwd() error");
    }
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