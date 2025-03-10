#include <stdio.h>
#include <stdlib.h>
#include "ProcessPID.h"




static ProcessResult process_result_new(size_t capacity){
    ProcessResult res;
    res.file_names = vector_string_with_capacity(capacity);
    res.res = calloc(capacity, sizeof(bool));
    res.len = 0;
    return res;
}

void set_process_contents(Vector_fileinfo *vec, ProcessResult *res,size_t size){
    size_t count = 0;
    char *file_name;
    
    for (size_t i = 0; i < size; i++)
    {   
        file_name = vector_fileinfo_get(vec, i).file_name;
        vector_string_push(&res->file_names, file_name);
        count++;
    }
    
    res->len = count;
}

void free_process_results(ProcessResult *res){
    vector_string_free_content(&res->file_names);
    free(res);
}











#ifdef __unix__

#include <spawn.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h> 

extern char **environ;


static pid_t* create_pids(size_t capacity){
    if(capacity == 0) return NULL;

    pid_t *pids = calloc(capacity, sizeof(pid_t));
    return pids;
}

static void create_process(size_t len, pid_t *pids, Vector_fileinfo *vec){

    FileInfo info;
    posix_spawn_file_actions_t file_actions;

    posix_spawn_file_actions_init(&file_actions);
        
        // Redirect stdout and stderr to /dev/null
    posix_spawn_file_actions_addopen(&file_actions, STDOUT_FILENO, "/dev/null", O_WRONLY, 0);
    posix_spawn_file_actions_addopen(&file_actions, STDERR_FILENO, "/dev/null", O_WRONLY, 0);

    for (size_t i = 0; i < len; i++)
    {   
        info = vector_fileinfo_get(vec, i);
        char *args[] = {info.dir_path, NULL}; // Arguments for the executable
        
        

        int status = posix_spawn(pids + i, info.dir_path, &file_actions, NULL, args, environ);
        
        if (status != 0) {
            perror("posix_spawn failed");
            exit(EXIT_FAILURE);
        }

        printf("[ \033[38;5;214mEXECUTING\033[0m ][PID: %d] %s\n", pids[i],vector_fileinfo_get(vec, i).file_name);


    }

    // Clean up file actions
    posix_spawn_file_actions_destroy(&file_actions);
    
}

static void wait_for_PID(size_t len, pid_t *pids, ProcessResult *res){
    int status;
    pid_t pid;

    for (size_t i = 0; i < len; i++)
    {
        pid = waitpid(pids[i], &status, 0);

        if (pid == -1) {
            perror("waitpid failed");
            continue;
        }

        if (WIFEXITED(status)) {
            printf("[ \033[32mPROGRAM EXITED SUCCESSFULLY\033[0m ][PID: %d] %s\n", pids[i],vector_string_get(&res->file_names, i));
            res->res[i] = true;

        } else if (WIFSIGNALED(status)) {
            printf("[ \033[31mPROGRAM FAILED\033[0m ][PID: %d] %s\n", pids[i],vector_string_get(&res->file_names, i));
            res->res[i] = false;
            
        } else {
            printf("[ \033[31mPROGRAM FAILED ABNORMALY\033[0m ][PID: %d] %s\n", pids[i],vector_string_get(&res->file_names, i));
            res->res[i] = false;

        }

    }
    

}


/**
 *  Pid index aligned according to the list index order
 */
ProcessResult process_executable(
    Vector_fileinfo *list_info
){  

    if(!list_info){
        char buffer[256];
        snprintf(buffer, 256, "[ \033[31mERROR\033[0m ] List is empty! Cannot create processes");
        perror(buffer);
        exit(EXIT_FAILURE);
    }

    size_t len = list_info->length;
    ProcessResult process = process_result_new(len);
    set_process_contents(list_info, &process, len);
    pid_t *pids = create_pids(len);

    create_process(len, pids, list_info);
    
    wait_for_PID(len, pids, &process);

    free(pids);
    return process;
}

#elif _WIN32

#include //windows stuff

void process_executable(
    Vector_fileinfo *list_info, 
    struct ProcessResult *res
){  
    size_t len = list_info->length;




}


#endif


