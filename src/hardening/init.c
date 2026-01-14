#include "hardcore.h"
#include "hardening.h"
#include "protector_common.h"
#include "protector_state.h"
#include "protector_log.h"
#include <fcntl.h>
#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

// Обязательно изменить это значение перед использованием на любое случайное! Это тот самый KEY - первый аргумент для protector-hashgen
#define PROTECTOR_STATIC_KEY 3211889077


static uint32_t random_u32(void)
{
    uint32_t value;
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0) {
        return 0;
    }

    ssize_t n = read(fd, &value, sizeof(value));
    close(fd);

    if (n != sizeof(value)) {
        return 0;
    }

    return value;
}

PROTECTOR_EXPORT
void hardening_init(uint64_t secret)
{
    const uint32_t correct_hash = 1341160356;

    PROTECTOR_LOG("[hardening] starting integrity check");
    if (integrity_check(PROTECTOR_STATIC_KEY, correct_hash)) {
        hardening_poison = 1;
        PROTECTOR_LOG("[hardening] integrity check failed");
        return;
    }
    PROTECTOR_LOG("[hardening] starting memory check");

    if (memory_integrity_check()) {
        hardening_poison = 1;
        PROTECTOR_LOG("[hardening] memory integrity check failed");
        return;
    }
    PROTECTOR_LOG("[hardening] starting roundtrip check");
    
    uint32_t random = random_u32();
    if (random == 0) {
        hardening_poison = 1;
        PROTECTOR_LOG("[hardening] unable to get a random number for roundtrip verification");
        return;
    }

    uint64_t challenge = secret ^ random;
    PROTECTOR_LOG("[hardcore] Using challenge %lu for roundtrip validation", challenge);

    uint64_t result = hardcore_roundtrip(challenge);

    if (result != expected_roundtrip(challenge, secret)) {
        hardening_poison = 1;
        PROTECTOR_LOG("[hardening] roundtrip failed, got %lu", result);
        return;
    }
}
