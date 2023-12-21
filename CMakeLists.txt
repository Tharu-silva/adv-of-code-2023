cmake_minimum_required(VERSION 3.26)
project(adv_of_code_2023)

set(CMAKE_CXX_STANDARD 20)

include_directories(.)

add_executable(adv_of_code_2023
        day_1/day_1.cpp
        day_2/day_2.cpp
        day_3/day_3.cpp
        day_3/day_3_part_2.cpp
        day_4/4_1.cpp
        day_4/4_2.cpp
        day_5/5_1.cpp
        day_5/5_2.cpp
        day_6/6_1.cpp
        day_6/6_2.cpp)
