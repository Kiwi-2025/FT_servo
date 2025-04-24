# 指定CMake的最低版本要求为2.8.3
cmake_minimum_required(VERSION 2.8.3)

# 设置项目名称为"EPROM_write"
set(project "EPROM_write")

# 使用之前设置的项目名称来定义项目
project(${project})

# 设置C++编译器的标志，添加-c++11标准和-O3优化选项
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -O3")

# 包含头文件目录，这里指定的是相对路径 ../../../src
# 这意味着编译器会在该目录下查找头文件
include_directories(../../../src)

# 设置链接库的目录，这里指定的是相对路径 ../../../src
# 这意味着链接器会在该目录下查找库文件
link_directories(../../../src)

# 链接名为 libSCServo.a 的静态库
# 假设这个库文件存在于 link_directories 指定的目录中
link_libraries(libSCServo.a)

# 使用 file(GLOB hdrs *.h) 命令查找当前目录下的所有.h文件，并将它们存储在变量 hdrs 中
file(GLOB hdrs *.h)

# 使用 file(GLOB srs *.cpp) 命令查找当前目录下的所有.cpp文件，并将它们存储在变量 srs 中
file(GLOB srs *.cpp)

# 添加一个可执行文件，文件名为之前设置的项目名称 ${project}
# 使用之前查找的头文件和源文件列表 ${hdrs} 和 ${srs} 来构建这个可执行文件
add_executable(${project} ${hdrs} ${srs})
