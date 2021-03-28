#include "rtw_hmap.h"
#include <string.h>

rtw_hmap rtw_hmap_init(rtw_hmap_hash_fn hash_fn, rtw_hmap_eq_fn eq_fn,
                       size_t key_len, size_t value_len) {
    rtw_hmap map;
    map.hash_fn = hash_fn;
    map.eq_fn = eq_fn;
    map.key_len = key_len;
    map.data = rtw_vec_init(key_len + value_len);

    memset(map.elements, 0, sizeof(map.elements));

    return map;
}

int rtw_hmap_del(rtw_hmap *map, const void *key) {
    unsigned long index = map->hash_fn(key) % RTW_HMAP_BUCKET_SIZE_;

    rtw_hmap_elem_ *curr_node = map->elements[index];
    rtw_hmap_elem_ *prev_node = NULL;

    while (NULL != curr_node) {
        if (map->eq_fn(key, curr_node->key)) {
            char last_elem[map->data.elem_len];
            rtw_vec_pop_back(&map->data, last_elem);
            if (1 != map->data.len) {
                // Overwrite the deleted element's data with the last element's
                // data. We don't delete the deleted key from the vector.
                // Because it would be expensive. We overwrite the deleted
                // element's data with the last element's data so that we only
                // make 1 memcpy and no allocation.
                memcpy(curr_node->key, last_elem, map->data.elem_len);
            }

            if (NULL == prev_node) {
                map->elements[index] = curr_node->next;
            } else {
                prev_node->next = curr_node->next;
            }

            free(curr_node);
            return 1;
        }
        prev_node = curr_node;
        curr_node = curr_node->next;
    }
    return 0;
}

int rtw_hmap_get(const rtw_hmap *self, const void *key, void *out_value) {
    unsigned long index = self->hash_fn(key) % RTW_HMAP_BUCKET_SIZE_;
    rtw_hmap_elem_ *last = self->elements[index];
    while (NULL != last) {
        if (self->eq_fn(key, last->key)) {
            memcpy(out_value, last->key + self->key_len,
                   self->data.elem_len - self->key_len);
            return 1;
        }
        last = last->next;
    }
    return 0;
}

inline static rtw_hmap_elem_ *
rtw_hmap_elem_init_(rtw_hmap *map, const void *key, const void *data) {
    // Key and value needed to be packed in a single memory location.
    char temp[(map->data.elem_len)];
    memcpy(temp, key, map->key_len);
    memcpy(temp + map->key_len, data, map->data.elem_len - map->key_len);

    rtw_vec_push_back(&map->data, temp);

    rtw_hmap_elem_ *item = (rtw_hmap_elem_ *)malloc(sizeof(rtw_hmap_elem_));
    item->next = NULL;
    item->key = rtw_vec_last(&map->data);

    return item;
}

void rtw_hmap_insert(rtw_hmap *self, const void *key, const void *data) {
    unsigned long index = self->hash_fn(key) % RTW_HMAP_BUCKET_SIZE_;

    rtw_hmap_elem_ *last = self->elements[index];
    if (last == NULL) {
        self->elements[index] = rtw_hmap_elem_init_(self, key, data);
        return;
    }
    for (;;) {
        if (self->eq_fn(key, last->key)) {
            memcpy(last->key + self->key_len, data,
                   self->data.elem_len - self->key_len);
            return;
        }
        if (last->next == NULL)
            break;
        last = last->next;
    }

    last->next = rtw_hmap_elem_init_(self, key, data);
}

void rtw_hmap_free(rtw_hmap *self) {
    rtw_vec_free(&self->data);

    for (int i = 0; i < RTW_HMAP_BUCKET_SIZE_; i++) {
        if (self->elements[i]) {
            rtw_hmap_elem_ *elem = self->elements[i];
            while (elem != NULL) {
                rtw_hmap_elem_ *tmp = elem;
                elem = elem->next;
                free(tmp);
            }
        }
    }
}
