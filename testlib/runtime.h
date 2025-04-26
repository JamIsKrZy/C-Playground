


#ifdef TEST_CASES

#ifndef INCLUDES_FOR_TEST_RUNTIME
#define INCLUDES_FOR_TEST_RUNTIME
#include <stdio.h>
#include <unistd.h>
#include "../testlib/essential.h"
#include <pthread.h>
#include <errno.h>
#endif



#define TEST(func, _ssize) void* func(void*);
TEST_CASES
#undef TEST

struct test_case{
    pthread_t tr;
    size_t ssize;
    char *thread_name;
    void* (*func_ptr)(void*);
};

struct contents {
    struct test_case *c;
    size_t len;
};

struct contents init_thread_content(){
    void* (*func_ptrs[])(void*) = {
        #define TEST(func, ssize) func, 
        TEST_CASES
        #undef TEST
    };

    // store all function namee as arr of strings
    char *function_names[] = {
        #define TEST(func, _ssize) #func ,
        TEST_CASES
        #undef TEST
    };
    size_t len = sizeof(function_names)/sizeof(function_names[0]);

    // store in arr all stack size
    size_t ssizes[] = {
        #define TEST(_func, ssize) ssize ,
        TEST_CASES
        #undef TEST
    };

    struct test_case *test_list = malloc(sizeof(struct test_case) * len);
    for (size_t i = 0; i < len; i++){
        test_list[i].func_ptr = func_ptrs[i];
        test_list[i].thread_name = function_names[i];
        test_list[i].ssize = ssizes[i]; 
    }
    
    return (struct contents){
        .len = len, .c = test_list
    };
}   

int main(){
    size_t len; 
    struct test_case *thread_list;
    char **results = calloc(len, sizeof(char*));
    if(!results){
        perror("Fail to setup data!");
        exit(EXIT_FAILURE);
    }



    {
        struct contents c = init_thread_content();
        len = c.len;
        thread_list = c.c;
    }



    // init threads
    {
        pthread_attr_t attr;
        pthread_attr_init(&attr);char **results = calloc(len, sizeof(char*));
        for (size_t i = 0; i < len; i++){
            pthread_attr_setstacksize(&attr, thread_list[i].ssize);
            
            pthread_create(
                &thread_list[i].tr,
                &attr,
                thread_list[i].func_ptr,
                NULL
            );
        }
        pthread_attr_destroy(&attr);
    }
    
    // wait for results
    size_t waiting = len;
    char *catch;
    while (waiting){
        // puts("Waiting for test case...");
        usleep(2 * 10000);
        for (size_t i = 0; i < len; i++){
            int res = pthread_tryjoin_np(
                thread_list[i].tr,
                (void**)&catch
            );

            if (res == 0) {

                if(catch){
                    printf("⁉️  Thread Failed - %s: %s\n", 
                        thread_list[i].thread_name,
                        catch
                    );

                    free(catch);
                } else {
                    printf("✅ Thread Success - %s\n",
                        thread_list[i].thread_name
                    );
                }


                waiting--;
                break;
            } else if (res == EBUSY) {
                // printf("Thread still working...\n");
                sleep(1); // check again after some time
            } else {
                perror("pthread_tryjoin_np error");
                break;
            }
            
        }
        
    }
    
    
    


    


    return 0;
}



#undef TEST_CASES


// #error "Undefined Test cases"

#endif

