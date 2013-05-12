cmake_minimum_required(VERSION 2.6)

project(Salt2D)

set(Salt2D_VERSION_MAJOR 0)
set(Salt2D_VERSION_MINOR 1)

set(SRC_DIR src)

#set(CMAKE_CURRENT_BINARY_DIR bin)

set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)

include_directories(${INCLUDE_DIR})

include(CheckLibs.cmake)

if ( CMAKE_COMPILER_IS_GNUCXX )
    set(CMAKE_CXX_FLAGS  "-Wall -std=c++0x")
endif(CMAKE_COMPILER_IS_GNUCXX )

option(MS_WINDOWS OFF)

if(WIN32)
    set(MS_WINDOWS ON)
endif()

include_directories(${LUA_INCLUDE_DIR})
include_directories(${FREETYPE_INCLUDE_DIR_freetype2})
include_directories(${LUABIND_INCLUDE_DIR})
include_directories(${Boost_INCLUDE_DIR})

set(ENGINE_GAME_STATES_SOURCES
  ${SRC_DIR}/Engine/GameStates/MenuState.cpp
  ${SRC_DIR}/Engine/GameStates/SingleGameState.cpp
)

set(ENGINE_SOURCES
  ${ENGINE_GAME_STATES_SOURCES}
  ${SRC_DIR}/Engine/Game.cpp
  ${SRC_DIR}/Engine/Object.cpp
  ${SRC_DIR}/Engine/Renderer.cpp
  ${SRC_DIR}/Engine/SaltEngine.cpp
  ${SRC_DIR}/Engine/World.cpp
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
  ${UTILS_UI_SOURCES}
  ${SRC_DIR}/Utils/Lua.cpp 
  ${SRC_DIR}/Utils/Texture.cpp 
  ${SRC_DIR}/Utils/Utils.cc
)

set(SOURCES 
  ${ENGINE_SOURCES}
  ${UTILS_SOURCES}
  ${SRC_DIR}/main.cpp 
  ${SRC_DIR}/Application.cpp
)

set(ENGINE_GAME_STATES_HEADERS
  ${INCLUDE_DIR}/Engine/GameStates/IGameState.hpp
  ${INCLUDE_DIR}/Engine/GameStates/MenuState.hpp
  ${INCLUDE_DIR}/Engine/GameStates/SingleGameState.hpp
)

set(ENGINE_HEADERS
  ${ENGINE_GAME_STATES_HEADERS}
  ${INCLUDE_DIR}/Engine/Camera.hpp
  ${INCLUDE_DIR}/Engine/Controller.hpp
  ${INCLUDE_DIR}/Engine/Direction.hpp
  ${INCLUDE_DIR}/Engine/Game.hpp
  ${INCLUDE_DIR}/Engine/IUpdatable.hpp
  ${INCLUDE_DIR}/Engine/Object.hpp
  ${INCLUDE_DIR}/Engine/Player.hpp
  ${INCLUDE_DIR}/Engine/Renderer.hpp
  ${INCLUDE_DIR}/Engine/SaltEngine.hpp
  ${INCLUDE_DIR}/Engine/World.hpp
)

set(EXCEPTIONS_HEADERS
  ${INCLUDE_DIR}/Exceptions/already_exist_error.hpp
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
  ${INCLUDE_DIR}/Utils/Color.hpp
  ${INCLUDE_DIR}/Utils/FreeType.hpp
  ${INCLUDE_DIR}/Utils/Lua.hpp
  ${INCLUDE_DIR}/Utils/MouseButton.hpp
  ${INCLUDE_DIR}/Utils/Singleton.hpp
  ${INCLUDE_DIR}/Utils/Texture.hpp
  ${INCLUDE_DIR}/Utils/UI.hpp
)

set(HEADERS
  ${ENGINE_HEADERS}
  ${EXCEPTIONS_HEADERS}
  ${TINY_XML_HEADERS}
  ${UTILS_HEADERS}
  ${INCLUDE_DIR}/Application.hpp
  ${INCLUDE_DIR}/config.h
  ${INCLUDE_DIR}/Engine.hpp
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
  ${SDL_LIBRARY}
  ${SDLIMAGE_LIBRARY}
  ${FREETYPE_LIBRARIES}
  ${LUABIND_LIBRARIES}
  TinyXML
)

configure_file(
	"config.h.in"
	"include/config.h"
)

add_subdirectory(${SRC_DIR}/TinyXML bin)

add_executable(Salt2D ${HEADERS} ${SOURCES})

target_link_libraries(Salt2D ${LIBS})
