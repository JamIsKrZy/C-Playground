#ifndef _HASHMAP_H_GAURD

typedef struct Hashmap Hashmap;

Hashmap hashmap_init();

bool hashmap_try_insert(Hashmap*, void* key, void* value);

bool hashmap_try_get(Hashmap*, void* key, void** return_value);



#endif