#ifndef _SALT2D_UTILS_OPENAL_ISTREAM_HPP
#define _SALT2D_UTILS_OPENAL_ISTREAM_HPP

#include <Utils/OpenAL/Buffer.hpp>

namespace Utils {

    namespace OpenAL {

        class IStream {

            public:

                virtual ~IStream();

                virtual bool nextBuffer(Buffer& buffer) = 0;

        };

    }

}

#endif
