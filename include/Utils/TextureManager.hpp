#ifndef UTILS_TEXTUREMANAGER_HPP
#define UTILS_TEXTUREMANAGER_HPP

#include <list>
#include <map>
#include <mutex>
#include <string>
#include <thread>

#include <boost/foreach.hpp>

#include <Utils/Singleton.hpp>

#include "gl_includes.h"

namespace Utils {

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

            void update();

            /** Создать текстуру.
            */

            GLuint createTexture();

            void copyTexture(GLuint dst, GLuint src);

            /** Установить параметры текстуры.
            */

            void setTexture(GLuint texture, unsigned int width, unsigned int height, GLint format, const std::string& textureData);

            /** Удалить текстуру.
            */

            void deleteTexture(GLuint texture);

        protected:

            TextureManager();
            ~TextureManager();

        private:

            static const std::size_t MIN_TEXTURES_NUMBER;
            static const std::size_t MAX_TEXTURES_NUMBER;

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
            void updateTexturesForCreate();
            void updateTexturesForCopy();

            void copy(GLuint dst, GLuint src);

            const std::thread::id mainThreadID_;

    };

}

#endif
