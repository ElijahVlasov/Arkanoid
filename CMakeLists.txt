cmake_minimum_required(VERSION 2.8.8)

project(Arkanoid)

set(${PROJECT_NAME}_PROJECT_NAME ${PROJECT_NAME})

set(VERSION_MAJOR 0)
set(VERSION_MINOR 9)

set(SRC_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(PROTOCOLS_DIR ${CMAKE_CURRENT_SOURCE_DIR}/protocols)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${CMAKE_CURRENT_BINARY_DIR}/lib)


include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${INCLUDE_DIR}
    ${CMAKE_CURRENT_BINARY_DIR}
)

include(CheckLibs.cmake)

if ( CMAKE_COMPILER_IS_GNUCXX )

    set(CMAKE_CXX_FLAGS_RELEASE "-w -O2 -std=c++11")
    set(CMAKE_CXX_FLAGS_DEBUG   "-Wall -std=c++11 -g")

endif()

if(WIN32)
    add_definitions(-DWINDOWS)
endif()

add_definitions(${PNG_DEFINITIONS})

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/FTGL/src
    ${CMAKE_CURRENT_SOURCE_DIR}/TinyXML
    ${Boost_INCLUDE_DIR}
    ${FREETYPE_INCLUDE_DIR_ft2build}
    ${FREETYPE_INCLUDE_DIR_freetype2}
    ${LUA_INCLUDE_DIR}
    ${LUABIND_INCLUDE_DIR}
    ${OGG_INCLUDE_DIR}
    ${OPENAL_INCLUDE_DIR}
    ${OPENGL_INCLUDE_DIR}
    ${PNG_INCLUDE_DIRS}
    ${SDL_INCLUDE_DIR}
    ${VORBISFILE_INCLUDE_DIR}
)

set(ENGINE_GAME_STATES_SOURCES
    ${SRC_DIR}/Engine/GameStates/LoadingState.cpp
    ${SRC_DIR}/Engine/GameStates/MenuState.cpp
    ${SRC_DIR}/Engine/GameStates/SingleGameState.cpp
    ${SRC_DIR}/Engine/GameStates/StartLogoState.cpp
)

set(ENGINE_SOURCES
    ${ENGINE_GAME_STATES_SOURCES}
    ${SRC_DIR}/Engine/Ball.cpp
    ${SRC_DIR}/Engine/Block.cpp
    ${SRC_DIR}/Engine/DebugOutput.cpp
    ${SRC_DIR}/Engine/EasyBlock.cpp
    ${SRC_DIR}/Engine/Game.cpp
    ${SRC_DIR}/Engine/Object.cpp
    ${SRC_DIR}/Engine/Platform.cpp
)

set(LUA_API_SOURCES
    ${SRC_DIR}/LuaAPI/LuaAPI.cpp
    ${SRC_DIR}/LuaAPI/Sprite_wrapper.cpp
)

set(UTILS_AUDIO_SOURCES
    ${SRC_DIR}/Utils/Audio/AudioManager.cpp
    ${SRC_DIR}/Utils/Audio/Buffer.cpp
    ${SRC_DIR}/Utils/Audio/IStream.cpp
    ${SRC_DIR}/Utils/Audio/OGGSound.cpp
    ${SRC_DIR}/Utils/Audio/OGGSoundFactory.cpp
    ${SRC_DIR}/Utils/Audio/OGGStream.cpp
    ${SRC_DIR}/Utils/Audio/PCMSound.cpp
    ${SRC_DIR}/Utils/Audio/PCMStream.cpp
    ${SRC_DIR}/Utils/Audio/Sound.cpp
    ${SRC_DIR}/Utils/Audio/SoundPlayer.cpp
)

set(UTILS_FREETYPE_SOURCES
    ${SRC_DIR}/Utils/FreeType/Font.cpp
    ${SRC_DIR}/Utils/FreeType/FontManager.cpp
)

set(UTILS_GRAPHICS_SOURCES
    ${SRC_DIR}/Utils/Graphics/AnimationSprite.cpp
    ${SRC_DIR}/Utils/Graphics/GraphicsManager.cpp
    ${SRC_DIR}/Utils/Graphics/PNGTextureFactory.cpp
    ${SRC_DIR}/Utils/Graphics/Sprite.cpp
    ${SRC_DIR}/Utils/Graphics/SpriteFactory.cpp
    ${SRC_DIR}/Utils/Graphics/StaticSprite.cpp
    ${SRC_DIR}/Utils/Graphics/Texture.cpp
    ${SRC_DIR}/Utils/Graphics/TextureManager.cpp
)

set(UTILS_UI_SOURCES
    ${SRC_DIR}/Utils/UI/Button.cpp
    ${SRC_DIR}/Utils/UI/Component.cpp
    ${SRC_DIR}/Utils/UI/ComponentFactory.cpp
    ${SRC_DIR}/Utils/UI/Container.cpp
    ${SRC_DIR}/Utils/UI/Dialog.cpp
    ${SRC_DIR}/Utils/UI/Label.cpp
    ${SRC_DIR}/Utils/UI/LoadingAnimation.cpp
    ${SRC_DIR}/Utils/UI/Menu.cpp
    ${SRC_DIR}/Utils/UI/MenuFactory.cpp
    ${SRC_DIR}/Utils/UI/Picture.cpp
)

set(UTILS_SOURCES
    ${UTILS_AUDIO_SOURCES}
    ${UTILS_GRAPHICS_SOURCES}
    ${UTILS_FREETYPE_SOURCES}
    ${UTILS_UI_SOURCES}
    ${SRC_DIR}/Utils/LocalizationManager.cpp
    ${SRC_DIR}/Utils/Lua.cpp
    ${SRC_DIR}/Utils/PCResourceLoader.cpp
    ${SRC_DIR}/Utils/ResourceLoader.cpp
    ${SRC_DIR}/Utils/ResourceManager.cpp
)

set(${PROJECT_NAME}_SOURCES
    ${ENGINE_SOURCES}
    ${LUA_API_SOURCES}
    ${UTILS_SOURCES}
    ${SRC_DIR}/main.cpp
    ${SRC_DIR}/Application.cpp
)

set(ENGINE_GAME_STATES_HEADERS
    ${INCLUDE_DIR}/Engine/GameStates/IGameState.hpp
    ${INCLUDE_DIR}/Engine/GameStates/LoadingState.hpp
    ${INCLUDE_DIR}/Engine/GameStates/MenuState.hpp
    ${INCLUDE_DIR}/Engine/GameStates/SingleGameState.hpp
    ${INCLUDE_DIR}/Engine/GameStates/StartLogoState.hpp
)

set(ENGINE_HEADERS
    ${ENGINE_GAME_STATES_HEADERS}
    ${INCLUDE_DIR}/Engine/Ball.hpp
    ${INCLUDE_DIR}/Engine/Block.hpp
    ${INCLUDE_DIR}/Engine/DebugOutput.hpp
    ${INCLUDE_DIR}/Engine/EasyBlock.hpp
    ${INCLUDE_DIR}/Engine/Game.hpp
    ${INCLUDE_DIR}/Engine/GameStates.hpp
    ${INCLUDE_DIR}/Engine/Object.hpp
    ${INCLUDE_DIR}/Engine/Platform.hpp
)

set(LUA_API_HEADERS
    ${INCLUDE_DIR}/LuaAPI/LuaAPI.hpp
    ${INCLUDE_DIR}/LuaAPI/Sprite_wrapper.hpp
)

set(UTILS_FREETYPE_HEADERS
    ${INCLUDE_DIR}/Utils/FreeType/Font.hpp
    ${INCLUDE_DIR}/Utils/FreeType/FontManager.hpp
)

set(UTILS_AUDIO_HEADERS
    ${INCLUDE_DIR}/Utils/Audio/AudioManager.hpp
    ${INCLUDE_DIR}/Utils/Audio/Buffer.hpp
    ${INCLUDE_DIR}/Utils/Audio/IStream.hpp
    ${INCLUDE_DIR}/Utils/Audio/OGGSound.hpp
    ${INCLUDE_DIR}/Utils/Audio/OGGSoundFactory.hpp
    ${INCLUDE_DIR}/Utils/Audio/OGGStream.hpp
    ${INCLUDE_DIR}/Utils/Audio/PCMSound.hpp
    ${INCLUDE_DIR}/Utils/Audio/PCMStream.hpp
    ${INCLUDE_DIR}/Utils/Audio/Sound.hpp
    ${INCLUDE_DIR}/Utils/Audio/SoundPlayer.hpp
)

set(UTILS_GRAPHICS_HEADERS
    ${INCLUDE_DIR}/Utils/Graphics/AnimationSprite.hpp
    ${INCLUDE_DIR}/Utils/Graphics/GraphicsManager.hpp
    ${INCLUDE_DIR}/Utils/Graphics/PNGTextureFactory.hpp
    ${INCLUDE_DIR}/Utils/Graphics/Sprite.hpp
    ${INCLUDE_DIR}/Utils/Graphics/SpriteFactory.hpp
    ${INCLUDE_DIR}/Utils/Graphics/StaticSprite.hpp
    ${INCLUDE_DIR}/Utils/Graphics/Texture.hpp
    ${INCLUDE_DIR}/Utils/Graphics/TextureManager.hpp
)

set(UTILS_UI_HEADERS
    ${INCLUDE_DIR}/Utils/UI/Button.hpp
    ${INCLUDE_DIR}/Utils/UI/Component.hpp
    ${INCLUDE_DIR}/Utils/UI/ComponentFactory.hpp
    ${INCLUDE_DIR}/Utils/UI/ComponentEvent_wrapper.hpp
    ${INCLUDE_DIR}/Utils/UI/Container.hpp
    ${INCLUDE_DIR}/Utils/UI/Dialog.hpp
    ${INCLUDE_DIR}/Utils/UI/Event.hpp
    ${INCLUDE_DIR}/Utils/UI/KeyEvent.hpp
    ${INCLUDE_DIR}/Utils/UI/Label.hpp
    ${INCLUDE_DIR}/Utils/UI/LoadingAnimation.hpp
    ${INCLUDE_DIR}/Utils/UI/Menu.hpp
    ${INCLUDE_DIR}/Utils/UI/MenuFactory.hpp
    ${INCLUDE_DIR}/Utils/UI/MouseEvent.hpp
    ${INCLUDE_DIR}/Utils/UI/Picture.hpp
)

set(UTILS_HEADERS
    ${UTILS_AUDIO_HEADERS}
    ${UTILS_GRAPHICS_HEADERS}
    ${UTILS_FREETYPE_HEADERS}
    ${UTILS_UI_HEADERS}
    ${INCLUDE_DIR}/Utils/assert.hpp
    ${INCLUDE_DIR}/Utils/Audio.hpp
    ${INCLUDE_DIR}/Utils/Color.hpp
    ${INCLUDE_DIR}/Utils/FreeType.hpp
    ${INCLUDE_DIR}/Utils/Graphics.hpp
    ${INCLUDE_DIR}/Utils/LocalizationManager.hpp
    ${INCLUDE_DIR}/Utils/Lua.hpp
    ${INCLUDE_DIR}/Utils/MouseButton.hpp
    ${INCLUDE_DIR}/Utils/PCResourceLoader.hpp
    ${INCLUDE_DIR}/Utils/ResourceLoader.hpp
    ${INCLUDE_DIR}/Utils/ResourceManager.hpp
    ${INCLUDE_DIR}/Utils/Singleton.hpp
    ${INCLUDE_DIR}/Utils/SingletonPointer.hpp
    ${INCLUDE_DIR}/Utils/UI.hpp
)

set(${PROJECT_NAME}_HEADERS
    ${ENGINE_HEADERS}
    ${LUA_API_HEADERS}
    ${TINY_XML_HEADERS}
    ${UTILS_HEADERS}
    ${INCLUDE_DIR}/Application.hpp
    ${INCLUDE_DIR}/config.h
    ${INCLUDE_DIR}/geometry_defines.hpp
    ${INCLUDE_DIR}/gl_includes.h
    ${INCLUDE_DIR}/salt_defines.h
    ${INCLUDE_DIR}/Engine.hpp
    ${INCLUDE_DIR}/LuaAPI.hpp
    ${INCLUDE_DIR}/Utils.hpp
)

if(WIN32)
    set(${PROJECT_NAME}_SOURCES ${${PROJECT_NAME}_SOURCES} ${SRC_DIR}/resource.rc)
endif()

set(${PROJECT_NAME}_LIBS
    ${Boost_SYSTEM_LIBRARY}
    ${LUA_LIBRARIES}
    ${OPENAL_LIBRARY}
    ${OPENGL_LIBRARIES}
    ${PNG_LIBRARIES}
    ${OGG_LIBRARY}
    ${SDL_LIBRARY}
    ${LUABIND_LIBRARIES}
    ${VORBISFILE_LIBRARY}
    FTGL
    TinyXML
)

if(NOT WIN32)
    include_directories(${GTK2_INCLUDE_DIRS})
    set(${PROJECT_NAME}_LIBS ${${PROJECT_NAME}_LIBS} ${GTK2_LIBRARIES})
endif()

configure_file(
    ${CMAKE_CURRENT_SOURCE_DIR}/config.h.in
    ${INCLUDE_DIR}/config.h
)

add_definitions(-DTIXML_USE_STL)

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/TinyXML)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/FTGL)

add_executable(${PROJECT_NAME} WIN32 ${${PROJECT_NAME}_HEADERS} ${${PROJECT_NAME}_SOURCES})
target_link_libraries(${PROJECT_NAME} ${${PROJECT_NAME}_LIBS})

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tests)
