#ifndef STRING_H_
#define STRING_H_


#include <stddef.h>
#include <stdbool.h>

//Define __VECTOR_CHAR__ for String Object
#define VEC_CHAR_STRING_TYPE
#include "vector.h"



typedef struct String {
   __VectorChar__ buffer;
} String; 

typedef struct StrSlice{
    char *ptr;
    size_t len;
} StrSlice;


/**
 * - Do not free
 * 
 */
struct StringFormat{
    int spacing;
    char *ref;
};


String string_new()
    __attribute_warn_unused_result__;

String string_clone(String *str)
    __attribute_warn_unused_result__;

String string_from_cstr(const char *cstr)
    __attribute_warn_unused_result__;

String string_from_slice(const char *cstr)
    __attribute_warn_unused_result__;


void string_push(String *str1, String *str2);
void string_push_cstr(String *str, const char *src);
void string_push_slice(String *str, StrSlice src);


StrSlice string_to_slice(String *str);
StrSlice cstr_to_slice(const char *str);

StrSlice string_slice(const String *src, const size_t start, const size_t end);
StrSlice cstr_slice(char const *src, const size_t start, const size_t end);
StrSlice strslice_slice(const StrSlice *src, const size_t start, const size_t end);

void string_free(String str);

void print_string(String *str)
    __attribute_deprecated_msg__("Use string_format instead!");

/**
 * Formats a String into a StringFormat struct.
 *
 * @param str Pointer to the String to format.
 * @return A StringFormat struct containing formatting data.
 *
 * @example \
 * String str = string_from("Hello, World!");
 * StringFormat fmt = string_format(&str);
 * print_format(&fmt);
 */
struct StringFormat string_format(String *str);
struct StringFormat strslice_format(StrSlice *slice);

size_t string_len(String *str);
void string_clear(String *str);

/**
 * @brief 
 * 
 * @param str1 
 * @param str2 
 * @return bool 
 *  
 */

int str_slice_eq(StrSlice *str1, StrSlice *str2);



#endif

#ifndef __STRING_DEFINE_FLAG__
    #define __STRING_DEFINE_FLAG__ 
#endif