#include <stdio.h>
#include <string.h>

int memory_integrity_check(void)
{
    FILE *f = fopen("/proc/self/maps", "r");
    if (!f)
        return 0;

    char line[256];
    while (fgets(line, sizeof(line), f)) {
        if (strstr(line, "rwxp")) {
            fclose(f);
            return 1;
        }
    }

    fclose(f);
    return 0;
}
