cmake_minimum_required(VERSION 2.8.3)

set(project_name "finger_test")
project(${project_name})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

include_directories(../../../src)
link_directories(../../../src)
link_libraries(libSCServo.a)

file(GLOB headers *.h)
file(GLOB sources *.cpp)

add_executable(${project_name} ${headers} ${sources})