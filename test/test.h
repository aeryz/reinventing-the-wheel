#include <string.h>

#define RTW_TEST_NAME(X)
#define TIM_TEST(X) rtw_test_res_t X()

typedef struct {
    const char *file;
    size_t line;
    unsigned success;
} rtw_test_res_t;

rtw_test_res_t _rtw_test_err(const char *file, size_t line) {
    rtw_test_res_t res;
    res.file = file;
    res.line = line;
    res.success = 0;
    return res;
}

rtw_test_res_t _rtw_test_success() {
    rtw_test_res_t res;
    res.file = NULL;
    res.line = 0;
    res.success = 1;
    return res;
}

#define RTW_ASSERT(X)                                                          \
    if (!X)                                                                    \
        return _rtw_test_err(__FILE__, __LINE__);

#define RTW_ASSERT_EQ(LHS, RHS)                                                \
    if (LHS != RHS)                                                            \
        return _rtw_test_err(__FILE__, __LINE__);

#define RTW_ASSERT_EQ_STR(LHS, RHS)                                            \
    if (strcmp(LHS, RHS) != 0)                                                 \
        return _rtw_test_err(__FILE__, __LINE__);

#define RTW_ASSERT_EQ_ARR(LHS, RHS, LEN)                                       \
    for (int i = 0; i < LEN; ++i) {                                            \
        if (LHS[i] != RHS[i])                                                  \
            return _rtw_test_err(__FILE__, __LINE__);                          \
    }

#define RTW_TEST_SUCCESS return _rtw_test_success()
