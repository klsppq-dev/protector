#ifndef PROTECTOR_LOG_H
#define PROTECTOR_LOG_H

#ifndef PROTECTOR_LOG_ENABLED
#define PROTECTOR_LOG_ENABLED 0
#endif

#if PROTECTOR_LOG_ENABLED
#include <stdio.h>

#define PROTECTOR_LOG(fmt, ...) \
    fprintf(stderr, "[protector debug] " fmt "\n", ##__VA_ARGS__)

#else

#define PROTECTOR_LOG(fmt, ...) ((void)0)

#endif

#endif
