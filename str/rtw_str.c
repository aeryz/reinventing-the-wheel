#include "rtw_str.h"
#include <stdio.h>
#include <string.h>

rtw_str rtw_str_new_heap(const char *str) {
    rtw_str heap_str;
    heap_str.type = HEAP_STR;
    rtw_str_data data;
    size_t len = strlen(str);
    data.heap_str.data = (char *)malloc(len + 1);
    data.heap_str.len = len;
    data.heap_str.capacity = len;
    strncpy(data.heap_str.data, str, len);
    heap_str.data = data;
    return heap_str;
}

void rtw_str_concat_heap(rtw_str *self, const rtw_str *other) {
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

rtw_str rtw_str_new() {
    rtw_str str;
    rtw_str_data data;
    memset(data.stack_str, 0, sizeof(data.stack_str));
    str.type = STACK_STR;
    str.data = data;
    return str;
}

int rtw_str_from(char *data, rtw_str *out) {
    size_t len = strlen(data);
    if (len > sizeof(rtw_heap_str) - 1) {
        out->type = HEAP_STR;
        rtw_heap_str str;
        str.data = (char *)malloc(len + 1);
        strncpy(str.data, data, len);
        str.capacity = len;
        str.len = len;
        if (!str.data)
            return -1;
        out->data.heap_str = str;
    } else {
        *out = rtw_str_new();
        strncpy(out->data.stack_str, data, len);
        out->data.stack_str[sizeof(out->data) - 1] =
            sizeof(out->data) - len - 1;
    }
    return 0;
}

char *rtw_str_get_data(rtw_str *self) {
    if (self->type == HEAP_STR)
        return self->data.heap_str.data;
    else
        return self->data.stack_str;
}

size_t rtw_str_len(rtw_str *self) {
    if (self->type == HEAP_STR)
        return self->data.heap_str.len;
    else
        return sizeof(self->data) -
               self->data.stack_str[sizeof(self->data) - 1] - 1;
}

int rtw_str_concat(rtw_str *self, rtw_str *other) {
    char *other_str = rtw_str_get_data(other);
    size_t other_len = rtw_str_len(other);
    size_t self_len = rtw_str_len(self);
    if (self->type == HEAP_STR) {
        rtw_heap_str *self_str = &self->data.heap_str;
        if (self_len + other_len > self_str->capacity) {
            char *new_ptr =
                (char *)realloc(self_str->data, self_len + other_len + 1);
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
        if (self->data.stack_str[sizeof(self->data) - 1] + other_len >
            sizeof(self->data) - 1) {
            rtw_heap_str str;
            str.data = (char *)malloc(self_len + other_len + 1);
            if (!str.data)
                return -1;
            strncpy(str.data, self->data.stack_str, self_len);
            strncpy(str.data + self_len, other_str, other_len);
            str.capacity = self_len + other_len;
            str.len = str.capacity;
            self->type = HEAP_STR;
            self->data.heap_str = str;
        } else {
            char *self_ptr = self->data.stack_str;
            strncpy(self_ptr + self_len, other_str, other_len);
            self_ptr[sizeof(self->data) - 1] =
                sizeof(self->data) - (self_len + other_len) - 1;
        }
    }
    return 0;
}

void rtw_str_debug(rtw_str *self) {
    if (self->type == HEAP_STR)
        printf("%s\n", self->data.heap_str.data);
    else
        printf("%s\n", self->data.stack_str);
}
