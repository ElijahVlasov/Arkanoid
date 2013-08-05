#ifndef _SALT2D_UTILS_AUDIO_SOUNDPLAYER_HPP
#define _SALT2D_UTILS_AUDIO_SOUNDPLAYER_HPP

#include <map>
#include <mutex>
#include <stdexcept>

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

#include <Utils/Audio/Buffer.hpp>
#include <Utils/Audio/IStream.hpp>
#include <Utils/Audio/Sound.hpp>

#include "oal_includes.h"

namespace Utils {

    namespace Audio {

        class SoundPlayer: public boost::noncopyable {

            public:

                SoundPlayer(const boost::shared_ptr<Sound>& sound) throw(std::runtime_error);
                ~SoundPlayer();

                void play() throw(std::runtime_error);
                void stop();
                void pause();

                void update() throw(std::runtime_error);

                void setLooping(bool isLooped);
                bool isLooped() const;

            private:

                static const std::size_t BUFFERS_COUNT;

                mutable std::mutex synchroMutex_;

                boost::shared_ptr<IStream> stream_;

                ALuint sourceID_;

                std::map< ALuint, boost::shared_ptr<Buffer> > buffers_;

                bool isLooped_;



        };

    }

}

#endif
