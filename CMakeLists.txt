cmake_minimum_required(VERSION 3.24)
project(bmp_project)

set(CMAKE_CXX_STANDARD 17)
set(SOURCE_FILES main.c)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_LIST_DIR}/cmake")

add_executable(bmp_project ${SOURCE_FILES})

include(FindPkgConfig)
find_package(bmp REQUIRED)
include_directories(${BMP_INCLUDE_DIR})
target_link_libraries(${PROJECT_NAME} ${BMP_LIBRARY})