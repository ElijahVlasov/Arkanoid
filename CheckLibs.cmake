# Проверяем необходимые для сборки библиотеки

find_package(Lua51 REQUIRED)

if(NOT LUA51_FOUND)
    message(FATAL_ERROR "Can't find Lua 5.1!")
    return()
endif()

find_package(OpenAL REQUIRED)

if(NOT OPENAL_FOUND)
    message(FATAL_ERROR "Can't find OpenAL!")
    return()
endif()

find_package(OpenGL REQUIRED)

if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "Can't find OpenGL!")
    return()
endif()

find_package(PNG REQUIRED)

if(NOT PNG_FOUND)
    message(FATAL_ERROR "Can't find libPNG!")
    return()
endif()

find_package(SDL REQUIRED)

if(NOT SDL_FOUND)
    message(FATAL_ERROR "Can't find SDL!")
    return()
endif()

find_package(Freetype REQUIRED)

if(NOT FREETYPE_FOUND)
    message(FATAL_ERROR "Can't find FreeType!")
    return()
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR})

find_package(Luabind REQUIRED)

if(NOT LUABIND_FOUND)
    message(FATAL_ERROR "Can't find Luabind")
    return()
endif()

set(Boost_USE_STATIC_LIBS        1)
set(Boost_USE_MULTITHREADED      1)
set(Boost_USE_STATIC_RUNTIME     0)
set(Boost_DEBUG                  0)

find_package(Boost 1.53.0 REQUIRED COMPONENTS system)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Can't find Boost")
    return()
endif ()

find_package(Protobuf REQUIRED)

if(NOT PROTOBUF_FOUND)
  message(FATAL_ERROR "Can't find Google Protocol Buffers")
  return()
endif()

if(NOT WIN32)

  find_package(GTK2 REQUIRED)

  if(NOT GTK2_FOUND)
    message(FATAL_ERROR "Can't find gtk+ 2.0")
  endif()

endif()

