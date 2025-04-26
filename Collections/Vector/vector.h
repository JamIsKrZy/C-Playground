#ifndef VECTOR_H__
#define VECTOR_H__

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>


// [Deprecated]
#define VECTOR_INIT_TYPE(type)               \
typedef struct Vector##type {          \
    type* alloc;                        \
    size_t len;                         \
    size_t cap;                         \
} Vector##type                           \




#if defined(VEC_CHAR_STRING_TYPE)
typedef struct VectorChar {          
    char* alloc;                        
    size_t len;                         
    size_t cap;                         
} __VectorChar__; 
#endif // VEC_CHAR_STRING_TYPE

 
#define vector_new(type) {0}

#define vector_with_capacity(type, capacity) {\
    .alloc= malloc(sizeof(type) *\
        (capacity == 0 ? 1 :\
            ( 1U << (64 - __builtin_clzll(capacity - 1)))\
        ) \
    ),\
    .cap = capacity,\
    .len =0\
}

#define vector_box() do{}while(0);

#define vector_clone( to_clone) ({\
    __typeof__(to_clone) cloned = {\
        .alloc = malloc(sizeof(__typeof__(to_clone.alloc)) * (to_clone.cap) ),\
        .cap = to_clone.cap,\
        .len = to_clone.len,\
    };\
    memcpy(cloned.alloc, to_clone.alloc, sizeof(__typeof__(to_clone.alloc)) * to_clone.cap);\
    cloned;\
})


#define vector_push(vec, value) do{\
    if(vec.len >= vec.cap){\
        if (vec.cap == 0)\
            vec.cap = 8;\
        else\
            vec.cap *= 2;\
\
        vec.alloc =\
            realloc(vec.alloc, vec.cap * sizeof(*vec.alloc));\
        \
    }\
    vec.alloc[vec.len++] = value;\
} while(0)\

#define vector_pop(vec)\
    (vec.len > 0? \
        vec.alloc[--vec.len] :\
        (fprintf(stderr, "Vector Underflow!\n"),\
        exit(EXIT_FAILURE),\
        0)\
    )\



#define vector_from(type, ...) \
    ({\
        Vector_##type vec = {0}; \
        type arr[] = __VA_ARGS__; \
        size_t len = sizeof(arr)/sizeof(arr[0]);\
        for (size_t i = 0; i < len; i++) {vector_push(vec, arr[i]);}\
        vec;\
    })

#define vector_clear(vec) do { \
    if ((vec).alloc) { \
        memset((vec).alloc, 0, sizeof(*(vec).alloc) * (vec).len); \
    } \
    (vec).len = 0; \
} while(0)

#define vector_grow(vec) do{\
    vec.cap *= 2;\
    vec.alloc =\
        realloc(vec.alloc, vec.cap * sizeof(*vec.alloc));\
}while(0)

#define vector_get_len(vec) (vec.len);

#define vector_is_empty(vec) (vec.len == 0)
    

#define vector_get() do{}while(0)

#define vector_get_ref(vec, index)\
    (index < vec.len?  \
        vec.alloc + index:\
        (fprintf(stderr, "Vector: Out of Bounds!\n"),\
        exit(EXIT_FAILURE),\
        0)\
    )\


#define vector_swap(vec, index_1, index_2) do { \
    if (index_1 >= vec.len) { \
        fprintf(stderr, "Vector: Index 1 Out of Bounds!\n"); \
        exit(EXIT_FAILURE); \
    } \
    if (index_2 >= vec.len) { \
        fprintf(stderr, "Vector: Index 2 Out of Bounds!\n"); \
        exit(EXIT_FAILURE); \
    } \
    __typeof__(*vec.alloc) temp = vec.alloc[index_1]; \
    vec.alloc[index_1] = vec.alloc[index_2]; \
    vec.alloc[index_2] = temp; \
} while (0)



#define vector_contains(vec, value) \
    ({ \
        bool return_val = false;\
        for(size_t i=0; i < vec.len; i++){\
            if (vec.alloc[i] == value){\
                return_val = true;\
                break;\
            }      \
        }\
        return_val;\
    })\

/**
 * @brief get the index position of a value. The first occurence will be returned
 * 
 * - Linear Search - Time Complexity O(n)
 * 
 */
#define vector_index_of(vec, value, returned_index)\
    ({ \
        bool return_val = false;\
        returned_index = 0;\
        for(size_t i=0; i < vec.len; i++){\
            if (vec.alloc[i] == value){\
                returned_index = i;\
                return_val = true;\
                break;\
            }      \
        }\
        return_val;\
    })\



#define vector_print(vec, format) do{\
    printf("[");\
    for (size_t i = 0; i < vec.len; i++)\
    {\
        printf(format, vec.alloc[i]);\
        if(i < vec.len -1) printf(", ");\
    }\
    printf("]\n");\
} while(0)\


#define vector_free(vec) do{\
    free(vec.alloc);\
    vec.alloc = NULL;\
    vec.len = 0;\
    vec.cap = 0;\
}while(0)

#define vector_swap_remove(vec, index)({})


#endif





#ifdef T

#define _VEC_JOIN(a,b) a##b
#define VEC_JOIN(a,b) _VEC_JOIN(a,b)

#ifdef T_NAME
    #define VEC_TYPE_NAME T_NAME
#else 
    #define VEC_TYPE_NAME T
#endif


#define VEC_STRUCT_NAME(name) VEC_JOIN(name, VEC_TYPE_NAME)

typedef struct {          
    T* alloc;                        
    size_t len;                         
    size_t cap;                         
} VEC_STRUCT_NAME(Vector_);

#undef _VEC_JOIN
#undef VEC_JOIN
#undef VEC_TYPE_NAME
#ifdef T_NAME
    #undef T_NAME
#endif 


#undef T

#endif