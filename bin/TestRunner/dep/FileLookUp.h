#ifndef FILE_LOOK_UP_H
#define FILE_LOOK_UP_H

#include "VectorSizeT.h"
#include "VectorString.h"
#include "Vector_Template.h"
#include <dirent.h>
#include <stddef.h>

struct FolderContent{
    char *dir_path;
    Vector_ST vec_index;
};

#define foldcon struct FolderContent
VECTOR_TEMPLATE_INIT_PROTOTYPE(foldcon)
#undef  foldcon

typedef struct TestFilesData{
    Vector_string file_names;
    Vector_string dir_path;
    Vector_foldcon order;
} TestFilesData;


TestFilesData locate_files(char *starting_dir);

char * get_filename_from_list(TestFilesData *list);
char * get_dirpath_from_list(TestFilesData *list);
void free_vector_fileinfo_fields(TestFilesData *fi);





// ----------------- Factoring -------------------
 











#endif