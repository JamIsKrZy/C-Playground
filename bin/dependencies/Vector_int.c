#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>



typedef struct vector{
    int* alloc;
    size_t capacity;
    size_t length;
} Vector;


Vector vector_new(){
    Vector vec = { 
        .alloc = malloc(sizeof(int) * 10),
        .capacity = 10,
        .length = 0, 
    };
    return vec;
}

Vector vector_with_capacity(size_t capacity){
    Vector vec = { 
        .alloc = malloc(sizeof(int) * capacity),
        .capacity = capacity,
        .length = 0, 
    };
    return vec;
}

static inline bool vector_is_empty(Vector *vec){
    return vec->length == 0;
}

void PANIC_IF_EMPTY(Vector *vec, const char *file, int line) {
    if (vector_is_empty(vec)){
        fprintf(stderr, "Error: List is empty! File: %s, Line: %d\n", file, line);
        exit(EXIT_FAILURE);
    } 
}


void PANIC_IF_NULL(Vector *vec, const char *file, int line) {
    if (!vec){
        fprintf(stderr, "Error: List is NULL! File: %s, Line: %d\n", file, line);
        exit(EXIT_FAILURE);
    } 
}

static void PANIC_IF_OUT_OF_BOUNDS(Vector *vec, size_t index, const char *file, int line) {
    if (vec->length <= index ){
        fprintf(stderr, "Error: Accessing an index out of bounds: %s, Line: %d\n", file, line);
        exit(EXIT_FAILURE);
    } 
}


void vector_clear(Vector *vec){
    PANIC_IF_NULL(vec, __FILE__, __LINE__);

    vec->length = 0;
}

size_t vector_get_length(Vector *vec){
    PANIC_IF_NULL(vec, __FILE__, __LINE__);

    return vec->length;
}

Vector vector_clone(Vector *vec){
    PANIC_IF_NULL(vec, __FILE__, __LINE__);

    Vector cloned = vector_with_capacity(vec->capacity);

    memcpy(cloned.alloc, vec->alloc, sizeof(int) * cloned.capacity); 
    cloned.length = vec->length;

    return cloned;
}

static void vector_resize(Vector *vec){
    size_t new_cap = vec->capacity * 2;

    int *new_alloc = realloc(vec->alloc, sizeof(int) * new_cap);
    if(!new_alloc) {
        vec->alloc = NULL;
        return;
    }

    vec->capacity = new_cap;
    vec->alloc = new_alloc;
}

bool vector_push(Vector *vec, int val){
    PANIC_IF_NULL(vec, __FILE__, __LINE__);

    if(vec->length == vec->capacity) vector_resize(vec); 
    if(!vec->alloc) return false;

    vec->alloc[vec->length] = val;
    vec->length++;
    
    return true;
}


int vector_pop(Vector *vec){
    PANIC_IF_NULL(vec, __FILE__, __LINE__);
    PANIC_IF_EMPTY(vec, __FILE__, __LINE__);

    int temp = vec->alloc[vec->length-1];
    vec->length--;

    return temp;
}

bool vector_contains(Vector *vec, int target, bool (*compare_func)(const int*, const int*)){
    PANIC_IF_NULL(vec, __FILE__, __LINE__);

    for(size_t i=0; i < vec->length; i++){
        if(compare_func(&target, vec->alloc + i)){
            return true;
        }
    }
    return false;
}

long vector_index_of(Vector *vec, int target, bool (*compare_func)(const int*, const int*)){
    PANIC_IF_NULL(vec, __FILE__, __LINE__);

    for(size_t i=0; i < vec->length; i++){
        if(compare_func(&target, vec->alloc + i)){
            return i;
        }
    }
    return -1;
}

int vector_get(Vector *vec, size_t index){
    PANIC_IF_EMPTY(vec, __FILE__, __LINE__);
    PANIC_IF_OUT_OF_BOUNDS(vec, index,__FILE__, __LINE__);

    int temp = vec->alloc[index];
    return temp;
}

void vector_display(Vector *vec, void (*print)(const int* val)){

    printf("[ ");
    for(size_t i=0; i < vec->length; i++) print(vec->alloc + i);
    printf("]\n");
}












void print_int(const int* val){
    printf("%d ", *val);
}

void add_vec(Vector *vec){
    int i;
    printf("Input Value: ");
    scanf(" %d", &i);

    vector_push(vec, i);
}


void pop_vec(Vector *vec){
    if(vector_is_empty(vec)){
        printf("Vector is empty\n");
        return;
    }

    int p = vector_pop(vec);
    printf("Poped Value: %d\n", p);
}


bool compare_int(const int* v1, const int* v2){
    return *v1 == *v2;
}

void index_of_arr(Vector *vec){
    int i;
    printf("Value to search for: ");
    scanf(" %d", &i);

    long temp = vector_index_of(vec, i, compare_int);
    if(temp == -1){
        printf("[\033[31mFAIL\033[0m] Value is not found in the vector!\n");
    } else {
        printf("[\033[32mSUCCESS\033[0m] Found in index: %ld\n", temp);
    }
}

void contain_vec(Vector *vec){
    int i;
    printf("Contains Value: ");
    scanf(" %d", &i);

    if(vector_contains(vec, i, compare_int)){
        printf("[\033[32mSUCCESS\033[0m] Vector contains %d!\n", i);
    } else {
        printf("[\033[31mFAIL\033[0m] Vector does not contain %d!\n", i);
    }
}



int main(int argc, char const *argv[])
{
    Vector vec = vector_new();
    char i[255];

    while (true)
    {   
        printf("CHOOSE: ");
        scanf(" %s", i);

        if(!strcmp(i, "QUIT")) break;
        if(!strcmp(i, "ADD")) add_vec(&vec);
        if(!strcmp(i, "POP")) pop_vec(&vec);
        if(!strcmp(i, "INDEX_OF")) index_of_arr(&vec);
        if(!strcmp(i, "CONTAINS")) contain_vec(&vec);
        if(!strcmp(i, "PRINT")) vector_display(&vec, print_int);
        
    }
    

    return 0;
}
