#ifndef HARDCORE_H
#define HARDCORE_H

#include <stdint.h>

void hardcore_init(void);
int load_hardening(void);

uint64_t hardcore_get_secret(void);
uint64_t hardcore_roundtrip(uint64_t value);

int proc_debugger_check(void);
int ptrace_debugger_check(void);

#endif
