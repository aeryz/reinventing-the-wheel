#include "rtw_vec.h"
#include "assert.h"

rtw_vec rtw_vec_init(size_t elem_len) {
    assert(elem_len);
    rtw_vec vec;
    vec.data = NULL;
    vec.len = 0;
    vec.capacity = 0;
    vec.elem_len = elem_len;
    return vec;
}

int rtw_vec_with_capacity(rtw_vec *vector, size_t capacity, size_t elem_len) {
    vector->data = (void *)malloc(capacity * elem_len);
    if (vector->data == NULL)
        return -1;
    vector->len = 0;
    vector->capacity = capacity;
    vector->elem_len = elem_len;
    return 0;
}

int rtw_vec_push_back(rtw_vec *self, const void *data) {
    int err;
    if (!self->data || !self->capacity)
        if ((err = rtw_vec_with_capacity(self, 8, self->elem_len)))
            return err;

    if (self->len >= self->capacity) {
        void *new_ptr =
            (void *)realloc(self->data, self->capacity * 2 * self->elem_len);
        if (new_ptr == NULL) {
            return -1;
        }
        self->data = new_ptr;
        self->capacity *= 2;
    }
    memcpy(self->data + self->len++ * self->elem_len, data, self->elem_len);
    return 0;
}

int rtw_vec_pop_back(rtw_vec *self, void *out) {
    if (!self->data || !self->len)
        return -1;
    if (memcpy(out, self->data + (self->len - 1) * self->elem_len,
               self->elem_len) < 0)
        return -1;
    self->len--;
    return 0;
}

void *rtw_vec_get(rtw_vec *self, const size_t index) {
    if (!self || !self->data || index >= self->len) {
        return NULL;
    }
    return &self->data[index * self->elem_len];
}

int rtw_vec_reserve(rtw_vec *self, const size_t count) {
    if (count <= self->capacity)
        return 0;
    void *new_ptr = (void *)realloc(self->data, count * self->elem_len);
    if (new_ptr == NULL)
        return -1;
    self->data = new_ptr;
    self->capacity = count;
    return 0;
}

int rtw_vec_shrink_to_fit(rtw_vec *self) {
    if (self->len >= self->capacity) {
        return 0;
    }
    void *new_ptr = (void *)realloc(self->data, self->len * self->elem_len);
    if (!new_ptr)
        return -1;
    self->data = new_ptr;
    self->capacity = self->len;
    return 0;
}

int rtw_vec_insert(rtw_vec *self, const void *elems, size_t count) {
    int rc = 0;
    for (size_t i = 0; i < count; ++i)
        if ((rc = rtw_vec_push_back(self, elems + i * self->elem_len)))
            return rc;
    return rc;
}

int rtw_vec_extend(rtw_vec *self, const rtw_vec *other) {
    int rc = 0;
    return rtw_vec_insert(self, other->data, other->len);
}

void rtw_vec_clear(rtw_vec *self, unsigned shred) {
    if (shred)
        memset(self->data, 0, self->capacity * self->elem_len);
    self->len = 0;
}

void *rtw_vec_data(rtw_vec *self) {
    if (!self)
        return NULL;
    return self->data;
}

void rtw_vec_debug(const rtw_vec *self) {}
