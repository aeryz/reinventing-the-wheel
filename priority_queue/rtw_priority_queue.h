#include "../vec/rtw_vec.h"

typedef struct {
    rtw_vec vec;
    int (*cmp_fn)(const void *, const void *);
} rtw_priority_queue;

/**
 * Creates an empty priority queue without any allocation
 *
 * @param elem_len Size of the data unit that the vector inside priority queue holds
 * @param cmp_fn Is function pointer to sort our priority queue, comparasion function.
 *      It takes 2 parameters, left hand side and right hand side.
 *      It returns -1 if right hand side is greater than left hand side
 *      It returns 1 if right hand side is smaller than left hand side
 *      It returns 0 if two value is same.
 */
rtw_priority_queue rtw_priority_queue_init(size_t elem_len, int (*cmp_fn)(const void *, const void *));

/**
 * Pops the last item from 'self' and writes it to 'out'.
 *
 * @param self Pointer to this priority queue
 * @param out  Pointer to the output data
 *
 * @return -1 if 'self' is empty, otherwise 0
 */
int rtw_priority_queue_top(rtw_priority_queue *self, void *out);

/**
 * Function to detect if priority queue empty or not
 *
 * @param self Pointer to this priority queue
 *
 * @return 1 if priority queue is empty, otherwise 0
 */
int rtw_priority_queue_empty(rtw_priority_queue *self);


/**
 * Function to return priority queues size
 *
 * @param self Pointer to this priority queue
 *
 * @return Size of the priority queue
 */
int rtw_priority_queue_size(rtw_priority_queue *self);

/**
 * Adds the data pointed by 'data' to priority queue.
 *
 * @param self Pointer to this priority queue.
 * @param data Pointer to data that will be inserted.
 *
 * @return 0 on success, -1 on error
 */
int rtw_priority_queue_push(rtw_priority_queue *self, const void *data);