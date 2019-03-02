#include <bsp.h>
#include "test.h"

TEST( get_pid_greater_nprocs, abort("bsp_get: The source process ID does not exist") )
{
    char src, dst;

    bsp_begin(bsp_nprocs());

    bsp_get(bsp_nprocs(), &src, 0, &dst, 1);

    bsp_end();
}
