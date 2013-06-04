#ifndef _SALT2D_UTILS_AUDIO_HPP
#define _SALT2D_UTILS_AUDIO_HPP

#include <AL/al.h>
#include <AL/alc.h>

#include <Utils/Singleton.hpp>
#include <Utils/Sound.hpp>

namespace Utils {

    class Audio: public Singleton<Audio> {

        SINGLETON(Audio)

        public:

            void playMusic(const Sound& music);

            void playSound(const Sound& sound);

        protected:

            Audio();
            ~Audio();

        private:

            ALCdevice*  device_;
            ALCcontext* context_;

            ALuint musicSource_;

    };

}

#endif
