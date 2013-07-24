#ifndef _UTILS_TEXTURE_HPP
#define _UTILS_TEXTURE_HPP

#include "config.h"

#include <string>
#include <stdexcept>

#include <Utils/SingletonPointer.hpp>
#include <Utils/TextureManager.hpp>

#include "gl_includes.h"

namespace Utils {

    /** Обертка для OpenGL-текстуры. Инкапсулирует
      * создание и удаление OpenGL-текстуры.
      * @author Elijah Vlasov
    */

    class Texture {

        public:

            enum Format {

                RGB  = GL_RGB,
                RGBA = GL_RGBA

            };

            Texture(unsigned int width, unsigned int height, Format format, const std::string& textureData);

            /** Полное копирование.
            */

            Texture(const Texture& texture);

            ~Texture();

            Texture& operator = (const Texture& texture);

            /** Формат текстуры.
            */

            Format getFormat() const;

            /** OpenGL-идентификатор текстуры
            */

            GLuint getName()const;

            /** Ширина текстуры
            */

            unsigned int getWidth() const;

            /** Высота текстуры
            */

            unsigned int getHeight() const;

        private:

            mutable SingletonPointer<TextureManager> textureManager_;

            unsigned int width_, height_;

            Format format_;

            GLuint name_;

    };

}


#endif
