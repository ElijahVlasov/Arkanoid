#ifndef _SALT2D_UTILS_SOUND_HPP
#define _SALT2D_UTILS_SOUND_HPP

#include <AL/al.h>

#include <string>

#include <Utils/Resource.hpp>

namespace Utils {

    class Sound: public Resource {

        public:

            Sound();
            Sound(const Sound&);

            ~Sound();

            std::string getData() const;
            void setData(const std::string& data);

            ALuint getBuffer() const;

            void setFormat(ALenum format);

            void setFrequency(ALsizei frequency);
            ALsizei getFrequency() const;

        private:

			std::string binaryBuffer_;

            ALuint buffer_;

            ALenum format_;

            ALsizei frequency_;

    };

}

#endif
