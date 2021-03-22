#include "../priority_queue/rtw_priority_queue.h"
#include "assert.h"

typedef struct {
    int data;
    int priority;
} example_struct;

//This is a comp_fn, to push variables into our priority queue we need to
//define a comparasion function to identify how we compare our datas.
//In this example we will use "example_struct" struct for data.
//This comparasion function takes 2 const void * value and compares left hand side
//with right hand side. If left side is greater we should return 1
//If left side is smaller then we should return -1, if they are equal we should return 0.
int cmp_fun_struct(const void *lhs, const void *rhs){
    example_struct *d_lhs = (example_struct *) lhs;
    example_struct *d_rhs = (example_struct *) rhs;
    
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

void example_struct_fun(){
    //we have to create our queue object with rtw_priority_queue_init function.
    //It takes 2 parameter, first one is sizeof our object (in this case its sizeof(example_struct))
    //Second one is our predefined comparasion function
    rtw_priority_queue queue = rtw_priority_queue_init(sizeof(example_struct), &cmp_fun_struct);

    //Lets assume that we have 3 struct element and we want to push them to our queue.
    example_struct elem1;
    elem1.data = 5;
    elem1.priority = 4;

    example_struct elem2;
    elem2.data = 3;
    elem2.priority=4;

    example_struct elem3;
    elem3.data = 6;
    elem3.priority = 9;

    //To push object we are using rtw_priority_queue_push function.
    //It takes 2 argument, first one is address of our queue and second one is address of our data.
    //While pushing they are added to our queue with priorities ascending order 
    //with the help of the function that we write before.
    rtw_priority_queue_push(&queue, &elem1);
    rtw_priority_queue_push(&queue, &elem2);
    rtw_priority_queue_push(&queue, &elem3);


    //To get size of the queue we are using rtw_priority_queue_size
    int queue_size = rtw_priority_queue_size(&queue);

    //Lets pop them and print value and priority
    //Output will be:
    
    //1) data: 6, priority: 9
    //2) data: 3, priority: 4
    //3) data: 5, priority: 4
    for(int i = 0; i < queue_size; i++){
        example_struct elem;
        rtw_priority_queue_top(&queue, &elem);
        printf("%d) data: %d, priority: %d\n",i+1,elem.data, elem.priority);
    }

    //This function shrinks the allocations.
    rtw_priority_queue_shrink(&queue);
}   


//This is an comp_fn like cmp_fun_struct, difference is we just want to save
//integers in our queue instead of struct, so we need different comparasion function.
int cmp_fun_int(const void *lhs, const void *rhs){
    
    int left  = *(int*)lhs;
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

void example_int_fun(){
    //we have to create our queue object with rtw_priority_queue_init function.
    //It takes 2 parameter, first one is sizeof our object (in this case its sizeof(int))
    //Second one is our predefined comparasion function
    rtw_priority_queue queue = rtw_priority_queue_init(sizeof(int), &cmp_fun_int);

    //Lets assume that we have 3 integer and we want to push them to our queue.
    int elem1 = 5;
    int elem2 = 6;
    int elem3 = 7;

    //To push object we are using rtw_priority_queue_push function.
    //It takes 2 argument, first one is address of our queue and second one is address of our data.
    //While pushing they are added to our queue with priorities ascending order 
    //with the help of the function that we write before.
    rtw_priority_queue_push(&queue, &elem1);
    rtw_priority_queue_push(&queue, &elem2);
    rtw_priority_queue_push(&queue, &elem3);

    //To get size of the queue we are using rtw_priority_queue_size
    int queue_size = rtw_priority_queue_size(&queue);

    //Lets pop them and print value and priority
    //Output will be:
    
    //1) data: 7
    //2) data: 6
    //3) data: 5
    for(int i = 0; i < queue_size; i++){
        int elem;
        rtw_priority_queue_top(&queue, &elem);
        printf("%d) data: %d \n",i+1,elem);
    }

    //This function shrinks the allocations.
    rtw_priority_queue_shrink(&queue);
}

int main(){
    printf("---- example to hold struct in queue ----\n");
    example_struct_fun();
    printf("\n\n---- example to hold int in queue ----\n");
    example_int_fun();
}