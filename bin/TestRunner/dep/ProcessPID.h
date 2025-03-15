#ifndef PROCESS_PID_H
#define PROCESS_PID_H

#include "FileLookUp.h"

typedef struct ProcessResults{
    bool *res;
    size_t len;
} ProcessResults;


ProcessResults process_executable(TestFilesData *list_info);





#endif