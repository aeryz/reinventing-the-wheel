#include "../hmap/rtw_hmap.h"
#include <stdio.h>

int personal_comp_func_charptr(const void *lhs, const void *rhs) {
    return strcmp(lhs, rhs) == 0;
}

int personal_hash_func_charptr(const void *key) {
    int index = -1;
    for (int i = 0; i < strlen(key); i++) {
        index += ((char *)key)[i];
    }
    return index % 30;
}

int personal_hash_func_int(const int key) { return key % 30; }

void test_map_str_to_int(rtw_hmap *map_str_to_int) {
    rtw_hmap_insert(map_str_to_int, "abf", (void *)1);
    rtw_hmap_insert(map_str_to_int, "acd", (void *)2);
    rtw_hmap_insert(map_str_to_int, "asdasd", (void *)3);
    rtw_hmap_insert(map_str_to_int, "kaan", (void *)5);
    rtw_hmap_insert(map_str_to_int, "kaan", (void *)4);
    rtw_hmap_insert(map_str_to_int, "map_str_to_int", (void *)5);

    int data;

    if (!rtw_hmap_get(map_str_to_int, "abf", &data, sizeof(data))) {
        printf("\t(search_key) key: xasxasxa, data: %d\n", data);
        exit(1);
    }

    if (!rtw_hmap_get(map_str_to_int, "map_str_to_int", &data, sizeof(data))) {
        if (data != 5) {
            printf("TEST FAILED\n");
            exit(1);
        }
    } else {
        printf("(search_key) key: map_str_to_int couldn't find!\n");
        printf("TEST FAILED\n");
        exit(1);
    }

    if (!rtw_hmap_get(map_str_to_int, "kaan", &data, sizeof(data))) {
        if (data != 4) {
            printf("TEST FAILED\n");
            exit(1);
        }
    } else {
        printf("(search_key) key: kaan couldn't find!\n");
        printf("TEST FAILED\n");
        exit(1);
    }

    if (rtw_hmap_del(map_str_to_int, "asdasdasd")) {
        printf("asdasdasd deleted from map.");
        printf("TEST FAILED\n");
        exit(1);
    }

    if (rtw_hmap_del(map_str_to_int, "kaan")) {
        if (!rtw_hmap_get(map_str_to_int, "kaan", &data, sizeof(data))) {
            printf("kaan couldn't delete from map.");
            printf("TEST FAILED\n");
            exit(1);
        }
    } else {
        printf("kaan couldn't delete from map.");
        printf("TEST FAILED\n");
        exit(1);
    }
}

int main() {

    int (*my_hash_func_charptr)(const void *);
    int (*my_comp_func_charptr)(const void *, const void *);
    my_hash_func_charptr = &personal_hash_func_charptr;
    my_comp_func_charptr = &personal_comp_func_charptr;

    rtw_hmap map_str_to_int =
        rtw_hmap_init(my_hash_func_charptr, my_comp_func_charptr);

    test_map_str_to_int(&map_str_to_int);

    rtw_hmap_free(&map_str_to_int);

    printf("ALL TEST CASES PASSED!\n");
}
