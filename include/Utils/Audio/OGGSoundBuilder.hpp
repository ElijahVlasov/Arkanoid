#ifndef _SALT2D_UTILS_AUDIO_OGGSOUNDBUILDER_HPP
#define _SALT2D_UTILS_AUDIO_OGGSOUNDBUILDER_HPP

#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#include <Utils/Singleton.hpp>

#include <Utils/Audio/Sound.hpp>

namespace Utils {

    namespace Audio {

        /** Класс для создания звуков из Ogg Vorbis данных.
          * @author Elijah Vlasov
        */

        class OGGSoundBuilder: public Singleton<OGGSoundBuilder> {

            SINGLETON(OGGSoundBuilder)

            public:

                boost::shared_ptr<Sound> createSound(const std::string& oggBuffer)
                                                    throw(std::invalid_argument, std::runtime_error);

                static bool ReadOggBlock(OggVorbis_File* oggVorbisFile, std::string& out, std::size_t blockSize);

                static std::size_t ReadOgg(void* out, std::size_t size, std::size_t num, void* datasource);
                static int SeekOgg(void* dataSource, ogg_int64_t offset, int whence);
                static long TellOgg(void* dataSource);
                static int CloseOgg(void* dataSource);

            private:

                static const std::size_t MAX_PCM_SOUND_SIZE;

        };

    }

}

#endif
