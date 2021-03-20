#include "binary_set.h"

int personal_comp_func_int(const int lhs, const int rhs){
    if(lhs < rhs)
        return -1;
    else if(lhs > rhs)
        return 1;
    return 0;
}

int main()
{
    int (*my_comp_func_int)(const int, const int);
    my_comp_func_int = &personal_comp_func_int;

    struct BinarySet *set = binary_set_init(my_comp_func_int);
    
    insert(set,12);
    insert(set,12);
    
    insert(set,4);
    
    insert(set,13);
    
    insert(set,14);
    insert(set,9);
    insert(set,13);
    
    insert(set,14);
    insert(set,9);
    
    if(search(set,12))
        printf("12 exists\n");
    if(search(set,3))
        printf("3 exists\n");
    if(search(set,12))
        printf("12 exists\n");
    if(search(set,13))
        printf("13 exists\n");
    if(search(set,17))
        printf("17 exists\n");
    if(search(set,14))
        printf("14 exists\n");


    free_set(set);
    return 0;
}
 