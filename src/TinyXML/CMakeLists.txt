cmake_minimum_required(VERSION 2.6)

project(Salt2D)

include_directories(${INCLUDE_DIR}/TinyXML)

set(TINY_XML_SOURCES 
  tinyxml.cpp
  tinyxmlerror.cpp
  tinyxmlparser.cpp
)

add_library(TinyXML ${TINY_XML_HEADERS} ${TINY_XML_SOURCES})
