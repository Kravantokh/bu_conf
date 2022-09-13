cmake_minimum_required(VERSION 3.24.1)

project(bu_conf VERSION 1.0)

if (MSVC)
    add_compile_options(/W4)
else()
	add_compile_options(-Wall -Wextra -pedantic)
endif()

set(CMAKE_C_STANDARD 99)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_library(bu_conf ${CMAKE_CURRENT_SOURCE_DIR}/src/bu_conf.c)

add_executable(bu_conf_test ${CMAKE_CURRENT_SOURCE_DIR}/src/test.c)
target_link_libraries(bu_conf_test bu_conf)
