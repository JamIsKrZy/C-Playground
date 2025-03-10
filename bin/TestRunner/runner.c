#include <stdio.h>
#include "dep/TableDisplayer.h"
#include "dep/FileLookUp.h"
#include "dep/ProcessPID.h"




int main(int argc, char const *argv[])
{
    printf("[ COLLECTING INFORMATION... ]\n");
    Vector_fileinfo vec = locate_files("./.target/test_bin/");
    if(vector_fileinfo_is_empty(&vec)){
        perror("Location is empty!");
        exit(EXIT_FAILURE);
    } 
    
 
    ProcessResult res = process_executable(&vec);
    
    printf("\n\n"); 
    
    display_result_table(&res);

    //Free allocated memory
    free_process_results(&res);
    free_vector_fileinfo_fields(&vec);

    return 0;
}




