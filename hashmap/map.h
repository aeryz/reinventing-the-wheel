#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

typedef int (*Hash)(const void*);
typedef int (*Comp)(const void*, const void*);

struct HashMapElements {
   void* key;   
   void* data;
   struct HashMapElements *next;
};
struct HashMap{
    Hash hash_func;
    Comp comp_func;
    struct HashMapElements* elements[30];
};

struct HashMap *hash_map_init(Hash hash_func, Comp comp_func);

int delete_key(struct HashMap *map, void* key);
void* search_key(struct HashMap *map, void* key);
void insert_key(struct HashMap *map, void *key, void *data);
void free_map(struct HashMap *map);