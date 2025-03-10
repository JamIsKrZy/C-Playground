#ifndef FILE_LOOK_UP_H
#define FILE_LOOK_UP_H

#include "VectorString.h"
#include <dirent.h>

/**
 * Make sure to deallocate dir_path
 * Do not dealloc dir - its pointing to an program location
 */
typedef struct FileInfo
{
    char *file_name;
    char *dir_path;
} FileInfo;

#define fileinfo FileInfo
    VECTOR_TEMPLATE_INIT_PROTOTYPE(fileinfo)
#undef fileinfo

void display_fileinfo(const FileInfo info);
void display_filename(const FileInfo info);


Vector_fileinfo locate_files(char *starting_dir);
bool is_directory_empty(char *dir);


free_vector_fileinfo_fields(Vector_fileinfo *fi);

#define self Vector_fileinfo *vec

void filter_files_by_extensions(self, char *ext);
void filter_files_by_executables(self);
void filter_files_by_folders(self);

Vector_string get_file_names(self);


#undef self



#endif