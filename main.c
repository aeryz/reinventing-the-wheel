#include "str/rtw_str.h"
#include "vec/rtw_vec.h"
#include <stdio.h>
#include <unistd.h>

typedef struct {
    int X;
    int Y;
    int Z;
} Vec3;

int main() {

    Vec3 v;
    v.X = 1;
    v.Y = 2;
    v.Z = 3;

    rtw_vec vec = rtw_vec_init(sizeof(Vec3));

    for (int i = 0; i < 10; ++i) {
        rtw_vec_push_back(&vec, &v);
    }

    ((Vec3 *)rtw_vec_get(&vec, vec.len - 1))->X = 25;
    Vec3 testV = *((Vec3 *)rtw_vec_get(&vec, vec.len - 1));
    testV.Z = 2323;
    rtw_vec_push_back(&vec, &testV);

    Vec3 *ptr = rtw_vec_data(&vec);
    for (int i = 0; i < vec.len; ++i) {
        ptr = rtw_vec_get(&vec, i);
        printf("Vec: %d %d %d\n", ptr->X, ptr->Y, ptr->Z);
    }

    Vec3 testZ;
    rtw_vec_pop_back(&vec, &testZ);

    printf("TEST Z: %d %d %d\n", testZ.X, testZ.Y, testZ.Z);
    for (int i = 0; i < vec.len; ++i) {
        ptr = rtw_vec_get(&vec, i);
        printf("Vec: %d %d %d\n", ptr->X, ptr->Y, ptr->Z);
    }

    return 0;
}
