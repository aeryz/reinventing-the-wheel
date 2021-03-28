#include "../hset/rtw_hset.h"

// This is hash_fun to get hash value of given key, in first example our key is
// char* so we are casting void * type to char *, at the end of function we are
// taking modular 30 because our bucket size is 30. So our key should be between
// 0-29.

unsigned long hash_func(const void *key) {
    char *my_key = (char *)key;

    unsigned long hash = 5381;
    int c;

    while ((c = *my_key++))
        hash = ((hash << 5) + hash) + c;

    return hash;
}

// This is a cmp_fun to identify if two strings are same or not.
// We will use this function when we try to push - get something from our set.
// If our key is char*(string) then we have to compare keys inorder to push to
// set or get from set.
int cmp_fun_str(const void *lhs, const void *rhs) {
    return strcmp((char *)lhs, (char *)rhs) == 0;
}

void example_set_int() {
    // in this example we will use our hashset like
    // std::set<int> so our data is integer

    // we have to create our hash set object with rtw_hset_init function.
    // It takes 3 parameter, first one is predefined hash_func,
    // Second one is our predefined comparasion function
    // third one is sizeof our object (in this case its sizeof(int))
    rtw_hset set = rtw_hset_init(&hash_func, &cmp_fun_str, sizeof(int));

    int data1 = 5;
    int data2 = 6;
    int data3 = 12;

    // To push pairs into our hash set our function is "rtw_hset_insert", it
    // takes 2 parameter. First one is address of our set, second one is our data
    rtw_hset_insert(&set, &data1);
    rtw_hset_insert(&set, &data2);
    rtw_hset_insert(&set, &data3);

    // Now lets try to find our data. To do that our function is
    // "rtw_hset_find", it takes 2 arg. First one is address of our set, second
    // one is our data. If thereis value
    // with given data it returns 1 otherwise it returns 0.

    if (rtw_hset_find(&set, &data1))
        printf("%d exists in hashet.\n", data1);
    else
        printf("data: %d couldn't found!\n", data1);

    if (rtw_hset_find(&set, &data2))
        printf("%d exists in hashset.\n", data2);
    else
        printf("data: %d couldn't found!\n", data2);

    // This is a data which we do not have in our hset.
    int data4 = 56;

    if (rtw_hset_find(&set, &data4))
        printf("%d exists in hashset.\n", data4);
    else
        printf("key: '%d' couldn't found!\n", data4);

    // Now lets try to access our data3 and delete it from hset.
    if (rtw_hset_find(&set, &data3))
        printf("%d exists in hashset.\n", data3);
    else
        printf("data: %d couldn't found!\n", data3);

    // Our data3 is in hset, so now lets try to delete it.
    if (rtw_hset_del(&set, &data3))
        printf("data: %d deleted from hset.\n", data3);
    else
        printf("data: %d does not exist on hset.\n", data3);

    // We have deleted data3 already from set, lets try to delete it again.
    if (rtw_hset_del(&set, &data3))
        printf("data: %d deleted from hset.\n", data3);
    else
        printf("data: %d does not exist on hset.\n", data3);
    

    rtw_hset_free(&set);
}
int main() {
    
    printf("---- example of str as key ----\n");
    example_set_int();

}
