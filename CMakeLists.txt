cmake_minimum_required(VERSION 2.8.8)

project(Salt2D)

set(Salt2D_VERSION_MAJOR 0)
set(Salt2D_VERSION_MINOR 1)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROTOCOLS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protocols)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)


include_directories(${INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})

include(CheckLibs.cmake)

set(PROTOBUF_IMPORT_DIRS ${PROTOCOLS_DIR})

if ( CMAKE_COMPILER_IS_GNUCXX )
    set(CMAKE_CXX_FLAGS  "-Wall -std=gnu++0x -g")
endif(CMAKE_COMPILER_IS_GNUCXX )

option(MS_WINDOWS OFF)

if(WIN32)
    set(MS_WINDOWS ON)
endif()

include_directories(${Boost_INCLUDE_DIR})
include_directories(${IL_INCLUDE_DIR})
include_directories(${FREETYPE_INCLUDE_DIR_ft2build})
include_directories(${FREETYPE_INCLUDE_DIR_freetype2})
include_directories(${LUA_INCLUDE_DIR})
include_directories(${LUABIND_INCLUDE_DIR})
include_directories(${OPENAL_INCLUDE_DIR})
include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${PROTOBUF_INCLUDE_DIRS})

set(ENGINE_GAME_STATES_SOURCES
  ${SRC_DIR}/Engine/GameStates/MenuState.cpp
  ${SRC_DIR}/Engine/GameStates/SingleGameState.cpp
  ${SRC_DIR}/Engine/GameStates/StartLogoState.cpp
)

set(ENGINE_SOURCES
  ${ENGINE_GAME_STATES_SOURCES}
  ${SRC_DIR}/Engine/DynamicObject.cpp
  ${SRC_DIR}/Engine/Game.cpp
  ${SRC_DIR}/Engine/LocationLayer.cpp
  ${SRC_DIR}/Engine/Object.cpp
  ${SRC_DIR}/Engine/Renderer.cpp
  ${SRC_DIR}/Engine/SaltEngine.cpp
  ${SRC_DIR}/Engine/StaticObject.cpp
  ${SRC_DIR}/Engine/World.cpp
)

set(LUA_API_SOURCES
  ${SRC_DIR}/LuaAPI/LuaAPI.cpp
)

set(UTILS_FREETYPE_SOURCES
  ${SRC_DIR}/Utils/FreeType/Font.cpp
  ${SRC_DIR}/Utils/FreeType/Library.cpp
)

set(UTILS_UI_SOURCES
  ${SRC_DIR}/Utils/UI/Button.cpp
  ${SRC_DIR}/Utils/UI/Component.cpp
  ${SRC_DIR}/Utils/UI/ComponentFactory.cpp
  ${SRC_DIR}/Utils/UI/Label.cpp
  ${SRC_DIR}/Utils/UI/Menu.cpp
  ${SRC_DIR}/Utils/UI/MenuFactory.cpp
)

set(UTILS_SOURCES
  ${UTILS_FREETYPE_SOURCES}
  ${UTILS_UI_SOURCES}
  ${SRC_DIR}/Utils/Audio.cpp
  ${SRC_DIR}/Utils/Graphics.cpp
  ${SRC_DIR}/Utils/Lua.cpp 
  ${SRC_DIR}/Utils/PCResourceLoader.cpp
  ${SRC_DIR}/Utils/Resource.cpp
  ${SRC_DIR}/Utils/ResourceFile.cpp
  ${SRC_DIR}/Utils/ResourceLoader.cpp
  ${SRC_DIR}/Utils/ResourceManager.cpp
  ${SRC_DIR}/Utils/Sound.cpp
  ${SRC_DIR}/Utils/Texture.cpp 
  ${SRC_DIR}/Utils/Utils.cc
)

set(PROTOCOLS
  ${PROTOCOLS_DIR}/Box.proto
  ${PROTOCOLS_DIR}/Point.proto
  ${PROTOCOLS_DIR}/StaticObject.proto
  ${PROTOCOLS_DIR}/World.proto
)

set(SOURCES 
  ${ENGINE_SOURCES}
  ${LUA_API_SOURCES}
  ${UTILS_SOURCES}
  ${SRC_DIR}/main.cpp 
  ${SRC_DIR}/Application.cpp
)

set(ENGINE_GAME_STATES_HEADERS
  ${INCLUDE_DIR}/Engine/GameStates/IGameState.hpp
  ${INCLUDE_DIR}/Engine/GameStates/MenuState.hpp
  ${INCLUDE_DIR}/Engine/GameStates/SingleGameState.hpp
  ${INCLUDE_DIR}/Engine/GameStates/StartLogoState.hpp
)

set(ENGINE_HEADERS
  ${ENGINE_GAME_STATES_HEADERS}
  ${INCLUDE_DIR}/Engine/Camera.hpp
  ${INCLUDE_DIR}/Engine/Direction.hpp
  ${INCLUDE_DIR}/Engine/DynamicObject.hpp
  ${INCLUDE_DIR}/Engine/Game.hpp
  ${INCLUDE_DIR}/Engine/GameStates.hpp
  ${INCLUDE_DIR}/Engine/IController.hpp
  ${INCLUDE_DIR}/Engine/IRenderer.hpp
  ${INCLUDE_DIR}/Engine/IUpdatable.hpp
  ${INCLUDE_DIR}/Engine/LocationLayer.hpp
  ${INCLUDE_DIR}/Engine/Object.hpp
  ${INCLUDE_DIR}/Engine/Player.hpp
  ${INCLUDE_DIR}/Engine/Renderer.hpp
  ${INCLUDE_DIR}/Engine/SaltEngine.hpp
  ${INCLUDE_DIR}/Engine/StaticObject.hpp
  ${INCLUDE_DIR}/Engine/World.hpp
)

set(LUA_API_HEADERS
)

set(TINY_XML_HEADERS
  ${INCLUDE_DIR}/TinyXML/tinystr.h
  ${INCLUDE_DIR}/TinyXML/tinyxml.h
)

set(UTILS_FREETYPE_HEADERS
  ${INCLUDE_DIR}/Utils/FreeType/Font.hpp
  ${INCLUDE_DIR}/Utils/FreeType/Library.hpp
)

set(UTILS_UI_HEADERS
  ${INCLUDE_DIR}/Utils/UI/Button.hpp
  ${INCLUDE_DIR}/Utils/UI/Component.hpp
  ${INCLUDE_DIR}/Utils/UI/ComponentEvent_wrapper.hpp
  ${INCLUDE_DIR}/Utils/UI/ComponentFactory.hpp
  ${INCLUDE_DIR}/Utils/UI/Event.hpp
  ${INCLUDE_DIR}/Utils/UI/KeyEvent.hpp
  ${INCLUDE_DIR}/Utils/UI/Label.hpp
  ${INCLUDE_DIR}/Utils/UI/Menu.hpp
  ${INCLUDE_DIR}/Utils/UI/MenuFactory.hpp
  ${INCLUDE_DIR}/Utils/UI/MouseEvent.hpp
)

set(UTILS_HEADERS
  ${UTILS_FREETYPE_HEADERS}
  ${UTILS_UI_HEADERS}
  ${INCLUDE_DIR}/Utils/assert.hpp
  ${INCLUDE_DIR}/Utils/Audio.hpp
  ${INCLUDE_DIR}/Utils/Color.hpp
  ${INCLUDE_DIR}/Utils/FreeType.hpp
  ${INCLUDE_DIR}/Utils/Graphics.hpp
  ${INCLUDE_DIR}/Utils/Lua.hpp
  ${INCLUDE_DIR}/Utils/MouseButton.hpp
  ${INCLUDE_DIR}/Utils/PCResourceLoader.hpp
  ${INCLUDE_DIR}/Utils/Resource.hpp
  ${INCLUDE_DIR}/Utils/ResourceFile.hpp
  ${INCLUDE_DIR}/Utils/ResourceLoader.hpp
  ${INCLUDE_DIR}/Utils/ResourceManager.hpp
  ${INCLUDE_DIR}/Utils/Singleton.hpp
  ${INCLUDE_DIR}/Utils/Sound.hpp
  ${INCLUDE_DIR}/Utils/Texture.hpp
  ${INCLUDE_DIR}/Utils/UI.hpp
)

set(HEADERS
  ${ENGINE_HEADERS}
  ${LUA_API_HEADERS}
  ${TINY_XML_HEADERS}
  ${UTILS_HEADERS}
  ${INCLUDE_DIR}/Application.hpp
  ${INCLUDE_DIR}/config.h
  ${INCLUDE_DIR}/Engine.hpp
  ${INCLUDE_DIR}/LuaAPI.hpp
  ${INCLUDE_DIR}/Utils.hpp
)

set(LIBS
  ${Boost_DATE_TIME_LIBRARY}
  ${Boost_FILESYSTEM_LIBRARY}
  ${Boost_SERIALIZATION_LIBRARY}
  ${Boost_SYSTEM_LIBRARY}
  ${Boost_THREAD_LIBRARY}
  ${LUA_LIBRARIES}
  ${OPENAL_LIBRARY}
  ${OPENGL_LIBRARIES}
  ${IL_LIBRARIES}
  ${ILU_LIBRARIES}
  ${SDL_LIBRARY}
  ${FREETYPE_LIBRARIES}
  ${LUABIND_LIBRARIES}
  ${PROTOBUF_LITE_LIBRARIES}
  TinyXML
)

if(NOT WIN32)
  include_directories(${GTK2_INCLUDE_DIRS})
  set(LIBS ${LIBS} ${GTK2_LIBRARIES})
endif()

protobuf_generate_cpp(PROTOCOLS_SOURCES PROTOCOLS_HEADERS ${PROTOCOLS})

configure_file(
  "config.h.in"
  "include/config.h"
)

add_subdirectory(${SRC_DIR}/TinyXML)

add_executable(Salt2D WIN32 ${HEADERS} ${SOURCES} ${PROTOCOLS_SOURCES} ${PROTOCOLS_HEADERS})

target_link_libraries(Salt2D ${LIBS})
