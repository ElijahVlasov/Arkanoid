#ifndef _SALT2D_UTILS_OPENAL_AUDIO_HPP
#define _SALT2D_UTILS_OPENAL_AUDIO_HPP


#include <list>
#include <stdexcept>

#include <Utils/Singleton.hpp>

#include <Utils/OpenAL/Sound.hpp>
#include <Utils/OpenAL/SoundPlayer.hpp>

#include "oal_includes.h"

namespace Utils {

    namespace OpenAL {

        class Audio: public Singleton<Audio> {

            SINGLETON(Audio)

            public:

                boost::shared_ptr<SoundPlayer> createSoundPlayer(const boost::shared_ptr<Sound>& sound);

                void update()                   throw(std::runtime_error);

                static void CheckALErrors()     throw(std::runtime_error);
                static void CheckALCErrors()    throw(std::runtime_error);

            protected:

                Audio() throw(std::runtime_error);
                ~Audio();

            private:

                std::list< boost::shared_ptr<SoundPlayer> > players_;

                ALCdevice*  device_;
                ALCcontext* context_;

        };

    }

}

#endif
