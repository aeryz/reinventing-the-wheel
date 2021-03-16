#include "map.h"
#include<stdio.h>

int personal_comp_func_charptr(const char* lhs, const char* rhs){
    return strcmp(lhs,rhs) == 0;
}

int personal_comp_func_int(const int lhs, const int rhs){
    return lhs == rhs;
}

int personal_hash_func_charptr(const char *key)
{
    
    int index = -1;
    for(int i = 0; i < strlen(key); i++)
    {
        index += key[i];
    }
    return index % 30;
}

int personal_hash_func_int(const int key)
{
    return key % 30;
}

void test_map_str_to_int(struct HashMap* map_str_to_int)
{
    insert_key(map_str_to_int, "abf",1);
    insert_key(map_str_to_int, "acd",2);
    insert_key(map_str_to_int, "asdasd",3);
    insert_key(map_str_to_int, "kaan",4);
    insert_key(map_str_to_int, "map_str_to_int",5);

    int data = (int)search_key(map_str_to_int, "xasxasxa");
    if(data != NULL)
    {
        printf("\t(search_key) key: xasxasxa, data: %d\n",data);
        exit(1);
    }

    int data2 = (int)search_key(map_str_to_int, "map_str_to_int");
    if(data2 != NULL)
    {
        if(data2 != 5)
        {
            printf("TEST FAILED\n");
            exit(1);
        }
    }
    else
    {
        printf("(search_key) key: map_str_to_int couldn't find!\n");
        printf("TEST FAILED\n");
        exit(1);
    }

    int data3 = (int)search_key(map_str_to_int, "kaan");
    if(data3 != NULL)
    {
        if(data3 != 4)
        {
            printf("TEST FAILED\n");
            exit(1);
        }
    }
    else
    {
        printf("(search_key) key: kaan couldn't find!\n");
        printf("TEST FAILED\n");
        exit(1);
    }

    if(delete_key(map_str_to_int, "asdasdasd"))
    {
        printf("asdasdasd deleted from map.");
        printf("TEST FAILED\n");
        exit(1);
    }
    

    if(delete_key(map_str_to_int, "kaan"))
    {
        data3 = (int)search_key(map_str_to_int, "kaan");
        if(data3 != NULL)
        {
            printf("kaan couldn't delete from map.");
            printf("TEST FAILED\n");
            exit(1);
        }
    }
    else
    {
        printf("kaan couldn't delete from map.");
        printf("TEST FAILED\n");
        exit(1);
    }
}

void test_map_str_to_str(struct HashMap* map_str_to_str)
{
    insert_key(map_str_to_str, "abf","1a");
    insert_key(map_str_to_str, "acd","2a");
    insert_key(map_str_to_str, "asdasd","3a");
    insert_key(map_str_to_str, "kaan","4a");
    insert_key(map_str_to_str, "map_str_to_int","5a");

    char* data = (char *)search_key(map_str_to_str, "xasxasxa");
    if(data != NULL)
    {
        printf("\t(search_key) key: xasxasxa, data: %s\n",data);
        printf("TEST FAILED\n");
        exit(1);
    }

    char* data2 = (char *)search_key(map_str_to_str, "map_str_to_int");
    if(data2 != NULL)
    {
        if(strcmp(data2,"5a") != 0)
        {
            printf("TEST FAILED\n");
            exit(1);
        }
    }
    else
    {
        printf("(search_key) key: map_str_to_int couldn't find!\n");
        printf("TEST FAILED\n");
        exit(1);
    }

    char * data3 = (char *)search_key(map_str_to_str, "kaan");
    if(data3 != NULL)
    {
        if(strcmp(data3,"4a") != 0)
        {
            printf("TEST FAILED\n");
            exit(1);
        }
    }
    else
    {
        printf("(search_key) key: kaan couldn't find!\n");
        printf("TEST FAILED\n");
        exit(1);
    }

    if(delete_key(map_str_to_str, "asdasdasd"))
    {
        printf("asdasdasd deleted from map.");
        printf("TEST FAILED\n");
        exit(1);
    }
    

    if(delete_key(map_str_to_str, "kaan"))
    {
        data3 = (char *)search_key(map_str_to_str, "kaan");
        if(data3 != NULL)
        {
            printf("kaan couldn't delete from map.");
            printf("TEST FAILED\n");
            exit(1);
        }
    }
    else
    {
        printf("kaan couldn't delete from map.");
        printf("TEST FAILED\n");
        exit(1);
    }
}

void test_map_int_to_str(struct HashMap* map_int_to_str)
{
    insert_key(map_int_to_str, 1,"1a");
    insert_key(map_int_to_str, 2,"2a");
    insert_key(map_int_to_str, 3,"3a");
    insert_key(map_int_to_str, 4,"4a");
    insert_key(map_int_to_str, 5,"5a");

    char* data = (char *)search_key(map_int_to_str, 6);
    if(data != NULL)
    {
        printf("\t(search_key) key: 6, data: %s\n",data);
        printf("TEST FAILED\n");
        exit(1);
    }

    char* data2 = (char *)search_key(map_int_to_str, 5);
    if(data2 != NULL)
    {
        if(strcmp(data2,"5a") != 0)
        {
            printf("TEST FAILED\n");
            exit(1);
        }
    }
    else
    {
        printf("(search_key) key: 5 couldn't find!\n");
        printf("TEST FAILED\n");
        exit(1);
    }

    char * data3 = (char *)search_key(map_int_to_str, 4);
    if(data3 != NULL)
    {
        if(strcmp(data3,"4a") != 0)
        {
            printf("TEST FAILED\n");
            exit(1);
        }
    }
    else
    {
        printf("(search_key) key: 4 couldn't find!\n");
        printf("TEST FAILED\n");
        exit(1);
    }

    if(delete_key(map_int_to_str, 12))
    {
        printf("12 deleted from map.");
        printf("TEST FAILED\n");
        exit(1);
    }
    
    if(delete_key(map_int_to_str, 2))
    {
        data3 = (char *)search_key(map_int_to_str, 2);
        if(data3 != NULL)
        {
            printf("2 couldn't delete from map.");
            printf("TEST FAILED\n");
            exit(1);
        }
    }
    else
    {
        printf("2 couldn't delete from map.");
        printf("TEST FAILED\n");
        exit(1);
    }
}

void test_map_int_to_int(struct HashMap* map_int_to_int)
{
    insert_key(map_int_to_int, 1,12);
    insert_key(map_int_to_int, 2,22);
    insert_key(map_int_to_int, 3,32);
    insert_key(map_int_to_int, 4,42);
    insert_key(map_int_to_int, 5,52);

    int data = (int)search_key(map_int_to_int, 6);
    if(data != NULL)
    {
        printf("\t(search_key) key: 6, data: %s\n",data);
        printf("TEST FAILED\n");
        exit(1);
    }

    int data2 = (int)search_key(map_int_to_int, 5);
    if(data2 != NULL)
    {
        if(data2 != 52)
        {
            printf("TEST FAILED\n");
            exit(1);
        }
    }
    else
    {
        printf("(search_key) key: 5 couldn't find!\n");
        printf("TEST FAILED\n");
        exit(1);
    }

    int data3 = (int)search_key(map_int_to_int, 4);
    if(data3 != NULL)
    {
        if(data3 != 42)
        {
            printf("TEST FAILED\n");
            exit(1);
        }
    }
    else
    {
        printf("(search_key) key: 4 couldn't find!\n");
        printf("TEST FAILED\n");
        exit(1);
    }

    if(delete_key(map_int_to_int, 12))
    {
        printf("12 deleted from map.");
        printf("TEST FAILED\n");
        exit(1);
    }
    
    if(delete_key(map_int_to_int, 2))
    {
        data3 = (int)search_key(map_int_to_int, 2);
        if(data3 != NULL)
        {
            printf("2 couldn't delete from map.");
            printf("TEST FAILED\n");
            exit(1);
        }
    }
    else
    {
        printf("2 couldn't delete from map.");
        printf("TEST FAILED\n");
        exit(1);
    }
}


int main() {
    
    int (*my_hash_func_charptr)(const char*);
    int (*my_comp_func_charptr)(const char*, const char*);
    my_hash_func_charptr = &personal_hash_func_charptr;
    my_comp_func_charptr = &personal_comp_func_charptr;

    int (*my_hash_func_int)(const int);
    int (*my_comp_func_int)(const int, const int);
    my_hash_func_int = &personal_hash_func_int;
    my_comp_func_int = &personal_comp_func_int;
    
    struct HashMap* map_str_to_int = hash_map_init(my_hash_func_charptr, my_comp_func_charptr);
    struct HashMap* map_str_to_str = hash_map_init(my_hash_func_charptr, my_comp_func_charptr);
    struct HashMap* map_int_to_str = hash_map_init(my_hash_func_int, my_comp_func_int);
    struct HashMap* map_int_to_int = hash_map_init(my_hash_func_int, my_comp_func_int);

    test_map_str_to_int(map_str_to_int);
    test_map_str_to_str(map_str_to_str);
    test_map_int_to_str(map_int_to_str);
    test_map_int_to_int(map_int_to_int);

    
    free_map(map_str_to_int);
    free_map(map_str_to_str);
    free_map(map_int_to_str);
    free_map(map_int_to_int);
    
    printf("ALL TEST CASES PASSED!\n");

    sleep(3);
}