#include <cstring>

#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/assert.hpp>

#include <Utils/Resource.hpp>
#include <Utils/ResourceLoader.hpp>

using namespace std;

using namespace Utils;



boost::shared_ptr<Resource> ResourceLoader::loadResource(ResourceLoader::ResourceType resourceType, const char* resourceName) throw(invalid_argument, runtime_error) {

    ASSERT(
        (resourceName != 0),
        invalid_argument("resourceName")
    );

    ASSERT(
        (strlen(resourceName) != 0),
        invalid_argument("resourceName")
    );

    switch(resourceType) {

        case BINARY_FILE: {
            return loadBinaryFile(resourceName);
        }
        break;

        case PLAIN_TEXT: {
            return loadPlainText(resourceName);
        }
        break;

        case TEXTURE: {
            return loadTexture(resourceName);
        }
        break;

        case FONT: {
            return loadFont(resourceName);
        }
        break;

        case SOUND: {
            return loadSound(resourceName);
        }
        break;

    }

    return boost::shared_ptr<Resource>((Resource*)0);

}



boost::shared_ptr<Resource> ResourceLoader::loadResource(ResourceLoader::ResourceType resourceType, const std::string& resourceName) throw(invalid_argument, runtime_error) {

    return loadResource(resourceType, resourceName.c_str());

}
