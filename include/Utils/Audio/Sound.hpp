#ifndef _SALT2D_UTILS_AUDIO_SOUND_HPP
#define _SALT2D_UTILS_AUDIO_SOUND_HPP

#include <boost/shared_ptr.hpp>

#include <Utils/Audio/IStream.hpp>

#include "oal_includes.h"

namespace Utils {

    namespace Audio {

        /** Звук.
          * @author Elijah Vlasov
        */

        class Sound {

            public:

                Sound();
                virtual ~Sound();

                /** Создать поток для проигрывания этого звука.
                */

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
