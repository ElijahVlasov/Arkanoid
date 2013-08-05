cmake_minimum_required(VERSION 2.6)

project(AudioTest)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(OpenAL REQUIRED)
find_package(OGG REQUIRED)
find_package(VorbisFile REQUIRED)
find_package(Boost REQUIRED)

include_directories(
  ${INCLUDE_DIR}
  ${BOOST_INCLUDE_DIR}
)

set(AudioTest_SOURCES
  ${UTILS_AUDIO_SOURCES}
  ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

set(AudioTest_HEADERS
  ${UTILS_AUDIO_HEADERS}
)

set(AudioTest_LIBS
  ${OPENAL_LIBRARY}
  ${OGG_LIBRARY}
  ${VORBISFILE_LIBRARY}
)

add_executable(AudioTest ${AudioTest_SOURCES} ${AudioTest_HEADERS})
target_link_libraries(AudioTest ${AudioTest_LIBS})
