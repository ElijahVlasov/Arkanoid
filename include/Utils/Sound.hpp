#ifndef _SALT2D_UTILS_SOUND_HPP
#define _SALT2D_UTILS_SOUND_HPP

#include <AL/al.h>

#include <string>

namespace Utils {

    /** Звук. Обертка над OpenAL-буфером.
      *
    */

    class Sound {

        public:

            Sound(ALenum format, ALsizei frequency, const std::string& data);
            Sound(const Sound&);

            ~Sound();

            /** OpenAL-буфер.
            */

            ALuint getBuffer() const;

            /** Частота.
            */

            ALsizei getFrequency() const;

        private:

            ALuint buffer_;

            ALenum format_;

            ALsizei frequency_;

    };

}

#endif
