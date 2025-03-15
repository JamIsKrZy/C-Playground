#include <stdio.h>
#include "dep/FileLookUp.h"
#include "dep/ProcessPID.h"
#include "dep/TableDisplayer.h"


int main(int argc, char const *argv[])
{
    printf("[ COLLECTING INFORMATION... ]\n");

    TestFilesData *data = locate_files("./.target/test_bin/");
    if(!data){
        perror("Location is empty!");
        exit(EXIT_FAILURE);
    } 
    
    printf("\n\n");

    ProcessResults res = process_executable(data);

    printf("\n\n");
    display_result_table(data, res);
    
    free_process_results(&res);
    free_test_files_data(&data);
    return 0;
}




