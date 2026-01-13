#include "hardcore.h"
#include <stdio.h>
#define _GNU_SOURCE
#include <dlfcn.h>
#include "protector_state.h"

__attribute__((constructor))
static void load_shared(void)
{
    printf("[DEBUG] load_shared() constructor running\n");

    void *h = dlopen("./libhardening.so", RTLD_NOW | RTLD_LOCAL);
    if (!h) {
        fprintf(stderr, "dlopen failed: %s\n", dlerror());
        hardening_poison = 1;
        return;
    }

    printf("[DEBUG] libhardening.so loaded\n");

    void (*init)(uint64_t) = dlsym(h, "hardening_init");
    if (!init) {
        fprintf(stderr, "dlsym failed: %s\n", dlerror());
        hardening_poison = 1;
        return;
    }

    init(hardcore_get_secret());
    printf("[DEBUG] shared library initialized\n");
}
