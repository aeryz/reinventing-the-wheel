#include "rtw_str.h"
#include <stdio.h>
#include <string.h>

/* Private */
int _rtw_str_grow_heap_str(rtw_heap_str *str, const char *data, size_t len);

int _rtw_str_heap_from(const char *data, size_t len, rtw_str *out);

int _rtw_str_stack_from(const char *data, size_t len, rtw_str *out);
/* Private end */

rtw_str rtw_str_new() {
    rtw_str str;
    rtw_str_data_ data;
    memset(data.stack_str, 0, sizeof(data.stack_str));
    str.type = STACK_STR;
    str.data = data;
    return str;
}

int rtw_str_from(const char *data, rtw_str *out) {
    size_t len = strlen(data);
    if (len > sizeof(rtw_heap_str) - 1) {
        return _rtw_str_heap_from(data, len, out);
    } else {
        return _rtw_str_stack_from(data, len, out);
    }
}

void rtw_str_free(rtw_str *self) {
    rtw_heap_str *str = &self->data.heap_str;
    if (self->type == STACK_STR) {
        self->type = HEAP_STR;
    } else {
        if (str->data == NULL)
            return;
        free(str->data);
    }
    str->data = NULL;
    str->capacity = 0;
    str->len = 0;
}

int rtw_str_concat(rtw_str *self, const rtw_str *other) {
    if (self->type == HEAP_STR) {
        _rtw_str_grow_heap_str(&self->data.heap_str, rtw_str_data(other),
                               rtw_str_len(other));
    } else {
        size_t self_len = rtw_str_len(self);
        size_t other_len = rtw_str_len(other);
        if (self_len + other_len > RTW_STR_SS - 1) {
            rtw_str new_str;
            int rc;
            if ((rc = _rtw_str_heap_from(self->data.stack_str, self_len,
                                         &new_str) ||
                      _rtw_str_grow_heap_str(&new_str.data.heap_str,
                                             rtw_str_data(other), other_len))) {
                return rc;
            }
        }
    }
    return 0;
}

size_t rtw_str_len(const rtw_str *self) {
    if (self->type == HEAP_STR)
        return self->data.heap_str.len;
    else
        return sizeof(self->data) - self->data.stack_str[RTW_STR_SS - 1] - 1;
}

size_t rtw_str_capacity(const rtw_str *self) {
    if (self->type == HEAP_STR)
        return self->data.heap_str.capacity;
    else
        return sizeof(self->data.heap_str);
}

// TODO: unimpl
int rtw_str_reserve(rtw_str *self, size_t n) {
    if (rtw_str_capacity(self) > n) {
        return 0;
    }
    return 1;
}

void rtw_str_clear(rtw_str *self) {
    if (rtw_str_empty(self))
        return;
    if (self->type == HEAP_STR) {
        self->data.heap_str.data[0] = '\0';
        self->data.heap_str.len = 0;
    } else {
        self->data.stack_str[0] = '\0';
        self->data.stack_str[RTW_STR_SS - 1] = sizeof(rtw_heap_str) - 1;
    }
}

int rtw_str_empty(const rtw_str *self) {
    if (self->type == HEAP_STR)
        return self->data.heap_str.len == 0;
    else
        return self->data.stack_str[RTW_STR_SS - 1] == RTW_STR_SS - 1;
}

int rtw_str_shrink_to_fit(rtw_str *self) {
    if (self->type == STACK_STR ||
        self->data.heap_str.len == self->data.heap_str.capacity) {
        return 0;
    }
    char *new_ptr =
        (char *)realloc(self->data.heap_str.data, self->data.heap_str.len);
    if (!new_ptr)
        return -1;
    self->data.heap_str.data = new_ptr;
    self->data.heap_str.capacity = self->data.heap_str.len;
    return 0;
}

char rtw_str_at(rtw_str *self, size_t n) {
    if (rtw_str_len(self) < n) {
        return 0;
    } else {
        return rtw_str_data(self)[n];
    }
}

// TODO: unimpl
int rtw_str_push_back(rtw_str *self, char c) { return 0; }

// TODO: unimpl
int rtw_str_copy(rtw_str *self, const rtw_str *other);

char rtw_str_pop_back(rtw_str *self) {
    if (rtw_str_empty(self)) {
        return '\0';
    }
    char ret;
    if (self->type == HEAP_STR) {
        ret = self->data.heap_str.data[self->data.heap_str.len - 1];
        self->data.heap_str.data[self->data.heap_str.len-- - 1] = '\0';
    } else {
        ret = self->data.stack_str[RTW_STR_SS -
                                   self->data.stack_str[RTW_STR_SS - 1] - 1];
        self->data.stack_str[RTW_STR_SS -
                             self->data.stack_str[RTW_STR_SS - 1]++ - 1] = '\0';
    }
    return ret;
}

const char *rtw_str_data(const rtw_str *self) {
    if (self->type == HEAP_STR)
        return self->data.heap_str.data;
    else
        return self->data.stack_str;
}

int rtw_str_compare(const rtw_str *self, const rtw_str *other) {
    return strcmp(rtw_str_data(self), rtw_str_data(other));
}

/* Benches */
rtw_str rtw_str_new_heap(const char *str) {
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
/* Benches end */

/* Private implementations */
int _rtw_str_grow_heap_str(rtw_heap_str *str, const char *data, size_t len) {
    if (str->len + len > str->capacity) {
        char *new_ptr = (char *)realloc(str->data, str->len + len + 1);
        if (!new_ptr)
            return -1;
        str->data = new_ptr;
        strncpy(str->data + str->len, data, len);
        str->capacity = str->len + len;
        str->len = str->capacity;
    } else {
        strncpy(str->data + str->len, data, len);
        str->len += len;
    }
    return 0;
}

int _rtw_str_heap_from(const char *data, size_t len, rtw_str *out) {
    out->type = HEAP_STR;
    rtw_heap_str str;
    str.data = (char *)malloc(len + 1);
    strncpy(str.data, data, len);
    str.capacity = len;
    str.len = len;
    if (!str.data)
        return -1;
    out->data.heap_str = str;
    return 0;
}

int _rtw_str_stack_from(const char *data, size_t len, rtw_str *out) {
    *out = rtw_str_new();
    strncpy(out->data.stack_str, data, len);
    out->data.stack_str[sizeof(out->data) - 1] = sizeof(out->data) - len - 1;
    return 0;
}
