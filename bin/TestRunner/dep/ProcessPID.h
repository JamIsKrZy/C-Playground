#ifndef PROCESS_PID_H
#define PROCESS_PID_H

#include "FileLookUp.h"

typedef struct ProcessResult{
    Vector_string file_names;
    size_t len;
    bool *res;
} ProcessResult;

ProcessResult process_executable(Vector_fileinfo *list_info);


void free_process_results(ProcessResult*);


#endif