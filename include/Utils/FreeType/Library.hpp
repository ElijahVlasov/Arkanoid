#ifndef _SALT2D_UTILS_FREETYPE_LIBRARY_HPP
#define _SALT2D_UTILS_FREETYPE_LIBRARY_HPP

#include <map>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>

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

                FT_Face createFaceFromFile(const char* fileName, unsigned int index)
                                                            throw(std::invalid_argument, std::runtime_error);

				FT_Face createFaceFromFile(const std::string& fileName, unsigned int index)
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

                std::mutex synchroMutex_;

                FT_Library getLibrary() throw(std::runtime_error);

                // Объекты библиотеки для каждого потока приложения
                std::map< std::thread::id, FT_Library> libraries_;

                //FT_Library library_;

        };

    }

}

#endif
