#include "map.h"

struct HashMap *hash_map_init(Hash hash_func, Comp comp_func){
    struct HashMap *map = malloc(sizeof(struct HashMap));
    map->hash_func = hash_func;
    map->comp_func = comp_func;

    return map;
}

int delete_key(struct HashMap *map, void* key)
{
    int index = map->hash_func(key);
    struct HashMapElements *curr_node = map->elements[index];
    struct HashMapElements *prev_node = NULL;
    while(curr_node != NULL)
    {
        if(map->comp_func(key, curr_node->key))
        {
            if(prev_node == NULL)
            {  
                map->elements[index] = map->elements[index]->next;
                free(curr_node);
                free(prev_node);
                return 1;
            }
            prev_node->next = curr_node->next;
            struct HashMapElements* temp = curr_node;
            free(temp);
            return 1;
        }
        prev_node = curr_node;
        curr_node = curr_node -> next;
    }
    return 0;
}
void* search_key(struct HashMap *map, void* key)
{
    int index = map->hash_func(key);
    struct HashMapElements *last = map->elements[index];
    while(last != NULL)
    {
        if(map->comp_func(key, last->key))
        {
            return last->data;
        }
        last = last -> next;
    }
    return NULL;     
}

void insert_key(struct HashMap *map, void *key, void *data) {
    struct HashMapElements *item = (struct HashMapElements*) malloc(sizeof(struct HashMapElements));

    item->key = key;
    item->data = data;  
    item->next = NULL;
    int index = map->hash_func(key);

    struct HashMapElements *last = map->elements[index];
    if(last == NULL)
    {
        map->elements[index] = item;
        map->elements[index]->next = NULL;
        return;
    }
    for(;;)
    {
        if(map->comp_func(key, last->key))
        {
            free(item);
            last->data = data;
            return;
        }
        if(last->next == NULL)
            break;
        last = last -> next;
    }
   last->next = item;
}

void free_map(struct HashMap *map){
    for(int i = 0; i < 30; i++)
    {
        free(map->elements[i]);
    }
    free(map);
}