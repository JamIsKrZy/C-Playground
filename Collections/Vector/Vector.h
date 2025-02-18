#ifndef VEC_H_
#define VEC_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct Vec Vec;
typedef struct iter VecIterator;

#define self Vec*vec

#define stackmem_vec(memory_size, capacity) \
    {\
        .ptr = (char[capacity * memory_size]){0},\
        .cap = capacity,\
        .top = 0,\
        .memSize = memory_size\
    }

void new_vector(size_t memSize, size_t capacity);

bool vector_push(self, void* ptr);
bool vector_pop(self, void* returnVal);

void* vector_peek(self);
bool vector_empty(self);



VecIterator vector_iter(self);

#undef self
#endif