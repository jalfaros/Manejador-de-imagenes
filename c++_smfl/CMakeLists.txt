cmake_minimum_required(VERSION 3.17)
project(c___smfl)

set(CMAKE_CXX_STANDARD 14)

find_package( SFML 2.5 COMPONENTS system window graphics )

add_executable(c___smfl main.cpp)
target_link_libraries(c___smfl sfml-system sfml-window sfml-graphics)
target_link_libraries(c___smfl csfml-system csfml-window csfml-graphics)