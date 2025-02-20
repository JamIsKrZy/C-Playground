#include "Vector.h"
#include <stdlib.h>
#include <string.h>


struct Vec{
    void* base;
    size_t cap;
    size_t top;
    size_t memSize;
};

Vec new_vector(size_t memSize, size_t capacity){
    Vec vec = {
        .base = malloc(memSize * capacity),
        .cap = capacity,
        .memSize = memSize,
        .top = 0,
    };
    return vec;
}

void* vector_get_index(Vec *vec, size_t index){
    if(!vec || vec->base == NULL || index >= vec->top) return NULL;
    return get_index_of(vec, index);
}


static inline void* get_index_of(Vec *vec, size_t index){
    return ((char*)vec->base) + (vec->memSize * index);
}

bool vector_push(Vec *vec, const void* source){
    if(vec == NULL || vec->base == NULL) return false;

    if(vec->top == vec->cap){
        size_t new_size = vec->cap * 1.6;
        void* new_base = realloc(vec->base, vec->memSize * new_size);
        if(new_base == NULL) {
            vec->base = NULL;
            return false;
        }

        vec->base = new_base;
        vec->cap = new_size;
    }
    void* buffer = get_index_of(vec, vec->top);
    memmove(buffer, source, vec->memSize);
    vec->top++;

    return true;
}

bool vector_memcpy_pop(Vec *vec, void* dest){
    if(!vec || vec->top == 0)  return false;
    void *to_mv = get_index_of(vec, --vec->top);

    memmove(dest, to_mv, vec->memSize);
    return true;
}

void* vector_alloc_pop(Vec *vec){
    if(!vec || vec->top == 0)  return NULL;
    void *ptr = malloc(vec->memSize);
    void *to_mv = get_index_of(vec, --vec->top);

    memmove(ptr, to_mv, vec->memSize);

    return ptr;
}

void* vector_peek(Vec *vec){
    if( !vec || !vec->base || vec->top == 0) return NULL;
    return get_index_of(vec, vec->top-1);
}

bool vector_is_empty(Vec *vec){
    return vec->top == 0;
}

void vector_free(Vec *vec){
    if(!vec || !vec->base) return;
    free(vec->base);
}


