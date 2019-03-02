#include <bsp.h>
#include "test.h"

TEST( get_src_registered_same_superstep,
      abort("bsp_get: Remote address was not registered") )
{
    char src,dst;

    bsp_begin(bsp_nprocs());

    bsp_push_reg(&src, 1);
    bsp_get(0, &src, 0, &dst, 1);

    bsp_end();
}
