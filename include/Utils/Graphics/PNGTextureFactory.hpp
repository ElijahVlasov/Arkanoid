#ifndef _SALT2D_UTILS_GRAPHICS_PNGTEXTUREFACTORY_HPP
#define _SALT2D_UTILS_GRAPHICS_PNGTEXTUREFACTORY_HPP

#include <istream>
#include <list>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>

#include <boost/shared_ptr.hpp>

#include <png.h>

#include <Utils/assert.hpp>
#include <Utils/Singleton.hpp>

#include <Utils/Graphics/Texture.hpp>

#define PNG_SIG_SIZE  8

namespace Utils {

    namespace Graphics {

        /** Строитель, создающий из PNG-буферов текстуры.
          * @author Elijah Vlasov
        */

        class PNGTextureFactory: public Singleton<PNGTextureFactory> {

            SINGLETON(PNGTextureFactory)

            public:

                /** Создать текстуру из буфера, содержащего данные PNG-файла.
                  * @throws Генерирует invalid_argument, если buffer.size() == 0.
                  *         runtime_error - при ошибках libPNG.
                */

                boost::shared_ptr<Texture> createTexture(const std::string& buffer) throw(std::invalid_argument, std::runtime_error);

            private:

                struct PNGReadStruct { // структура, для выделения и освобождения PNG read структуры

                    inline PNGReadStruct() throw(std::runtime_error):
                        readStruct( png_create_read_struct(PNG_LIBPNG_VER_STRING, 0, PNGErrFunc, 0) )
                    {

                        ASSERT(
                            (readStruct != 0),
                            std::runtime_error("Can't create PNG read structure!")
                        );

                        infoStruct = png_create_info_struct(readStruct);

                        if(infoStruct == 0) {

                            png_destroy_read_struct(&readStruct, static_cast<png_infopp>(0), static_cast<png_infopp>(0));

                            throw(std::runtime_error("Can't create PNG info structure"));

                        }

                    }

                    inline ~PNGReadStruct() {

                        png_destroy_read_struct(&readStruct, &infoStruct, static_cast<png_infopp>(0));

                    }

                    png_structp readStruct;
                    png_infop   infoStruct;

                };

                inline static bool checkPNG(std::istream& pngStream);

                boost::shared_ptr<Texture> PNGToTexture(png_structp readStruct, png_infop infoStruct) throw(std::runtime_error);

                static void PNGReadFunc(png_structp readStruct, png_bytep data, png_size_t length);

                static void PNGErrFunc(png_structp readStruct, const char* errString);

        };

        // Проверить сигнатуру PNG.
        bool PNGTextureFactory::checkPNG(std::istream& pngStream) {

            png_byte pngSig[PNG_SIG_SIZE];

            pngStream.read(reinterpret_cast<char*>(pngSig), PNG_SIG_SIZE);

            if(!pngStream.good()) {
                return false;
            }

            return (png_sig_cmp(pngSig, 0, PNG_SIG_SIZE) == 0);

        }

    }

}

#endif
