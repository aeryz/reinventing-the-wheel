cmake_minimum_required(VERSION 3.10)

project(rtw)

if (DEFINED TIM_TEST_BUILD)
    message("Test build")
    set(CMAKE_OSX_ARCHITECTURES arm64)
    set(LLVM_TARGETS_TO_BUILD AArch64)
    set(LLVM_DEFAULT_TARGET_TRIPLE aarch64-apple-darwin20.1.0)
    add_library(rtw SHARED test/tim.c str/rtw_str.c str/rtw_str.h test/rtw_str_test.c)
    set_target_properties(rtw PROPERTIES PREFIX "")
    set_target_properties(rtw PROPERTIES SUFFIX "")
    set_target_properties(rtw PROPERTIES OUTPUT_NAME "tim-test-lib")
elseif (${BUILD_EXAMPLES} MATCHES "all")
    message("Build examples (all)")
    add_executable(rtw_hmap_example hmap/rtw_hmap.c examples/hash_map_example.c)
    add_executable(rtw_bset_example bset/rtw_bset.c examples/binary_set_example.c)
    add_executable(rtw_pq_example priority_queue/rtw_priority_queue.c vec/rtw_vec.c examples/priority_queue_example.c)
elseif (${BUILD_EXAMPLES} MATCHES "hmap")
    message("Build examples (hmap)")
    add_executable(rtw_hmap_example vec/rtw_vec.c hmap/rtw_hmap.c examples/hash_map_example.c)
elseif (${BUILD_EXAMPLES} MATCHES "bset")
    message("Build examples (bset)")
    add_executable(rtw_bset_example bset/rtw_bset.c examples/binary_set_example.c)
elseif (${BUILD_EXAMPLES} MATCHES "priority_queue")
    message("Build examples (priority_queue)")
    add_executable(rtw_pq_example priority_queue/rtw_priority_queue.c examples/priority_queue_example.c)
else()
    message("Build")
    add_library(rtw SHARED bset/rtw_bset.c hmap/rtw_hmap.c str/rtw_str.c vec/rtw_vec.c)
endif()
