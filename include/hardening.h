#ifndef HARDENING_H
#define HARDENING_H

#include <stdint.h>
#include "protector_common.h"

PROTECTOR_EXPORT
void hardening_so_init(uint64_t secret);

int integrity_check(uint32_t correct_hash);
int memory_integrity_check();
static uint32_t crc32_table[256];
static uint64_t expected_roundtrip(uint64_t challenge, uint64_t secret);

#endif
