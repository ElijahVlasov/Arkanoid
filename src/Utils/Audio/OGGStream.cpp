#include <cmath>

#include <stdexcept>
#include <string>
#include <sstream>

#include <vorbis/codec.h>
#include <vorbis/vorbisfile.h>

#include <Utils/assert.hpp>

#include <Utils/Audio/Buffer.hpp>
#include <Utils/Audio/OGGSoundBuilder.hpp>
#include <Utils/Audio/OGGStream.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::Audio;



const std::size_t OGGStream::BUFFERS_COUNT = 16;



OGGStream::OGGStream(const string& oggData) throw(runtime_error):
    oggDataStream_(oggData)
{

    ov_callbacks cb;

    cb.read_func    =   OGGSoundBuilder::ReadOgg;
    cb.close_func   =   OGGSoundBuilder::CloseOgg;
    cb.seek_func    =   OGGSoundBuilder::SeekOgg;
    cb.tell_func    =   OGGSoundBuilder::TellOgg;

    ASSERT(
        (ov_open_callbacks(&oggDataStream_, &oggVorbisFile_, 0, -1, cb) == 0),
        runtime_error("Stream is not a OGG Vorbis")
    );

    std::size_t pcmTotal = ov_pcm_total(&oggVorbisFile_, -1);

    bufferSize_ = static_cast<std::size_t>(
                    ceil(
                        static_cast<float>(pcmTotal) / BUFFERS_COUNT
                    )
                 );

}



OGGStream::~OGGStream() {

    ov_clear(&oggVorbisFile_);

}



bool OGGStream::nextBuffer(Buffer& buffer) {

    string pcm;

    bool res = OGGSoundBuilder::ReadOggBlock(&oggVorbisFile_, pcm, bufferSize_);

    buffer.setData(pcm);

    return res;

}
