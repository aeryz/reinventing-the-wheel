#include "priority_queue.h"
#include "assert.h"

int randint(int n) {
  if ((n - 1) == RAND_MAX) {
    return rand();
  } else {

    assert (n <= RAND_MAX);

    int end = RAND_MAX / n;
    assert (end > 0);
    end *= n;
    
    int r;
    while ((r = rand()) >= end);

    return r % n;
  }
}


typedef struct {
    int data;
    int priority;
} datas;

int personal_comp_func_datas(const void *lhs, const void *rhs){
    datas *d_lhs = (datas *) lhs;
    datas *d_rhs = (datas *) rhs;
    
    int left = d_lhs->priority;
    int right = d_rhs->priority;

    if(left > right)
    {
        return 1;
    }
    else if(left < right)
    {
        return -1;
    }
    return 0;
}

int personal_comp_func_int(const void *lhs, const void *rhs){
    int left = *(int*)lhs;
    int right = *(int*)rhs;

    if(left > right)
    {
        return 1;
    }
    else if(left < right)
    {
        return -1;
    }
    return 0;
}

int main()
{
    printf("----------priority queue with struct value----------\n\n");
    rtw_priority_queue queue_with_struct = rtw_priority_queue_init(sizeof(datas), &personal_comp_func_datas);

    for(int i = 0; i < 15; i++){
        int data = randint(13);
        int priority = randint(10);
        datas d;
        d.data = data;
        d.priority = priority;
        rtw_priority_queue_push(&queue_with_struct, &d);
    }

    for(int i = 0; i < queue_with_struct.vec.len; i++){
        datas *d = (datas *)rtw_vec_get(&queue_with_struct, i);
        printf("queue_with_struct data:%d, priority:%d\n", d->data, d->priority);
    }

    printf("size of queue_with_struct :%d\n\n", rtw_priority_queue_size(&queue_with_struct));

    datas top_val_struct;

    rtw_priority_queue_top(&queue_with_struct, &top_val_struct);
    

    printf("queue_with_struct top_val: %d, priority:%d\n\n", top_val_struct.data, top_val_struct.priority);
    
    printf("size of queue_with_struct :%d\n", rtw_priority_queue_size(&queue_with_struct));







    printf("\n\n\n----------priority queue with int value----------\n\n\n\n");
    rtw_priority_queue queue_with_int = rtw_priority_queue_init(sizeof(int), &personal_comp_func_int);

    for(int i = 0; i < 15; i++){
        int data = randint(13);
        
        rtw_priority_queue_push(&queue_with_int, &data);
    }

    for(int i = 0; i < queue_with_int.vec.len; i++){
        int d = *(int *)rtw_vec_get(&queue_with_int, i);
        printf("queue_with_int data:%d\n", d);
    }

    printf("size of queue_with_int :%d\n\n", rtw_priority_queue_size(&queue_with_int));

    int top_val_int;

    rtw_priority_queue_top(&queue_with_int, &top_val_int);
    

    printf("queue_with_int top_val: %d\n\n", top_val_int);
    
    printf("size of queue_with_int :%d\n", rtw_priority_queue_size(&queue_with_int));

}