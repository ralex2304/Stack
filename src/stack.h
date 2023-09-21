#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <math.h>

#include "utils/console.h"
#include "utils/macros.h"
#include "checksum/hash.h"
#include "log/log.h"

#define DEBUG

typedef int Elem_t;                                     //< stack elements type
static const Elem_t ELEM_T_POISON = __INT_MAX__ - 13;   //< poison value for stack
#define ELEM_T_PRINTF "%d"                              //< printf specificator

/**
 * @brief Stack data struct
 */
struct Stack {
    static const ssize_t INIT_CAPACITY = 2;
    static const Elem_t POISON = ELEM_T_POISON;
    static const ssize_t UNITIALISED_CAPACITY = -1;

    Elem_t* data = nullptr;
    ssize_t capacity = UNITIALISED_CAPACITY;
    ssize_t size = UNITIALISED_CAPACITY;

    Hash checksum = {};

    enum Results {
        OK                = 0x0000,
        UNITIALISED       = 0x0001,
        DATA_NULLPTR      = 0x0002,
        ALLOC_ERR         = 0x0004,
        NOTHING_TO_POP    = 0x0008,
        POISON_VAL_FOUND  = 0x0010,
        NON_POISON_EMPTY  = 0x0020,
        CHECKSUM_ERR      = 0x0040,
        LOW_CAPACITY      = 0x0080,
        NEGATIVE_CAPACITY = 0x0100,
        NEGATIVE_SIZE     = 0x0200,
    };
};

/**
 * @brief Stack constructor
 *
 * @param stk
 * @param init_capacity
 * @return int
 */
int stk_ctor(Stack* stk, const ssize_t init_capacity = Stack::INIT_CAPACITY);

/**
 * @brief Pushes elem to stack
 *
 * @param stk
 * @param elem
 * @return int
 */
int stk_push(Stack* stk, const Elem_t elem);

/**
 * @brief Pops elem from stack
 *
 * @param stk
 * @param res
 * @return int
 */
int stk_pop(Stack* stk, Elem_t *const res);

/**
 * @brief Resizes stack
 *
 * @param stk
 * @param new_size
 * @return int
 */
int stk_resize(Stack* stk, ssize_t new_size);

/**
 * @brief Verifies stack
 *
 * @param stk
 * @return int error code
 */
int stk_verify(Stack* stk);

/**
 * @brief Dumps all stack data to log
 *
 * @param stk
 * @param file __FILE__
 * @param line __LINE__
 * @param func __func__
 */
void stk_dump(const Stack* stk, const char* file, const int line, const char* func);

/**
 * @brief Prints errors to log file
 *
 * @param err_code
 */
void stk_print_error(const int err_code);

/**
 * @brief Stack destructor
 *
 * @param stk
 * @return int
 */
int stk_dtor(Stack* stk);


/**
 * @brief stk_dump macros
 *
 */
#define STK_DUMP(stk)   do {                                             \
                            stk_dump(stk, __FILE__, __LINE__, __func__); \
                        } while (0)

#ifdef DEBUG
/**
 * @brief calls stk_print_error() and STK_DUMP() if stack is not OK
 *
 */
#define STK_OK(stk, res)    do {                            \
                                if (res != stk->OK) {       \
                                    stk_print_error(res);   \
                                    STK_DUMP(stk);          \
                                }                           \
                            } while (0)
#else // #ifndef DEBUG
#define STK_OK(stk, res) void (0)
#endif // #ifdef DEBUG


#endif // #ifndef STACK_H_
