cmake_minimum_required(VERSION 3.20)

project(Numint CXX)

add_compile_options(-Wall -Wextra -std=c++17)

set(SRCFILES    src/Numint.cpp
                src/Utility.cpp
                src/Container/History.cpp
                src/Container/State.cpp
                src/Container/TimeSeriesState.cpp
                src/Math/Integration.cpp
                src/Math/ODE.cpp
                src/Math/IteratedMap.cpp
                src/Math/Random.cpp
                src/Math/Math.cpp
                src/Math/Filtering.cpp
                src/Math/Model.cpp
                src/Debug/Logger.cpp)

add_library(Numint STATIC ${SRCFILES})
target_include_directories(Numint PUBLIC ${PROJECT_SOURCE_DIR}/include)

add_executable(exec src/main.cpp)
target_link_libraries(exec PRIVATE Numint)