cmake_minimum_required(VERSION 3.14)
project(ActiveSource)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES main.cpp
        board.h
        board.cpp
        random.h
        random.cpp
        TextureManager.h
        TextureManager.cpp
        menu.cpp)
add_executable(main ${SOURCE_FILES})
include_directories(/usr/local/include)

find_package(SFML 2.5 COMPONENTS system window graphics network audio REQUIRED)
include_directories(${SFML_INCLUDE_DIRS})
target_link_libraries(main sfml-system sfml-window sfml-graphics sfml-audio sfml-network)