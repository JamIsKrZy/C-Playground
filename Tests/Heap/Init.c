#include "Heap/HeapInt.h"
#include <assert.h>



bool display_int_sample(const int val){
    printf("%d, ", val);
}

bool compare_int(const int val1, const int val2){
    return val1 > val2;
}

int main(int argc, char const *argv[])
{
    struct HeapTrait trait = {
        .compare_value = compare_int,
        .display_value = display_int_sample
    };

    Heap heap = heap_new(trait);

    int to_push[] = {43,36,32,76,23,55};
    size_t len = sizeof(to_push)/sizeof(to_push[0]); 
    int catch;
    
    for (size_t i = 0; i < len; i++)
    {
        heap_push(&heap, to_push[i]);
    }

    print_heap(&heap);
    
    heap_pop(&heap, &catch);
    assert(catch == 76);
    print_heap(&heap);

    heap_pop(&heap, &catch);
    assert(catch == 55);
    print_heap(&heap);


    heap_pop(&heap, &catch);
    assert(catch == 100);
    print_heap(&heap);

    heap_pop(&heap, &catch);
    assert(catch == 36);
    
    


    
    return 0;
}
