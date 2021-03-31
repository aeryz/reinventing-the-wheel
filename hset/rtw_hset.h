#ifndef RTW_HSET_H
#define RTW_HSET_H

#include "../vec/rtw_vec.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define RTW_HSET_BUCKET_SIZE_ 30

typedef unsigned long (*rtw_hset_hash_fn)(const void *);
typedef int (*rtw_hset_eq_fn)(const void *, const void *);

typedef struct rtw_hset_elem_s_ {
    void *data;
    struct rtw_hset_elem_s_ *next;
} rtw_hset_elem_;

typedef struct {
    rtw_hset_hash_fn hash_fn;
    rtw_hset_eq_fn eq_fn;
    rtw_hset_elem_ *elements[RTW_HSET_BUCKET_SIZE_];
    rtw_vec data;
    size_t data_len;
} rtw_hset;

/**
 * Creates an empty binary set without any allocation
 *
 * @param cmp_fn Is function pointer to add our datas to hash set, comparasion
 * function. Help of this comp_fn we will know if incoming data exists in set or
 * not. It takes 2 parameters, left hand side and right hand side. It returns -1
 * if right hand side is greater than left hand side It returns 1 if right hand
 * side is smaller than left hand side It returns 0 if two value is same.
 * @param hash_fn Is function pointer to hash data, hash function.
 *      It takes only one void* parameter and get hash of that value.
 *      It returns a hash value with int.
 * @param data_len Size of the data that the vector holds
 */
rtw_hset rtw_hset_init(rtw_hset_hash_fn hash_fn, rtw_hset_eq_fn eq_fn,
                       size_t data_len);

/**
 * Deletes an element from hash set with given data.
 *
 * @param self Pointer to this set
 * @param data Pointer to the data

 * @return if deletion operation is success it returns 1, otherwise it returns 0.
 */
int rtw_hset_del(rtw_hset *self, const void *data);

/**
 * Finds the element with given data from 'self' .
 *
 * @param self Pointer to this set
 * @param data  Pointer to the data
 *
 * @return 1 if element found, 0 otherwise.
 */
int rtw_hset_find(const rtw_hset *self, const void *data);

/**
 * Adds the data pointed by 'data' to the set.
 *
 * @param self Pointer to this set.
 * @param data Pointer to data that will be inserted.
 *
 */
void rtw_hset_insert(rtw_hset *self, const void *data);

/**
 * Frees allocated memory for this set.
 *
 * @param self  Pointer to this set.
 *
 */
void rtw_hset_free(rtw_hset *self);

#endif
