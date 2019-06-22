get_filename_component (TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string (REPLACE " " "_" TARGET_NAME ${TARGET_NAME})

cmake_minimum_required (VERSION 3.5.1)
project (${TARGET_NAME})

file (GLOB_RECURSE INCLUDES LIST_DIRECTORIES false "Headers/*.hpp")
file (GLOB_RECURSE SOURCES LIST_DIRECTORIES false "Sources/*.cpp")
add_library (${TARGET_NAME} SHARED ${SOURCES} ${INCLUDES})

set (ASSIMP_LIBRARY "libassimp.so")

include_directories (Headers/ Headers/Math/)
target_link_libraries (${TARGET_NAME} ${OPENGL_LIBRARY} ${GLEW_LIBRARY} -lILU ${ASSIMP_LIBRARY})

set (BINDIR ${CMAKE_SOURCE_DIR}/../Bin/${TARGET_NAME})

set_target_properties (${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BINDIR})
set_target_properties (${TARGET_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${BINDIR})
set_target_properties (${TARGET_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BINDIR})
set_target_properties (${TARGET_NAME} PROPERTIES DEBUG_OUTPUT_NAME "${TARGET_NAME}_d")

add_definitions (-DGLNGIN_DYNAMIC_COMPILE)
