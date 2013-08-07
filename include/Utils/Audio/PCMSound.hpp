#ifndef _SALT2D_UTILS_AUDIO_PCMSOUND_HPP
#define _SALT2D_UTILS_AUDIO_PCMSOUND_HPP

#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/Audio/Buffer.hpp>
#include <Utils/Audio/IStream.hpp>
#include <Utils/Audio/Sound.hpp>

namespace Utils {

    namespace Audio {

        /** PCM-звук.
          * @author Elijah Vlasov
        */

        class PCMSound: public Sound {

            public:

                PCMSound(const std::string& pcmData);

                boost::shared_ptr<IStream> createStream();


            private:

                boost::shared_ptr<IStream> stream_;

        };

    }

}

#endif
