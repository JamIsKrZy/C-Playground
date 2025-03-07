#ifndef Linkedlist_H_
#define Linkedlist_H_

#include <stdbool.h>

typedef struct Linkedlist Linkedlist;
struct Node;

#define define_type_linkedlist(type)\
    struct Node{\
        type element;\
        struct Node *next;\
    }

Linkedlist linkedlist_new();






#endif