cmake_minimum_required(VERSION 3.16)
project(bigmath C)

<<<<<<< HEAD
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
=======
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type (Debug, Release, RelWithDebInfo, MinSizeRel)" FORCE)
endif()

set(BUILD_DIR ${CMAKE_BINARY_DIR}/build/${CMAKE_BUILD_TYPE})
set(TARGET_DIR ${CMAKE_BINARY_DIR}/target/${CMAKE_BUILD_TYPE})

include_directories(${PROJECT_SOURCE_DIR}/include)

set(CMAKE_C_FLAGS_DEBUG   "-g -Wall -Wextra")
set(CMAKE_C_FLAGS_RELEASE "-O3 -DNDEBUG -Wall -Wextra")

file(GLOB_RECURSE SRC_FILES ${PROJECT_SOURCE_DIR}/src/*.c)

add_library(bigmath STATIC ${SRC_FILES})
set_target_properties(bigmath PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY ${BUILD_DIR}
)

file(GLOB EXAMPLE_FILES ${PROJECT_SOURCE_DIR}/examples/*.c)
foreach(example_src ${EXAMPLE_FILES})
  get_filename_component(example_name ${example_src} NAME_WE)
  add_executable(${example_name} ${example_src})
  target_link_libraries(${example_name} bigmath)
  set_target_properties(${example_name} PROPERTIES
          RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR}
  )
endforeach()

file(GLOB TEST_FILES ${PROJECT_SOURCE_DIR}/tests/*.c)
foreach(test_src ${TEST_FILES})
  get_filename_component(test_name ${test_src} NAME_WE)
  add_executable(${test_name} ${test_src})
  target_link_libraries(${test_name} bigmath)
  set_target_properties(${test_name} PROPERTIES
          RUNTIME_OUTPUT_DIRECTORY ${TARGET_DIR}
  )
endforeach()
>>>>>>> d298bd08d2532790bb18077cdc032b7196e79351
