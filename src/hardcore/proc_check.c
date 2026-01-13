#include "hardcore.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/ptrace.h>
#include <errno.h>

int proc_debugger_check(void)
{
    FILE *f = fopen("/proc/self/status", "r");
    if (!f)
        return 0;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if (strncmp(line, "TracerPid:", 10) == 0) {
            int pid = atoi(line + 10);
            fclose(f);
            return pid != 0;
        }
    }

    fclose(f);
    return 0;
}

int ptrace_debugger_check(void)
{
    errno = 0;
    if (ptrace(PTRACE_TRACEME, 0, NULL, NULL) == -1) {
        if (errno == EPERM)
            return 1;
    }
    ptrace(PTRACE_DETACH, 0, NULL, NULL);
    return 0;
}
