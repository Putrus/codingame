cmake_minimum_required(VERSION 3.6..3.28)

project(jumputra
   VERSION 0.0.1
   LANGUAGES CXX
   DESCRIPTION "Putra CodinGame solutions"
   )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(cmake/UpdateSubmodules.cmake)

add_subdirectory(external)