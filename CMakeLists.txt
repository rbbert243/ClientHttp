cmake_minimum_required(VERSION 3.10)
project(Client LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(lib/include)

add_library(ClientLib STATIC
    lib/src/Client.cpp
    lib/src/Session.cpp
    lib/src/Request.cpp
    lib/src/Response.cpp)

add_executable(Client main.cpp)

target_link_libraries(Client ClientLib)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror")