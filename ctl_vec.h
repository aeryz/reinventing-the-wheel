#define TYPENAME int

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	TYPENAME* data;
	size_t len;
	size_t capacity;
} ctl_vec;

int ctl_vec_with_capacity(ctl_vec* vector, size_t capacity);

int ctl_vec_push_back(ctl_vec* self, const TYPENAME data);

int ctl_vec_pop_back(ctl_vec* self, TYPENAME* out);

TYPENAME* ctl_vec_get(ctl_vec* self, const size_t index);

int ctl_vec_reserve(ctl_vec* self, const size_t len);

int ctl_vec_shrink(ctl_vec* self);

int ctl_vec_insert(ctl_vec* self, const TYPENAME* elems, size_t len);

int ctl_vec_extend(ctl_vec* self, const ctl_vec* other);

int ctl_vec_clear(ctl_vec* self, unsigned shred);

void ctl_vec_debug(const ctl_vec* self);
