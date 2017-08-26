cmake_minimum_required(VERSION 3.7)
project(hplearn)

set(CMAKE_CXX_STANDARD 11)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x -O2 -Wall -DNDEBUG")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LANGUAGE_STANDARD "c++0x")
set(CMAKE_XCODE_ATTRIBUTE_CLANG_CXX_LIBRARY "libc++")
set(CMAKE_XCODE_ATTRIBUTE_GCC_VERSION "com.apple.compilers.llvm.clang.1_0")
set(CMAKE_MACOSX_RPATH 1)

set(SOURCE_FILES main.cpp op.h op.cpp)
add_executable(main ${SOURCE_FILES})
