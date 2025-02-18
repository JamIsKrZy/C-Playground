#include "Vector.h"


struct Vec{
    void* ptr;
    size_t cap;
    size_t top;
    size_t memSize;
};




void main(){
    Vec vec = stackmem_vec(sizeof(int), 10);
}