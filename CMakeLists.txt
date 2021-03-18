cmake_minimum_required(VERSION 3.10)

project(rtw)

if (DEFINED TIM_TEST_BUILD)
    message("Test build")
    add_library(rtw SHARED test/test.h str/rtw_str.c str/rtw_str.h test/rtw_str_test.c)
else()
    message("Debug build")
    add_executable(rtw str/rtw_str.c vec/rtw_vec.c main.c)
endif()
