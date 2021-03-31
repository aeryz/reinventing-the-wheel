#include "tim.h"
#include "../str/rtw_str.h"
#include <stdio.h>

const char *STACK_DATA = "stack_str";
const char *HEAP_DATA = "heap_str heap_str heap_str heap_str";
const char *SNH_DATA = "stack_strheap_str heap_str heap_str heap_str";

TIM_TEST(str_from) {
    rtw_str str;
    TIM_ASSERT_EQ(rtw_str_from(STACK_DATA, &str), 0);

    TIM_ASSERT_EQ(str.type, STACK_STR);
    TIM_ASSERT_EQ_STR(rtw_str_data(&str), STACK_DATA);
    TIM_ASSERT_EQ(rtw_str_len(&str), strlen(STACK_DATA));
    TIM_ASSERT_EQ(rtw_str_capacity(&str), sizeof(rtw_heap_str));

    rtw_str str2;
    TIM_ASSERT_EQ(rtw_str_from(HEAP_DATA, &str2), 0);

    TIM_ASSERT_EQ(str2.type, HEAP_STR);
    TIM_ASSERT_EQ_STR(rtw_str_data(&str2), HEAP_DATA);
    TIM_ASSERT_EQ(rtw_str_len(&str2), strlen(HEAP_DATA));
    TIM_ASSERT_EQ(rtw_str_capacity(&str2), rtw_str_len(&str2));

    TIM_TEST_SUCCESS();
}

TIM_TEST(str_concat) {
    rtw_str empty_str = rtw_str_new();

    rtw_str stack_str;
    TIM_ASSERT_EQ(rtw_str_from(STACK_DATA, &stack_str), 0);

    rtw_str heap_str;
    TIM_ASSERT_EQ(rtw_str_from(HEAP_DATA, &heap_str), 0);

    // 'empty_str' should be still a stack str.
    TIM_ASSERT_EQ(rtw_str_concat(&empty_str, &stack_str), 0);
    TIM_ASSERT_EQ(empty_str.type, STACK_STR);
    TIM_ASSERT_EQ(rtw_str_len(&empty_str), strlen(STACK_DATA));
    TIM_ASSERT_EQ_STR(rtw_str_data(&empty_str), STACK_DATA);

    // 'empty_strs should now be a heap str.
    TIM_ASSERT_EQ(rtw_str_concat(&empty_str, &heap_str), 0);
    TIM_ASSERT_EQ(empty_str.type, HEAP_STR);
    TIM_ASSERT_EQ(rtw_str_len(&empty_str), strlen(SNH_DATA));
    TIM_ASSERT_EQ_STR(rtw_str_data(&empty_str), SNH_DATA);

    TIM_TEST_SUCCESS();
}
