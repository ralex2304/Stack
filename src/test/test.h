#ifndef TEST_H_
#define TEST_H_

#include "../stack.h"
#include "../log/log.h"
#include "../utils/html.h"

extern LogFileData log_file;

/**
 * @brief Tests stack without messing it up
 */
void test_stack_normal();

/**
 * @brief Tests stack by damaging it
 */
void test_stack_error();

#endif // #ifndef TEST_H_
