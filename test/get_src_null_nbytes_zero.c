#include <bsp.h>
#include "test.h"

TEST( get_src_null_nbytes, success() )
{
    char dst;

    bsp_begin(bsp_nprocs());

    bsp_get(0, NULL, 0, &dst, 0);

    bsp_end();
}
