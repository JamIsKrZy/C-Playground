#ifndef Vector_Integer_H
#define Vector_Integer_H

#include "Vector_Template.h"

#define i32 int
VECTOR_TEMPLATE_INIT_TYPE(i32)
VECTOR_TEMPLATE_INIT_PROTOTYPE(i32)
#undef u32

void display_int(const int val);



#endif