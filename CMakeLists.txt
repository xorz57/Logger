cmake_minimum_required(VERSION 3.26)
project(Logger)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(CMAKE_MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")

add_library(Logger INTERFACE)
target_include_directories(Logger INTERFACE ${CMAKE_SOURCE_DIR}/include)

add_executable(Example examples/Example.cpp)
target_link_libraries(Example PRIVATE Logger)
