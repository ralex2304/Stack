#include "test/test.h"
#include "log/log.h"

LogFileData log_file = {"log.html"};

int main() {
    stk_log_open_file(&log_file, "wb");

    test_stack_normal();

    test_stack_error();

    stk_log_close_file(&log_file);
}
