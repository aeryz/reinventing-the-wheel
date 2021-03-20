#include "../bset/rtw_bset.h"

int personal_comp_func_int(const int lhs, const int rhs) {
    if (lhs < rhs)
        return -1;
    else if (lhs > rhs)
        return 1;
    return 0;
}

int main() {
    int (*my_comp_func_int)(const int, const int);
    my_comp_func_int = &personal_comp_func_int;

    rtw_bset set = rtw_bset_init(my_comp_func_int);

    rtw_bset_insert(&set, 12);
    rtw_bset_insert(&set, 12);

    rtw_bset_insert(&set, 4);

    rtw_bset_insert(&set, 13);

    rtw_bset_insert(&set, 14);
    rtw_bset_insert(&set, 9);
    rtw_bset_insert(&set, 13);

    rtw_bset_insert(&set, 14);
    rtw_bset_insert(&set, 9);

    if (rtw_bset_search(&set, 12))
        printf("12 exists\n");
    if (rtw_bset_search(&set, 3))
        printf("3 exists\n");
    if (rtw_bset_search(&set, 12))
        printf("12 exists\n");
    if (rtw_bset_search(&set, 13))
        printf("13 exists\n");
    if (rtw_bset_search(&set, 17))
        printf("17 exists\n");
    if (rtw_bset_search(&set, 14))
        printf("14 exists\n");

    rtw_bset_free(&set);
    return 0;
}
