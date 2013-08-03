cmake_minimum_required(VERSION 2.6)

project(OALTest)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenAL REQUIRED)
find_package(OGG REQUIRED)
find_package(VorbisFile REQUIRED)
find_package(Boost REQUIRED)

include_directories(
  ${INCLUDE_DIR}
  ${BOOST_INCLUDE_DIR}
)

set(OALTest_SOURCES
  ${UTILS_OPENAL_SOURCES}
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

set(OALTest_HEADERS
  ${UTILS_OPENAL_HEADERS}
)

set(OALTest_LIBS
  ${OPENAL_LIBRARY}
  ${OGG_LIBRARY}
  ${VORBISFILE_LIBRARY}
)

add_executable(OALTest ${OALTest_SOURCES} ${OALTest_HEADERS})
target_link_libraries(OALTest ${OALTest_LIBS})
