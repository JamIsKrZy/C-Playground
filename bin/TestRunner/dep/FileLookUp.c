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

static void locate_executable_files(char *dir_path, Vector_fileinfo *vec){
    struct dirent *entry;
    DIR *dir = opendir(dir_path);

    if(!dir){
        printf("[ \033[33mERROR]\033[0m There was a problem on accessing \"%s\"\n", dir_path);
        return;
    }

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // If Folder
        if(entry->d_type == 4){
            
            char *dir_location = string_new_concat_dir(dir_path, entry->d_name);
            if(!dir_location) continue;

            locate_executable_files(dir_location, vec);
            free(dir_location);
            continue;
        }

        FileInfo info = {
            .file_name = string_clone(entry->d_name), 
            .dir_path = string_new_concat_dir(dir_path, entry->d_name)
        };
        vector_fileinfo_push(vec, info);
    }

    closedir(dir);

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

    // Push all test contents
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." to avoid infinite loops
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if(entry->d_type == 4){
            printf("A FOLDER: %s\n", entry->d_name);
            char *dir_folder = string_new_concat_dir(starting_dir, entry->d_name);
            if(!dir_folder) continue;

            locate_executable_files(dir_folder, &vec);
            free(dir_folder);
            continue;
        }

        FileInfo info = {
            .file_name = string_clone(entry->d_name), 
            .dir_path = string_new_concat_dir(starting_dir, entry->d_name)
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


free_vector_fileinfo_fields(Vector_fileinfo *fi){
    size_t len = fi->length;
    FileInfo info;
    for (size_t i = 0; i < len; i++)
    {
        info = vector_fileinfo_get(fi, i);
        free(info.dir_path);
        free(info.file_name);
    }

    free(fi->alloc);
    fi->alloc = NULL;
    fi->capacity = 0;
    fi->capacity = 0;
}


#define self Vector_fileinfo *vec

void filter_files_by_extensions(self, char *ext){

}

void filter_files_by_executables(self){

}

void filter_files_by_folders(self){

}


#undef self

