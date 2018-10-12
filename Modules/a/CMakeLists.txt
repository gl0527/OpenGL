get_filename_component (TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string (REPLACE " " "_" TARGET_NAME ${TARGET_NAME})

cmake_minimum_required (VERSION 3.5.1)
project (${TARGET_NAME})

include_directories (${CMAKE_SOURCE_DIR}/GLngin/inc/)
include_directories (${CMAKE_SOURCE_DIR}/GLngin/inc/Math/)

add_executable (${TARGET_NAME} src/a.cpp)

find_package (GLUT REQUIRED)

include_directories (${GLUT_INCLUDE_DIRS})
link_directories (${CMAKE_SOURCE_DIR}/../Bin/GLngin)
target_link_libraries (${TARGET_NAME} GLngin ${OPENGL_LIBRARY} ${GLEW_LIBRARY} ${GLUT_LIBRARY})

set (BINDIR ${CMAKE_SOURCE_DIR}/../Bin/${TARGET_NAME})

set_target_properties (${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BINDIR})
set_target_properties (${TARGET_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${BINDIR})
set_target_properties (${TARGET_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BINDIR})
set_target_properties (${TARGET_NAME} PROPERTIES DEBUG_OUTPUT_NAME "${TARGET_NAME}_d")

add_dependencies (${TARGET_NAME} GLngin)
