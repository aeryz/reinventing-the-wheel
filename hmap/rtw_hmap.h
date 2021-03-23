#include "../vec/rtw_vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RTW_HMAP_BUCKET_SIZE_ 30

typedef unsigned long (*rtw_hmap_hash_fn)(const void *);
typedef int (*rtw_hmap_cmp_fn)(const void *, const void *);

typedef struct rtw_hmap_elem_s_ {
    void *key;
    struct rtw_hmap_elem_s_ *next;
} rtw_hmap_elem_;

typedef struct {
    rtw_hmap_hash_fn hash_func;
    rtw_hmap_cmp_fn comp_func;
    rtw_hmap_elem_ *elements[RTW_HMAP_BUCKET_SIZE_];
    rtw_vec keys_and_values;
    size_t value_len;
    size_t key_len;
} rtw_hmap;

/**
 * Creates an empty binary set without any allocation
 *
 * @param cmp_fn Is function pointer to add our datas to hash map, comparasion function.
 *      Help of this comp_fn we will know if incoming key exists in map or not.
 *      It takes 2 parameters, left hand side and right hand side.
 *      It returns -1 if right hand side is greater than left hand side
 *      It returns 1 if right hand side is smaller than left hand side
 *      It returns 0 if two value is same.
 * @param hash_fn Is function pointer to hash key, hash function.
 *      It takes only one void* parameter and get hash of that value.
 *      It returns a hash value with int.
 * @param key_len Size of the key that the vector holds
 * @param value_len Size of the data that the vector holds
 */
rtw_hmap rtw_hmap_init(rtw_hmap_hash_fn hash_fn, rtw_hmap_cmp_fn cmp_fn, size_t key_len, size_t value_len);


/**
 * Deletes an element from hash map with given key.
 *
 * @param self Pointer to this map
 * @param key key of the variable to be deleted.

 * @return if deletion operation is success it returns 1, otherwise it returns 0.
 */
int rtw_hmap_del(rtw_hmap *self, void *key);

/**
 * Finds the element with given key from 'self' and writes it to 'out_value'.
 *
 * @param self Pointer to this map
 * @param key  Pointer to the key
 * @param out_value  Pointer to the output data
 *
 * @return 1 if element found and out_value has been written with that value, 0 otherwise.
 */
int rtw_hmap_get(rtw_hmap *self, void *key, void *out_value);

/**
 * Adds the data pointed by 'data' with 'key' to the map.
 *
 * @param self Pointer to this map.
 * @param key Pointer to key that data will be inserted.
 * @param data Pointer to data that will be inserted.
 *
 */
void rtw_hmap_insert(rtw_hmap *self, void *key, void *data);

/**
 * Frees allocated memory for this map.
 *
 * @param self  Pointer to this map.
 *
 */
void rtw_hmap_free(rtw_hmap *self);
