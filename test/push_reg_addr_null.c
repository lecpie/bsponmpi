#include <bsp.h>
#include "test.h"

TEST( push_reg_addr_null,
      abort("bsp_push_reg: NULL can only be registered if size is zero") )
{
    bsp_begin(bsp_nprocs());

    bsp_push_reg(NULL, 1);

    bsp_end();
}
