#ifndef _SALT2D_UTILS_RESOURCEMANAGER_HPP
#define _SALT2D_UTILS_RESOURCEMANAGER_HPP

#include <algorithm>
#include <map>
#include <mutex>
#include <stdexcept>
#include <string>

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

#include <Utils/assert.hpp>
#include <Utils/ResourceLoader.hpp>
#include <Utils/Singleton.hpp>

#include <Utils/Audio/Sound.hpp>
#include <Utils/Graphics/Texture.hpp>

#include <Utils/FreeType/Font.hpp>

namespace Utils {

    /** Менеджер ресурсов.
      * @author Elijah Vlasov
    */

    class ResourceManager: public Singleton<ResourceManager> {

        SINGLETON(ResourceManager)

        public:

            template <class ResourceType>
            boost::shared_ptr<ResourceType> getResource(const char* fileName)
                                            throw(std::invalid_argument, std::runtime_error)
            {

                ASSERT(
                    (fileName != 0),
                    std::invalid_argument("fileName")
                );

                return getResource<ResourceType>(std::string(fileName));

            }

            template <class ResourceType>
            boost::shared_ptr<ResourceType> getResource(const std::string& fileName)
                                            throw(std::invalid_argument, std::runtime_error)
            {

                ASSERT(
                    (!fileName.empty()),
                    std::invalid_argument("fileName")
                );

                typedef std::map< std::string, boost::shared_ptr<ResourceType> > MapType;

                MapType& resourcesMap = getResourcesMap<ResourceType>();

                std::lock_guard<std::mutex> guard(getResourcesAccessMutex<ResourceType>());

                auto resourceIter = resourcesMap.find(fileName);

                if(resourceIter != resourcesMap.end()) {
                    return resourceIter->second;
                }

                std::lock_guard<std::mutex> resourceLoaderGuard(resourceLoaderAccess_);

                ASSERT(
                    (resourceLoader_ != 0),
                    std::runtime_error(
                        (boost::format("Can't load resource \"%1%\"")
                            % fileName
                        ).str()
                    )
                );

                auto newResource = loadResource<ResourceType>(fileName);

                resourcesMap[fileName] = newResource;

                return newResource;

            }



            template <class ResourceType>
            void deleteResource(const boost::shared_ptr<ResourceType>& resource) {

                std::lock_guard<std::mutex> guard(getResourcesAccessMutex<ResourceType>());

                typedef std::map<  std::string, boost::shared_ptr<ResourceType> > MapType;
                typedef std::pair< std::string, boost::shared_ptr<ResourceType> > PairType;

                MapType& resourcesMap = getResourcesMap<ResourceType>();

                auto resourceIter = std::find_if(resourcesMap.begin(), resourcesMap.end(), [=] (const PairType& elem) -> bool {
                                                                        return elem.second == resource;
                                                                    }
                );

                resourcesMap.erase(resourceIter->first);


            }

            inline std::string getFileData(const char* fileName)
                                                    throw(std::invalid_argument, std::runtime_error);

            std::string getFileData(const std::string& fileName)
                                                    throw(std::invalid_argument, std::runtime_error);


            /** Установить загрузчик ресурсов.
              *
            */

            void setResourceLoader(ResourceLoader* resourceLoader)
                                                    throw(std::invalid_argument);

        protected:

            ResourceManager();

        private:

            template <class ResourceType>
            std::map< std::string, boost::shared_ptr<ResourceType> >& getResourcesMap();

            template <class ResourceType>
            boost::shared_ptr<ResourceType> loadResource(const std::string& name) throw(std::invalid_argument, std::runtime_error);

            template <class ResourceType>
            std::mutex& getResourcesAccessMutex();

            std::mutex resourceLoaderAccess_;
            ResourceLoader* resourceLoader_;

            std::mutex fontsAccess_;
            std::map< std::string, boost::shared_ptr<FreeType::Font> >  fonts_;

            std::mutex texturesAccess_;
            std::map< std::string, boost::shared_ptr<Graphics::Texture> >         textures_;

            std::mutex soundsAccess_;
            std::map< std::string, boost::shared_ptr<Audio::Sound> >           sounds_;

    };

    std::string ResourceManager::getFileData(const char* fileName) throw(std::invalid_argument, std::runtime_error) {

        ASSERT(
            (fileName != 0),
            std::invalid_argument("fileName")
        );

        return getFileData(std::string(fileName));

    }

}

#endif
