#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef int (*rtw_hmap_hash_fn)(const void *);
typedef int (*rtw_hmap_cmp_fn)(const void *, const void *);

typedef struct rtw_hmap_elem_s_ {
    void *key;
    void *data;
    struct rtw_hmap_elem_s_ *next;
} rtw_hmap_elem_;

typedef struct {
    rtw_hmap_hash_fn hash_func;
    rtw_hmap_cmp_fn comp_func;
    struct rtw_hmap_elem_s_ *elements[30];
} rtw_hmap;

rtw_hmap rtw_hmap_init(rtw_hmap_hash_fn hash_func, rtw_hmap_cmp_fn comp_func);

int rtw_hmap_del(rtw_hmap *map, void *key);

void *rtw_hmap_search(rtw_hmap *map, void *key);

void rtw_hmap_insert(rtw_hmap *map, void *key, void *data);

void rtw_hmap_free(rtw_hmap *map);
