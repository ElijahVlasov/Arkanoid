#ifndef _SALT2D_UTILS_OPENAL_SOUND_HPP
#define _SALT2D_UTILS_OPENAL_SOUND_HPP

#include <boost/shared_ptr.hpp>

#include <Utils/OpenAL/IStream.hpp>

#include "oal_includes.h"

namespace Utils {

    namespace OpenAL {

        class Sound {

            public:

                Sound();
                virtual ~Sound();

                virtual boost::shared_ptr<IStream> createStream() = 0;

                void setFormat(ALenum format);
                ALenum getFormat() const;

                void setFrequency(ALsizei frequency);
                ALsizei getFrequency() const;

            private:

                ALenum  format_;
                ALsizei frequency_;

        };

    }

}

#endif
