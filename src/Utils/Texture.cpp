#include "config.h"

#include <cstdlib>

#include <stdexcept>
#include <string>

#include <boost/format.hpp>

#ifdef MS_WINDOWS
#include <Windows.h>
#endif

#include <GL/gl.h>

#include <il/il.h>


#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include <Utils/assert.hpp>

#include <Utils/Texture.hpp>



using Utils::Texture;

using namespace std;



Texture::Texture():
    isCreated_(false),
    name_(0)
{
}



Texture::Texture(GLuint glTexture):
    isCreated_(true)
{

    glBindTexture(GL_TEXTURE_2D, name_);

    // Получаем формат текстуры
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_INTERNAL_FORMAT, &mode_);

    // Получаем размеры текстуры
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_WIDTH,    reinterpret_cast<GLint*>(&width_));
    glGetTexLevelParameteriv(GL_TEXTURE_2D, 0, GL_TEXTURE_HEIGHT,   reinterpret_cast<GLint*>(&height_));

    createFromGLTex(glTexture);

}



Texture::Texture(const Texture& texture):
    isCreated_(texture.isCreated_),
    width_(texture.width_),
    height_(texture.height_),
    mode_(texture.mode_)
{

    if(!isCreated_) {
        return;
    }

    createFromGLTex(texture.name_);

}



Texture::~Texture() {

    if(isCreated_) {

        glDeleteTextures(1, &name_);

    }

}



Texture& Texture::operator=(const Texture& texture) {

    width_      =  texture.width_;
    height_     =  texture.height_;

    mode_       =  texture.mode_;

    isCreated_  =  texture.isCreated_;

    if(!isCreated_) {
        return *this;
    }

    createFromGLTex(texture.name_);

    return *this;

}



void Texture::createFromGLTex(GLuint tex) {

    unsigned int bpp;

    switch(mode_) {

        case GL_RGB: {
            bpp = 3;
        }
        break;

        case GL_RGBA: {
            bpp = 4;
        }
        break;

    }

    GLvoid* buffer = malloc(width_ * height_ * bpp); // Промежуточный буфер для текстуры

    glBindTexture(GL_TEXTURE_2D, tex);

    glGetTexImage(GL_TEXTURE_2D, 0, mode_, GL_UNSIGNED_BYTE, buffer);

    glGenTextures(1, &name_);

    glBindTexture(GL_TEXTURE_2D, name_);

    glTexImage2D(GL_TEXTURE_2D, 0, mode_, width_, height_, 0, mode_, GL_UNSIGNED_BYTE, buffer);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    free(buffer);

}


const string& Texture::getData() const {

    

}



void Texture::setData(const std::string& data) {

    const void* rawData = reinterpret_cast<const void*>(data.data());

    mode_ = * ( reinterpret_cast<const GLint*>(rawData) );

    

}



unsigned int Texture::getName() const {

    return name_;

}



unsigned int Texture::getWidth() const {

    return width_;

}



unsigned int Texture::getHeight() const {

    return height_;

}
