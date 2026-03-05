add_executable(test_bigmath
        ${CMAKE_CURRENT_SOURCE_DIR}/test_mpn.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test_mpz.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/test_bigint.cpp
)

target_link_libraries(test_bigmath
        bigmath++
        gtest
        gtest_main
)

target_include_directories(test_bigmath PRIVATE ${PROJECT_SOURCE_DIR}/include)

include(GoogleTest)
gtest_discover_tests(test_bigmath)