#ifndef _SALT2D_UTILS_OPENAL_PCMSOUND_HPP
#define _SALT2D_UTILS_OPENAL_PCMSOUND_HPP

#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/OpenAL/Buffer.hpp>
#include <Utils/OpenAL/IStream.hpp>
#include <Utils/OpenAL/Sound.hpp>

namespace Utils {

    namespace OpenAL {

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
