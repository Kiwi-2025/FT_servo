cmake_Minimum_required(VERSION 2.8.3)
set(project "ProgramEprom")
project(${project})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

include_directories(../../../src)
link_directories(../../../src)
link_libraries(libSCServo.a)

file(GLOB hdrs *h)
file(GLOB srs *.cpp)

add_executable(${project} ${hdrs} ${srs})