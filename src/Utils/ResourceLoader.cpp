#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/Resource.hpp>
#include <Utils/ResourceLoader.hpp>

using namespace std;

using namespace Utils;



boost::shared_ptr<Resource> ResourceLoader::loadResource(ResourceType resourceType, const std::string& resourceName) throw(invalid_argument, runtime_error) {

    return loadResource(resourceType, resourceName.c_str());

}
