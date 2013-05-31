#include <cstring>

#include <map>
#include <mutex>
#include <stdexcept>
#include <string>

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

#include <Utils/assert.hpp>
#include <Utils/Resource.hpp>
#include <Utils/ResourceLoader.hpp>
#include <Utils/ResourceManager.hpp>

using namespace std;

using namespace Utils;



ResourceManager::ResourceManager(): resourceLoader_(0)
{}



boost::shared_ptr<Resource> ResourceManager::getResource(ResourceLoader::ResourceType resourceType, const char* resourceName) throw(invalid_argument, runtime_error) {

    ASSERT(
        (resourceName != 0),
        invalid_argument("resourceName")
    );

    ASSERT(
        (strlen(resourceName) != 0),
        invalid_argument("resourceName")
    );

    string strResName = resourceName;

    std::lock_guard<std::mutex> lockGuard(managerMutex_);

    map<string, boost::shared_ptr<Resource>>::iterator res = resources_.find(string(strResName)); // Находим нужный ресурс

    if(res != resources_.end()) { // ресурс найден
        return res->second;
    }

    ASSERT( // если нет загрузчика ресурсов
        (resourceLoader_ != 0),
        runtime_error(
            (boost::format("Can't load resource \"%1%\"")
                % resourceName
            ).str()
        )
    );

    boost::shared_ptr<Resource> newRes = resourceLoader_->loadResource(resourceType, resourceName); // загружаем ресурс

    resources_[strResName] = newRes;

    return newRes;

}



boost::shared_ptr<Resource> ResourceManager::getResource(ResourceLoader::ResourceType resourceType, const string& resourceName) throw(invalid_argument, runtime_error) {

    return getResource(resourceType, resourceName.c_str());

}



void ResourceManager::setResourceLoader(ResourceLoader* resourceLoader) throw(invalid_argument) {

    ASSERT(
        (resourceLoader != 0),
        invalid_argument("resourceLoader")
    );

    std::lock_guard<std::mutex> lockGuard(managerMutex_);

    resourceLoader_ = resourceLoader;

}
