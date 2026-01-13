#include "hardcore.h"
#include "hardening.h"
#include "protector_state.h"
#include <stdint.h>
#include <stdio.h>

void hardening_init(uint64_t secret)
{
    printf("[SHARED] starting integrity check\n");
    if (integrity_check(-1839978380)) {
        hardening_poison = 1;
        printf("[SHARED] integrity check failed\n");
        return;
    }
    printf("[SHARED] starting memory check\n");

    if (memory_integrity_check()) {
        hardening_poison = 1;
        printf("[SHARED] memory integrity check failed\n");
        return;
    }
    printf("[SHARED] starting roundtrip check\n");
    
    uint64_t challenge = secret ^ 0xA5A5A5A5A5A5A5A5ULL;
    uint64_t result = hardcore_roundtrip(challenge);

    if (result != expected_roundtrip(challenge, secret)) {
        printf("[SHARED] roundtrip failed\n");
        hardening_poison = 1;
        return;
    }
}
