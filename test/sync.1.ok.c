#include <bsp.h>
#include <assert.h>

int main( int argc, char ** argv )
{
    (void) argc; (void) argv;
    bsp_begin( bsp_nprocs() );
    
    bsp_sync();

    bsp_end();
    return 0;
}
