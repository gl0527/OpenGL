cmake_minimum_required (VERSION 3.7.3)
project (OpenGL)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -pedantic -W -Wall -Wextra -Wcast-align -Wdeprecated")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Winit-self -Wmissing-declarations -Wmissing-include-dirs")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wold-style-cast -Woverloaded-virtual")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  -Wstrict-overflow=5")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wswitch-default -Wundef -Wno-unused")
set (CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g -O0")
set (CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -DNDEBUG -s -O3 -ffast-math -msse -msse2 -mfpmath=sse")

find_package (OpenGL REQUIRED)
find_package (GLEW REQUIRED)

include_directories (${OPENGL_INCLUDE_DIRS} ${GLEW_INCLUDE_DIRS})
link_directories (${OPENGL_LIBRARIES})

add_definitions(${OPENGL_DEFINITIONS})

add_subdirectory (GLngin)
add_subdirectory (a)
add_subdirectory (Fractals)
add_subdirectory (NBody)
add_subdirectory (PositionBasedDynamics)
