#include "test/test.h"
#include "log/log.h"

LogFileData log_file = {"log.txt"};

int main() {
    log_open_file(&log_file, "wb");

    test_stack_normal();

    test_stack_error();

}