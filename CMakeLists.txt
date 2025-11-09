cmake_minimum_required(VERSION 3.16)
project(bigmath C)

set(LIB_NAME bigmath)
set(CMAKE_C_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Collect all .c source files recursively
file(GLOB_RECURSE SRC src/*.c)

add_library(${LIB_NAME} STATIC ${SRC})
target_include_directories(${LIB_NAME} PUBLIC include)

# === Tests ===
add_executable(test_basic tests/test_basic.c)
target_link_libraries(test_basic PRIVATE ${LIB_NAME})
