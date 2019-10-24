cmake_minimum_required (VERSION 2.8)
#name
project (module_thread)
#include compile macro
include (../head.cmake)

#include dir
include_directories(./include)

#link dir
#link_directories()

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib)

#add source file
aux_source_directory(./source/ SRC_FILES)
#libname
add_library(${PROJECT_NAME} STATIC ${SRC_FILES})
set (INC_LIB ${CMAKE_CURRENT_SOURCE_DIR}/../lib)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/lib ${INC_LIB} )
