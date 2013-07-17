#include <cstring>

#include <ios>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <boost/format.hpp>
#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>

#include <png.h>
#include <pngconf.h>

#include <Utils.hpp>

#include <Utils/PCResourceLoader.hpp>
#include <Utils/TextureFactory.hpp>

#include "salt_defines.h"
#include "gl_includes.h"

using namespace std;

using namespace Utils;

using namespace Utils::FreeType;



PCResourceLoader::PCResourceLoader():
    textureFactory_(TextureFactory::getInstance())
{}



boost::shared_ptr<Resource> PCResourceLoader::loadPlainText(const char* resourceName) throw(runtime_error) {

    // Получаем строку вида ресурсы/имя_ресурса
    string path = (boost::format("%1%/%2%")
                      % RESOURCE_PATH % resourceName
                  ).str();

    ResourceFile* resource = new ResourceFile();

    ifstream resourceStream(path);

    // Если ошибка потока
    ASSERT(
        resourceStream.good(),
        runtime_error(
            (boost::format("Can't find file \"%1%\"")
                % path
            ).str()
        )
    );

    string data = Utils::readStreamToString(resourceStream);

    resource->setData(data);

    return boost::shared_ptr<Resource>(resource);

}



boost::shared_ptr<Resource> PCResourceLoader::loadBinaryFile(const char* resourceName) throw(runtime_error) {

     // Получаем строку вида ресурсы/имя_ресурса
    string path = (boost::format("%1%/%2%")
                      % RESOURCE_PATH % resourceName
                  ).str();

    ResourceFile* resource = new ResourceFile();

    ifstream resourceStream(path, ios::binary);

    // Если ошибка потока
    ASSERT(
        resourceStream.good(),
        runtime_error(
            (boost::format("Can't find file \"%1%\"")
                % path
            ).str()
        )
    );

    string data = Utils::readBinaryStream(resourceStream);

    resource->setData(data);

    return boost::shared_ptr<Resource>(resource);

}



boost::shared_ptr<Resource> PCResourceLoader::loadFont(const char* resourceName) throw(runtime_error) {

    boost::shared_ptr<Resource> resource = loadBinaryFile(resourceName);

    Font* font = new Font();

    string fontData = resource->getData();

    font->setData(fontData);

    return boost::shared_ptr<Font>(font);

}



boost::shared_ptr<Resource> PCResourceLoader::loadSound(const char* fileName) throw(runtime_error) {

    Sound* sound = new Sound();

    return boost::shared_ptr<Sound>(sound);

}



boost::shared_ptr<Resource> PCResourceLoader::loadTexture(const char* resourceName) throw(runtime_error) {

    boost::shared_ptr<Resource> textureResource = loadBinaryFile(resourceName);

    boost::shared_ptr<Texture> texture = textureFactory_->createFromPNGBuffer(textureResource->getData());

    return texture;

}
