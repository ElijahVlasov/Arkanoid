#ifndef UTILS_TEXTUREMANAGER_HPP
#define UTILS_TEXTUREMANAGER_HPP

#include <list>
#include <map>
#include <mutex>
#include <stdexcept>
#include <string>
#include <thread>

#include <boost/foreach.hpp>

#include <Utils/Singleton.hpp>

#include "gl_includes.h"

namespace Utils {

    namespace Graphics {

        /** Менеджер текстур. Предназначен для создания, удаления,
          * задания параметров OGL-текстур в неглавных потоках.
          * Чтобы текстуры были успешно созданы, удалены и т.д.
          * в главном потоке надо вызвать метод update().
          * @author Elijah Vlasov
        */

        class TextureManager: public Utils::Singleton<TextureManager> {

            SINGLETON(TextureManager)

            public:

                /** Завершает создание, удаление и установку параметров
                  * текстур. Должен вызываться в главном потоке.
                */

                void update() throw(std::runtime_error);

                /** Создать текстуру.
                */

                GLuint createTexture();

                void copyTexture(GLuint dst, GLuint src);

                /** Установить параметры текстуры.
                */

                void setTexture(GLuint texture, unsigned int width, unsigned int height, GLint format, const std::string& textureData) throw(std::runtime_error);

                /** Удалить текстуру.
                */

                void deleteTexture(GLuint texture);

            protected:

                TextureManager();
                ~TextureManager();

            private:

                static const std::size_t MIN_TEXTURES_NUMBER;
                static const std::size_t MAX_TEXTURES_NUMBER;

                const std::thread::id mainThreadID_;

                mutable std::mutex synchroMutex_;

                std::list< GLuint > freeTextures_;
                std::list< GLuint > texturesForDelete_;

                struct TextureStruct {

                    GLuint id;

                    unsigned int width, height;
                    GLint format;
                    std::string data;

                };

                std::list< TextureStruct > texturesForCreate_;

                std::map <GLuint, GLuint> texturesForCopy_;

                void updateFreeTextures();
                void updateTexturesForDelete();
                void updateTexturesForCreate() throw(std::runtime_error);
                void updateTexturesForCopy();

                static void setTextureAttribs(GLuint texture, unsigned int width, unsigned int height, GLint format, const std::string& textureData) throw(std::runtime_error);
                static void copy(GLuint dst, GLuint src);

                static std::string resize(const std::string& textureData, unsigned int width, unsigned int height, GLint format, unsigned int newWidth, unsigned newHeight) throw(std::runtime_error);

                static inline unsigned int nextPowerOf2(unsigned int n);
                static inline unsigned int formatToBPP(GLint format);

        };



        unsigned int TextureManager::nextPowerOf2(unsigned int n) {

            n -= 1;

            n |= n >> 16;
            n |= n >> 8;
            n |= n >> 4;
            n |= n >> 2;
            n |= n >> 1;

            return n + 1;

        }



        unsigned int TextureManager::formatToBPP(GLint format) {

            switch(format) {

                case GL_RGB: {

                    return 3;

                }
                break;

                case GL_RGBA: {

                    return 4;

                }
                break;

            }

            return 0;

        }

    }

}

#endif
