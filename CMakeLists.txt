cmake_minimum_required(VERSION 3.11.0)
project(prescription VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY      https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_MakeAvailable(googletest)

configure_file(moby_dick.txt ${CMAKE_CURRENT_BINARY_DIR}/moby_dick.txt COPYONLY)
configure_file(10x_moby_dick.txt ${CMAKE_CURRENT_BINARY_DIR}/10x_moby_dick.txt COPYONLY)

set(PROJECT_SOURCES entry.h entry.cpp word_counter.h word_counter.cpp)

add_executable(testGoogle testGoogle.cpp ${PROJECT_SOURCES})
add_executable(moby_dick moby_dick.cpp ${PROJECT_SOURCES})

target_link_libraries(testGoogle PUBLIC gtest_main)