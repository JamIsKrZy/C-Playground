#ifndef ESSENTIAL_TESTING_HEADER
#define ESSENTIAL_TESTING_HEADER

#include <pthread.h>
#include <stdlib.h>

#define MB_1 (1024 * 1024)
#define KB_1 (1024)
#define DEFAULT_SSIZE MB_1
#define RETURN_SUCCESS pthread_exit((void*)0)

#define assert(condition) do{\
    if(!(condition)){\
        char* fail_msg = malloc(128); \
        snprintf(fail_msg, 128, "Assertion failed at %s:%d", __FILE__, __LINE__); \
        pthread_exit((void*)fail_msg);\
    }\
} while (0)


#define TEST(title) void* title(void*)

#endif