
#include "VectorString.h"

#define string char* 
VECTOR_TEMPLATE_INIT(string)

void display_string(const char* str){
    printf("%s, ", str);
}



