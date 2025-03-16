#ifndef VECTOR_FLOAT_H
#define VECTOR_FLOAT_H

#include "Vector_Template.h"

#define f32 float
VECTOR_TEMPLATE_INIT_TYPE(f32);
VECTOR_TEMPLATE_INIT_PROTOTYPE(f32);
#undef f32



void float_display(const float val);

#endif