#include <cstdlib>

#include <stdexcept>
#include <string>

#include <boost/format.hpp>

#include <Utils/assert.hpp>
#include <Utils/Texture.hpp>
#include <Utils/TextureManager.hpp>

#include "gl_includes.h"

using namespace std;

using namespace Utils;



Texture::Texture():
    textureManager_(TextureManager::getInstance()),
    width_(0),
    height_(0),
    name_(textureManager_->createTexture())
{}



Texture::Texture(const Texture& texture):
    textureManager_(TextureManager::getInstance()),
    width_(texture.width_),
    height_(texture.height_),
    format_(texture.format_)
{

    setData(texture.getData());

}



Texture::~Texture() {

    textureManager_->deleteTexture(name_);

}



Texture& Texture::operator=(const Texture& texture) {

    width_        =  texture.width_;
    height_       =  texture.height_;

    format_       =  texture.format_;

    setData(texture.getData());

    return *this;

}



string Texture::getData() const {

    return textureManager_->getTextureData(name_);

}



void Texture::setData(const std::string& data) {

    textureManager_->setTexture(name_, width_, height_, format_, data);

}



unsigned int Texture::getName() const {

    return name_;

}



void Texture::setFormat(GLint format) {

    format_ = format;

}



GLint Texture::getFormat() const {

    return format_;

}



void Texture::setWidth(unsigned int width) {

    width_ = width;

}



void Texture::setHeight(unsigned int height) {

    height_ = height;

}



unsigned int Texture::getWidth() const {

    return width_;

}



unsigned int Texture::getHeight() const {

    return height_;

}
