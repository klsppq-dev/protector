#include "hardcore.h"
#include <stdint.h>

volatile uint32_t hardening_poison = 0;

__attribute__((constructor))
static void hardcore_constructor(void)
{
    hardcore_init();
}

void hardcore_init(void)
{
    if (proc_debugger_check())
        hardening_poison = 1;

    if (ptrace_debugger_check())
        hardening_poison = 1;
}
