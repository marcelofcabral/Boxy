cmake_minimum_required(VERSION 3.10)
project(Boxy)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_DEBUG "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY_RELEASE "${CMAKE_BINARY_DIR}")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}")

set(INCLUDE_DIR "" CACHE PATH "Path to include directory")
set(LIB_DIR "" CACHE PATH "Path to lib directory")

include_directories(${INCLUDE_DIR})

file(COPY "shaders" DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

file(GLOB_RECURSE SOURCES
    "Main.cpp"
    "camera/*.cpp"
    "collision/*.cpp"
    "objects/*.cpp"
    "rendering/*.cpp"
    "scene/*.cpp"
    "shaders/*.cpp"
    "utils/*.cpp"
    "glad.c"
    "stb_image_impl.cpp"
)

add_executable(Boxy ${SOURCES})

target_link_libraries(Boxy
    PRIVATE
    "${LIB_DIR}/glfw3.lib"
)

