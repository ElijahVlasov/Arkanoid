#include <algorithm>
#include <list>
#include <mutex>
#include <stdexcept>
#include <thread>

#include <boost/foreach.hpp>
#include <boost/shared_array.hpp>

#include <Utils/assert.hpp>
#include <Utils/TextureManager.hpp>

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

    updateTexturesForDelete(); // Удаляем текстуры для удаления.

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



void TextureManager::update() throw(runtime_error) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(std::this_thread::get_id() != mainThreadID_) {
        return;
    }

    updateFreeTextures();
    updateTexturesForDelete();
    updateTexturesForCreate();
    updateTexturesForCopy();

}



GLuint TextureManager::createTexture() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    auto texture = freeTextures_.front();

    freeTextures_.pop_front();

    return texture;

}



void TextureManager::copyTexture(GLuint dst, GLuint src) {

    if(std::this_thread::get_id() == mainThreadID_) {

        copy(dst, src);

        return;

    }

    std::lock_guard<std::mutex> guard(synchroMutex_);

    texturesForCopy_[dst] = src;

}



void TextureManager::setTexture(GLuint texture, unsigned int width, unsigned int height, GLint format, const string& data) throw(std::runtime_error) {

    if(std::this_thread::get_id() == mainThreadID_) { // Если мы в главном потоке, можно создать текстуру.

        setTextureAttribs(texture, width, height, format, data);

        return;

    }

    // Иначе создадим в главном потоке.

    std::lock_guard<std::mutex> guard(synchroMutex_);

    TextureManager::TextureStruct textureForCreate = {texture, width, height, format, data};

    texturesForCreate_.push_back(textureForCreate);


}



void TextureManager::deleteTexture(GLuint texture) {

    if(std::this_thread::get_id() == mainThreadID_) {

        glDeleteTextures(1, &texture);

        return;

    }

    // Удалим позже, в главном потоке:

    std::lock_guard<std::mutex> guard(synchroMutex_);

    texturesForDelete_.push_back(texture);

}



void TextureManager::updateFreeTextures() {

    std::size_t freeNumber = freeTextures_.size();

    if(freeNumber >= MIN_TEXTURES_NUMBER) {
        return;
    }

    std::size_t needTexturesNumber = MAX_TEXTURES_NUMBER - freeNumber; // Столько текстур не хватает до максимума.

    // Сгенерируем столько текстур.

    boost::shared_array< GLuint > newTextures(new GLuint[needTexturesNumber]);

    glGenTextures(needTexturesNumber, newTextures.get());

    std::copy(newTextures.get(), newTextures.get() + needTexturesNumber, back_inserter(freeTextures_));

}



void TextureManager::updateTexturesForDelete() {

    if(texturesForDelete_.empty()) {
        return;
    }

    boost::shared_array< GLuint > textures(new GLuint[texturesForDelete_.size()]);

    // Перенесем текстуры из списка в массив.

    auto iter = texturesForDelete_.begin();

    for(std::size_t i = 0; iter != texturesForDelete_.end(); ++iter, ++i) {

        textures[i] = *iter;

    }

    glDeleteTextures(texturesForDelete_.size(), textures.get());

}



void TextureManager::updateTexturesForCreate() throw(runtime_error) {

    if(texturesForCreate_.empty()){
        return;
    }

    BOOST_FOREACH(TextureManager::TextureStruct& textureForCreate, texturesForCreate_) {

        setTextureAttribs(textureForCreate.id, textureForCreate.width, textureForCreate.height, textureForCreate.format, textureForCreate.data);

    }

    texturesForCreate_.clear();

}



void TextureManager::updateTexturesForCopy() {

    typedef pair< GLuint, GLuint > TexturesForCopy;

    BOOST_FOREACH(TexturesForCopy texturesForCopy, texturesForCopy_) {

        copy(texturesForCopy.first, texturesForCopy.second);

    }

}



void TextureManager::setTextureAttribs(GLuint texture, unsigned int width, unsigned int height, GLint format, const string& textureData) throw(runtime_error) {

    unsigned newWidth   =   nextPowerOf2(width);
    unsigned newHeight  =   nextPowerOf2(height);

    string newData = resize(textureData, width, height, format, newWidth, newHeight);

    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(

        GL_TEXTURE_2D,
        0,
        format,
        newWidth,
        newHeight,
        0,
        format,
        GL_UNSIGNED_BYTE,
        static_cast<const GLvoid*>(newData.data())

    );

    int err = glGetError();

    ASSERT(
        (err == GL_NO_ERROR),
        runtime_error(reinterpret_cast<const char*>(gluErrorString(err)))
    );

}



void TextureManager::copy(GLuint dst, GLuint src) {

    string data;

    GLint width, height, format;

    glBindTexture(GL_TEXTURE_2D, src);

    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH, &width);
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT, &height);

    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &format);

    unsigned int bpp = formatToBPP(format);

    data.resize(width * height * bpp);

    glGetTexImage(GL_TEXTURE_2D, 0, format, GL_UNSIGNED_BYTE, static_cast<GLvoid*>(const_cast<char*>(data.data())));

    glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, static_cast<const GLvoid*>(data.data()));

}



string TextureManager::resize(const string& textureData, unsigned int width, unsigned int height, GLint format, unsigned int newWidth, unsigned newHeight) throw(runtime_error) {

    string newData;

    unsigned int bpp = formatToBPP(format);

    ASSERT(
        (bpp != 0),
        runtime_error("Texture has unknown format")
    );

    newData.resize(newWidth * newHeight * bpp);

    int err = gluScaleImage(
                format,
                width,
                height,
                GL_UNSIGNED_BYTE,
                reinterpret_cast<const GLvoid*>(textureData.data()),
                newWidth,
                newHeight,
                GL_UNSIGNED_BYTE,
                reinterpret_cast<GLvoid*>(const_cast<char*>(newData.data()))
              );

    ASSERT(
        (err == 0),
        runtime_error(reinterpret_cast<const char*>(gluErrorString(err)))
    );

    return newData;

}
