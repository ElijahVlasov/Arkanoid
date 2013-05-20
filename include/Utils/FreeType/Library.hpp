#ifndef _SALT2D_UTILS_FREETYPE_LIBRARY_HPP
#define _SALT2D_UTILS_FREETYPE_LIBRARY_HPP

#include <stdexcept>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Utils/Singleton.hpp>

namespace Utils {

    namespace FreeType {

        class Library: public Utils::Singleton<Library> {

            SINGLETON(Library)

            public:

                // filePath - путь до файла с шрифтом, index - индекс в файле
                // в faceBuf будет загружена структура FT_Face
                std::string loadFaceFile(const char* filePath) 
                                                            throw(std::invalid_argument, std::runtime_error);
                std::string loadFaceFile(const std::string& filePath) 
                                                            throw(std::invalid_argument, std::runtime_error);

                FT_Face createFaceFromBuffer(const std::string& buffer, unsigned int index) 
                                                            throw(std::invalid_argument, std::runtime_error);

            protected:

                // генерирует runtime_error, если невозможно
                // загрузить FreeType библиотеку
                Library() throw(std::runtime_error);

                ~Library();

            private:

                FT_Library library_;

        };

    }

}

#endif
