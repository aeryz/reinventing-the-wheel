#define TYPENAME int

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	TYPENAME* data;
	size_t len;
	size_t capacity;
} rtw_vec;

int rtw_vec_with_capacity(rtw_vec* vector, size_t capacity);

int rtw_vec_push_back(rtw_vec* self, const TYPENAME data);

int rtw_vec_pop_back(rtw_vec* self, TYPENAME* out);

TYPENAME* rtw_vec_get(rtw_vec* self, const size_t index);

int rtw_vec_reserve(rtw_vec* self, const size_t len);

int rtw_vec_shrink(rtw_vec* self);

int rtw_vec_insert(rtw_vec* self, const TYPENAME* elems, size_t len);

int rtw_vec_extend(rtw_vec* self, const rtw_vec* other);

int rtw_vec_clear(rtw_vec* self, unsigned shred);

void rtw_vec_debug(const rtw_vec* self);
