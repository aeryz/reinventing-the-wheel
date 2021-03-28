#include "rtw_hset.h"
#include <string.h>

rtw_hset rtw_hset_init(rtw_hset_hash_fn hash_fn, rtw_hset_eq_fn eq_fn,
                       size_t data_len) {
    rtw_hset set;
    set.hash_fn = hash_fn;
    set.eq_fn = eq_fn;
    set.data = rtw_vec_init(data_len);

    memset(set.elements, 0, sizeof(set.elements));

    return set;
}

int rtw_hset_del(rtw_hset *set, const void *data) {
    unsigned long index = set->hash_fn(data) % RTW_HSET_BUCKET_SIZE_;

    rtw_hset_elem_ *curr_node = set->elements[index];
    rtw_hset_elem_ *prev_node = NULL;

    while (NULL != curr_node) {
        if (set->eq_fn(data, curr_node->data)) {
            char last_elem[set->data.elem_len];
            rtw_vec_pop_back(&set->data, last_elem);
            if (1 != set->data.len) {
                // Overwrite the deleted element's data with the last element's
                // data. We don't delete the deleted key from the vector.
                // Because it would be expensive. We overwrite the deleted
                // element's data with the last element's data so that we only
                // make 1 memcpy and no allocation.
                memcpy(curr_node->data, last_elem, set->data.elem_len);
            }

            if (NULL == prev_node) {
                set->elements[index] = curr_node->next;
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

int rtw_hset_find(const rtw_hset *self, const void *data) {
    unsigned long index = self->hash_fn(data) % RTW_HSET_BUCKET_SIZE_;
    rtw_hset_elem_ *last = self->elements[index];
    while (NULL != last) {
        if (self->eq_fn(data, last->data)) {
            return 1;
        }
        last = last->next;
    }
    return 0;
}

inline static rtw_hset_elem_ *
rtw_hset_elem_init_(rtw_hset *set, const void *data) {
    // Key and value needed to be packed in a single memory location.
    char temp[(set->data.elem_len)];
    memcpy(temp, data, set->data_len);

    rtw_vec_push_back(&set->data, temp);

    rtw_hset_elem_ *item = (rtw_hset_elem_ *)malloc(sizeof(rtw_hset_elem_));
    item->next = NULL;
    item->data = rtw_vec_last(&set->data);

    return item;
}

void rtw_hset_insert(rtw_hset *self, const void *data) {
    unsigned long index = self->hash_fn(data) % RTW_HSET_BUCKET_SIZE_;

    rtw_hset_elem_ *last = self->elements[index];
    if (last == NULL) {
        self->elements[index] = rtw_hset_elem_init_(self, data);
        return;
    }
    for (;;) {
        if (self->eq_fn(data, last->data)) {
            return;
        }
        if (last->next == NULL)
            break;
        last = last->next;
    }

    last->next = rtw_hset_elem_init_(self, data);
}

void rtw_hset_free(rtw_hset *self) {
    rtw_vec_free(&self->data);

    for (int i = 0; i < RTW_HSET_BUCKET_SIZE_; i++) {
        if (self->elements[i]) {
            rtw_hset_elem_ *elem = self->elements[i];
            while (elem != NULL) {
                rtw_hset_elem_ *tmp = elem;
                elem = elem->next;
                free(tmp);
            }
        }
    }
}
