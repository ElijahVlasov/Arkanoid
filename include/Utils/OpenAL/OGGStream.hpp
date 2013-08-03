#ifndef _SALT2D_UTILS_OPENAL_OGGSTREAM_HPP
#define _SALT2D_UTILS_OPENAL_OGGSTREAM_HPP

#include <stdexcept>
#include <string>
#include <sstream>

#include <boost/utility.hpp>

#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#include <Utils/OpenAL/Buffer.hpp>
#include <Utils/OpenAL/IStream.hpp>

namespace Utils {

    namespace OpenAL {

        class OGGStream: public boost::noncopyable, public IStream {

            public:

                OGGStream(const std::string& oggData) throw(std::runtime_error);
                ~OGGStream();

                bool nextBuffer(Buffer& buffer);

            private:

                static const std::size_t BUFFERS_COUNT;

                std::size_t bufferSize_;

                OggVorbis_File oggVorbisFile_;

                std::istringstream oggDataStream_;

        };

    }

}

#endif
