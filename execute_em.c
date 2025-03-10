#include <stdio.h>
#include <stdlib.h>
#include <spawn.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

extern char **environ;


int main(int argc, char const *argv[])
{
    // List of recently compiled executables
    char *executables[] = {"./test_bin/run_1", "./test_bin/array", "./test_bin/Tester", NULL}; // Replace with your executables
    pid_t pids[3]; // Adjust based on the number of executables
    int num_progs = 3;

    for (int i = 0; i < num_progs; i++) {
        // pids[i] = fork(); // Create a new process

        // if (pids[i] == -1) {
        //     perror("fork failed");
        //     exit(EXIT_FAILURE);
        // }

        // if (pids[i] == 0) { // Child process
        //     execl(executables[i], executables[i], NULL);
        //     perror("execl failed"); // If execl fails
        //     exit(EXIT_FAILURE);
        // }

        

        char *args[] = {executables[i], NULL}; // Arguments for the executable
        
        int status = posix_spawn(&pids[i], executables[i], NULL, NULL, args, environ);
        if (status != 0) {
            perror("posix_spawn failed");
            exit(EXIT_FAILURE);
        }
    }

    // Parent process: Wait for each child and check status
    for (int i = 0; i < num_progs; i++) {
        int status;
        pid_t pid = waitpid(pids[i], &status, 0);
        
        if (pid == -1) {
            perror("waitpid failed");
            continue;
        }

        if (WIFEXITED(status)) {
            printf("Process %s (PID: %d) finished with exit code %d\n",
                   executables[i], pid, WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
            printf("Process %s (PID: %d) terminated by signal %d\n",
                   executables[i], pid, WTERMSIG(status));
        } else {
            printf("Process %s (PID: %d) ended abnormally\n", executables[i], pid);
        }
    }
    
    return 0;
}
