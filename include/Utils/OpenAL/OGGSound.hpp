#ifndef _SALT2D_UTILS_OPENAL_OGGSOUND_HPP
#define _SALT2D_UTILS_OPENAL_OGGSOUND_HPP

#include <string>

#include <Utils/OpenAL/IStream.hpp>
#include <Utils/OpenAL/Sound.hpp>

namespace Utils {

    namespace OpenAL {

        class OGGSound: public Sound {

            public:

                OGGSound(const std::string& oggData);

                boost::shared_ptr<IStream> createStream();

            private:

                std::string oggData_;

        };

    }

}

#endif // _SALT2D_UTILS_OPENAL_OGGSOUND_HPP
