#include <cstdlib>

#include <stdexcept>
#include <string>

#include <boost/format.hpp>

#include <Utils/assert.hpp>

#include <Utils/Graphics/Texture.hpp>
#include <Utils/Graphics/TextureManager.hpp>

#include "gl_includes.h"

using namespace std;

using namespace Utils;
using namespace Utils::Graphics;



Texture::Texture(unsigned int width, unsigned int height, Format format, const std::string& textureData):
    textureManager_(TextureManager::getInstance()),
    width_(width),
    height_(height),
    format_(format),
    name_(textureManager_->createTexture())
{

    textureManager_->setTexture(name_, width_, height_, static_cast<GLint>(format_), textureData);

}



Texture::Texture(const Texture& texture):
    textureManager_(texture.textureManager_),
    width_(texture.width_),
    height_(texture.height_),
    format_(texture.format_),
    name_(textureManager_->createTexture())
{

    textureManager_->copyTexture(name_, texture.name_);

}



Texture::~Texture() {

    textureManager_->deleteTexture(name_);

}



Texture& Texture::operator=(const Texture& texture) {

    width_        =  texture.width_;
    height_       =  texture.height_;

    format_       =  texture.format_;

    textureManager_->copyTexture(name_, texture.name_);

    return *this;

}



unsigned int Texture::getName() const {

    return name_;

}



Texture::Format Texture::getFormat() const {

    return format_;

}



unsigned int Texture::getWidth() const {

    return width_;

}



unsigned int Texture::getHeight() const {

    return height_;

}
