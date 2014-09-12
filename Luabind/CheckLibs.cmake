find_package(Lua51 REQUIRED)

if(NOT LUA51_FOUND)
    message(FATAL_ERROR "Can't find Lua 5.1!")
    return()
endif()

find_package(Boost 1.53.0 REQUIRED)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Can't find Boost")
    return()
endif ()