#include "log.h"

int log_printf(LogFileData* log_file, const char* format, ...) {
    assert(log_file);
    assert(format);

    if (log_file->file == nullptr)
        if (!log_open_file(log_file))
            return -1;

    va_list argList;
    va_start(argList, format);
    return vfprintf(log_file->file, format, argList);
}

bool log_open_file(LogFileData* log_file, const char* mode) {
    assert(log_file);

    log_file->file = fopen(log_file->filename, mode);

    if (log_file->file == nullptr) {
        perror("Error opening log_file file");
        return false;
    }

    return true;
}

bool log_close_file(LogFileData* log_file) {
    if (fclose(log_file->file) != 0) {
        perror("Error closing log_file file");
        return false;
    }

    log_file->file = nullptr;
    return true;
}
