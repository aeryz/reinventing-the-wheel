#include "../hmap/rtw_hmap.h"

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
// We will use this function when we try to push - get something from our map.
// If our key is char*(string) then we have to compare keys inorder to push to
// map or get from map.
int cmp_fun_str(const void *lhs, const void *rhs) {
    return strcmp((char *)lhs, (char *)rhs) == 0;
}

void example_str_to_int_fun() {
    // in this example we will use our hashmap like
    // std::unordered_map<std::string,int> so our key is char*, our value is
    // integer.

    // we have to create our hash map object with rtw_hmap_init function.
    // It takes 3 parameter, first one is predefined hash_func,
    // Second one is our predefined comparasion function
    // third one is sizeof our object (in this case its sizeof(int))
    rtw_hmap map = rtw_hmap_init(&hash_func, &cmp_fun_str, sizeof(char*) ,sizeof(int));

    // Lets create 3 key - value pairs.
    char *key1 = "key1";
    char *key2 = "key2";
    char *key3 = "key3";

    int data1 = 5;
    int data2 = 6;
    int data3 = 12;

    // To push pairs into our hash map our function is "rtw_hmap_insert", it
    // takes 3 parameter. First one is address of our map, second one is our key
    // and third one is address of our data.
    rtw_hmap_insert(&map, key1, &data1);
    rtw_hmap_insert(&map, key2, &data2);
    rtw_hmap_insert(&map, key3, &data3);

    // Now lets try to get our data by using keys. To do that our function is
    // "rtw_hmap_get", it takes 3 arg. First one is address of our map, second
    // one is our key and third one is address of our out data. If thereis value
    // with given key it returns 1 otherwise it returns 0.
    int out_data1;
    int out_data2;
    int out_data3;

    if (rtw_hmap_get(&map, key1, &out_data1))
        printf("map[%s]:%d\n", key1, out_data1);
    else
        printf("key: %s couldn't found!\n", key1);

    if (rtw_hmap_get(&map, key2, &out_data2))
        printf("map[%s]:%d\n", key2, out_data2);
    else
        printf("key: %s couldn't found!\n", key2);

    // This is a key which we do not have in our hmap.
    char *key4 = "not_valid_key";
    int out_data4;
    if (rtw_hmap_get(&map, key4, &out_data4))
        printf("map[%s]:%d\n", key4, out_data4);
    else
        printf("key: '%s' couldn't found!\n", key4);

    // Now lets try to access our key3 and delete it from hmap.
    if (rtw_hmap_get(&map, key3, &out_data3))
        printf("map[%s]:%d\n", key3, out_data3);
    else
        printf("key: %s couldn't found!\n", key3);

    // Our key3 is in hmap, so now lets try to delete it.
    if (rtw_hmap_del(&map, key3))
        printf("key: %s deleted from hmap.\n", key3);
    else
        printf("key: %s does not exist on hmap.\n", key3);

    // We have deleted key3 already from map, lets try to delete it again.
    if (rtw_hmap_del(&map, key3))
        printf("key: %s deleted from hmap.\n", key3);
    else
        printf("key: %s does not exist on hmap.\n", key3);
    
    // So since key does not exist on map, rtw_hmap_del returned 0.
    // To update key-value pair we just have to use insert function with
    // different value.
    if (rtw_hmap_get(&map, key2, &out_data2))
        printf("map[%s]:%d\n", key2, out_data2);
    else
        printf("key: %s couldn't found!\n", key2);
    // Our key2 still do have same value. To change it lets use insert function.
    int new_data = 12;
    rtw_hmap_insert(&map, key2, &new_data);

    // Lets print it again.
    if (rtw_hmap_get(&map, key2, &out_data2))
        printf("map[%s]:%d\n", key2, out_data2);
    else
        printf("key: %s couldn't found!\n", key2);

    // Now key2 value changed with new_data.
    rtw_hmap_free(&map);
}

// Now lets use struct as key.
typedef struct {
    int width;
    int height;
} Square;

// SO our key will be square object, to compare functions lets compare both
// height and width of square.
int comp_fun_struct(const void *lhs, const void *rhs) {
    Square *s1 = (Square *)lhs;
    Square *s2 = (Square *)rhs;
    return s1->height == s2->height && s1->width == s2->width;
}

// And for hash function lets take %30 of width.
unsigned long hash_fun_struct(const void *key) {
    Square *s = (Square *)key;
    return s->width;
}

void example_struct_to_int_fun() {
    // I will do exactly same thing with just changing key to struct.

    // our value is still int so third parameter is stll sizeof(int)
    rtw_hmap map =
        rtw_hmap_init(&hash_fun_struct, &comp_fun_struct, sizeof(Square), sizeof(int));

    // Lets create 3 key - value pairs.
    Square s1;
    s1.width = 4;
    s1.height = 5;

    Square s2;
    s2.width = 34;
    s2.height = 13;

    Square s3;
    s3.width = 5;
    s3.height = 4;

    int data1 = 5;
    int data2 = 6;
    int data3 = 12;

    // To push pairs into our hash map our function is "rtw_hmap_insert", it
    // takes 3 parameter. First one is address of our map, second one is our key
    // and third one is address of our data.
    rtw_hmap_insert(&map, &s1, &data1);
    rtw_hmap_insert(&map, &s2, &data2);
    rtw_hmap_insert(&map, &s3, &data3);

    // Now lets try to get our data by using keys. To do that our function is
    // "rtw_hmap_get", it takes 3 arg. First one is address of our map, second
    // one is our key and third one is address of our out data. If thereis value
    // with given key it returns 1 otherwise it returns 0.
    int out_data1;
    int out_data2;
    int out_data3;

    if (rtw_hmap_get(&map, &s1, &out_data1))
        printf("map[(Square)->width:%d, (Square)->height:%d]:%d\n", s1.width,
               s1.height, out_data1);
    else
        printf(
            "key: '(Square)->width:%d, (Square)->height:%d' couldn't found!\n",
            s1.width, s1.height);

    if (rtw_hmap_get(&map, &s2, &out_data2))
        printf("map[(Square)->width:%d, (Square)->height:%d]:%d\n", s2.width,
               s2.height, out_data2);
    else
        printf(
            "key: '(Square)->width:%d, (Square)->height:%d' couldn't found!\n",
            s2.width, s2.height);

    // This is a key which we do not have in our hmap.
    Square s4;
    s4.height = 13;
    s4.width = 4;

    int out_data4;
    if (rtw_hmap_get(&map, &s4, &out_data4))
        printf("map[(Square)->width:%d, (Square)->height:%d]:%d\n", s4.width,
               s4.height, out_data4);
    else
        printf(
            "key: '(Square)->width:%d, (Square)->height:%d' couldn't found!\n",
            s4.width, s4.height);

    // Now lets try to access our key3 and delete it from hmap.
    if (rtw_hmap_get(&map, &s3, &out_data3))
        printf("map[(Square)->width:%d, (Square)->height:%d]:%d\n", s3.width,
               s3.height, out_data3);
    else
        printf(
            "key: '(Square)->width:%d, (Square)->height:%d' couldn't found!\n",
            s3.width, s3.height);
    
    // Our key3 is in hmap, so now lets try to delete it.
    if (rtw_hmap_del(&map, &s3))
        printf(
            "key: (Square)->width:%d, (Square)->height:%d deleted from hmap.\n",
            s3.width, s3.height);
    else
        printf("key: (Square)->width:%d, (Square)->height:%d does not exist on "
               "hmap.\n",
               s3.width, s3.height);
    
    // We have deleted key3 already from map, lets try to delete it again.
    if (rtw_hmap_del(&map, &s3))
        printf("map[(Square)->width:%d, (Square)->height:%d]:%d\n", s3.width,
               s3.height, out_data3);
    else
        printf(
            "key: '(Square)->width:%d, (Square)->height:%d' couldn't found!\n",
            s3.width, s3.height);

    // So since key does not exist on map, rtw_hmap_del returned 0.
    // To update key-value pair we just have to use insert function with
    // different value.
    if (rtw_hmap_get(&map, &s2, &out_data2))
        printf("map[(Square)->width:%d, (Square)->height:%d]:%d\n", s2.width,
               s2.height, out_data2);
    else
        printf(
            "key: '(Square)->width:%d, (Square)->height:%d' couldn't found!\n",
            s2.width, s2.height);
    // Our key2 still do have same value. To change it lets use insert function.
    int new_data = 12;
    rtw_hmap_insert(&map, &s2, &new_data);

    // Lets print it again.
    if (rtw_hmap_get(&map, &s2, &out_data2))
        printf("map[(Square)->width:%d, (Square)->height:%d]:%d\n", s2.width,
               s2.height, out_data2);
    else
        printf(
            "key: '(Square)->width:%d, (Square)->height:%d' couldn't found!\n",
            s2.width, s2.height);

    // Now key2 value changed with new_data.

    rtw_hmap_free(&map);
}

int com_fun_int(const void *lhs, const void *rhs) {
    
    return *(int*)lhs == *(int*)rhs;
}

// And for hash function lets take %30 of width.
unsigned long hash_fun_int(const void *key) {
    return *(int *)key%30;
}


int main() {
    
    printf("---- example of str as key ----\n");
    example_str_to_int_fun();
    printf("\n\n---- example struct as key ----\n");
    example_struct_to_int_fun();
    
    
    rtw_hmap map = rtw_hmap_init(&hash_fun_int, &com_fun_int, sizeof(int), sizeof(int));
    int key = 3;
    int val = 5;
    rtw_hmap_insert(&map, &key, &val);
    
    int out;
    rtw_hmap_get(&map, &key, &out);
    printf("out :%d\n",out);
    int key1 = 4;
    int val1 = 12;
    rtw_hmap_insert(&map, &key1, &val1);
    int out1;
    rtw_hmap_get(&map, &key1, &out1);
    printf("out :%d\n",out1);

    

    int key2 = 33;
    int val2 = 24;
    rtw_hmap_insert(&map, &key2, &val2);
    int out2;
    rtw_hmap_get(&map, &key2, &out2);
    printf("out :%d\n",out2);

    int key4 = 3;
    int val4 = 53;
    rtw_hmap_insert(&map, &key4, &val4);
    int out4;
    rtw_hmap_get(&map, &key4, &out4);
    printf("out :%d\n",out4);


    rtw_hmap_get(&map, &key1, &out1);
    printf("out :%d\n",out1);
    rtw_hmap_free(&map);
    
    
}
