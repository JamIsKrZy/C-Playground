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
    
    // TestFilesDataIter iter = init_file_data_iter(data);
    
    // printf("\n");

    // char *catch;

    // while ((catch = next_folder(&iter)) != NULL)
    // {
    //     printf("Folder: %s\n", catch);

    //     while ((catch = next_files_by_filedir(&iter)) != NULL)
    //     {
    //         printf("\t%s\n", catch);
    //     }
        
    // }
    
    printf("\n\n");

    ProcessResults res = process_executable(data);

    display_result_table(data, res);
    

    

    return 0;
}




