#include "rtw_hmap.h"
#include <string.h>

rtw_hmap rtw_hmap_init(rtw_hmap_hash_fn hash_func, rtw_hmap_cmp_fn comp_func,
                       size_t value_len) {
    rtw_hmap map;
    map.hash_func = hash_func;
    map.comp_func = comp_func;
    map.data = rtw_vec_init(value_len);

    memset(map.elements, 0, sizeof(map.elements));

    return map;
}

int rtw_hmap_del(rtw_hmap *map, void *key) {
    int index = map->hash_func(key);
    rtw_hmap_elem_ *curr_node = map->elements[index];
    rtw_hmap_elem_ *prev_node = NULL;
    while (curr_node != NULL) {
        if (map->comp_func(key, curr_node->key)) {
            if (prev_node == NULL) {
                map->elements[index] = map->elements[index]->next;
                free(curr_node);
                free(prev_node);
                return 1;
            }
            prev_node->next = curr_node->next;
            rtw_hmap_elem_ *temp = curr_node;
            free(temp);
            return 1;
        }
        prev_node = curr_node;
        curr_node = curr_node->next;
    }
    return 0;
}

int rtw_hmap_get(rtw_hmap *map, void *key, void *out_value,
                 size_t out_value_len) {
    int index = map->hash_func(key);
    rtw_hmap_elem_ *last = map->elements[index];
    while (NULL != last) {
        if (map->comp_func(key, last->key)) {
            memcpy(out_value, last->data, out_value_len);
            return 1;
        }
        last = last->next;
    }
    return 0;
}

void rtw_hmap_insert(rtw_hmap *map, void *key, void *data) {
    int index = map->hash_func(key);

    rtw_hmap_elem_ *last = map->elements[index];
    if (last == NULL) {
        rtw_hmap_elem_ *item = (rtw_hmap_elem_ *)malloc(sizeof(rtw_hmap_elem_));
        item->key = key;
        rtw_vec_push_back(&map->data, data);
        memcpy(item->data, data, map->value_len);
        item->next = NULL;
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
    for (int i = 0; i < RTW_HMAP_BUCKET_SIZE_; i++) {
        if (map->elements[i]) {
            rtw_hmap_elem_ *elem = map->elements[i];
            while (elem != NULL) {
                rtw_hmap_elem_ *tmp = elem;
                elem = elem->next;
                free(tmp);
            }
        }
    }
}
