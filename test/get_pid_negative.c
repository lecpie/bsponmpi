#include <bsp.h>
#include "test.h"

TEST( get_pid_negative, abort("bsp_get: The source process ID does not exist") )
{
    char src, dst;

    bsp_begin(bsp_nprocs());

    bsp_get(-1, &src, 0, &dst, 1);

    bsp_end();
}
