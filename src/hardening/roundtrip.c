#include <stdint.h>
#include "hardening.h"

static uint64_t expected_roundtrip(uint64_t challenge, uint64_t secret)
{
    uint64_t x = challenge ^ secret;
    x = (x << 13) | (x >> (64 - 13));
    return x + secret;
}
