#ifndef MACROS_H_
#define MACROS_H_

#include <stdlib.h>
#include <memory.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

#define FREE(ptr) do {                \
                      free(ptr);      \
                      ptr = nullptr;  \
                  } while (0)

inline void* recalloc(void* ptr, size_t old_size, size_t new_size) {
    ptr = realloc(ptr, new_size);

    if (!ptr)
        return ptr;

    if (new_size > old_size)
        memset((char*)ptr + old_size, 0, new_size - old_size);

    return ptr;
}

#endif // #ifndef MACROS_H_
