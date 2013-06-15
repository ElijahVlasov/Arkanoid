#ifndef _UTILS_TEXTURE_HPP
#define _UTILS_TEXTURE_HPP

#include "config.h"

#include <string>
#include <stdexcept>

#ifdef WINDOWS
#include <Windows.h>
#endif

#include <GL/gl.h>

#include <Utils/Resource.hpp>

namespace Utils {

    /** Обертка для OpenGL-текстуры. Инкапсулирует 
      * создание и удаление OpenGL-текстуры.
      * @author Elijah Vlasov
    */

    class Texture: public Resource {

        public:

            /** Создается непригодная для прорисовки текстура.
            */

            Texture();

            /** Полное копирование.
            */

            Texture(const Texture& texture);

            ~Texture();

            Texture& operator = (const Texture& texture);

            std::string getData() const;
            void setData(const std::string& data);

            /** Установить формат текстуры.
            */

            void setFormat(GLint format);

            /** Формат текстуры.
            */

            GLint getFormat() const;

            /** OpenGL-идентификатор текстуры
            */

            GLuint getName()const;

            /** Установить ширину.
            */

            void setWidth(unsigned int width);

            /** Установить длину текстуры
            */

            void setHeight(unsigned int height);

            /** Ширина текстуры
            */

            unsigned int getWidth() const;

            /** Высота текстуры
            */

            unsigned int getHeight() const;

        private:

            unsigned int width_, height_;

            GLint format_;

            GLuint name_;

    };

}


#endif
