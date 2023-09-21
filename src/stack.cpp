#include "stack.h"

extern LogFileData log_file;

int stk_ctor(Stack* stk, ssize_t init_capacity) {
    assert(stk);

    int res = stk->OK;

    stk->data = (Elem_t*)calloc(init_capacity, sizeof(Elem_t));

    if (!stk->data) {
        res |= stk->ALLOC_ERR;
        STK_OK(stk, res);
        return res;
    }

    for (ssize_t i = 0; i < init_capacity; i++)
        stk->data[i] = stk->POISON;

    stk->capacity = init_capacity;
    stk->size = 0;

    stk->checksum = hash_init(sizeof(Elem_t));

    res |= stk_verify(stk);
    STK_OK(stk, res);

    return res;
}

int stk_dtor(Stack* stk) {
    assert(stk);

    int res = stk_verify(stk);
    STK_OK(stk, res);

    FREE(stk->data);

    stk->capacity = stk->UNITIALISED_CAPACITY;
    stk->size     = stk->UNITIALISED_CAPACITY;
    stk->checksum = {};

    return res;
}

int stk_resize(Stack* stk, const ssize_t new_size) {
    assert(stk);

    int res = stk_verify(stk);
    STK_OK(stk, res);

    if (res != stk->OK)
        return res;

    Elem_t* tmp = stk->data;

    stk->data = (Elem_t*)recalloc((void*)stk->data, stk->capacity * sizeof(Elem_t),
                                                         new_size * sizeof(Elem_t));

    if (!stk->data) {
        stk->data = tmp;
        res |= stk->ALLOC_ERR;
        STK_OK(stk, res);
        return res;
    }

    for (ssize_t i = stk->capacity; i < new_size; i++)
        stk->data[i] = stk->POISON;

    stk->capacity = new_size;

    res |= stk_verify(stk);
    STK_OK(stk, res);

    return res;
}

int stk_push(Stack* stk, const Elem_t elem) {
    assert(stk);

    int res = stk_verify(stk);
    STK_OK(stk, res);

    if (res != stk->OK)
        return res;

    if (stk->size == stk->capacity)
        res |= stk_resize(stk, stk->capacity * 2);

    if (res != stk->OK)
        return res;

    stk->data[stk->size++] = elem;

    hash_push(&stk->checksum, &elem);

    res |= stk_verify(stk);
    STK_OK(stk, res);

    return res;
}

int stk_pop(Stack* stk, Elem_t *const elem) {
    assert(stk);

    int res = stk_verify(stk);
    STK_OK(stk, res);

    if (res != stk->OK)
        return res;

    if (stk->size <= 0) {
        res |= stk->NOTHING_TO_POP;
        STK_OK(stk, res);
        return res;
    }

    *elem = stk->data[--stk->size];

    hash_create(&stk->checksum, stk->data, stk->size);

    stk->data[stk->size] = stk->POISON;

    res |= stk_verify(stk);
    STK_OK(stk, res);

    return res;
}

int stk_verify(Stack* stk) {
    assert(stk);

    int res = stk->OK;

    if (stk->size == stk->INIT_CAPACITY &&
        stk->capacity == stk->INIT_CAPACITY &&
        stk->data == nullptr) {
            res |= stk->UNITIALISED;
            return res;
    }

    if (stk->data == nullptr)
        res |= stk->DATA_NULLPTR;

    for (ssize_t i = 0; i < stk->size; i++)
        if (stk->data[i] == stk->POISON) {
            res |= stk->POISON_VAL_FOUND;
            break;
        }

    for (ssize_t i = stk->size; i < stk->capacity; i++)
        if (stk->data[i] != stk->POISON) {
            res |= stk->NON_POISON_EMPTY;
            break;
        }

    Hash checksum = hash_init(sizeof(Elem_t));
    hash_create(&checksum, stk->data, stk->size);

    if (stk->checksum.hash != checksum.hash)
        res |= stk->CHECKSUM_ERR;

    if (stk->capacity < stk->size)
        res |= stk->LOW_CAPACITY;

    if (stk->capacity < 0)
        res |= stk->NEGATIVE_CAPACITY;

    if (stk->size < 0)
        res |= stk->NEGATIVE_SIZE;

    return res;
}

void stk_print_error(const int err_code) {
    if (err_code == Stack::OK)
        log_printf(&log_file, "No error\n");
    else {
        if (err_code & Stack::UNITIALISED)
            log_printf(&log_file, "!!! Stack is not initialised\n");

        if (err_code & Stack::DATA_NULLPTR)
            log_printf(&log_file, "!!! stk.data = nullptr\n");

        if (err_code & Stack::ALLOC_ERR)
            log_printf(&log_file, "!!! Can't allocate memory\n");

        if (err_code & Stack::NOTHING_TO_POP)
            log_printf(&log_file, "!!! Program is trying to pop empty stack\n");

        if (err_code & Stack::POISON_VAL_FOUND)
            log_printf(&log_file, "!!! There is poison value in stack\n");

        if (err_code & Stack::NON_POISON_EMPTY)
            log_printf(&log_file, "!!! Empty element value is not poison\n");

        if (err_code & Stack::CHECKSUM_ERR)
            log_printf(&log_file, "!!! Stack was modified (wrong checksum)\n");

        if (err_code & Stack::LOW_CAPACITY)
            log_printf(&log_file, "!!! stk.size > stk.capacity\n");

        if (err_code & Stack::NEGATIVE_CAPACITY)
            log_printf(&log_file, "!!! Negative stk.capacity\n");

        if (err_code & Stack::NEGATIVE_SIZE)
            log_printf(&log_file, "!!! Negative stk.size\n");
    }
}

void stk_dump(const Stack* stk, const char* file, const int line, const char* func) {
    assert(stk);

    log_printf(&log_file, "    stk_dump()\n"
                          "    stack[%p] called from %s:%d %s\n", stk, file, line, func);

    log_printf(&log_file, "    {\n"
                          "        size     = %zd\n"
                          "        capacity = %zd\n"
                          "        checksum = 0x%llx\n"
                          "        data[%p] {\n", stk->size, stk->capacity, stk->checksum.hash, stk->data);


    int index_len = 1;
    ssize_t index = MAX(stk->size, stk->capacity);
    while ((index /= 10) > 0)
        index_len++;

    for (ssize_t i = 0; i < stk->capacity; i++) {
        if (i < stk->size)
            log_printf(&log_file, "            *");
        else
            log_printf(&log_file, "             ");

        log_printf(&log_file, "[%*zu] ", index_len, i);
        if (stk->data[i] == stk->POISON)
            log_printf(&log_file, "(poison)\n");
        else
            log_printf(&log_file, ELEM_T_PRINTF "\n", stk->data[i]);
    }
    log_printf(&log_file, "        }\n"
                          "    }\n");
}
