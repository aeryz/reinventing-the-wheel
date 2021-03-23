#include "rtw_hmap.h"
#include <string.h>

rtw_hmap rtw_hmap_init(rtw_hmap_hash_fn hash_func, rtw_hmap_cmp_fn comp_func,
                       size_t key_len, size_t value_len) {
    rtw_hmap map;
    map.hash_func = hash_func;
    map.comp_func = comp_func;
    map.key_len   = key_len;
    map.data = rtw_vec_init(key_len + value_len);

    memset(map.elements, 0, sizeof(map.elements));

    return map;
}

int rtw_hmap_del(rtw_hmap *map, void *key) {
    unsigned long index = map->hash_func(key) % RTW_HMAP_BUCKET_SIZE_;
    rtw_hmap_elem_ *curr_node = map->elements[index];
    rtw_hmap_elem_ *prev_node = NULL;
    while (curr_node != NULL) {
        if (map->comp_func(key, curr_node->key)) {
            if (prev_node == NULL) {

                map->elements[index] = map->elements[index]->next;
                void *last_elem = rtw_vec_last(&map->data);
        
                memcpy(curr_node->key, last_elem, map->key_len);
                memcpy(curr_node->key+map->key_len, last_elem+map->key_len, map->data.elem_len - map->key_len);
                
                free(curr_node);
                free(prev_node);
                return 1;
            }
            void *last_elem;
            rtw_vec_pop_back(&map->data, last_elem);

            memcpy(curr_node->key, last_elem, map->key_len);
            memcpy(curr_node->key+map->key_len, last_elem+map->key_len, map->data.elem_len - map->key_len);

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

int rtw_hmap_get(rtw_hmap *map, void *key, void *out_value) {
    unsigned long index = map->hash_func(key) % RTW_HMAP_BUCKET_SIZE_;
    rtw_hmap_elem_ *last = map->elements[index];
    while (NULL != last) {
        if (map->comp_func(key, last->key)) {
            memcpy(out_value, last->key+map->key_len, map->data.elem_len - map->key_len);
            return 1;
        }
        last = last->next;
    }
    return 0;
}

void rtw_hmap_insert(rtw_hmap *map, void *key, void *data) {
    unsigned long index = map->hash_func(key) % RTW_HMAP_BUCKET_SIZE_;

    rtw_hmap_elem_ *last = map->elements[index];
    if (last == NULL) {        
        unsigned char temp[(map->key_len + map->data.elem_len - map->key_len) / sizeof(char)];
        memcpy(temp, key, map->key_len);
        memcpy(temp + map->key_len, data, map->data.elem_len - map->key_len);
        
        rtw_vec_push_back(&map->data, temp);

        rtw_hmap_elem_ *item = (rtw_hmap_elem_ *)malloc(sizeof(rtw_hmap_elem_));
        item->next = NULL;
        item->key = map->data.data + (map->data.len-1) * (map->data.elem_len);
        
        map->elements[index] = item;
      
        return;
    }
    for (;;) {
        if (map->comp_func(key, last->key)) {
            memcpy(last->key+map->key_len, data, map->data.elem_len - map->key_len);
            return;
        }
        if (last->next == NULL)
            break;
        last = last->next;
    }


    unsigned char temp[(map->data.elem_len) / sizeof(char)];
    memcpy(temp, key, map->key_len);
    memcpy(temp + map->key_len, data, map->data.elem_len - map->key_len);
    
    rtw_vec_push_back(&map->data, temp);
    rtw_hmap_elem_ *item = (rtw_hmap_elem_ *)malloc(sizeof(rtw_hmap_elem_));
    item->next = NULL;
    
    item->key = rtw_vec_last(&map->data);
    map->elements[index]->next = item;
}

void rtw_hmap_free(rtw_hmap *map) {

    free(map->data.data);

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
