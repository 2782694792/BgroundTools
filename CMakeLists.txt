cmake_minimum_required(VERSION 3.0.0)
project(CMGCC7.3.0_BgTools VERSION 0.1.0)

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
add_executable(${PROJECT_NAME} "./src/main_multiProc.cpp")

target_link_libraries(${PROJECT_NAME} ${UTEST_LIB})
