#include "../str/rtw_str.h"
#include <string.h>

rtw_str rtw_str_bench_new_heap(const char *str) {
    rtw_str heap_str;
    heap_str.type = HEAP_STR;
    rtw_str_data_ data;
    size_t len = strlen(str);
    data.heap_str.data = (char *)malloc(len + 1);
    data.heap_str.len = len;
    data.heap_str.capacity = len;
    strncpy(data.heap_str.data, str, len);
    heap_str.data = data;
    return heap_str;
}

void rtw_str_bench_concat_heap(rtw_str *self, const rtw_str *other) {
    rtw_heap_str *self_str = &self->data.heap_str;
    const rtw_heap_str *other_str = &other->data.heap_str;
    if (self_str->len + other_str->len > self_str->capacity) {
        self_str->data =
            (char *)realloc(self_str->data, self_str->len + other_str->len + 1);
    }
    strncpy(self_str->data + self_str->len, other_str->data, other_str->len);
    self_str->len += other_str->len;
    self_str->capacity += other_str->len;
}
