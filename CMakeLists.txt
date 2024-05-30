cmake_minimum_required(VERSION 3.14)

project(cafe)

add_executable(cafe-cli)

include(CMakeInclude.txt)

target_link_libraries(cafe-cli ncurses)