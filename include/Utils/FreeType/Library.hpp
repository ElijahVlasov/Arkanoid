#ifndef _SALT2D_UTILS_FREETYPE_LIBRARY_HPP
#define _SALT2D_UTILS_FREETYPE_LIBRARY_HPP

#include <stdexcept>
#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Utils/Singleton.hpp>

namespace Utils {

    namespace FreeType {

        /** Класс-обертка над Freetype2 FT_Library.
          * @author Elijah Vlasov
        */

        class Library: public Utils::Singleton<Library> {

            SINGLETON(Library)

            public:

                /** Загрузит шрифт в буфер.
                  * @param filePath Имя файла с шрифтом.
                  * @throws Генерирует std::invalid_argument, если filePath == NULL,
                  *         или пустая строка. Генерирует std::runtime_error, если 
                  *         невозможно открыть файл.
                  * @returns Содержимое файла шрифта.
                */

                std::string loadFaceFile(const char* filePath) 
                                                            throw(std::invalid_argument, std::runtime_error);

                /** Загрузит шрифт в буфер.
                  * @param filePath Имя файла с шрифтом.
                  * @throws Генерирует std::invalid_argument, если filePath пустая строка. 
                  *         Генерирует std::runtime_error, если невозможно открыть файл.
                  * @returns Содержимое файла шрифта.
                */

                std::string loadFaceFile(const std::string& filePath) 
                                                            throw(std::invalid_argument, std::runtime_error);

                /** Создать шрифт из буфера.
                  * @param buffer Буфер шрифта
                  * @param index Индекс шрифта в буфере
                  * @throws Генерирует std::invalid_argument, если buffer.size() == 0.
                  *         Генерирует std::runtime_error, если buffer имеет неверный
                  *         формат.
                */ 

                FT_Face createFaceFromBuffer(const std::string& buffer, unsigned int index) 
                                                            throw(std::invalid_argument, std::runtime_error);

            protected:

                Library() throw(std::runtime_error);

                ~Library();

            private:

                FT_Library library_;

        };

    }

}

#endif
