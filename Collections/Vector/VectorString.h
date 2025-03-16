#ifndef VECTOR_STRING_H
#define VECTOR_STRING_H

#include "Vector_Template.h"

#define string char*
VECTOR_TEMPLATE_INIT_TYPE(string)
VECTOR_TEMPLATE_INIT_PROTOTYPE(string)

#undef string

void display_string(const char* str);



#endif