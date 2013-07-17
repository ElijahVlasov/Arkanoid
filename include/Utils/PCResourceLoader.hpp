#ifndef _SALT2D_UTILS_PCRESOURCELOADER_HPP
#define _SALT2D_UTILS_PCRESOURCELOADER_HPP

#include <istream>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <png.h>

#include <Utils/Resource.hpp>
#include <Utils/ResourceLoader.hpp>
#include <Utils/Singleton.hpp>
#include <Utils/SingletonPointer.hpp>
#include <Utils/Texture.hpp>
#include <Utils/TextureFactory.hpp>

namespace Utils {

    /** Загрузчик ресурсов для ПК.
      * @author Elijah Vlasov
    */

    class PCResourceLoader: public Singleton<PCResourceLoader>,
                                public ResourceLoader {

        SINGLETON(PCResourceLoader)

        protected:

            PCResourceLoader();

            boost::shared_ptr<Resource> loadSound(const char* fileName)      throw(std::runtime_error);
            boost::shared_ptr<Resource> loadTexture(const char* fileName)    throw(std::runtime_error);
            boost::shared_ptr<Resource> loadFont(const char* fileName)       throw(std::runtime_error);
            boost::shared_ptr<Resource> loadPlainText(const char* fileName)  throw(std::runtime_error);
            boost::shared_ptr<Resource> loadBinaryFile(const char* fileName) throw(std::runtime_error);

        private:

            SingletonPointer<TextureFactory> textureFactory_;


    };

}

#endif
