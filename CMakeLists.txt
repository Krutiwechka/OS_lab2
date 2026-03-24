cmake_minimum_required(VERSION 3.10)
project(OS_LAB2)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

if(MINGW)
    add_executable(Main src/main.cpp src/functions.cpp)
    target_link_options(Main PRIVATE "-static" "-static-libgcc" "-static-libstdc++")

    add_executable(Tests tests/tests.cpp src/functions.cpp)
    target_link_options(Tests PRIVATE "-static" "-static-libgcc" "-static-libstdc++")
else()
    add_executable(Tests tests/tests.cpp src/functions.cpp)
endif()
