# License: MIT. See LICENSE in root directory.
# Date: 2020/06/27

cmake_minimum_required(VERSION 3.1.0)

project("ensemble-array" LANGUAGES CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories("${CMAKE_CURRENT_LIST_DIR}/inc")

add_compile_definitions("uint=unsigned int")

set(ENSEMBLE_ARRAY_LIB "ensemble-array-lib")
add_library(${ENSEMBLE_ARRAY_LIB} STATIC "")
target_sources(
    ${ENSEMBLE_ARRAY_LIB}
    PRIVATE
    "${CMAKE_CURRENT_LIST_DIR}/src/ensemble/array.cpp"
    "${CMAKE_CURRENT_LIST_DIR}/inc/ensemble/array.hpp"
)

if (CMAKE_BUILD_TYPE MATCHES "^[Dd]ebug")
    set(ENSEMBLE_ARRAY_EXE "ensemble-array-exe")
    add_executable(${ENSEMBLE_ARRAY_EXE} "${CMAKE_CURRENT_LIST_DIR}/test/main.cpp")
    target_link_libraries(${ENSEMBLE_ARRAY_EXE} ${ENSEMBLE_ARRAY_LIB})
endif ()
