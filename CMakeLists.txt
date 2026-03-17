cmake_minimum_required(VERSION 3.20)
project(bigmath C CXX)
option(BIGMATH_BUILD_CXX     "Build bigmath++ C++ wrapper library" ON)
option(BIGMATH_BUILD_TESTS   "Build tests"                         ON)
option(BIGMATH_BUILD_EXAMPLE "Build examples"                      ON)
add_library(bigmath STATIC
        src/alloc.c
        src/mpn/add_n.c
        src/mpn/add.c
        src/mpn/add_1.c
        src/mpn/sub_n.c
        src/mpn/sub.c
        src/mpn/sub_1.c
        src/mpn/cmp.c
        src/mpn/mul_1.c
        src/mpn/addmul_1.c
        src/mpn/submul_1.c
        src/mpn/mul.c
        src/mpn/divrem.c
        src/mpn/lshift.c
        src/mpn/rshift.c
        src/mpn/and_n.c
        src/mpn/ior_n.c
        src/mpn/xor_n.c
        src/mpn/com_n.c
        src/mpn/popcount.c
        src/mpn/scan1.c
        src/mpz/init.c
        src/mpz/inits.c
        src/mpz/init_set.c
        src/mpz/init_set_ui.c
        src/mpz/inits_sets.c
        src/mpz/inits_sets_ui.c
        src/mpz/clear.c
        src/mpz/clears.c
        src/mpz/set.c
        src/mpz/sets.c
        src/mpz/set_ui.c
        src/mpz/sets_ui.c
        src/mpz/get_ui.c
        src/mpz/get_si.c
        src/mpz/add.c
        src/mpz/add_ui.c
        src/mpz/sub.c
        src/mpz/sub_ui.c
        src/mpz/mul.c
        src/mpz/mul_ui.c
        src/mpz/tdiv_q.c
        src/mpz/tdiv_r.c
        src/mpz/tdiv_qr.c
        src/mpz/fdiv_q.c
        src/mpz/fdiv_r.c
        src/mpz/fdiv_qr.c
        src/mpz/cdiv_q.c
        src/mpz/cdiv_r.c
        src/mpz/cdiv_qr.c
        src/mpz/mod.c
        src/mpz/pow_ui.c
        src/mpz/powm.c
        src/mpz/cmp.c
        src/mpz/cmp_ui.c
        src/mpz/cmp_si.c
        src/mpz/cmpabs.c
        src/mpz/and.c
        src/mpz/or.c
        src/mpz/xor.c
        src/mpz/com.c
        src/mpz/mul_2exp.c
        src/mpz/div_2exp.c
        src/mpz/size.c
        src/mpz/sizeinbase.c
        src/mpz/get_str.c
        src/mpz/popcount.c
        src/mpz/scan1.c
        src/mpz/gcd.c
        src/mpz/lcm.c
        src/mpz/invert.c
        src/mpz/neg.c
        src/mpz/abs.c
        src/mpz/sgn.c
)
target_include_directories(bigmath PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)
if(BIGMATH_BUILD_CXX)
    add_library(bigmath++ STATIC
            src/bigint/bigint.cpp
            src/bigfloat/arithmetics.cpp
            src/bigfloat/bigfloat.cpp
            src/bigfloat/exponential.cpp
            src/bigfloat/io.cpp
            src/bigfloat/logarithmic.cpp
            src/bigfloat/logical.cpp
            src/bigfloat/trigonometry.cpp
    )
    target_link_libraries(bigmath++ PUBLIC bigmath)
    target_include_directories(bigmath++ PUBLIC
            $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
            $<INSTALL_INTERFACE:include>
    )
endif()
if(BIGMATH_BUILD_TESTS AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    include(FetchContent)
    FetchContent_Declare(
            googletest
            GIT_REPOSITORY https://github.com/google/googletest.git
            GIT_TAG v1.14.0
    )
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
    enable_testing()
    add_subdirectory(tests)
endif()
if(BIGMATH_BUILD_EXAMPLE AND CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    add_executable(bigmath_example examples/main.cpp)
    target_link_libraries(bigmath_example PRIVATE bigmath++)
endif()