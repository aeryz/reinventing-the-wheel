#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    void *data;
    size_t len;
    size_t capacity;
    size_t elem_len;
} rtw_vec;

/**
 * Creates an empty vector without any allocation
 *
 * @param elem_len Size of the data unit that the vector holds
 */
rtw_vec rtw_vec_init(size_t elem_len);

/**
 * Creates an empty vector by allocating 'capacity' * 'elem_len' bytes.
 *
 * @param vector   Pointer to output vector
 * @param capacity Count of the element capacity
 * @param elem_len Size of the data unit that the vector holds
 *
 * @return 0 on success, -1 on error
 */
int rtw_vec_with_capacity(rtw_vec *vector, size_t capacity, size_t elem_len);

/**
 * Adds the data pointed by 'data' to end of the vector.
 *
 * If the capacity is exhausted, the vector will double its size and copy its
 * items to the new location.
 *
 * @param self Pointer to this vector.
 * @param data Pointer to data that will be inserted.
 *
 * @return 0 on success, -1 on error
 */
int rtw_vec_push_back(rtw_vec *self, const void *data);

/**
 * Pops the last item from 'self' and writes it to 'out'.
 *
 * @param self Pointer to this vector
 * @param out  Pointer to the output data
 *
 * @return -1 if 'self' is empty, otherwise 0
 */
int rtw_vec_pop_back(rtw_vec *self, void *out);

/**
 * Returns a pointer to the element at 'index'.
 *
 * @param self  Pointer to this vector.
 * @param index Index of the element.
 *
 * @return NULL if 'index' is out of bounds
 */
void *rtw_vec_get(rtw_vec *self, const size_t index);

/**
 * Reserves enough memory to hold 'len' elements.
 *
 * If 'len' is smaller than the current capacity, the function does nothing.
 * Otherwise, it re-allocates the memory to hold exactly 'len' elements.
 *
 * @param self  Pointer to this vector.
 * @param count Count of the element capacity.
 *
 * @return 0 on success, -1 on error.
 */
int rtw_vec_reserve(rtw_vec *self, const size_t count);

/**
 * Shrinks the allocation to be able to hold exactly the amount of elements that
 * the vector currently contains.
 *
 * This function re-allocates the memory if it is needed (in most cases it is).
 *
 * @param self Pointer to this vector.
 *
 * @return 0 on success, -1 on error.
 */
int rtw_vec_shrink(rtw_vec *self);

/**
 * Pushes back 'count' elements starting from 'elems' pointer
 *
 * @param self  Pointer to this vector.
 * @param elems Pointer to the beginning of the elements to add.
 * @param count Count of elements to be added.
 *
 * @return 0 on success, -1 on error.
 */
int rtw_vec_insert(rtw_vec *self, const void *elems, size_t count);

/**
 * Concatenates the 'other's data with 'self'.
 *
 * This function may require re-allocation if the capacity is exhausted.
 *
 * @param self  Pointer to this vector.
 * @param other Pointer to the vector to be concatenated to 'self'.
 *
 * @return 0 on success, -1 on error.
 */
int rtw_vec_extend(rtw_vec *self, const rtw_vec *other);

/**
 * Clears the data of the vector.
 *
 * If 'shred' is false, the function just sets the length to zero. Otherwise the
 * allocated memory is overwritten with 0.
 *
 * @param self  Pointer to this vector.
 * @param shred Indicator to overwrite the allocated memory of the vector or
 * not.
 *
 * @return 0 on success,
 */
void rtw_vec_clear(rtw_vec *self, unsigned shred);

/**
 * Returns a pointer to the inner data.
 *
 * @param self Pointer to this vector.
 *
 * @return Pointer to the inner data.
 */
void *rtw_vec_data(rtw_vec *self);

/**
 * Sorts the array in ascending order with quick sort approach
 *
 * @param self Pointer to this vector
 * @param cmp_fn Is function pointer to sort our array, comparasion function.
 *      It takes 2 parameters, left hand side and right hand side.
 *      It returns -1 if right hand side is greater than left hand side
 *      It returns 1 if right hand side is smaller than left hand side
 *      It returns 0 if two value is same.
 *
 * @return -1 if 'self' is empty, otherwise 0
 */
int rtw_vec_sort(rtw_vec *self, int (*cmp_fn)(const void *, const void *));

/**
 * Retuns the pointer to the last element.
 *
 * @param self Pointer to this vector
 *
 * @return if size is 0, returns NULL otherwise pointer to the last element i
 */

void *rtw_vec_last(rtw_vec *self);


/**
 * Deletes an element with given index.
 *
 * @param self Pointer to this vector
 * @param index Index of the element to be deleted
 * @return if deletion operation is success it returns 1, otherwise it returns 0.
 */
int rtw_vec_delete_index(rtw_vec *self, const size_t index);


/**
 * Deletes an element with given data.
 *
 * @param self Pointer to this vector
 * @param data Data of the variable to be deleted.
 * @param cmp_fn Is function pointer to compare datas. It should return 1 if datas are same, otherwise 0. 
 * @return if deletion operation is success it returns 1, otherwise it returns 0.
 */
int rtw_vec_delete_data(rtw_vec *self, const void *data, int (*cmp_fn)(const void *, const void *));