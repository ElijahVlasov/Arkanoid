#ifndef _SALT2D_UTILS_GLTEXTUREPOOL_HPP
#define _SALT2D_UTILS_GLTEXTUREPOOL_HPP

#include <list>
#include <mutex>
#include <thread>

#include <Utils/Singleton.hpp>

#include "gl_includes.h"

namespace Utils {

    class GLTexturePool: public Singleton<GLTexturePool> {

        SINGLETON(GLTexturePool)

        public:

            void update();

            GLuint getTexture();

        protected:

            GLTexturePool();
            ~GLTexturePool();

        private:

            static const std::size_t MAX_TEXTURE_NUMBER;
            static const std::size_t MIN_TEXTURE_NUMBER;

            const std::thread::id mainThreadID_;

            std::mutex synchroMutex_;

            std::list< GLuint > textures_;

    };

}

#endif
