#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RTW_HMAP_BUCKET_SIZE_ 30

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
    rtw_hmap_elem_ *elements[RTW_HMAP_BUCKET_SIZE_];
} rtw_hmap;

rtw_hmap rtw_hmap_init(rtw_hmap_hash_fn hash_func, rtw_hmap_cmp_fn comp_func);

int rtw_hmap_del(rtw_hmap *map, void *key);

int rtw_hmap_get(rtw_hmap *map, void *key, void *out_value, size_t out_value_size);

void rtw_hmap_insert(rtw_hmap *map, void *key, void *data);

void rtw_hmap_free(rtw_hmap *map);
