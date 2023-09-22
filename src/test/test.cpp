#include "test.h"

void test_stack_normal() {
    log_printf(&log_file, "---Test stack (normal)---\n");

    Stack stk = {};
    STK_CTOR(&stk);

    stk_push(&stk, 123);

    STK_DUMP(&stk);

    for (int i = 0; i < 10; i++)
        stk_push(&stk, i);

    STK_DUMP(&stk);

    for (int i = 0; i < 20; i++) {
        stk_push(&stk, i);

        int p = 0;
        stk_pop(&stk, &p);
    }

    STK_DUMP(&stk);

    for (size_t i = 0; i < 5; i++) {
        int p = 0;
        stk_pop(&stk, &p);
    }

    STK_DUMP(&stk);

    for (size_t i = 0; i < 6; i++) {
        int p = 0;
        stk_pop(&stk, &p);
    }

    STK_DUMP(&stk);

    stk_dtor(&stk);

    STK_DUMP(&stk);
    log_printf(&log_file, "---Test stack (normal) end---\n");
}

void test_stack_error() {
    log_printf(&log_file, "---Test stack (error)---\n");

    Stack stk = {};
    STK_CTOR(&stk);

    stk_push(&stk, 123);

    STK_DUMP(&stk);

    for (int i = 0; i < 10; i++)
        stk_push(&stk, i);

    STK_DUMP(&stk);

    /// incorrect stk.data usage test
    stk.data[13] = 0;
    stk.data[5] = 234;


    stk_push(&stk, 1);

    STK_DUMP(&stk);

    stk_dtor(&stk); /// reset stack
    STK_CTOR(&stk);

    for (int i = 0; i < 10; i++)
        stk_push(&stk, i);

    /// empty stack pop test
    for (int i = 0; i < 11; i++) {
        int p = 0;
        stk_pop(&stk, &p);
    }

    STK_DUMP(&stk);

    stk_dtor(&stk);

    STK_DUMP(&stk);
    log_printf(&log_file, "---Test stack (error) end---\n");
}
