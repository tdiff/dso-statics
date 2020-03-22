cmake_minimum_required(VERSION 3.13)
project(dso_statics)
cmake_policy(SET CMP0003 NEW)

#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address  -fsanitize=leak -g")
#set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")
#set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -fsanitize=address")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g")

add_library(common common.cpp)
set_property(TARGET common PROPERTY POSITION_INDEPENDENT_CODE ON)

add_library(shared SHARED shared.cpp)
target_link_libraries(shared common)

add_executable(app main.cpp)
#target_link_libraries(app common shared)
target_link_libraries(app common -ldl)
