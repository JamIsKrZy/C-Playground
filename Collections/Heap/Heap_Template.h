#ifndef HEAP_TEMPLATE_DS_H
#define HEAP_TEMPLATE_DS_H

#include "../Vector/Vector_Template.h"



#define HEAP_INIT_TYPES(type, vec_type)\
struct HeapTrait{\
    bool (*compare_vlaue)(const int* val1, const int* val2);\
    bool (*display_value)(const int* val);\
};\
typedef struct Heap{\
    vec_type vec;\
    struct HeapTrait *triats;\
} Heap;\

#endif