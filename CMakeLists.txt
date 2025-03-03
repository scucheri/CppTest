cmake_minimum_required(VERSION 3.30)
project(HelloWorld)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -DMY_DEBUG")


set(IS_DEBUG_BUILD CMAKE_BUILD_TYPE STREQUAL "Debug")

# Indication to the code that this is a debug build
if (${IS_DEBUG_BUILD})
    add_compile_definitions(__DEBUG__)
endif ()

add_executable(HelloWorld main.cpp
        Log.cpp
        Log.h
        Common.cpp
        Common.h
        sub/Test.cpp
        sub/Test.h
        Test.cpp
        Test.h
)
