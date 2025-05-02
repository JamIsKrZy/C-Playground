#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "FileLookUp.h"


typedef struct filegroup{
    char* group_name;
    size_t len;
} filegroup;


#define T filegroup
#include "vector.h"


struct TestFilesData{
    Vector_Cstr file_names;
    Vector_Cstr dir_path;
    Vector_filegroup groups;
};

TestFilesData new_test_file_data(){
    TestFilesData data = {
        .file_names = vector_new(),
        .dir_path = vector_new(),
        .groups = vector_new()
    };
    return data;
}

size_t get_files_data_len(TestFilesData *list){
    return vector_get_len(list->dir_path);
}

void vector_filegroup_free_content(Vector_filegroup vec_fg){
    filegroup fg;
    while (!vector_is_empty(vec_fg))
    {
        fg = vector_pop(vec_fg);
        free(fg.group_name);
    }
    free(vec_fg.alloc);
}


void push_file_data(TestFilesData *data, char *file_name, char *dir_path){

    vector_push(data->file_names, file_name);
    vector_push(data->dir_path, dir_path);
    
}


TestFilesData* locate_files(char *starting_dir){
    
    //open directory path
    struct dirent *entry;
    DIR *dir = opendir(starting_dir);


    //Catch Error - Directory not found
    if(!dir){
        char buffer[256];
        snprintf(buffer, 256, "[ \033[31mERROR\033[0m ] Directory \"%s\" is not found", starting_dir);
        perror(buffer);
        exit(EXIT_FAILURE);
    } 

    TestFilesData data = new_test_file_data();
    Vector_Cstr folders_to_check = vector_with_capacity(Cstr, 8);

    size_t count = 0;
    // Push all test contents
    while ((entry = readdir(dir)) != NULL) {
        // Skip "." and ".." to avoid infinite loops
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if(entry->d_type == 4){
            printf("[ Collecting %s... ]\n", entry->d_name);
            char *dir_child = string_new_concat(starting_dir, entry->d_name);
            if(!dir_child) continue;

            vector_push(folders_to_check, dir_child);
            continue;
        }


        printf("Adding \"%s\" to file info\n", entry->d_name);
        push_file_data(
            &data,
            string_clone(entry->d_name),
            string_new_concat_dir(starting_dir, entry->d_name)
        );
        count++;
        
    }

    if(count == 0 && vector_is_empty(folders_to_check)) return NULL;
    
    filegroup fg = {
        .group_name=string_clone("/"), 
        .len = count
    };
    
    vector_push(data.groups, fg);

    closedir(dir);

    // Check on other folders
    char *path;
    while (!vector_is_empty(folders_to_check))
    {
        path = vector_pop(folders_to_check);
        dir = opendir(path);

        if(!dir){
            printf( "[ \033[31mERROR\033[0m ] Directory \"%s\" is not found", path);
            continue;
        };

        count = 0;
        while ((entry = readdir(dir)) != NULL) {
            // Skip "." and ".." to avoid infinite loops
            if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
                continue;
            }
    
            if(entry->d_type == 4){
                printf("[ Collecting %s... ]\n", entry->d_name);
                char *dir_child = string_new_concat_dir(path, entry->d_name);
                if(!dir_child) continue;
    
                vector_push(folders_to_check, dir_child);
                continue;
            }
            
            printf("Adding \"%s\" to file info\n", entry->d_name);

            push_file_data(
                &data,
                string_clone(entry->d_name),
                string_new_concat_dir(path, entry->d_name)
            );
            count++;
            
        }

        filegroup fg = {
            .group_name= trim_prefix(path, starting_dir), 
            .len = count
        };
        vector_push(data.groups, fg);
        free(path);
        closedir(dir);
    }
    
    vector_cstr_free_content(folders_to_check);



    TestFilesData *data_box = malloc(sizeof(TestFilesData));
    *data_box = data;
    return data_box;    
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


char* get_filename_from_list(TestFilesData *list, size_t index){
    if(index >= vector_get_len(list->file_names)) return NULL;
    return vector_get(list->file_names, index);
}



char * get_dirpath_from_list(TestFilesData *list, size_t index){
    if(index >= vector_get_len(list->file_names)) return NULL;
    return vector_get(list->dir_path, index);
}


TestFilesDataIter init_file_data_iter(TestFilesData* data){
    TestFilesDataIter iter = {
        .data = data,
        .counter = 0,
        .i = 0,
        .j = 0
    };
    return iter;
}


char* next_files_by_name(TestFilesDataIter *data){
    if(data->counter == 0) return NULL;

    char* name = get_filename_from_list(data->data, data->i);
    data->counter--;
    data->i++;
    return name;
}

void debug_iter(TestFilesDataIter *data){
    printf("{\n");
    printf("\tcounter: %ld\n", data->counter);
    printf("\ti: %ld\n", data->i);
    printf("\tj: %ld\n", data->j);
    printf("}\n");
}


char* next_files_by_filedir(TestFilesDataIter *data){
    if(data->counter == 0) return NULL;

    char* path = get_dirpath_from_list(data->data, data->i);
    data->counter--;
    data->i++;
    return path;
}

char* next_folder(TestFilesDataIter *data){
    if(data->j >= vector_get_len(data->data->groups)) return NULL;

    struct filegroup fg = vector_get(data->data->groups, data->j);
    data->j++;
    data->counter = fg.len;
    return fg.group_name;
} 

bool next_file_is_empty(TestFilesDataIter *data){
    return data->counter == 0;
}


void show_list(TestFilesData *data){
    size_t len = vector_get_len(data->dir_path);
    for (size_t i = 0; i < len; i++)
    {
        printf("[DBUG] %s\n", get_filename_from_list(data, i));
    }
    
}

void free_test_files_data(TestFilesData **data){

    char *catch;
    while (!vector_is_empty((*data)->file_names))
    {   
        // get file name string
        catch = vector_pop((*data)->file_names);
        free(catch);

        // get path string
        catch = vector_pop((*data)->dir_path);
        free(catch);
    }

    

    struct filegroup group; 
    while (!vector_is_empty((*data)->groups))
    {
        group = vector_pop((*data)->groups);
        free(group.group_name);
    }
    
    vector_cstr_free_content((*data)->dir_path);
    vector_cstr_free_content((*data)->file_names);
    vector_filegroup_free_content((*data)->groups);

    free(*data);
    *data = NULL;
    
}






