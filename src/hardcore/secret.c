#include "hardcore.h"
#include <unistd.h>
#include <time.h>

static uint64_t core_secret;

__attribute__((constructor))
static void secret_init(void)
{
    core_secret =
        ((uint64_t)getpid() << 32) ^
        (uint64_t)time(NULL) ^
        (uintptr_t)&core_secret;
}

uint64_t hardcore_get_secret(void)
{
    return core_secret;
}

uint64_t hardcore_roundtrip(uint64_t challenge)
{
    uint64_t x = challenge ^ core_secret;
    x = (x << 13) | (x >> (64 - 13));
    return x + core_secret;
}
