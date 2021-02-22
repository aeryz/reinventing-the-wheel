#include "ctl_str.h"
#include <string.h>
#include <stdio.h>

ctl_str ctl_str_new() {
	ctl_str str;
	ctl_str_data data;
	memset(data.stack_str, 0, sizeof(data.stack_str));
	str.type = STACK;
	str.data = data;
	return str;
}

int ctl_str_from(char* data, ctl_str* out) {
	size_t len = strlen(data);
	if (len > sizeof(ctl_heap_str) - 1) {
		out->type = HEAP;
		ctl_heap_str str;
		str.data = (char *)malloc(len + 1);
		strncpy(str.data, data, len);
		str.capacity = len;
		str.len = len;
		if (!str.data) 
			return -1;
		out->data.heap_str = str;
	} else {
		*out = ctl_str_new();
		strncpy(out->data.stack_str, data, len);
		out->data.stack_str[sizeof(out->data) - 1] = sizeof(out->data) - len - 1;
	}
	return 0;
}

char* ctl_str_get_data(ctl_str* self) {
	if (self->type == HEAP)
		return self->data.heap_str.data;
	else
		return self->data.stack_str;
}

size_t ctl_str_len(ctl_str* self) {
	if (self->type == HEAP) 
		return self->data.heap_str.len;
	else
		return sizeof(self->data) - self->data.stack_str[sizeof(self->data) - 1] - 1;
}

int ctl_str_concat(ctl_str* self, ctl_str* other) {
	char* other_str = ctl_str_get_data(other);
	size_t other_len = ctl_str_len(other);
	size_t self_len = ctl_str_len(self);
	if (self->type == HEAP) {
		ctl_heap_str* self_str = &self->data.heap_str;
		if (self_len + other_len > self_str->capacity) {
			char* new_ptr = (char *)realloc(self_str->data, self_len + other_len + 1);
			if (!new_ptr)
				return -1;
			self_str->data = new_ptr;
			strncpy(self_str->data + self_len, other_str, other_len);
			self_str->capacity = self_len + other_len;
			self_str->len = self_str->capacity;
		} else {
			strncpy(self_str->data + self_len, other_str, other_len);
			self_str->len += other_len;
		}	
	} else {
		if (self->data.stack_str[sizeof(self->data) - 1] + other_len > sizeof(self->data) - 1) {
			ctl_heap_str str;
			str.data = (char *)malloc(other_len + 1);
			if (!str.data)
				return -1;
			strncpy(str.data, self->data.stack_str, self_len);
			strncpy(str.data + self_len, other_str, other_len);
			str.capacity = self_len + other_len;
			str.len = str.capacity;
			self->type = HEAP;
			self->data.heap_str = str;
		} else {
			char* self_ptr = self->data.stack_str;
			strncpy(self_ptr + self_len, other_str, other_len);
			self_ptr[sizeof(self->data) - 1] = sizeof(self->data) - (self_len + other_len) - 1;
		}
	}
	return 0;
}

void ctl_str_debug(ctl_str *self) {
	if (self->type == HEAP)
		printf("%s\n", self->data.heap_str.data);
	else
		printf("%s\n", self->data.stack_str);
}
