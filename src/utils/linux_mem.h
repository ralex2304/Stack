#ifndef LINUX_MEM_H_
#define LINUX_MEM_H_

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <inttypes.h>
#include <assert.h>

/**
 * @brief Checks if pointer is valid for access in mode
 *
 * @param p pointer
 * @param mode 'w' or 'r'
 * @return true is valid
 * @return false is not valid
 */
bool is_ptr_valid(void* p, const char mode = 'w');

#endif /// #ifndef LINUX_MEM_H_
