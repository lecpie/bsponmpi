#include <bsp.h>
#include "test.h"

TEST( get_offset_negative, abort("bsp_get: The offset was negative, which is illegal") )
{
    char src, dst;

    bsp_begin(bsp_nprocs());

    bsp_get(0, &src, -1, &dst, 1);

    bsp_end();
}
