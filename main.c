#include "str/rtw_str.h"
#include <stdio.h>

int main() {
    rtw_str str1;
    rtw_str str2;
    rtw_str_from("selameke", &str1);
    rtw_str_from("cool and very very very long strrrssss", &str2);
    rtw_str_debug(&str1);
    rtw_str_debug(&str2);
    rtw_str_concat(&str1, &str2);
    rtw_str_debug(&str1);
    rtw_str_concat(&str2, &str1);
    rtw_str_debug(&str2);
}
