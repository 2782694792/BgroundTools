cmake_minimum_required(VERSION 3.0.0)
project(BgTools VERSION 0.1.0)

set(CMAKE_C_COMPILER "gcc")
set(CMAKE_CXX_COMPILER "g++")
set(CMAKE_CXX_STANDARD 14)

include_directories(${PROJECT_SOURCE_DIR}/include INC)
include_directories(${PROJECT_SOURCE_DIR}/utest UTEST)
aux_source_directory(${PROJECT_SOURCE_DIR}/src DIR_SRCS)

link_directories(${PROJECT_SOURCE_DIR}/lib)
set(UTEST_LIB libgtest.a;libgtest_main.a;libgmock.a;libgmock_main.a)

SET(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS} -O3 -Wall -fexec-charset=UTF8")
set(EXECUTABLE_OUTPUT_PATH  ${PROJECT_SOURCE_DIR}/bin)
set(OUT ${PROJECT_NAME}_wait)
add_executable(${OUT} "./src/main_multi_thread.cpp")

# target_link_libraries(${OUT} ${UTEST_LIB})
