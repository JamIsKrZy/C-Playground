
#include "VectorString.h"

VECTOR_TEMPLATE_INIT(string)

char* string_new_concat_dir(char* str1, char* str2){
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t total_len = len1 + len2 + 2;  // +2 for '/' and '\0'

    char *str = malloc(total_len);
    if (!str) {
        return NULL; // Memory allocation failed
    }

    snprintf(str, total_len, "%s/%s", str1, str2);
    return str;
}

char* string_new_concat(char* str1, char* str2){
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    size_t total_len = len1 + len2 + 1;  // +2 for '/' and '\0'

    char *str = malloc(total_len);
    if (!str) {
        return NULL; // Memory allocation failed
    }

    snprintf(str, total_len, "%s%s", str1, str2);
    return str;
}


void display_string(const char *val){
    printf("\"%s\", ", val);
}

char* string_clone(const char* str) {
    if (!str) return NULL; // Handle NULL input

    // Allocate memory for the new string (+1 for null terminator)
    char *clone = malloc(strlen(str) + 1);
    if (!clone) return NULL; // Check if malloc failed

    // Copy the string
    strcpy(clone, str);
    
    return clone;
}

size_t string_longest_size(Vector_string *vec, size_t minimum){
    size_t t;

    for(size_t i=0; i < vec->length; i++){
        t = strlen(vector_string_get(vec, i));
        if(t > minimum){
            minimum = t;
        }
    }
    
    return minimum;
}

char *trim_prefix(const char *str1, const char *str2) {
    size_t len1 = strlen(str1);
    size_t len2 = strlen(str2);
    
    if (len1 >= len2 && strncmp(str1, str2, len2) == 0) {
        // Allocate memory for the new string
        char *result = malloc(len1 - len2 + 1);
        if (!result) return NULL; // Check for malloc failure
        
        strcpy(result, str1 + len2);
        return result;
    } 
    
    // If str2 is not a prefix, return a copy of str1
    char *result = malloc(len1 + 1);
    if (!result) return NULL;
    
    strcpy(result, str1);
    return result;
}

