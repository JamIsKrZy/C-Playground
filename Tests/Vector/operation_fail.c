
#include "Vector/VectorFloat.h"
#include "assert.h"

int main(int argc, char const *argv[])
{
    Vector_f32 vec = vector_f32_new();
    float catch_return;

    vector_f32_push(&vec, 7.77);
    vector_f32_push(&vec, 1.11);
    vector_f32_push(&vec, 55.32);
    vector_f32_push(&vec, 91.43);

    vector_f32_pop(&vec, &catch_return);
    assert(catch_return == 91.43);

    vector_f32_pop(&vec, &catch_return);
    assert(catch_return == 55.32);

    vector_f32_pop(&vec, &catch_return);
    assert(catch_return == 1.11);

    vector_f32_pop(&vec, &catch_return);
    assert(catch_return == 7.77);

    vector_f32_free(&vec);


    return 0;
}
