// #include "Vector/vector.h"
#include <pthread.h>
#include <stdio.h>


#define MB_1 (1024 * 1024)
#define DEFAULT_SSIZE MB_1

#define TEST_CASES\
    X(function_name, DEFAULT_SSIZE)\
    X(func_1, DEFAULT_SSIZE)\
    X(funcy, DEFAULT_SSIZE)

#include "test_runtime.h"

#define TEST_CASES\
    X(function_name, DEFAULT_SSIZE)\
    X(func_1, DEFAULT_SSIZE)\
    X(funcy, DEFAULT_SSIZE)




// struct test_case{
//     void* (*func_ptr)(void*);
//     size_t stack_size;
// };


int main(int argc, char const *argv[])
{   
    // have an array of pointer_func 
    

    char *function_names[] = {
        #define X(func, _ssize) #func ,
        TEST_CASES
        #undef X
    };
    size_t len = sizeof(function_names)/sizeof(function_names[0]);


    for (size_t i = 0; i < len; i++)
    {
        printf("func name[%lu]: %s\n", i+1, function_names[i]);
    }
    
    // pthread_t thread;
    // pthread_attr_t attr;

    // pthread_create(&thread,  &attr, funcy, NULL);


    return 0;
}


void* funcy(void *){

}


void* function_name(void *){

}

void* func_1(void *){
    
}