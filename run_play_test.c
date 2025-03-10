#include <stdlib.h>
#include <assert.h>


void add_five(int arr[], int  size){
    for (size_t i = 0; i < size; i++)
    {
        arr[i] += 5;
    }
}

void init_arr(int arr[], int  size){
    for (size_t i = 0; i < size; i++)
    {
        arr[i] = i;
    }
}

void assert_arr(int arr[], int cpy[], int  size){
    for (size_t i = 0; i < size; i++)
    {
        assert(arr[i] == cpy[i] + 7);
    }
}

int main(int argc, char const *argv[])
{
    size_t size = 50;
    int arr[size];
    int cpy[size];

    init_arr(arr, size);
    init_arr(cpy, size);

    add_five(arr, size);

    assert_arr(arr, cpy, size);

    return 0;
}
