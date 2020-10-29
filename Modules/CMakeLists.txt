cmake_minimum_required (VERSION 3.7.3)
project (OpenGL)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pedantic -W -Wall -Wextra -Wcast-align")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winit-self -Wuninitialized -Wmissing-include-dirs")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Woverloaded-virtual -Wshadow -Wno-sign-conversion -Wsign-promo")

set (CMAKE_EXPORT_COMPILE_COMMANDS ON)

find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED)

file(GLOB_RECURSE ALL_CXX_FILES *.cpp *.hpp)
add_custom_target(
        clang-format
        ALL /usr/bin/clang-format
        -i
        ${ALL_CXX_FILES}
)

include_directories (${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
link_directories (${OPENGL_LIBRARIES})

add_definitions (${OPENGL_DEFINITIONS})

add_subdirectory (GLngin)
add_subdirectory (Fractals)
add_subdirectory (NBody)
add_subdirectory (PositionBasedDynamics)
add_subdirectory (ImageProcessing)
add_subdirectory (Splines)
