#ifndef _SALT2D_UTILS_OPENAL_PCMSTREAM_HPP
#define _SALT2D_UTILS_OPENAL_PCMSTREAM_HPP

#include <string>

#include <Utils/OpenAL/Buffer.hpp>
#include <Utils/OpenAL/IStream.hpp>

namespace Utils {

    namespace OpenAL {

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
