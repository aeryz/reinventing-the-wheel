#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void *data;
    size_t len;
    size_t capacity;
    size_t elem_len;
} rtw_vec;

rtw_vec rtw_vec_init(size_t elem_len);

int rtw_vec_with_capacity(rtw_vec *vector, size_t capacity, size_t elem_len);

int rtw_vec_push_back(rtw_vec *self, const void *data);

int rtw_vec_pop_back(rtw_vec *self, void *out);

void *rtw_vec_get(rtw_vec *self, const size_t index);

int rtw_vec_reserve(rtw_vec *self, const size_t len);

int rtw_vec_shrink(rtw_vec *self);

int rtw_vec_insert(rtw_vec *self, const void *elems, size_t len);

int rtw_vec_extend(rtw_vec *self, const rtw_vec *other);

int rtw_vec_clear(rtw_vec *self, unsigned shred);

void * rtw_vec_data(rtw_vec *self);

void rtw_vec_debug(const rtw_vec *self);
