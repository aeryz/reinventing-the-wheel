#ifndef CTL_STR
#define CTL_STR

#include <stdlib.h>

typedef struct {
    char *data;
    size_t len;
    size_t capacity;
} rtw_heap_str;

typedef union {
    rtw_heap_str heap_str;
    char stack_str[sizeof(rtw_heap_str)];
} rtw_str_data;

typedef enum { HEAP_STR, STACK_STR } rtw_str_type;

typedef struct {
    rtw_str_type type;
    rtw_str_data data;
} rtw_str;

rtw_str rtw_str_new_heap(const char *str);

void rtw_str_concat_heap(rtw_str *self, const rtw_str *other);

rtw_str rtw_str_new();

int rtw_str_from(char *data, rtw_str *out);

int rtw_str_concat(rtw_str *self, rtw_str *other);

size_t rtw_str_len(rtw_str *self);

void rtw_str_debug(rtw_str *self);

#endif
