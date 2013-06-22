#ifndef _SALT2D_UTILS_RESOURCEMANAGER_HPP
#define _SALT2D_UTILS_RESOURCEMANAGER_HPP

#include <map>
#include <mutex>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/Resource.hpp>
#include <Utils/ResourceLoader.hpp>
#include <Utils/Singleton.hpp>

namespace Utils {

    /** Менеджер ресурсов.
      * @author Elijah Vlasov
    */

    class ResourceManager: public Singleton<ResourceManager> {

        SINGLETON(ResourceManager)

        public:

            typedef ResourceLoader::ResourceType ResourceType;

            /** Получить ресурс.
              * @param resourceName имя ресурса
              * @throws Генерирует std::invalid_argument, если resourceName == NULL, или
              *         resourceName - пустая строка. Генерирует std::runtime_error
              *         при ошибках загрузки ресурсов.
            */

            boost::shared_ptr<Resource> getResource(ResourceLoader::ResourceType resourceType, const char* resourceName)
                                                    throw(std::invalid_argument, std::runtime_error);

            /** Получить ресурс.
              * @param resourceName имя ресурса
              * @throws Генерирует std::invalid_argument, если resourceName -
              *         пустая строка. Генерирует std::runtime_error
              *         при ошибках загрузки ресурсов.
            */

            boost::shared_ptr<Resource> getResource(ResourceLoader::ResourceType resourceType, const std::string& resourceName)
                                                    throw(std::invalid_argument, std::runtime_error);

            /** Установить загрузчик ресурсов.
              *
            */

            void setResourceLoader(ResourceLoader* resourceLoader)
                                                    throw(std::invalid_argument);

        protected:

            ResourceManager();

        private:

            ResourceLoader* resourceLoader_;

            std::map<std::string, boost::shared_ptr<Resource>> resources_;
            std::mutex managerMutex_;

    };

}

#endif
