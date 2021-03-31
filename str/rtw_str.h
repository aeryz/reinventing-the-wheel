#ifndef RTW_STR_H
#define RTW_STR_H

#include <stdlib.h>

// Stack size of 'str'.
#define RTW_STR_SS sizeof(rtw_heap_str)

typedef struct {
    char *data;
    size_t len;
    size_t capacity;
} rtw_heap_str;

typedef union {
    rtw_heap_str heap_str;
    char stack_str[RTW_STR_SS];
} rtw_str_data_;

typedef enum { HEAP_STR, STACK_STR } rtw_str_type;

typedef struct {
    rtw_str_type type;
    rtw_str_data_ data;
} rtw_str;

/** Creates an empty string without any allocation. */
rtw_str rtw_str_new();

/** Creates a string from the given char*. */
int rtw_str_from(const char *data, rtw_str *out);

/** Frees the allocated memory. Data becomes NULL. */
void rwt_str_free(rtw_str *self);

/** Adds 'other' to 'self'. */
int rtw_str_concat(rtw_str *self, const rtw_str *other);

/** Returns the length of 'self'. */
size_t rtw_str_len(const rtw_str *self);

/** Returns the capacity of 'self'. For stack allocated strings,
 * it returns the maximum stack allocation length. */
size_t rtw_str_capacity(const rtw_str *self);

/** Expands the capacity of 'self'. If 'n' is less than MAX_STACK_LEN,
 * or current capacity, it does nothing. */
int rtw_str_reserve(rtw_str *self, size_t n);

/** Erases 'self' by writing null terminator to the first character and
 * changing the length to zero. */
void rtw_str_clear(rtw_str *self);

/** Returns if 'self' is empty or not. */
int rtw_str_empty(const rtw_str *self);

/** Reduces the capacity of 'self' to fit its 'size'. */
int rtw_str_shrink_to_fit(rtw_str *self);

/** Returns the 'n'th character of 'self'. Returns '\0' if 'n' exceeds the size
 * of 'self'. */
char rtw_str_at(const rtw_str *self, size_t n);

/** Appends 'c' to 'self'. */
int rtw_str_push_back(rtw_str *self, char c);

/** Copies the contents of 'other' to 'self'. */
int rtw_str_copy(rtw_str *self, const rtw_str *other);

/** Pops and returns the last character of 'self'. If 'self' is empty, returns
 * '\0'. */
char rtw_str_pop_back(rtw_str *self);

/** Returns the underlying char* of 'self'. */
const char *rtw_str_data(const rtw_str *self);

/** Wrapper of 'strcmp'. */
int rtw_str_compare(const rtw_str *self, const rtw_str *other);

#endif
