#ifndef _SALT2D_UTILS_SOUND_HPP
#define _SALT2D_UTILS_SOUND_HPP

#include <AL/al.h>

#include <string>

#include <Utils/Resource.hpp>

namespace Utils {

    /** Звук. Обертка над OpenAL-буфером.
      *
    */

    class Sound: public Resource {

        public:

            Sound();
            Sound(const Sound&);

            ~Sound();

            std::string getData() const;
            void setData(const std::string& data);

            /** OpenAL-буфер.
            */

            ALuint getBuffer() const;

            /** Установить формат буфера.
            */

            void setFormat(ALenum format);

            /** Установить частоту.
            */

            void setFrequency(ALsizei frequency);

            /** Частота.
            */

            ALsizei getFrequency() const;

        private:

			std::string binaryBuffer_;

            ALuint buffer_;

            ALenum format_;

            ALsizei frequency_;

    };

}

#endif
