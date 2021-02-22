#ifndef CTL_STR
#define CTL_STR

#include <stdlib.h>


typedef struct {
	char* data;
	size_t len;
	size_t capacity;
} ctl_heap_str;

typedef union {
	ctl_heap_str heap_str;
	char stack_str[sizeof(ctl_heap_str)];
} ctl_str_data;

typedef enum {
	HEAP,
	STACK
} ctl_str_type; 

typedef struct {
	ctl_str_type type;
	ctl_str_data data;
} ctl_str;

ctl_str ctl_str_new();

int ctl_str_from(char* data, ctl_str* out);

int ctl_str_concat(ctl_str* self, ctl_str* other);

size_t ctl_str_len(ctl_str* self);

void ctl_str_debug(ctl_str* self);

#endif
