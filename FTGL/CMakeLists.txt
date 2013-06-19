cmake_minimum_required(VERSION 2.6)

project(FTGL)

set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)

include(${CMAKE_CURRENT_SOURCE_DIR}/CheckLibs.cmake)

include_directories(

  ${FREETYPE_INCLUDE_DIR_ft2build}
  ${FREETYPE_INCLUDE_DIR_freetype2}
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_SOURCE_DIR}/src

)

set(FTGL_LIBS
  
  ${FREETYPE_LIBRARIES}
  ${OPENGL_LIBRARIES}

)

add_definitions(-DHAVE_GL_GL_H -DHAVE_GL_GLU_H -DHAVE_MEMORY_H -DHAVE_STDINT_H -DHAVE_STDLIB_H -DHAVE_STRING_H -DSTDC_HEADERS)

set(FTGL_SOURCES config.h)

add_subdirectory(src)

add_library(FTGL ${FTGL_SOURCES})

target_link_libraries(FTGL ${FTGL_LIBS})
