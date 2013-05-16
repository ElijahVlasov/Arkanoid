/*****************************************	

	Обертка для OpenGl-текстуры.

*****************************************/

#ifndef _UTILS_TEXTURE_HPP
#define _UTILS_TEXTURE_HPP

#include "config.h"

#include <string>
#include <stdexcept>

#ifdef MS_WINDOWS
#include <Windows.h>
#endif

#include <GL/gl.h>

#include <SDL/SDL.h>

namespace Utils {
	
    class Texture {

        public:

            Texture();

            Texture(const Texture& texture);

            explicit Texture(const std::string& textureFileName) throw(std::invalid_argument, std::runtime_error);

            explicit Texture(const char* textureFileName) throw(std::invalid_argument, std::runtime_error);

            Texture(GLuint glTexture);

            // генерирует invalid_argument, если textureSurface == 0
            Texture(const SDL_Surface* textureSurface) throw(std::invalid_argument);

            ~Texture();

            Texture& operator = (const Texture& texture);

            unsigned int getName()const;

            unsigned int getWidth() const;
            unsigned int getHeight() const;
	
        private:

            bool isCreated_;

            unsigned int width_, height_;

            GLuint name_;

            void createFromSurface(const SDL_Surface* surface);
            void loadBitmap(const char* name) throw(std::invalid_argument, std::runtime_error);

    };

}


#endif
