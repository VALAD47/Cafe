#Made by VALAD47
cmake_minimum_required(VERSION 3.14)

project(cafe)

add_executable(cafe-cli)

include(CMakeInclude.txt)

if (${CMAKE_SYSTEM_NAME} MATCHES "Windows")
        target_link_libraries(cafe-cli ncursesw)
else()
        target_link_libraries(cafe-cli ncurses)
endif()

