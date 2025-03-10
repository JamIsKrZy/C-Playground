#include <stdio.h>
#include "FileLookUp.h"

#define fileinfo FileInfo
    VECTOR_TEMPLATE_INIT(fileinfo)
#undef fileinfo

void display_fileinfo(const FileInfo info){
    printf("{ .fileName=\"%s\", .dir_path=\"%s\" } ", info.file_name, info.dir_path);
}

void display_filename(const FileInfo info){
    printf("\"%s\", ", info.file_name);
}



Vector_fileinfo locate_files(char *starting_dir){
    struct dirent *entry;

    Vector_fileinfo vec = vector_fileinfo_new();

    //open directory path
    DIR *dir = opendir(starting_dir);

    //Catch Error - Directory not found
    if(!dir){
        char buffer[256];
        snprintf(buffer, 256, "[ \033[31mERROR\033[0m ] Directory \"%s\" is not found", starting_dir);
        perror(buffer);
        exit(EXIT_FAILURE);
    }   

    // Push
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." to avoid infinite loops
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        FileInfo info = {
            .file_name = string_clone(entry->d_name), 
            .dir_path = string_new_concat(starting_dir, entry->d_name)
        };
        vector_fileinfo_push(&vec, info);
    }
    
    closedir(dir);
    return vec;    
}


bool is_directory_empty(char *dir_path){
    struct dirent *entry;
    DIR *dir = opendir(dir_path);

    if (!dir) {
        perror("Unable to open directory");
        return -1; // Error opening directory
    }

    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." entries
        if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) {
            closedir(dir);
            return false; // Directory is NOT empty
        }
    }

    closedir(dir);
    return true; // Directory is empty
}

#define self Vector_fileinfo *vec

void filter_files_by_extensions(self, char *ext){

}

void filter_files_by_executables(self){

}

void filter_files_by_folders(self){

}


#undef self

