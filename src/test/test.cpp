#include "test.h"

void test_stack_normal() {
    log_printf(&log_file, HTML_H2("---Test stack (normal)---\n"));

    Stack stk = {};
    STK_CTOR_CAP(&stk, 3);

    stk_push(&stk, 123);

    STK_DUMP(&stk);

    for (Elem_t i = 0; i < 10; i++)
        stk_push(&stk, i);

    STK_DUMP(&stk);

    for (Elem_t i = 0; i < 20; i++) {
        stk_push(&stk, i);

        Elem_t p = 0;
        stk_pop(&stk, &p);
    }

    STK_DUMP(&stk);

    for (size_t i = 0; i < 5; i++) {
        Elem_t p = 0;
        stk_pop(&stk, &p);
    }

    STK_DUMP(&stk);

    for (size_t i = 0; i < 6; i++) {
        Elem_t p = 0;
        stk_pop(&stk, &p);
    }

    STK_DUMP(&stk);

    stk_dtor(&stk);

    STK_DUMP(&stk);
    log_printf(&log_file, HTML_H2("---Test stack (normal) end---\n"));
}

void test_stack_error() {
    log_printf(&log_file, HTML_H2("---Test stack (error)---\n"));

    Stack stk = {};
    STK_CTOR(&stk);

    stk_push(&stk, 123);

    STK_DUMP(&stk);

    for (Elem_t i = 0; i < 10; i++)
        stk_push(&stk, i);

    STK_DUMP(&stk);

    /// incorrect stk.data usage test
    stk.data[13] = 0;
    stk.data[5] = 111;


    stk_push(&stk, 1);

    STK_DUMP(&stk);

    stk_dtor(&stk); /// reset stack
    STK_CTOR(&stk);

    for (Elem_t i = 0; i < 10; i++)
        stk_push(&stk, i);

    /// empty stack pop test
    for (Elem_t i = 0; i < 11; i++) {
        Elem_t p = 0;
        stk_pop(&stk, &p);
    }

    STK_DUMP(&stk);

    stk_dtor(&stk);

    STK_DUMP(&stk);
    log_printf(&log_file, HTML_H2("---Test stack (error) end---\n"));
}
