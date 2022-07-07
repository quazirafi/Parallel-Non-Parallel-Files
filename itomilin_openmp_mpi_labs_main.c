#include <stdio.h>
#include <string.h>
int dummyMethod1();
int dummyMethod2();
int dummyMethod3();
int dummyMethod4();

#include "omp.h"

int main( int argc, char** argv )
{
    if ( omp_get_max_threads () < 4 )
        printf( "omp_get_max_threads < 4. Set maximum threads. \n" );
    else
        omp_set_num_threads( 4 );

    const char string_a[] = "te12st_Strzzstring";
    const char string_b[] = "test_Strzzcdfaq";

//    const char string_a[] = "test_Str";
//    const char string_b[] = "test_Str";

    int min_size = strlen( string_a ) < strlen( string_b ) ?
                strlen( string_a ) : strlen( string_b ) ;

    int mismatch = 0;
dummyMethod1();
#pragma omp parallel for
    for ( int i = 0; i < min_size; ++i )
    {
        if ( string_a[i] != string_b[i] )
            ++mismatch;
        printf( "%c : %c : thread = %i\n", string_a[i], string_b[i],
                omp_get_thread_num() );
    }
dummyMethod2();

    if ( mismatch != 0 )
        printf( "Strings are ne. Count of mismatch: %i\n", mismatch );
    else
        printf( "Strings are equal.\n" );

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