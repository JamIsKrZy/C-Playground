#include "VectorFloat.h"

#define f32 float
VECTOR_TEMPLATE_INIT(f32)

void float_display(const float val){
    printf("%f, ", val);
}