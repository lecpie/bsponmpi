#include <bsp.h>
#include "test.h"

TEST( get_offset_beyond_bounds_remote,
      abort("bsp_get: Reads 1 bytes beyond registered range [...,...+1) at process 0") )
{
    char dst;
    char src[2];

    bsp_begin(bsp_nprocs());

    if (bsp_pid() == 0)
    {
        bsp_push_reg(&src, 1);
    }
    else
    {
        bsp_push_reg(&src, 2);
    }

    bsp_sync();

    if (bsp_pid() == 1)
    {
        bsp_get(0, &src, 0, &dst, 2);
    }

    bsp_end();
}
