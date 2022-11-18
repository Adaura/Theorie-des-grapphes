cmake_minimum_required(VERSION 3.23)
project(projet45 C)

set(CMAKE_C_STANDARD 99)

add_executable(projet45 main.c fonction.c fonction.h)

target_link_libraries(projet45 -lmingw32 -lalleg44)
