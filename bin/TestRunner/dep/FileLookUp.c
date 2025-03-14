#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileLookUp.h"
#include "VectorString.h"
#include "Vector_Template.h"
#include "VectorSizeT.h"

#define foldcon struct FolderContent
VECTOR_TEMPLATE_INIT(foldcon)
#undef  foldcon

static struct FolderContent new_folder_content(
    char *dir_path
){
    struct FolderContent f = {
        .dir_path = dir_path,
        .vec_index = vector_ST_new()
    };
    return f;
} 

static TestFilesData new_test_files_data(){
    TestFilesData data = {
        .file_names = vector_string_new(),
        .dir_path = vector_string_new(),
        .order = vector_foldcon_new()
    };
    return data;
}


static struct FolderContent* create_new_folder_content(
    TestFilesData *data,
    char* dir_path
){
    struct FolderContent f = new_folder_content(dir_path);
    vector_foldcon_push(&data->order, f);
    return vector_foldcon_get_ref(&data->order, data->order.length-1);
}

static size_t push_new_file(
    TestFilesData *data, 
    char *file_name,
    char *dir_path
){
    vector_string_push(&data->file_names, file_name);
    vector_string_push(&data->dir_path, dir_path);
    return data->file_names.length-1;
}

static void push_file_index(
    struct FolderContent *content,
    size_t index
){
    vector_ST_push(&content->vec_index, index);
}










static void locate_within_folder(TestFilesData* data, char *dir_path){
    
    struct dirent *entry;
    DIR *dir = opendir(dir_path);
    
    
    if(!dir){
        printf("[ \033[33mERROR]\033[0m There was a problem on accessing \"%s\"\n", dir_path);
        return;
    }
    
    struct FolderContent *ref = 
        create_new_folder_content(data, dir_path);

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        // If Folder
        if(entry->d_type == 4){

            printf("[ Collecting %s... ]\n", entry->d_name);
            char *dir_child = string_new_concat_dir(dir_path, entry->d_name);
            if(!dir_child) continue;

            locate_within_folder(data, dir_child);
            
        }
        
        size_t index = push_new_file(
            data,
            string_clone(entry->d_name),
            string_new_concat_dir(dir_path, entry->d_name)
        );
            
        
        
    }

    closedir(dir);

}



PathData locate_files(char *starting_dir){
    struct dirent *entry;

    PathData data = file_info_init();
    
    PathTreeNode *current_dir = PathTreeNode_box();
    if(!current_dir){
        char buffer[256];
        snprintf(buffer, 256, "[ \033[31mERROR\033[0m ] FAILED ROOT TREE! %s", starting_dir);
        perror(buffer);
        exit(EXIT_FAILURE);
    }

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
            printf("[ Collecting %s... ]\n", entry->d_name);
            char *dir_child = string_new_concat_dir(starting_dir, entry->d_name);
            if(!dir_child) continue;

            PathTreeNode *child_contents = locate_within_folder(dir_child, &data.file_list);
            free(dir_child);
            
            continue;
        }

        
        
        file_push(
            &data.file_list, 
            current_dir, 
            string_clone(entry->d_name), 
            string_new_concat_dir(starting_dir, entry->d_name)
        );
        
    }
    
    closedir(dir);
    return data;    
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


void free_vector_fileinfo_fields(PathData *fi){
    exit(EXIT_FAILURE);
}











