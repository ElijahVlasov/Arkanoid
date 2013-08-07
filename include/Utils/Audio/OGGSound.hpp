#ifndef _SALT2D_UTILS_AUDIO_OGGSOUND_HPP
#define _SALT2D_UTILS_AUDIO_OGGSOUND_HPP

#include <string>

#include <Utils/Audio/IStream.hpp>
#include <Utils/Audio/Sound.hpp>

namespace Utils {

    namespace Audio {

        /** Звук в формате Ogg Vorbis.
          * @author Elijah Vlasov
        */

        class OGGSound: public Sound {

            public:

                OGGSound(const std::string& oggData);

                boost::shared_ptr<IStream> createStream();

            private:

                std::string oggData_;

        };

    }

}

#endif
