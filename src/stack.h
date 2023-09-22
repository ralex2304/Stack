#ifndef STACK_H_
#define STACK_H_

#include <stdlib.h>
#include <assert.h>
#include <malloc.h>
#include <math.h>

#include "config.h"
#include "utils/console.h"
#include "utils/macros.h"
#include "checksum/hash.h"
#include "log/log.h"
#include "utils/linux_mem.h"

/**
 * @brief Stack data struct
 */
struct Stack {
    static const ssize_t INIT_CAPACITY = 2;
    static const Elem_t POISON = ELEM_T_POISON;
    static const ssize_t UNITIALISED_CAPACITY = -1;

#ifdef DEBUG
    unsigned long long canary_left = CANARY_VAL;
#endif

    Elem_t* data = nullptr;
    ssize_t capacity = UNITIALISED_CAPACITY;
    ssize_t size = UNITIALISED_CAPACITY;

    Hash checksum = {};

    enum Results {
        OK                  = 0x0000,
        NOTHING_TO_POP      = 0x0001,
        ALLOC_ERR           = 0x0002,

        UNITIALISED         = 0x0004,
        DATA_INVALID_PTR    = 0x0008,
        POISON_VAL_FOUND    = 0x0010,
        NON_POISON_EMPTY    = 0x0020,
        CHECKSUM_ERR        = 0x0040,
        LOW_CAPACITY        = 0x0080,
        NEGATIVE_CAPACITY   = 0x0100,
        NEGATIVE_SIZE       = 0x0200,
        STRUCT_L_CANARY_ERR = 0x0400,
        STRUCT_R_CANARY_ERR = 0x0800,
        DATA_L_CANARY_ERR   = 0x1000,
        DATA_R_CANARY_ERR   = 0x2000,
    };

#ifdef DEBUG
    const char* init_file = "";
          int   init_line = -1;
    const char* init_func = "";

    unsigned long long canary_right = CANARY_VAL;
#endif
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

#ifdef DEBUG

    /**
     * @brief Stack constructor in debug mode
     *
     * @param stk
     * @param file initialising place
     * @param line initialising place
     * @param func initialising place
     * @param init_capacity
     * @return int
     */
    int stk_ctor_debug(Stack* stk, const char* file, const int line, const char* func,
                    const ssize_t init_capacity = Stack::INIT_CAPACITY);

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
     * @brief Verifies stack
     *
     * @param stk
     * @return int error code
     */
    int stk_verify(Stack* stk);

    /**
     * @brief stk_ctor_debug macros
     */
    #define STK_CTOR(stk)   stk_ctor_debug(stk, __FILE__, __LINE__, __func__)

    /**
     * @brief stk_ctor_debug macros with capacity
     */
    #define STK_CTOR_CAP(stk, capacity)   stk_ctor_debug(stk, __FILE__, __LINE__, __func__, capacity)

    /**
     * @brief stk_verify() enables in DEBUG mode
     */
    #define STK_VERIFY(stk) stk_verify(stk)

    /**
     * @brief calls stk_print_error() and STK_DUMP() if stack is not OK
     */
    #define STK_OK(stk, res)    do {                            \
                                    if (res != stk->OK) {       \
                                        stk_print_error(res);   \
                                        STK_DUMP(stk);          \
                                    }                           \
                                } while (0)

    /**
     * @brief stk_dump macros
     */
    #define STK_DUMP(stk)   stk_dump(stk, __FILE__, __LINE__, __func__)
#else // #ifndef DEBUG
    /**
     * @brief stk_verify() returns OK in no DEBUG mode
     */
    #define STK_VERIFY(stk) Stack::OK;

    /**
     * @brief stk_ctor macros
     */
    #define STK_CTOR(stk)   stk_ctor(stk)

    /**
     * @brief stk_ctor macros with capacity
     */
    #define STK_CTOR_CAP(stk, capacity)   stk_ctor(stk, capacity)

    #define STK_OK(stk, res) void (0)

    #define STK_DUMP(stk) void (0)
#endif // #ifdef DEBUG

#endif // #ifndef STACK_H_
