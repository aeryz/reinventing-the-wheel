#include "rtw_hmap.h"

rtw_hmap rtw_hmap_init(rtw_hmap_hash_fn hash_func, rtw_hmap_cmp_fn comp_func) {
    rtw_hmap map;
    map.hash_func = hash_func;
    map.comp_func = comp_func;

    return map;
}

int rtw_hmap_del(rtw_hmap *map, void *key) {
    int index = map->hash_func(key);
    struct rtw_hmap_elem_s_ *curr_node = map->elements[index];
    struct rtw_hmap_elem_s_ *prev_node = NULL;
    while (curr_node != NULL) {
        if (map->comp_func(key, curr_node->key)) {
            if (prev_node == NULL) {
                map->elements[index] = map->elements[index]->next;
                free(curr_node);
                free(prev_node);
                return 1;
            }
            prev_node->next = curr_node->next;
            struct rtw_hmap_elem_s_ *temp = curr_node;
            free(temp);
            return 1;
        }
        prev_node = curr_node;
        curr_node = curr_node->next;
    }
    return 0;
}

void *rtw_hmap_search(rtw_hmap *map, void *key) {
    int index = map->hash_func(key);
    struct rtw_hmap_elem_s_ *last = map->elements[index];
    while (last != NULL) {
        if (map->comp_func(key, last->key)) {
            return last->data;
        }
        last = last->next;
    }
    return NULL;
}

void rtw_hmap_insert(rtw_hmap *map, void *key, void *data) {
    struct rtw_hmap_elem_s_ *item =
        (struct rtw_hmap_elem_s_ *)malloc(sizeof(struct rtw_hmap_elem_s_));

    item->key = key;
    item->data = data;
    item->next = NULL;
    int index = map->hash_func(key);

    struct rtw_hmap_elem_s_ *last = map->elements[index];
    if (last == NULL) {
        map->elements[index] = item;
        map->elements[index]->next = NULL;
        return;
    }
    for (;;) {
        if (map->comp_func(key, last->key)) {
            free(item);
            last->data = data;
            return;
        }
        if (last->next == NULL)
            break;
        last = last->next;
    }
    last->next = item;
}

void rtw_hmap_free(rtw_hmap *map) {
    for (int i = 0; i < 30; i++) {
        free(map->elements[i]);
    }
    free(map);
}
