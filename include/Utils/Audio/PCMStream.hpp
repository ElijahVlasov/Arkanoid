#ifndef _SALT2D_UTILS_AUDIO_PCMSTREAM_HPP
#define _SALT2D_UTILS_AUDIO_PCMSTREAM_HPP

#include <string>

#include <Utils/Audio/Buffer.hpp>
#include <Utils/Audio/IStream.hpp>

namespace Utils {

    namespace Audio {

        class PCMStream: public IStream {

            public:

                PCMStream(const std::string& pcmData);

                bool nextBuffer(Buffer& buffer);

            private:

                std::string pcmData_;

        };

    }

}

#endif
