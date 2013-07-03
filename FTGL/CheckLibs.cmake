find_package(Freetype REQUIRED)

if(NOT FREETYPE_FOUND)
    message(FATAL_ERROR "Can't find FreeType!")
    return()
endif()

find_package(OpenGL REQUIRED)

if(NOT OPENGL_FOUND)
    message(FATAL_ERROR "Can't find OpenGL!")
    return()
endif()