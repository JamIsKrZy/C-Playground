#ifndef HEAPS_DS_H_
#define HEAPS_DS_H_

#include <stddef.h>
#include <stdbool.h>
#include "../Vector/VectorInt.h"

struct HeapTrait{
    bool (*compare_value)(const int val1, const int val2);
    bool (*display_value)(const int val);
};


typedef struct Heap{
    Vector_i32 vec;
    struct HeapTrait triats;
} Heap;


#define self Heap *self
Heap heap_new(struct HeapTrait traits);
Heap heap_build_from(Vector_i32 vec, struct HeapTrait traits);
Heap heap_reheapify(self, struct HeapTrait traits);
bool heap_push(self, const int val);
bool heap_pop(self, int *return_value);
bool heap_peek(self, int *return_val);

void print_heap(self);
#undef self


#endif

