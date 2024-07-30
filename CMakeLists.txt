cmake_minimum_required(VERSION 3.14)

project(Some LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_library(Some STATIC
  API.cpp
  API.hpp
)

target_link_libraries(Some PRIVATE Qt${QT_VERSION_MAJOR}::Core)

target_compile_definitions(Some PRIVATE SOME_LIBRARY)
