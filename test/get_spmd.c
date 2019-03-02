#include <bsp.h>
#include "test.h"

TEST( get_spmd, abort("bsp_get: can only be called within SPMD section") )
{
    char src, dst;
    bsp_get(0, &src, 0, &dst, 1);
}
