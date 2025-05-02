#include <stdint.h>
#include "essential.h"


#define TEST_CASES\
    TEST_CASE(creating_vec, DEFAULT_SSIZE)\
    TEST_CASE(from_arr, DEFAULT_SSIZE)\
// TEST_CASE(iterate, DEFAULT_SSIZE)

#include "runtime.h"


typedef uint32_t u32;
#define T u32
#include "Vector/vector.h"


TEST(creating_vec){


    int expect[] = {53,77,22,55};

    Vector_u32 vec = vector_new();


    vector_push(vec, 55);
    vector_push(vec, 22);
    vector_push(vec, 77);
    vector_push(vec, 53);

    int catch;
    for (size_t i=0; 
        !vector_is_empty(vec);
        i++
    ){
        catch = vector_pop(vec);
        printf("Popped %d\n", catch);
        assert(catch == expect[i]);
    }
    

    RETURN_SUCCESS;
}

TEST(from_arr){

    int expect[] = {43,45,11,33};

    Vector_u32 vec = vector_from(u32, {33,11,45,43});

    int catch;
    for (size_t i=0; 
        !vector_is_empty(vec);
        i++
    ){
        catch = vector_pop(vec);
        printf("Popped %d\n", catch);
        assert(catch == expect[i]);
    }

    RETURN_SUCCESS;
}



