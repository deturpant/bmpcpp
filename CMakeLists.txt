cmake_minimum_required(VERSION 3.23)
project(BMP)

set(CMAKE_CXX_STANDARD 17)

add_executable(BMP src/main.cpp src/BMP/BMP.h src/BMP/BMP.cpp src/Menu/MenuItem.h src/Menu/MenuItem.cpp src/Menu/MyMenu.h src/Menu/MyMenu.cpp src/Exceptions/MyException.h src/Exceptions/MyException.cpp)
