#include "priority_queue.h"
#include "assert.h"

rtw_priority_queue rtw_priority_queue_init(size_t elem_len, int (*cmp_fn)(const void *, const void *)){
    rtw_priority_queue queue;

    assert(elem_len);
    rtw_vec vec;
    vec.data = NULL;
    vec.len = 0;
    vec.capacity = 0;
    vec.elem_len = elem_len;

    queue.vec = vec;
    queue.cmp_fn = cmp_fn;

    return queue;

}

int rtw_priority_queue_top(rtw_priority_queue *self, void *out){
    return rtw_vec_pop_back(&self->vec, out);
}

int rtw_priority_queue_empty(rtw_priority_queue *self){
    return self->vec.len == 0;
}

int rtw_priority_queue_size(rtw_priority_queue *self){
    return self->vec.len;
}

int rtw_priority_queue_push(rtw_priority_queue *self, const void *data){
    int res = rtw_vec_push_back(&self->vec, data);
    rtw_vec_sort(&self->vec, self->cmp_fn);
    return res;
}