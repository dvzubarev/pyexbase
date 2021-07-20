
cmake_minimum_required(VERSION 3.12)

project(pyexbase VERSION 0.1
  LANGUAGES CXX)

#devel
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


find_package(pybind11 CONFIG)

add_subdirectory(src)
