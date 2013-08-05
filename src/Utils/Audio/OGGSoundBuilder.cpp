#include <ios>
#include <istream>
#include <sstream>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/assert.hpp>

#include <Utils/Audio/OGGSound.hpp>
#include <Utils/Audio/OGGSoundBuilder.hpp>
#include <Utils/Audio/PCMSound.hpp>
#include <Utils/Audio/Sound.hpp>

#include "oal_includes.h"

using namespace std;

using namespace Utils;
using namespace Utils::Audio;



const std::size_t OGGSoundBuilder::MAX_PCM_SOUND_SIZE = 1024;



boost::shared_ptr<Sound> OGGSoundBuilder::createSound(const string& oggBuffer) throw(invalid_argument, runtime_error) {

    struct OggVorbisFile {

        inline OggVorbisFile(const string oggBuffer) throw(invalid_argument, runtime_error):
            oggInput(oggBuffer)
        {

            ASSERT(
                (oggBuffer.size() != 0),
                invalid_argument("oggBuffer")
            );

            ov_callbacks    cb;

            cb.read_func    =   OGGSoundBuilder::ReadOgg;
            cb.close_func   =   OGGSoundBuilder::CloseOgg;
            cb.seek_func    =   OGGSoundBuilder::SeekOgg;
            cb.tell_func    =   OGGSoundBuilder::TellOgg;

            ASSERT(
                (ov_open_callbacks(&oggInput, &vf, 0, -1, cb) == 0),
                runtime_error("Can't read as Ogg Vorbis file!")
            );

        }

        inline ~OggVorbisFile() {

            ov_clear(&vf);

        }

        istringstream   oggInput;
        OggVorbis_File  vf;

    } vorbisFile(oggBuffer);

    boost::shared_ptr<Sound> sound;

    std::size_t pcmTotal = ov_pcm_total(&vorbisFile.vf, -1);

    vorbis_info* vorbisInfo = ov_info(&vorbisFile.vf, -1);

    ALsizei frequency = vorbisInfo->rate;

    ALenum format = AL_FORMAT_STEREO16;

    if(vorbisInfo->channels == 1) {
        format = AL_FORMAT_MONO16;
    }

    if(pcmTotal > MAX_PCM_SOUND_SIZE) {

        sound = boost::shared_ptr<Sound>( new OGGSound(oggBuffer) );

    } else {

        string pcm;

        ReadOggBlock(&vorbisFile.vf, pcm, pcmTotal);

        sound = boost::shared_ptr<Sound>( new PCMSound(pcm) );

    }

    sound->setFormat(format);
    sound->setFrequency(frequency);

    return sound;

}



bool OGGSoundBuilder::ReadOggBlock(OggVorbis_File* oggVorbisFile, string& out, std::size_t blockSize) {

    std::size_t totalReserved = 0;

    long reserved;

    out.resize(blockSize);

    while(totalReserved < blockSize) {

        int currentSection;

        reserved = ov_read(
                           oggVorbisFile,
                           const_cast<char*>(out.data()) + totalReserved,
                           blockSize - totalReserved,
                           0, 2, 1,
                           &currentSection
                          );

        if(reserved == 0) {

            ov_pcm_seek(oggVorbisFile, 0);

            break;

        } else if(reserved < 0) { // Произошла ошибка.
        } else {

            totalReserved += reserved;

        }

    }

    return (reserved <= 0);

}



std::size_t OGGSoundBuilder::ReadOgg(void* out, std::size_t size, std::size_t num, void* dataSource) {

    istream* is = reinterpret_cast<istream*>(dataSource);

    is->read(reinterpret_cast<char*>(out), size * num);

    return is->gcount();

}



int OGGSoundBuilder::SeekOgg(void* dataSource, ogg_int64_t offset, int whence) {

    istream* is = reinterpret_cast<istream*>(dataSource);

    ios_base::seekdir dir;

    is->clear();

    switch (whence) {

        case SEEK_SET: {

            dir = ios::beg;

        }
        break;

        case SEEK_CUR: {

            dir = ios::cur;

        }
        break;

        case SEEK_END: {

            dir = ios::end;

        }
        break;

        default: {
            return -1;
        }

    }

    is->seekg((streamoff)offset, dir);

    return (is->fail() ? -1 : 0);

}



long OGGSoundBuilder::TellOgg(void* dataSource) {

    istream* is = reinterpret_cast<istream*>(dataSource);

    return is->tellg();

}



int OGGSoundBuilder::CloseOgg(void* dataSource) {

    return 0;

}
