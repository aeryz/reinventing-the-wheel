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
    data.stack_str[RTW_STR_SS - 1] = RTW_STR_SS - 1;
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
    if (STACK_STR == self->type) {
        self->type = HEAP_STR;
    } else {
        if (NULL == str->data)
            return;
        free(str->data);
    }
    str->data = NULL;
    str->capacity = 0;
    str->len = 0;
}

int rtw_str_concat(rtw_str *self, const rtw_str *other) {
    if (HEAP_STR == self->type) {
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
            *self = new_str;
        } else {
            strncpy(self->data.stack_str + self_len, rtw_str_data(other),
                    other_len + 1);
            self->data.stack_str[RTW_STR_SS - 1] =
                RTW_STR_SS - self_len - other_len - 1;
        }
    }
    return 0;
}

size_t rtw_str_len(const rtw_str *self) {
    if (HEAP_STR == self->type)
        return self->data.heap_str.len;
    else
        return sizeof(self->data) - self->data.stack_str[RTW_STR_SS - 1] - 1;
}

size_t rtw_str_capacity(const rtw_str *self) {
    if (HEAP_STR == self->type)
        return self->data.heap_str.capacity;
    else
        return sizeof(self->data.heap_str);
}

int rtw_str_reserve(rtw_str *self, size_t n) {
    if (rtw_str_capacity(self) > n) {
        return 0;
    }
    rtw_heap_str str;
    str.len = rtw_str_len(self);
    str.capacity = n;
    str.data = (char *)malloc(n + 1);
    if (!str.data)
        return -1;
    strncpy(str.data, rtw_str_data(self), str.len + 1);
    if (HEAP_STR == self->type && NULL != self->data.heap_str.data)
        free(self->data.heap_str.data);
    self->data.heap_str = str;
    return 0;
}

void rtw_str_clear(rtw_str *self) {
    if (rtw_str_empty(self))
        return;
    if (HEAP_STR == self->type) {
        self->data.heap_str.data[0] = '\0';
        self->data.heap_str.len = 0;
    } else {
        self->data.stack_str[0] = '\0';
        self->data.stack_str[RTW_STR_SS - 1] = RTW_STR_SS - 1;
    }
}

int rtw_str_empty(const rtw_str *self) {
    if (HEAP_STR == self->type)
        return self->data.heap_str.len == 0;
    else
        return RTW_STR_SS == self->data.stack_str[RTW_STR_SS - 1];
}

int rtw_str_shrink_to_fit(rtw_str *self) {
    if (STACK_STR == self->type ||
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

char rtw_str_at(const rtw_str *self, size_t n) {
    if (rtw_str_len(self) < n) {
        return 0;
    } else {
        return rtw_str_data(self)[n];
    }
}

int rtw_str_push_back(rtw_str *self, char c) {
    char c_str[2] = {c, '\0'};
    rtw_str tmp = rtw_str_new();
    tmp.data.stack_str[0] = c;
    return rtw_str_concat(self, &tmp);
}

int rtw_str_copy(rtw_str *self, const rtw_str *other) {
    rtw_str_free(self);
    return rtw_str_concat(self, other);
}

char rtw_str_pop_back(rtw_str *self) {
    if (rtw_str_empty(self)) {
        return '\0';
    }
    char ret;
    if (HEAP_STR == self->type) {
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
    if (HEAP_STR == self->type)
        return self->data.heap_str.data;
    else
        return self->data.stack_str;
}

int rtw_str_compare(const rtw_str *self, const rtw_str *other) {
    return strcmp(rtw_str_data(self), rtw_str_data(other));
}

/* Private implementations */
int _rtw_str_grow_heap_str(rtw_heap_str *str, const char *data, size_t len) {
    if (str->len + len > str->capacity) {
        char *new_ptr = (char *)realloc(str->data, str->len + len + 1);
        if (!new_ptr)
            return -1;
        str->data = new_ptr;
        strncpy(str->data + str->len, data, len + 1);
        str->capacity = str->len + len;
        str->len = str->capacity;
    } else {
        strncpy(str->data + str->len, data, len + 1);
        str->len += len;
    }
    return 0;
}

int _rtw_str_heap_from(const char *data, size_t len, rtw_str *out) {
    out->type = HEAP_STR;
    rtw_heap_str str;
    str.data = (char *)malloc(len + 1);
    strncpy(str.data, data, len + 1);
    str.capacity = len;
    str.len = len;
    if (!str.data)
        return -1;
    out->data.heap_str = str;
    return 0;
}

int _rtw_str_stack_from(const char *data, size_t len, rtw_str *out) {
    *out = rtw_str_new();
    strncpy(out->data.stack_str, data, len + 1);
    out->data.stack_str[sizeof(out->data) - 1] = sizeof(out->data) - len - 1;
    return 0;
}
