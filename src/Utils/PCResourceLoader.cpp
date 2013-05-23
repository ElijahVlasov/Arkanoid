#include <cstring>

#include <ios>
#include <fstream>
#include <stdexcept>
#include <string>

#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

#include "config.h"

#ifdef MS_WINDOWS
#include <Windows.h>
#endif

#include <GL/gl.h>

#include <IL/il.h>
#include <IL/ilu.h>

#include <Utils.hpp>

#include <Utils/PCResourceLoader.hpp>

using namespace std;

using namespace Utils;



PCResourceLoader::PCResourceLoader() {

    ilInit();
    iluInit();

}



boost::shared_ptr<Resource> PCResourceLoader::loadResource(ResourceLoader::ResourceType resourceType, const char* resourceName) 
                                                throw(invalid_argument, runtime_error) {

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

    }

    return boost::shared_ptr();

}



boost::shared_ptr<Resource> PCResourceLoader::loadPlainText(const char* resourceName) throw(runtime_error) {

    // Получаем строку вида ресурсы/имя_ресурса
    string path = (boost::format("%1%/%2%")
                      % RESOURCE_PATH % resourceName
                  ).str();

    ResourceFile* resource = new ResourceFile();

    ifstream resourcetStream(path);

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



boost::shared_ptr<Resource> PCResourceLoader::loadTexture(const char* resourceName) throw(runtime_error) {

    string path = (boost::format("%1%/%2%")
                      % TEXTURE_PATH % fileName
                  ).str();

    boost::shared_ptr<Resource> resource = loadBinaryFile(resourceName);

    Texture* texture = new Texture();

    string textureData = resource.getData();

    ILuint ilTexture;

    ilGenImages(1, &ilTexture);

    ilBindImage(ilTexture);

    ASSERT(
        ilLoadL(IL_PNG, textureData.data(), textureData.size()),
        runtime_error(
            (boost::format("Can't load \"%1%\":\n%2%")
                % resourceName
                % iluErrorString(ilGetError()))
            ).str()
        )
    );

    ILImageToTexture(ilTexture, texture);

    return boost::shared_ptr<Resource>(texture);

}



void PCResourceLoader::ILImageToTexture(ILuint ilTex, Texture* texture) {

    unsigned int width, height, bpp;

    ilBindImage(texture);

    width   =  ilGetInteger(IL_IMAGE_WIDTH);
    height  =  ilGetInteger(IL_IMAGE_HEIGHT);

    texture->setWidth(width);
    texture->setHeight(height);

    ILint format = ilGetInteger(IL_IMAGE_FORMAT);

    switch(format) {

        case IL_RGB: {
            texture->setFormat(GL_RGB);
            bpp = 3;
        }
        break;

        case IL_RGBA: {
            texture->setFormat(GL_RGBA);
            bpp = 4;
        }
        break;

    }

    string textureData;

    textureData.resize(width * height * bpp);

    ilCopyPixels(0, 0, 0,
                 width, height, 1,
                 format, IL_UNSIGNED_BYTE, const_cast<ILvoid*>(textureData.data())
                );

    texture->setData(textureData);

}
