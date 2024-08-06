cmake_minimum_required(VERSION 3.14)

project(BackendlessQt LANGUAGES CXX)

enable_testing()

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Network)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Network)

add_library(BackendlessQt STATIC
  API.cpp
  API.hpp
)
add_executable(BackendlessQt test.cpp)
add_test(BackendlessQt BackendlessQt)

target_link_libraries(BackendlessQt PRIVATE 
  Qt${QT_VERSION_MAJOR}::Core 
  Qt${QT_VERSION_MAJOR}::Network 
  Qt${QT_VERSION_MAJOR}::Test
)

target_compile_definitions(BackendlessQt PRIVATE BACKENDLESS_QT_LIBRARY)
