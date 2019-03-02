#include <bsp.h>
#include "test.h"

TEST( get_src_null, abort("bsp_get: Source address cannot be identified by NULL") )
{
    char dst;

    bsp_begin(bsp_nprocs());

    bsp_get(0, NULL, 0, &dst, 1);

    bsp_end();
}
