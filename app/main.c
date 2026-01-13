#include <stdio.h>
#include "protector_state.h"

int main(void)
{
    if (hardening_poison)
        printf("Running in degraded mode\n");
    else
        printf("Running normally\n");

    return 0;
}
