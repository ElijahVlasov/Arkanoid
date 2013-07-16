#include <algorithm>
#include <list>
#include <mutex>
#include <thread>

#include <boost/foreach.hpp>
#include <boost/shared_array.hpp>

#include <Utils/TextureFactory.hpp>

#include "gl_includes.h"

using namespace std;

using namespace Utils;



const std::size_t TextureManager::MAX_TEXTURES_NUMBER = 128;
const std::size_t TextureManager::MIN_TEXTURES_NUMBER = 16;



TextureManager::TextureManager():
    mainThreadID_(std::this_thread::get_id())
{

    updateFreeTextures();

}



TextureManager::~TextureManager() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    updateTexturesForDelete();

    if(freeTextures_.empty()) {
        return;
    }

    boost::shared_array< GLuint > textures(new GLuint[freeTextures_.size()]);

    auto iter = freeTextures_.begin();

    for(std::size_t i = 0; iter != freeTextures_.end(); ++iter, ++i) {

        textures[i] = *iter;

    }

    glDeleteTextures(freeTextures_.size(), textures.get());

}



void TextureManager::update() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(std::this_thread::get_id() != mainThreadID_) {
        return;
    }

    updateFreeTextures();
    updateTexturesForDelete();
    updateTexturesForCreate();

}



GLuint TextureManager::createTexture() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    auto texture = freeTextures_.front();

    freeTextures_.pop_front();

    return texture;

}



void TextureManager::setTexture(GLuint texture, unsigned int width, unsigned int height, GLint format, const string& data) {

    if(std::this_thread::get_id() == mainThreadID_) {

        glBindTexture(GL_TEXTURE_2D, texture);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(

            GL_TEXTURE_2D,
            0,
            format,
            width,
            height,
            0,
            format,
            GL_UNSIGNED_BYTE,
            static_cast<const GLvoid*>(data.data())

        );

        return;

    }

    std::lock_guard<std::mutex> guard(synchroMutex_);

    TextureManager::TextureStruct textureForCreate = {texture, width, height, format, data};

    texturesForCreate_.push_back(textureForCreate);


}



void TextureManager::deleteTexture(GLuint texture) {

    if(std::this_thread::get_id() == mainThreadID_) {

        glDeleteTextures(1, &texture);

        return;

    }

    std::lock_guard<std::mutex> guard(synchroMutex_);

    texturesForDelete_.push_back(texture);

}



string TextureManager::getTextureData(GLuint texture) {

    string data;

    GLint width, height, format;

    unsigned int bpp;

    glBindTexture(GL_TEXTURE_2D, texture);

    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);

    switch(format) {

        case GL_RGB: {

            bpp = 3;

        }
        break;

        case GL_RGBA: {

            bpp = 4;

        }
        break;

    }

    data.resize(width * height * bpp);

    glGetTexImage(GL_TEXTURE_2D, 0, format, GL_UNSIGNED_BYTE, static_cast<GLvoid*>(const_cast<char*>(data.data())));

    return data;

}



void TextureManager::updateFreeTextures() {

    std::size_t freeNumber = freeTextures_.size();

    if(freeNumber >= MIN_TEXTURES_NUMBER) {
        return;
    }

    std::size_t needTexturesNumber = MAX_TEXTURES_NUMBER - freeNumber;

    boost::shared_array< GLuint > newTextures(new GLuint[needTexturesNumber]);

    glGenTextures(needTexturesNumber, newTextures.get());

    copy(newTextures.get(), newTextures.get() + needTexturesNumber, back_inserter(freeTextures_));

}



void TextureManager::updateTexturesForDelete() {

    if(texturesForDelete_.empty()) {
        return;
    }

    boost::shared_array< GLuint > textures(new GLuint[texturesForDelete_.size()]);

    auto iter = texturesForDelete_.begin();

    for(std::size_t i = 0; iter != texturesForDelete_.end(); ++iter, ++i) {

        textures[i] = *iter;

    }

    glDeleteTextures(texturesForDelete_.size(), textures.get());

}



void TextureManager::updateTexturesForCreate() {

    if(texturesForCreate_.empty()){
        return;
    }

    BOOST_FOREACH(TextureManager::TextureStruct& textureForCreate, texturesForCreate_) {

        glBindTexture(GL_TEXTURE_2D, textureForCreate.id);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        glTexImage2D(

            GL_TEXTURE_2D,
            0,
            textureForCreate.format,
            textureForCreate.width,
            textureForCreate.height,
            0,
            textureForCreate.format,
            GL_UNSIGNED_BYTE,
            static_cast<const GLvoid*>(textureForCreate.data.data())

        );

    }

}
