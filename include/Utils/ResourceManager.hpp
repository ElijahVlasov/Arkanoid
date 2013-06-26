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

            boost::shared_ptr<Resource> getResource(ResourceType resourceType, const char* resourceName)
                                                    throw(std::invalid_argument, std::runtime_error);

            /** Получить ресурс.
              * @param resourceName имя ресурса
              * @throws Генерирует std::invalid_argument, если resourceName -
              *         пустая строка. Генерирует std::runtime_error
              *         при ошибках загрузки ресурсов.
            */

            boost::shared_ptr<Resource> getResource(ResourceType resourceType, const std::string& resourceName)
                                                    throw(std::invalid_argument, std::runtime_error);


            /** Удалить ресурс. Когда не требуется хранить ресурс в памяти, следует вызвать этот метод,
              * иначе возможны утечки памяти.
            */

            void deleteResource(const boost::shared_ptr<Resource>& resource);

            /** Установить загрузчик ресурсов.
              *
            */

            void setResourceLoader(ResourceLoader* resourceLoader)
                                                    throw(std::invalid_argument);

        protected:

            ResourceManager();

        private:

            ResourceLoader* resourceLoader_;

            std::map< std::string, boost::shared_ptr<Resource> > resources_;
            std::mutex managerMutex_;

    };

}

#endif
