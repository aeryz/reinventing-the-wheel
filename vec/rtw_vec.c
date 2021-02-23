#include "rtw_vec.h"

int rtw_vec_with_capacity(rtw_vec *vector, size_t capacity) {
    if (vector == NULL)
        return -1;
    vector->data = (TYPENAME *)malloc(capacity * sizeof(TYPENAME));
    if (vector->data == NULL)
        return -1;
    vector->len = 0;
    vector->capacity = capacity;
    return 0;
}

int rtw_vec_push_back(rtw_vec *self, const TYPENAME data) {
    if (!self)
        return -1;
    int err;
    if (!self->data || !self->capacity)
        if ((err = rtw_vec_with_capacity(self, 8)))
            return err;

    if (self->len >= self->capacity) {
        TYPENAME *new_ptr = (TYPENAME *)realloc(
            self->data, self->capacity * 2 * sizeof(TYPENAME));
        if (new_ptr == NULL) {
            return -1;
        }
        self->data = new_ptr;
        self->capacity *= 2;
    }
    self->data[self->len++] = data;
    return 0;
}

int rtw_vec_pop_back(rtw_vec *self, TYPENAME *out) {
    if (!self || !self->data || !self->len)
        return -1;
    return self->data[self->len--];
}

TYPENAME *rtw_vec_get(rtw_vec *self, const size_t index) {
    if (!self || !self->data || index >= self->len) {
        return NULL;
    }
    return &self->data[index];
}

int rtw_vec_reserve(rtw_vec *self, const size_t len) {
    if (!self)
        return -1;
    if (len <= self->capacity)
        return 0;
    TYPENAME *new_ptr = (TYPENAME *)realloc(self->data, len * sizeof(TYPENAME));
    if (new_ptr == NULL)
        return -1;
    self->data = new_ptr;
    self->capacity = len;
    return 0;
}

int rtw_vec_shrink_to_fit(rtw_vec *self) {
    if (!self)
        return -1;
    if (self->len >= self->capacity) {
        return 0;
    }
    TYPENAME *new_ptr =
        (TYPENAME *)realloc(self->data, self->len * sizeof(TYPENAME));
    if (!new_ptr)
        return -1;
    self->data = new_ptr;
    self->capacity = self->len;
    return 0;
}

int rtw_vec_insert(rtw_vec *self, const TYPENAME *elems, size_t len) {
    int rc = 0;
    for (size_t i = 0; i < len; ++i)
        if ((rc = rtw_vec_push_back(self, elems[i])))
            return rc;
    return rc;
}

int rtw_vec_extend(rtw_vec *self, const rtw_vec *other) {
    if (!other)
        return -1;
    int rc = 0;
    return rtw_vec_insert(self, other->data, other->len);
}

int rtw_vec_clear(rtw_vec *self, unsigned shred) {
    if (!self)
        return -1;
    if (shred)
        memset(self->data, 0, self->len * sizeof(TYPENAME));
    self->len = 0;
    return 0;
}

void rtw_vec_debug(const rtw_vec *self) {
    printf("PTR: %p, LEN: %ld, CAP: %ld\n", self->data, self->len,
           self->capacity);
    for (int i = 0; i < self->len; ++i) {
        printf("%d ", self->data[i]);
    }
    puts("");
}
