#ifndef _SALT2D_UTILS_AUDIO_AUDIOMANAGER_HPP
#define _SALT2D_UTILS_AUDIO_AUDIOMANAGER_HPP


#include <list>
#include <stdexcept>

#include <Utils/Singleton.hpp>

#include <Utils/Audio/Sound.hpp>
#include <Utils/Audio/SoundPlayer.hpp>

#include "oal_includes.h"

namespace Utils {

    namespace Audio {

        class AudioManager: public Singleton<AudioManager> {

            SINGLETON(AudioManager)

            public:

                boost::shared_ptr<SoundPlayer> createSoundPlayer(const boost::shared_ptr<Sound>& sound);

                void update()                   throw(std::runtime_error);

                static void CheckALErrors()     throw(std::runtime_error);
                static void CheckALCErrors()    throw(std::runtime_error);

            protected:

                AudioManager() throw(std::runtime_error);
                ~AudioManager();

            private:

                std::list< boost::shared_ptr<SoundPlayer> > players_;

                ALCdevice*  device_;
                ALCcontext* context_;

        };

    }

}

#endif
