#include "linux_mem.h"

bool is_ptr_valid(void* p, const char mode) {
    assert(mode == 'r' || mode == 'w');

    uintptr_t begin = 0;
    uintptr_t end = 0;

    char readable   = '\0';
    char writable   = '\0';
    char executable = '\0';
    char mapped     = '\0';

    FILE* file = fopen("/proc/self/maps", "r");

    if (!file)
        return false;

    while (fscanf(file, "%" SCNxPTR "-%" SCNxPTR " %c%c%c%c",
            &begin, &end, &readable, &writable, &executable, &mapped) == 6) {

        if (begin <= (uintptr_t)p && (uintptr_t)p < end) {
            fclose(file);

            switch (mode) {
                case 'r':
                    return readable == 'r';
                    break;
                case 'w':
                    return writable == 'w';
                    break;
                default:
                    assert(0 && "is_ptr_valid() wrong mode specified");
                    break;
            }
        }

        while (fgetc(file) != '\n') {}
    }

    fclose(file);

    return false;
}
