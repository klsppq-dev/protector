#include "hardcore.h"
#define _GNU_SOURCE
#include <dlfcn.h>
#include "protector_log.h"

int load_hardening(void)
{
    PROTECTOR_LOG("[hardcore] load_shared() constructor running");

    void *h = dlopen("./libhardening.so", RTLD_NOW | RTLD_LOCAL);
    if (!h) {
        PROTECTOR_LOG("[hardcore] dlopen failed: %s", dlerror());
        return 1;
    }

    PROTECTOR_LOG("[hardcore] libhardening.so loaded");

    void (*init)(uint64_t) = dlsym(h, "hardening_init");
    if (!init) {
        PROTECTOR_LOG("[hardcore] dlsym failed: %s", dlerror());
        return 1;
    }

    init(hardcore_get_secret());
    PROTECTOR_LOG("[hardcore] shared library initialized");
    return 0;
}
