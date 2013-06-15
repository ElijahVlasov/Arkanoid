cmake_minimum_required(VERSION 2.6)

project(TinyXML)

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

add_definitions(-DTIXML_USE_STL)

set(TINY_XML_HEADERS

  tinyxml.h

)

set(TINY_XML_SOURCES 
  tinyxml.cpp
  tinyxmlerror.cpp
  tinyxmlparser.cpp
)

add_library(TinyXML ${TINY_XML_HEADERS} ${TINY_XML_SOURCES})
