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

    /** Обертка для OpenGL-текстуры. Инкапсулирует 
      * создание и удаление OpenGL-текстуры.
      * @author Elijah Vlasov
    */

    class Texture {

        public:

            /** Создается непригодная для прорисовки текстура.
            */

            Texture();

            /** Полное копирование.
            */

            Texture(const Texture& texture);

            /** Загружает текстуру из файла.
              * @param textureFileName Имя файла с текстурой
              * @throw  Генерирует std::invalid_argument, если textureFileName - пустая строка.
              *         Генрирует std::runtime_error, если невозможно открыть файл или файл 
              *         неизвестного формата.
            */

            explicit Texture(const std::string& textureFileName) throw(std::invalid_argument, std::runtime_error);

            /** Загружает текстуру из файла.
              * @param textureFileName Имя файла с текстурой
              * @throw  Генерирует std::invalid_argument, если textureFileName - пустая строка или NULL.
              *         Генрирует std::runtime_error, если невозможно открыть файл или файл 
              *         неизвестного формата.
            */

            explicit Texture(const char* textureFileName) throw(std::invalid_argument, std::runtime_error);

            /** Создание текстуры из OpenGL-идентификатора.
              * @param glTexture OpenGL-идентификатор текстуры
            */

            Texture(GLuint glTexture);

            /** Создание текстуры из SDL_Surface. 
              * @param textureSurface SDL_Surface с текстурой
              * @throw  Генерирует std::invalid_argument, если textureSurface - NULL
            */
            Texture(const SDL_Surface* textureSurface) throw(std::invalid_argument);

            ~Texture();

            Texture& operator = (const Texture& texture);

            /** OpenGL-идентификатор текстуры
            */

            unsigned int getName()const;

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
            void createFromSurface(const SDL_Surface* surface);
            void loadBitmap(const char* name) throw(std::invalid_argument, std::runtime_error);

    };

}


#endif
