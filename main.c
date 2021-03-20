#include "str/rtw_str.h"
#include "vec/rtw_vec.h"
#include <stdio.h>
#include <unistd.h>

#include "assert.h"
typedef struct {
    int X;
    int Y;
    int Z;
} Vec3;

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

int personal_comp_func_int(const Vec3 *lhs, const Vec3 *rhs){
    int totalLHS = lhs->X + lhs->Y + lhs->Z;
    int totalRHS = rhs->X + rhs->Y + rhs->Z;
    if(totalLHS > totalRHS)
        return 1;
    else if(totalLHS < totalRHS)
        return -1;
    return 0;
}

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
    

    printf("----------TEST SORT FUNCTION----------\n");
    int (*my_comp_func_int)(const Vec3*, const Vec3*);
    my_comp_func_int = &personal_comp_func_int;
    
    Vec3 vectors[20];
    rtw_vec vec2 = rtw_vec_init(sizeof(Vec3));
    for(int i = 0; i < 20; i++)
    {
        vectors[i].X = randint(30);
        vectors[i].Y = randint(30);
        vectors[i].Z = randint(30);
        rtw_vec_push_back(&vec2, &vectors[i]);
    }
    
    
    rtw_vec_sort(&vec2, my_comp_func_int);

    for(int i = 0; i < 20; i++){
        Vec3 *res = (Vec3 *)rtw_vec_get(&vec2, i);
        printf("x:%d, y:%d, z:%d, total:%d\n", res->X, res->Y, res->Z, res->X+res->Y+res->Z);
    }
    return 0;
}

   