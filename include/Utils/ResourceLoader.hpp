#ifndef _SALT2D_UTILS_RESOURCELOADER_HPP
#define _SALT2D_UTILS_RESOURCELOADER_HPP

#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/Audio/Sound.hpp>
#include <Utils/Graphics/Texture.hpp>

#include <Utils/FreeType/Font.hpp>

namespace Utils {

    using namespace FreeType;

    /** Загрузчик ресурсов.
      * Унифицирует доступ к ресурсам на разных ОС.
      * Потомки должны определять load* методы, для загрузки
      * каждого из типов ресурсов.
      * @author Elijah Vlasov
    */

    class ResourceLoader {

        public:

            virtual std::string readFile(const char* fileName)
                                        throw(std::invalid_argument, std::runtime_error) = 0;

            inline  std::string readFile(const std::string& fileName)
                                        throw(std::invalid_argument, std::runtime_error);


            virtual boost::shared_ptr<Graphics::Texture> loadTexture(const char* fileName)
                                        throw(std::invalid_argument, std::runtime_error);

            inline  boost::shared_ptr<Graphics::Texture> loadTexture(const std::string& fileName)
                                        throw(std::invalid_argument, std::runtime_error);

            virtual boost::shared_ptr<Audio::Sound>   loadSound(const char* fileName)
                                        throw(std::invalid_argument, std::runtime_error);

            inline  boost::shared_ptr<Audio::Sound>   loadSound(const std::string& fileName)
                                        throw(std::invalid_argument, std::runtime_error);

            virtual boost::shared_ptr<Font>    loadFont(const char* fileName)
                                        throw(std::invalid_argument, std::runtime_error);

            inline  boost::shared_ptr<Font>    loadFont(const std::string& fileName)
                                        throw(std::invalid_argument, std::runtime_error);

    };

    std::string ResourceLoader::readFile(const std::string& fileName) throw(std::invalid_argument, std::runtime_error) {

        return readFile(fileName.c_str());

    }

    boost::shared_ptr<Graphics::Texture> ResourceLoader::loadTexture(const std::string& fileName) throw(std::invalid_argument, std::runtime_error) {

        return loadTexture(fileName.c_str());

    }

    boost::shared_ptr<Audio::Sound> ResourceLoader::loadSound(const std::string& fileName) throw(std::invalid_argument, std::runtime_error) {

        return loadSound(fileName.c_str());

    }

    boost::shared_ptr<Font> ResourceLoader::loadFont(const std::string& fileName) throw(std::invalid_argument, std::runtime_error) {

        return loadFont(fileName.c_str());

    }

}

#endif
