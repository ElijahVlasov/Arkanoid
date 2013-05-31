#ifndef _SALT2D_UTILS_PCRESOURCELOADER_HPP
#define _SALT2D_UTILS_PCRESOURCELOADER_HPP

#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <IL/il.h>

#include <Utils/Resource.hpp>
#include <Utils/ResourceLoader.hpp>
#include <Utils/Singleton.hpp>
#include <Utils/Texture.hpp>

namespace Utils {

    /** Загрузчик ресурсов для ПК.
      * @author Elijah Vlasov
    */

    class PCResourceLoader: public Singleton<PCResourceLoader>,
                                public ResourceLoader {

        SINGLETON(PCResourceLoader)

        public:

            boost::shared_ptr<Resource> loadResource(ResourceType resourceType, const char* resourceName)
                                                        throw(std::invalid_argument, std::runtime_error);

        protected:

            PCResourceLoader();

        private:

            boost::shared_ptr<Resource> loadTexture(const char* fileName)    throw(std::runtime_error);
            boost::shared_ptr<Resource> loadFont(const char* fileName)       throw(std::runtime_error);
            boost::shared_ptr<Resource> loadPlainText(const char* fileName)  throw(std::runtime_error);
            boost::shared_ptr<Resource> loadBinaryFile(const char* fileName) throw(std::runtime_error);

            void ILImageToTexture(ILuint ilTex, Texture* texture);

    };

}

#endif
