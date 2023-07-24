cmake_minimum_required(VERSION 3.20)

project(Numint CXX)

add_compile_options(-Wall -Wextra -std=c++17)

add_library(Numint STATIC src/Numint.cpp)
target_include_directories(Numint PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(exec src/main.cpp)
target_link_libraries(exec PRIVATE Numint)
