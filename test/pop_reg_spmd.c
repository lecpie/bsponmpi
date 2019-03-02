#include <bsp.h>
#include "test.h"

TEST( pop_reg_spmd, abort("bsp_pop_reg: can only be called within SPMD section") )
{
    bsp_pop_reg(NULL);
}
