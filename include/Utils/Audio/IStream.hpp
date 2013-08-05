#ifndef _SALT2D_UTILS_AUDIO_ISTREAM_HPP
#define _SALT2D_UTILS_AUDIO_ISTREAM_HPP

#include <Utils/Audio/Buffer.hpp>

namespace Utils {

    namespace Audio {

        class IStream {

            public:

                virtual ~IStream();

                virtual bool nextBuffer(Buffer& buffer) = 0;

        };

    }

}

#endif
