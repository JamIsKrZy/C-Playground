#include "Vector/VectorFloat.h"
#include <unistd.h>

int main(int argc, char const *argv[])
{
    Vector_f32 vec = vector_f32_with_capacity(1000);

    for (size_t i = 0; i < 5; i++)
    {
        vector_f32_push(&vec, i + 1.16);
        sleep(1);
    }
    
    vector_f32_free(&vec);

    return 0;
}
