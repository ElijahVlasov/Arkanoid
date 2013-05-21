#include "config.h"

#include <cstdlib>

#include <stdexcept>
#include <string>

#include <boost/format.hpp>

#ifdef MS_WINDOWS
#include <Windows.h>
#endif

#include <GL/gl.h>


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



Texture::Texture(const std::string& fileName) throw(invalid_argument, runtime_error) {

    loadBitmap(fileName.c_str());

}



Texture::Texture(const char* fileName) throw(invalid_argument, runtime_error) { 

    loadBitmap(fileName);

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



Texture::Texture(const SDL_Surface* textureSurface) throw(invalid_argument) {

    ASSERT(
        (textureSurface != 0),
        invalid_argument("textureSurface")
    );

    createFromSurface(textureSurface);

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



void Texture::loadBitmap(const char* fileName) throw(invalid_argument, runtime_error) {

    SDL_Surface* imgSurface = IMG_Load(fileName); // загружаем текстуру

    ASSERT(
        (imgSurface != 0),

        runtime_error(
            (
                boost::format("Can't load texture %1%:\n%2%") 
                        % fileName % ::IMG_GetError()
            ).str()
        )

    );

    createFromSurface(imgSurface);
 
    SDL_FreeSurface(imgSurface);

}



void Texture::createFromSurface(const SDL_Surface* surface) {

    mode_ = GL_RGB;

    if(surface->format->BytesPerPixel == 4) {

        mode_ = GL_RGBA;

    }

    glGenTextures(1, &name_);

    glBindTexture(GL_TEXTURE_2D, name_);

    // переносим из SDL_Surface в OpenGL texture
    glTexImage2D(GL_TEXTURE_2D, 0, mode_, surface->w, surface->h, 0, mode_, GL_UNSIGNED_BYTE, surface->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    width_  = surface->w;
    height_ = surface->h;

    isCreated_ = true;

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



unsigned int Texture::getName() const {

    return name_;

}



unsigned int Texture::getWidth() const {

    return width_;

}



unsigned int Texture::getHeight() const {

    return height_;

}
