#include <stdio.h>
#include <stdlib.h>

typedef int (*rtw_bset_cmp_fn)(const void *, const void *);

typedef struct rtw_bset_elem_s_ {
    void *a;
    struct rtw_bset_elem_s_ *left;
    struct rtw_bset_elem_s_ *right;
} rtw_bset_elem_;

typedef struct {
    rtw_bset_cmp_fn comp_func;
    rtw_bset_elem_ *element;
} rtw_bset;

rtw_bset rtw_bset_init(rtw_bset_cmp_fn comp_func);

void rtw_bset_insert(rtw_bset *self, void *elem);

int rtw_bset_search(rtw_bset *self, void *elem);

void rtw_bset_free(rtw_bset *self);
