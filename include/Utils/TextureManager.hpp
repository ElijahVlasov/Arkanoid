#ifndef UTILS_TEXTUREMANAGER_HPP
#define UTILS_TEXTUREMANAGER_HPP

#include <list>
#include <mutex>
#include <string>
#include <thread>

#include <boost/foreach.hpp>

#include <Utils/Singleton.hpp>

#include "gl_includes.h"

namespace Utils {

    class TextureManager: public Utils::Singleton<TextureManager> {

        SINGLETON(TextureManager)

        public:

            void update();

            GLuint createTexture();

            void setTexture(GLuint texture, unsigned int width, unsigned int height, GLint format, const std::string& textureData);

            void deleteTexture(GLuint texture);

            std::string getTextureData(GLuint texture);

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

            void updateFreeTextures();
            void updateTexturesForDelete();
            void updateTexturesForCreate();

            const std::thread::id mainThreadID_;

    };

}

#endif
