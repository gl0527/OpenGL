cmake_minimum_required (VERSION 3.5.1)
project (OpenGL)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -W -Wall -Wextra -Wdeprecated -Wpedantic")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -O3 -ffast-math -msse -msse2 -mfpmath=sse")

find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED)

include_directories (${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
link_directories (${OPENGL_LIBRARIES})

add_definitions(${OPENGL_DEFINITIONS})

add_subdirectory (GLngin)
add_subdirectory (a)
