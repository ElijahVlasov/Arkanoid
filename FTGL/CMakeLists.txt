cmake_minimum_required(VERSION 2.6)

project(FTGL)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)


include_directories(${FREETYPE_INCLUDE_DIR_ft2build})
include_directories(${FREETYPE_INCLUDE_DIR_freetype2})
include_directories(${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/src)

configure_file(
  "config.h.in"
  "config.h"
)

set(FTGL_LIBS
  
  ${FREETYPE_LIBRARIES}
  ${OPENGL_LIBRARIES}

)

set(FTGL_SOURCES config.h)

add_subdirectory(src)

add_library(FTGL ${FTGL_SOURCES})

target_link_libraries(FTGL ${FTGL_LIBRARIES})