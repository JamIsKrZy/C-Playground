#ifndef VECTOR_STRING_H
#define VECTOR_STRING_H




typedef char* Cstr;
#define T Cstr
#include "vector.h"


char* string_new_concat(char* str1, char* str2);
char* string_new_concat_dir(char* str1, char* str2);
void display_string(const char *val);
char* string_clone(const char* str);
size_t string_longest_size(Vector_Cstr *vec, size_t minimum);
char *trim_prefix(const char *str1, const char *str2);

void vector_cstr_free_content(Vector_Cstr vec_str);

#endif