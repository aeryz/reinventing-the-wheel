#include "../str/rtw_str.h"
#include "tim.h"
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

TIM_TEST(str_reserve_len_shrink) {
    rtw_str str;

    TIM_ASSERT(rtw_str_from(STACK_DATA, &str) == 0);
    rtw_str_reserve(&str, 100);

    TIM_ASSERT_EQ(rtw_str_capacity(&str), 100);
    TIM_ASSERT_EQ(rtw_str_len(&str), strlen(STACK_DATA));

    TIM_ASSERT_EQ(rtw_str_shrink_to_fit(&str), 0);
    TIM_ASSERT_EQ(rtw_str_len(&str), strlen(STACK_DATA));
    TIM_ASSERT_EQ(rtw_str_capacity(&str), strlen(STACK_DATA) * sizeof(char));

    TIM_TEST_SUCCESS();
}

TIM_TEST(str_clear_empty_shrink) {
    rtw_str str = rtw_str_new();

    TIM_ASSERT_EQ(rtw_str_empty(&str), 1);
    TIM_ASSERT_EQ(rtw_str_from(HEAP_DATA, &str), 0);
    size_t capacity = rtw_str_capacity(&str);

    TIM_ASSERT_EQ(rtw_str_empty(&str), 0);

    rtw_str_clear(&str);
    TIM_ASSERT_EQ(rtw_str_empty(&str), 1);

    TIM_ASSERT_EQ(rtw_str_capacity(&str), capacity);

    TIM_ASSERT_EQ(str.type, HEAP_STR);

    TIM_TEST_SUCCESS();
}

TIM_TEST(str_push_at_pop) {
    rtw_str str = rtw_str_new();

    TIM_ASSERT_EQ(rtw_str_from(HEAP_DATA, &str), 0);
    TIM_ASSERT_EQ(rtw_str_push_back(&str, 'a'), 0);
    size_t capacity = rtw_str_capacity(&str);
    TIM_ASSERT_EQ(rtw_str_pop_back(&str), 'a');
    TIM_ASSERT_EQ(rtw_str_capacity(&str), capacity);
    TIM_ASSERT_EQ(rtw_str_at(&str, 5), HEAP_DATA[5]);

    TIM_TEST_SUCCESS();
}

TIM_TEST(str_copy_compare) {
    rtw_str src_str;
    rtw_str dest_str;

    TIM_ASSERT_EQ(rtw_str_from(STACK_DATA, &dest_str), 0);
    TIM_ASSERT_EQ(rtw_str_from(HEAP_DATA, &src_str), 0);
    TIM_ASSERT_EQ(rtw_str_copy(&dest_str, &src_str), 0);

    TIM_ASSERT_EQ(dest_str.type, HEAP_STR);
    TIM_ASSERT_EQ(rtw_str_compare(&src_str, &dest_str), 0);

    TIM_TEST_SUCCESS();
}
