#include <bsp.h>
#include "test.h"

TEST( push_reg_spmd, abort("bsp_push_reg: can only be called within SPMD section") )
{
    bsp_push_reg(NULL, 0);
}
