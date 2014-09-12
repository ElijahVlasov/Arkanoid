cmake_minimum_required(VERSION 2.6)

project(Luabind)

include(${CMAKE_CURRENT_SOURCE_DIR}/CheckLibs.cmake)

include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${Boost_INCLUDE_DIR}
  ${LUA_INCLUDE_DIR}
)

set(LUABIND_SOURCES
  ${CMAKE_CURRENT_SOURCE_DIR}/src/class.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/class_info.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/class_registry.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/class_rep.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/create_class.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/error.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/exception_handler.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/function.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/inheritance.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/link_compatibility.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/object_rep.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/open.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/pcall.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/scope.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/stack_content_by_name.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/weak_ref.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/src/wrapper_base.cpp
)

add_library(Luabind ${LUABIND_SOURCES})