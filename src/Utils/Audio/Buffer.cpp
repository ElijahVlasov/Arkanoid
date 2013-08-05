#include <stdexcept>
#include <string>

#include <Utils/Audio/AudioManager.hpp>
#include <Utils/Audio/Buffer.hpp>

#include "oal_includes.h"

using namespace std;

using namespace Utils;
using namespace Utils::Audio;



Buffer::Buffer(ALenum format, ALsizei frequency, const string& data) throw(runtime_error):
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

    AudioManager::CheckALErrors();

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
