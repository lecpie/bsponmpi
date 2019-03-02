#include <bsp.h>
#include "test.h"

TEST( get_offset_beyond_bounds_local,
      abort("bsp_get: Reads 1 bytes beyond registered range [...,...+1) at process 0") )
{
    char dst;
    char src;

    bsp_begin(bsp_nprocs());

    bsp_push_reg(&src,1);

    bsp_sync();

    if (bsp_pid() == 1)
    {
        bsp_get(0, &src, 0, &dst, 2);
    }

    bsp_end();
}
