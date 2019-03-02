#include <bsp.h>
#include "test.h"

TEST( push_reg_addr_null_size_zero, success() )
{
    bsp_begin(bsp_nprocs());

    bsp_push_reg(NULL, 0);

    bsp_end();
}
