#include "../bset/rtw_bset.h"

typedef struct {
    int width;
    int height;
} Square;

// Binary set needs a comparison function to compare the order of data. This
// function should be provided by the user. Functions behavior should be like
// this: If lhs > rhs:
//     return 1;
// If rhs > lhs:
//     return -1;
// If rhs == lhs:
//     return 0;
int cmp_fun_struct(const void *lhs, const void *rhs) {
    Square *d_lhs = (Square *)lhs;
    Square *d_rhs = (Square *)rhs;

    int left = d_lhs->height * d_lhs->width;
    int right = d_rhs->height * d_rhs->width;

    if (left > right) {
        return 1;
    } else if (left < right) {
        return -1;
    }
    return 0;
}

void example_struct_fun() {
    // we have to create our binary set object with rtw_bset_init function.
    // It takes 1 parameter which is our predefined comparasion function.
    rtw_bset set = rtw_bset_init(&cmp_fun_struct);

    // Lets assume that we have 4 struct element and we want to push them to our
    // queue.
    Square elem1;
    elem1.height = 5;
    elem1.width = 4;

    Square elem2;
    elem2.height = 3;
    elem2.width = 4;

    Square elem3;
    elem3.height = 6;
    elem3.width = 9;

    Square elem4;
    elem3.height = 6;
    elem3.width = 9;

    // To push object we are using rtw_bset_insert function.
    // It takes 2 argument, first one is address of our queue and second one is
    // address of our data. If data exists in our binary tree, that data does
    // not added to our tree.

    rtw_bset_insert(&set, &elem1);
    rtw_bset_insert(&set, &elem2);
    rtw_bset_insert(&set, &elem3);
    rtw_bset_insert(&set, &elem4);

    if (rtw_bset_search(&set, &elem4))
        printf("elem4 found\n");
    else
        printf("elem4 couldn't be found\n");

    // Never forget to free the bset.
    rtw_bset_free(&set);
}

int main() {
    example_struct_fun();
    return 0;
}
