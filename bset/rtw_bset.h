#include <stdio.h>
#include <stdlib.h>

typedef int (*rtw_bset_cmp_fn)(const void *, const void *);

typedef struct rtw_bset_elem_s_ {
    void *data;
    struct rtw_bset_elem_s_ *left;
    struct rtw_bset_elem_s_ *right;
} rtw_bset_elem_;

typedef struct {
    rtw_bset_cmp_fn comp_func;
    rtw_bset_elem_ *element;
} rtw_bset;


/**
 * Creates an empty binary set without any allocation
 *
 * @param cmp_fn Is function pointer to add our datas to tree, comparasion function.
 *      It takes 2 parameters, left hand side and right hand side.
 *      It returns -1 if right hand side is greater than left hand side
 *      It returns 1 if right hand side is smaller than left hand side
 *      It returns 0 if two value is same.
 */
rtw_bset rtw_bset_init(rtw_bset_cmp_fn comp_func);

/**
 * Adds the data pointed by 'data' to end of the vector.
 *
 * If the capacity is exhausted, the vector will double its size and copy its
 * items to the new location.
 *
 * @param self Pointer to this binary set.
 * @param data Pointer to data that will be inserted to binary set.
 *
 */
void rtw_bset_insert(rtw_bset *self, void *data);

/**
 * Returns a pointer to the element at 'index'.
 *
 * @param self  Pointer to this vector.
 * @param data  Pointer to data that will be searched in binary set.
 *
 * @return 1 if given data is found, 0 otherwise.
 */
int rtw_bset_search(rtw_bset *self, void *elem);

/**
 * Frees allocated memory for this binary set.
 *
 * @param self  Pointer to this binary set.
 *
 */
void rtw_bset_free(rtw_bset *self);
