#include "config.h"

#include <cstdlib>

#include <stdexcept>
#include <string>

#include <boost/format.hpp>

#ifdef MS_WINDOWS
#include <Windows.h>
#endif

#include <GL/gl.h>


#include <Utils/assert.hpp>

#include <Utils/Texture.hpp>



using Utils::Texture;

using namespace std;



Texture::Texture():
    width_(0),
    height_(0)
{

    glGenTextures(1, &name_);

}



Texture::Texture(const Texture& texture):
    width_(texture.width_),
    height_(texture.height_),
    format_(texture.format_)
{

    setData(texture.getData());

}



Texture::~Texture() {

    glDeleteTextures(1, &name_);

}



Texture& Texture::operator=(const Texture& texture) {

    width_      =  texture.width_;
    height_     =  texture.height_;

    format_       =  texture.format_;

    setData(texture.getData());

    return *this;

}



string Texture::getData() const {

    unsigned int bpp;

    switch(format_) {

        case GL_RGB: {
            bpp = 3;
        }
        break;

        case GL_RGBA: {
            bpp = 4;
        }
        break;

    }

    string data;

    data.resize(width_ * height_ * bpp); // Размер данных равен количеству пикселей в текстуре * байт на пиксель

    glBindTexture(GL_TEXTURE_2D, name_);

    glGetTexImage(GL_TEXTURE_2D, 0, format_, GL_UNSIGNED_BYTE, reinterpret_cast<GLvoid*>(const_cast<char*>(data.data())));

    return data;

}



void Texture::setData(const std::string& data) {

    glBindTexture(GL_TEXTURE_2D, name_);

    glTexImage2D(GL_TEXTURE_2D, 0, format_, width_, height_, 0, format_, GL_UNSIGNED_BYTE, static_cast<const GLvoid*>(data.data()));

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

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
