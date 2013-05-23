#ifndef _UTILS_TEXTURE_HPP
#define _UTILS_TEXTURE_HPP

#include "config.h"

#include <string>
#include <stdexcept>

#ifdef MS_WINDOWS
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

            Texture(GLuint glTexture);

            ~Texture();

            Texture& operator = (const Texture& texture);

            const std::string& getData() const;
            void setData(const std::string& data);

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

            bool isCreated_;

            unsigned int width_, height_;

            GLint mode_;

            GLuint name_;

            void createFromGLTex(GLuint tex);

    };

}


#endif
