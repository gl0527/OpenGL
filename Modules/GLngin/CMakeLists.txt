get_filename_component (TARGET_NAME ${CMAKE_CURRENT_SOURCE_DIR} NAME)
string (REPLACE " " "_" TARGET_NAME ${TARGET_NAME})

cmake_minimum_required (VERSION 3.5.1)
project (${TARGET_NAME})

include_directories(inc/)
include_directories(inc/Math/)

file (GLOB_RECURSE INCLUDES LIST_DIRECTORIES false "inc/*.hpp")
file (GLOB_RECURSE SOURCES LIST_DIRECTORIES false "src/*.cpp")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DGLNGIN_DLL_CONFIG -DGLNGIN_DLL_EXPORT")

add_library (${TARGET_NAME} SHARED ${SOURCES} ${INCLUDES})

target_link_libraries (${TARGET_NAME} ${OPENGL_LIBRARY} ${GLEW_LIBRARY})

set (BINDIR ${CMAKE_SOURCE_DIR}/../Bin/${TARGET_NAME})

set_target_properties (${TARGET_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${BINDIR})
set_target_properties (${TARGET_NAME} PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${BINDIR})
set_target_properties (${TARGET_NAME} PROPERTIES ARCHIVE_OUTPUT_DIRECTORY ${BINDIR})
set_target_properties (${TARGET_NAME} PROPERTIES DEBUG_OUTPUT_NAME "${TARGET_NAME}_d")
