#ifndef FILE_LOOK_UP_H
#define FILE_LOOK_UP_H

#include "VectorSizeT.h"
#include "VectorString.h"
#include "Vector_Template.h"
#include <dirent.h>
#include <stddef.h>


typedef struct TestFilesData TestFilesData;


TestFilesData* locate_files(char *starting_dir);
size_t get_files_data_len(TestFilesData *list);

char * get_filename_from_list(TestFilesData *list, size_t index);
char * get_dirpath_from_list(TestFilesData *list, size_t index);


Vector_string* get_filenames_list(TestFilesData *list);

void free_test_files_data(TestFilesData **data);





// ----------------- Iterators -------------------
typedef struct TestFilesDataIter{
    TestFilesData *data;
    size_t i;
    size_t j;
    size_t counter;
} TestFilesDataIter;



TestFilesDataIter init_file_data_iter(TestFilesData* data);
char* next_files_by_name(TestFilesDataIter *data); 
char* next_files_by_filedir(TestFilesDataIter *data); 
bool next_file_is_empty(TestFilesDataIter *data);
char* next_folder(TestFilesDataIter *data); 

void debug_iter(TestFilesDataIter *data);
void show_list(TestFilesData *data);


#endif