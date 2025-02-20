#ifndef VEC_H_
#define VEC_H_

#include <stddef.h>
#include <stdbool.h>

typedef struct Vec Vec;
typedef struct iter VecIterator;

#define self Vec*vec

Vec new_vector(size_t memSize, size_t capacity);

bool vector_push(self, const void*);
bool vector_pop_cpy(self, void* dest);
void* vector_pop(self);

void* vector_peek(self);
bool vector_is_empty(self);
void* vector_get_index(self, size_t index);

void vector_free(self);


#undef self

#define self VecIterator*iter
VecIterator vector_iter(self);

void* vec_iter_next(self);


#undef self
#endif