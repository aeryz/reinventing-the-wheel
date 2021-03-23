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

int rtw_vec_shrink(rtw_vec *self) {
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

int partition_(rtw_vec *self, int l, int r,
               int (*cmp_fn)(const void *, const void *)) {
    unsigned char temp[self->elem_len / sizeof(char)];

    int pivot_index = l + ((r - l) / 2);

    int i = l;
    int j = r;
    void *pivot_value = rtw_vec_get(self, pivot_index);

    while (i <= j) {
        while (cmp_fn(rtw_vec_get(self, i), pivot_value) == -1)
            i++;

        while (cmp_fn(rtw_vec_get(self, j), pivot_value) == 1)
            j--;

        if (i <= j) {
            memcpy(temp, self->data + i * self->elem_len, self->elem_len);
            memcpy(self->data + i * self->elem_len,
                   self->data + j * self->elem_len, self->elem_len);
            memcpy(self->data + j * self->elem_len, temp, self->elem_len);

            if (i == pivot_index) {
                pivot_value = rtw_vec_get(self, j);
            } else if (j == pivot_index) {
                pivot_value = rtw_vec_get(self, i);
            }

            i++;
            j--;
        }
    }
    return i;
}
void quicksort_(rtw_vec *self, int l, int r,
                int (*cmp_fn)(const void *, const void *)) {
    if (l < r) {
        int pivotIndex = partition_(self, l, r, cmp_fn);
        quicksort_(self, l, pivotIndex - 1, cmp_fn);
        quicksort_(self, pivotIndex, r, cmp_fn);
    }
}
int rtw_vec_sort(rtw_vec *self, int (*cmp_fn)(const void *, const void *)) {
    if (!self->data || !self->len)
        return -1;

    quicksort_(self, 0, self->len - 1, cmp_fn);

    return 0;
}

void *rtw_vec_last(rtw_vec *self) {
    if (!self->data || 0 == self->len)
        return NULL;
    else
        return rtw_vec_get(self, self->len - 1);
}

int rtw_vec_delete_index(rtw_vec *self, const size_t index) {
    if (!self->data || 0 == self->len || index >= self->len)
        return -1;
    if (index == self->len - 1) {
        if (index == 0)
            rtw_vec_clear(self, 0);
        else {
            unsigned char temp[self->elem_len / sizeof(char)];
            if (memcpy(temp, self->data + (self->len - 1) * self->elem_len,
                       self->elem_len) < 0)
                return -1;
        }
    } else {
        if (memcpy(self->data + (index)*self->elem_len,
                   self->data + (index + 1) * self->elem_len,
                   self->elem_len * 3) < 0)
            return -1;
    }
    self->len--;
    return 0;
}

int rtw_vec_delete_data(rtw_vec *self, const void *data,
                        int (*cmp_fn)(const void *, const void *)) {
    if (!self->data || 0 == self->len)
        return -1;
    for (int i = 0; i < self->len; i++) {
        if (cmp_fn(data, rtw_vec_get(self, i))) {
            if (rtw_vec_delete_index(self, i) != 0)
                return -1;
            return 0;
        }
    }
    return -1;
}

int rtw_vec_delete_data_all(rtw_vec *self, const void *data) {
    // TODO: impl
    return 0;
}

void rtw_vec_free(rtw_vec *self) {
    if (self->data) {
        free(self->data);
        self->data = NULL;
    }
}
