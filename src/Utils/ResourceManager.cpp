#include <cstring>

#include <algorithm>
#include <functional>
#include <map>
#include <mutex>
#include <stdexcept>
#include <string>

#include <boost/format.hpp>
#include <boost/local_function.hpp>
#include <boost/shared_ptr.hpp>

#include <Utils/assert.hpp>
#include <Utils/ResourceLoader.hpp>
#include <Utils/ResourceManager.hpp>

#include <Utils/FreeType/Font.hpp>

using namespace std;

using namespace Utils;
using namespace FreeType;



ResourceManager::ResourceManager():
    resourceLoader_(0)
{}



string ResourceManager::getFileData(const string& fileName) throw(invalid_argument, runtime_error) {

    std::lock_guard<std::mutex> guard(resourceLoaderAccess_);

    ASSERT( // если нет загрузчика ресурсов
        (resourceLoader_ != 0),
        runtime_error(
            (boost::format("Can't load resource \"%1%\"")
                % fileName
            ).str()
        )
    );

    return resourceLoader_->readFile(fileName);

}



void ResourceManager::setResourceLoader(ResourceLoader* resourceLoader) throw(invalid_argument) {

    ASSERT(
        (resourceLoader != 0),
        invalid_argument("resourceLoader")
    );

    std::lock_guard<std::mutex> lockGuard(resourceLoaderAccess_);

    resourceLoader_ = resourceLoader;

}



namespace Utils {

template<> std::map< std::string, boost::shared_ptr<Font> >&
ResourceManager::getResourcesMap<Font>() {

    return fonts_;

}



template<> std::map< std::string, boost::shared_ptr<Texture> >&
ResourceManager::getResourcesMap<Texture>() {

    return textures_;

}



template<> std::map< std::string, boost::shared_ptr<Sound>  >&
ResourceManager::getResourcesMap<Sound>() {

    return sounds_;

}



template<>
boost::shared_ptr<Font> ResourceManager::loadResource<Font>(const std::string& name) throw(std::invalid_argument, std::runtime_error) {

    return resourceLoader_->loadFont(name);

}



template<>
boost::shared_ptr<Texture> ResourceManager::loadResource<Texture>(const std::string& name) throw(std::invalid_argument, std::runtime_error) {

    return resourceLoader_->loadTexture(name);

}



template<>
boost::shared_ptr<Sound> ResourceManager::loadResource<Sound>(const std::string& name) throw(std::invalid_argument, std::runtime_error) {

    return resourceLoader_->loadSound(name);

}



template<>
std::mutex& ResourceManager::getResourcesAccessMutex<Font>() {

    return fontsAccess_;

}



template<>
std::mutex& ResourceManager::getResourcesAccessMutex<Texture>() {

    return texturesAccess_;

}



template<>
std::mutex& ResourceManager::getResourcesAccessMutex<Sound>() {

    return soundsAccess_;

}


}
