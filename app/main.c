#include <stdio.h>
#include "protector_state.h"

int main(void)
{
    if (hardening_poison)
        printf("Running in degraded mode\n"); // Обнаружена попытка дебага / взлома программы
    else
        printf("Running normally\n"); // Все ОК

    return 0;
}
