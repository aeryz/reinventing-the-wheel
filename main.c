#include "str/rtw_str.h"
#include "vec/rtw_vec.h"
#include <stdio.h>
#include <unistd.h>

void bench_heap() {
    rtw_str s1 = rtw_str_new_heap("seleme");
    rtw_str s2 = rtw_str_new_heap(" aleme");

    rtw_str_concat_heap(&s1, &s2);
}

void bench_stack() {
    rtw_str s1, s2;
    rtw_str_from("seleme", &s1);
    rtw_str_from(" aleme", &s2);

    rtw_str_concat(&s1, &s2);
}

int main() {
    for (int i = 0; i < 9999999; ++i)
        bench_stack();

    sleep(1000);
}
