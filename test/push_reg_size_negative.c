#include <bsp.h>
#include "test.h"

TEST( push_reg_size_negative,
      abort("bsp_push_reg: memory size must be positive") )
{
    char c;

    bsp_begin(bsp_nprocs());

    bsp_push_reg(&c, -1);

    bsp_end();
}
