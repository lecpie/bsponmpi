#include <bsp.h>
#include "test.h"

TEST( get_src_unregistered, abort("bsp_get: Remote address was not registered") )
{
    char src,dst;

    bsp_begin(bsp_nprocs());

    bsp_get(0, &src, 0, &dst, 1);

    bsp_end();
}
