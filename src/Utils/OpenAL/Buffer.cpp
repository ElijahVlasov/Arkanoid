#include <stdexcept>
#include <string>

#include <Utils/OpenAL/Audio.hpp>
#include <Utils/OpenAL/Buffer.hpp>

#include "oal_includes.h"

using namespace std;

using namespace Utils;
using namespace Utils::OpenAL;



Buffer::Buffer(const string& data, ALenum format, ALsizei frequency) throw(runtime_error):
    format_(format),
    frequency_(frequency)
{

    alGenBuffers(1, &id_);

    alBufferData(
                 id_,
                 format,
                 reinterpret_cast<const ALvoid*>(data.data()),
                 data.size(),
                 frequency
                );

    Audio::CheckALErrors();

}



Buffer::~Buffer() {

    alDeleteBuffers(1, &id_);

}



void Buffer::setData(const string& data) {

    alBufferData(
                 id_,
                 format_,
                 reinterpret_cast<const ALvoid*>(data.data()),
                 data.size(),
                 frequency_
                );

}
