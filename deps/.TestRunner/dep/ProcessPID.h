#ifndef PROCESS_PID_H
#define PROCESS_PID_H

#include "stdbool.h"
#include "FileLookUp.h"

typedef struct ProcessResults{
    bool *res;
    size_t len;
} ProcessResults;


ProcessResults process_executable(TestFilesData *list_info);
void free_process_results(ProcessResults *res);


// --------------------------------------------------
//              IPC - Pipelining functions
// --------------------------------------------------
/**
 * Would have to create another tread to read 
 */


 




#endif