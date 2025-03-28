cmake_minimum_required(VERSION 3.10.0)
# project(my_project VERSION 0.1.0 LANGUAGES CXX)
project(my_project)
# set(CMAKE_CXX_STANDARD 17)

file (GLOB_RECURSE my_project_SOURCES CONFIGURE_DEPENDS "src/*.cpp")
add_executable(my_project "${my_project_SOURCES}")

# target_include_directories(my_project PUBLIC "include/")

# file (GLOB_RECURSE my_project_SOURCES_2 CONFIGURE_DEPENDS "src/*.c")

# add_executable(Projekt0_1 src/main.cpp)
# target_link_directories(src)
# add_subdirectory(src)
# add_executable(Projekt0_1 ${my_project_SOURCES_2})
# add_executable(my_project_executable main.c)

