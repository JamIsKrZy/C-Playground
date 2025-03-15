#include <stdio.h>
#include <stdlib.h>
#include "ProcessPID.h"





#define PROCESS_HANDLER_LIMIT 5

static char* get_next_executable(TestFilesDataIter *iter){
    char *catch;
    if(!(catch = next_files_by_filedir(iter))){

        if(!(catch = next_folder(iter))) return NULL;

        if(!(catch = next_files_by_filedir(iter))) return NULL;

    } 
    
    return catch;
}


static ProcessResults init_process_result(size_t capacity){
    ProcessResults res= {
        .res = calloc(capacity, sizeof(bool)),
        .len = capacity
    };
    return res;
}




#ifdef __unix__

#include <spawn.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h> 

extern char **environ;


struct PIDS_ID{
    pid_t pids[PROCESS_HANDLER_LIMIT];
    size_t index_rep[PROCESS_HANDLER_LIMIT];
};


static struct PIDS_ID create_pids(){
    struct PIDS_ID pids = {0};
    for (size_t i = 0; i < PROCESS_HANDLER_LIMIT; i++) {
        pids.pids[i] = -1;
    }
    return pids;
}


void set_file_actions(posix_spawn_file_actions_t *file_actions){
    posix_spawn_file_actions_init(file_actions);
        
    // Redirect stdout and stderr to /dev/null
    // Basically mutes any stdout from children process
    posix_spawn_file_actions_addopen(file_actions, STDOUT_FILENO, "/dev/null", O_WRONLY, 0);
    posix_spawn_file_actions_addopen(file_actions, STDERR_FILENO, "/dev/null", O_WRONLY, 0);
}

static void create_process(char* exe_dir, pid_t *pid,posix_spawn_file_actions_t *file_actions ){

    
    char *args[] = {exe_dir, NULL}; // Arguments for the executable
    
    int status = posix_spawn(pid, exe_dir, file_actions, NULL, args, environ);
    
    if (status != 0) {
        perror("posix_spawn failed");
        exit(EXIT_FAILURE);
    }
}


struct ReturnSignal{
    bool process_finished;
    bool return_value;
};

static struct ReturnSignal wait_for_PID_result(char *file_name, pid_t *pid){
    if (*pid == -1) return (struct ReturnSignal){0}; // Skip already handled/empty PIDs
    
    int status;
    struct ReturnSignal ret = { .process_finished = false, .return_value = false};
    pid_t pid_r = waitpid(*pid, &status, WNOHANG);  // Non-blocking check

    if (pid_r == 0) {
        // Process is still running
        printf("[ \033[38;5;214mRUNNING...\033[0m ][PID: %d] %s\n", *pid, file_name);

    } else if (pid_r > 0) {
        // Process has terminated
        if (WIFEXITED(status)) {
            printf("[ \033[32mPROGRAM EXITED SUCCESSFULLY\033[0m ][PID: %d] %s\n",
                    *pid, file_name);
            ret.return_value = true;
        } else {
            printf("[ \033[31mPROGRAM FAILED\033[0m ][PID: %d] %s\n",
                    *pid, file_name);
            ret.return_value = false;
        }
        *pid = -1;
        ret.process_finished = true;
    }
    
    return ret;
        
}




/**
 *  Pid index aligned according to the list index order
 */
ProcessResults process_executable(
    TestFilesData *data
){  

    if(!data){
        char buffer[256];
        snprintf(buffer, 256, "[ \033[31mERROR\033[0m ] List is empty! Cannot create processes");
        perror(buffer);
        exit(EXIT_FAILURE);
    }

    size_t index_no = 0;
    size_t remaining_executables = get_files_data_len(data);

    ProcessResults result = init_process_result(remaining_executables);

    posix_spawn_file_actions_t file_actions;
    set_file_actions(&file_actions);

    TestFilesDataIter iter = init_file_data_iter(data);
    next_folder(&iter); //set the iteration to the starting point

    struct PIDS_ID pids = create_pids();
    

    char *exe;
    struct ReturnSignal process_signal;
    while (remaining_executables != 0)
    {
        //if pid is empty, create new process 
        for (size_t i = 0; i < PROCESS_HANDLER_LIMIT; i++)
        {
            if(pids.pids[i] == -1){
                if ((exe = get_next_executable(&iter)) == NULL) break;

                create_process(exe, pids.pids + i, &file_actions);

                printf("[ \033[38;5;214mEXECUTING\033[0m ][PID: %d] %s\n", 
                    pids.pids[i], 
                    get_filename_from_list(data, index_no)
                );

                pids.index_rep[i] = index_no;
                index_no++;
            } 
        }

        sleep(1);
        
        //get an update from the PID
        for (size_t i = 0; i < PROCESS_HANDLER_LIMIT; i++)
        {
            if(pids.pids[i] == -1) continue;

            char *name = get_filename_from_list(data, pids.index_rep[i]);
            process_signal = wait_for_PID_result(name, pids.pids + i);

            if(process_signal.process_finished == true){
                result.res[pids.index_rep[i]] = process_signal.return_value;
                remaining_executables--;
            }

        }
        
    }

    posix_spawn_file_actions_destroy(&file_actions);
    return result;
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



void free_process_results(ProcessResults *res){
    free(res->res);
    res->len = 0;
}
