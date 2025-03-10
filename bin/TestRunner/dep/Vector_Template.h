#ifndef VECTOR_TEMPLATE_H
#define VECTOR_TEMPLATE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define VECTOR_TEMPLATE_INIT_PROTOTYPE(type)\
typedef struct Vector_##type {\
    type* alloc;\
    size_t capacity;\
    size_t length;\
}Vector_##type;\
\
Vector_##type*vector_##type##_box();\
Vector_##type vector_##type##_new();\
Vector_##type vector_##type##_with_capacity(size_t capacity);\
bool vector_##type##_is_empty(Vector_##type *vec);\
void vector_##type##_clear(Vector_##type *vec);\
size_t vector_##type##_get_length(Vector_##type *vec);\
Vector_##type vector_##type##_clone(Vector_##type *vec);\
bool vector_##type##_push(Vector_##type *vec, type val);\
bool vector_##type##_pop(Vector_##type *vec, type *return_type);\
type vector_##type##_get(Vector_##type *vec, size_t index);\
bool vector_##type##_contains(\
    Vector_##type *vec, \
    type target, \
    bool (*compare_func)(const type, const type)\
);\
long vector_##type##_index_of(\
    Vector_##type *vec, \
    type target, \
    bool (*compare_func)(const type, const type)\
);\
void vector_##type##_display(Vector_##type *vec, void (*print)(const type val));\
void vector_##type##_free_content(Vector_##type *vec);\
void vector_##type##_free_self(Vector_##type **vec);\








#define VECTOR_TEMPLATE_INIT(type)\
Vector_##type * vector_##type##_box(){\
    Vector_##type *vec = malloc(sizeof(Vector_##type));\
    if(!vec) return NULL;\
    vec->alloc = (type *)calloc(10, sizeof(type *));\
    vec->capacity = 10;\
    vec->length = 0;\
    return vec;\
}\
\
Vector_##type vector_##type##_new(){\
    Vector_##type vec = {\
        .alloc = (type *)calloc(10, sizeof(type *)),\
        .capacity = 10,\
        .length = 0,\
    };\
    return vec;\
}\
\
Vector_##type vector_##type##_with_capacity(size_t capacity){\
    Vector_##type vec = {\
        .alloc = (type *)calloc(10, sizeof(type *)),\
        .capacity = capacity,\
        .length = 0,\
    };\
    return vec;\
}\
\
bool vector_##type##_is_empty(Vector_##type *vec){\
    return vec->length == 0;\
}\
\
static void PANIC_##type##_IF_EMPTY(Vector_##type *vec, const char *file, int line) {\
    if (vector_##type##_is_empty(vec)){\
        fprintf(stderr, "Error: List is empty! File: %s, Line: %d\n", file, line);\
        exit(EXIT_FAILURE);\
    } \
}\
\
static void PANIC_##type##_IF_NULL(Vector_##type *vec, const char *file, int line) {\
    if (!vec){\
        fprintf(stderr, "Error: List is NULL! File: %s, Line: %d\n", file, line);\
        exit(EXIT_FAILURE);\
    } \
}\
\
static void PANIC_##type##_IF_OUT_OF_BOUNDS(Vector_##type *vec, size_t index, const char *file, int line) {\
    if (vec->length <= index ){\
        fprintf(stderr, "Error: Accessing an index out of bounds: %s, Line: %d\n", file, line);\
        exit(EXIT_FAILURE);\
    } \
}\
\
void vector_##type##_clear(Vector_##type *vec){\
    PANIC_##type##_IF_NULL(vec, __FILE__, __LINE__);\
    vec->length = 0;\
}\
\
size_t vector_##type##_get_length(Vector_##type *vec){\
    PANIC_##type##_IF_NULL(vec, __FILE__, __LINE__);\
    return vec->length;\
}\
\
Vector_##type vector_##type##_clone(Vector_##type *vec){\
    PANIC_##type##_IF_NULL(vec, __FILE__, __LINE__);\
\
    Vector_##type cloned = vector_##type##_with_capacity(vec->capacity);\
\
    memcpy(cloned.alloc, vec->alloc, sizeof(type) * vec->capacity); \
    cloned.length = vec->length;\
\
    return cloned;\
}\
\
static void vector_##type##_resize(Vector_##type *vec){\
    size_t new_cap = vec->capacity * 2;\
\
    type *new_alloc = realloc(vec->alloc, sizeof(type) * new_cap);\
    if(!new_alloc) {\
        vec->alloc = (void*)0;\
        return;\
    }\
\
    vec->capacity = new_cap;\
    vec->alloc = new_alloc;\
}\
\
bool vector_##type##_push(Vector_##type *vec, type val){\
    PANIC_##type##_IF_NULL(vec, __FILE__, __LINE__);\
\
    if(vec->length == vec->capacity) vector_##type##_resize(vec); \
    if(!vec->alloc) return false;\
\
    vec->alloc[vec->length] = val;\
    vec->length++;\
    \
    return true;\
}\
\
bool vector_##type##_pop(Vector_##type *vec, type *return_type){\
    PANIC_##type##_IF_NULL(vec, __FILE__, __LINE__);\
    if(vector_##type##_is_empty(vec)) {\
        return_type = (void*)0;\
        return false;\
    }\
    memcpy(return_type, vec->alloc + (vec->length-1), sizeof(type));\
    vec->length--;\
\
    return true;\
}\
\
bool vector_##type##_contains(\
    Vector_##type *vec, \
    type target, \
    bool (*compare_func)(const type, const type)\
){\
    PANIC_##type##_IF_NULL(vec, __FILE__, __LINE__);\
\
    for(size_t i=0; i < vec->length; i++){\
        if(compare_func(target, vec->alloc[i])){\
            return true;\
        }\
    }\
    return false;\
}\
\
long vector_##type##_index_of(\
    Vector_##type *vec, \
    type target, \
    bool (*compare_func)(const type, const type)\
){\
    PANIC_##type##_IF_NULL(vec, __FILE__, __LINE__);\
\
    for(size_t i=0; i < vec->length; i++){\
        if(compare_func(target, vec->alloc[i])){\
            return i;\
        }\
    }\
    return -1;\
}\
\
type vector_##type##_get(Vector_##type *vec, size_t index){\
    PANIC_##type##_IF_EMPTY(vec, __FILE__, __LINE__);\
    PANIC_##type##_IF_OUT_OF_BOUNDS(vec, index,__FILE__, __LINE__);\
\
    type temp = vec->alloc[index];\
    return temp;\
}\
\
void vector_##type##_display(Vector_##type *vec, void (*print)(const type val)){\
    printf("[ ");\
    for(size_t i=0; i < vec->length; i++) print(vec->alloc[i]);\
    printf("]\n");\
}\
void vector_##type##_free_content(Vector_##type *vec){\
    if(!vec) return;\
    free(vec->alloc);\
    vec->alloc = NULL;\
}\
void vector_##type##_free_self(Vector_##type **vec){\
    if(!vec && !(*vec)) return;\
    free((*vec)->alloc);\
    free(*vec);\
    *vec = NULL;\
}\

#endif
