#include <bsp.h>
#include "test.h"

TEST( pop_addr_unregistered,
      abort("bsp_pop_reg: memory at address ... was not registered") )
{
    char c;

    bsp_begin(bsp_nprocs());

    bsp_pop_reg(&c);

    bsp_end();
}
