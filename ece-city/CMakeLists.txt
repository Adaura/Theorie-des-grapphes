cmake_minimum_required(VERSION 3.23)
project(ece-city C)

set(CMAKE_C_STANDARD 99)
file(GLOB project_SRC CONFIGURE_DEPENDS "*.h" "*.c")
add_executable(ece-city ${project_SRC} )

target_link_libraries(ece-city -lmingw32 -lalleg44)