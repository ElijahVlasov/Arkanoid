#include <string>

#include <AL/al.h>

#include <Utils/Sound.hpp>

using namespace std;

using namespace Utils;



Sound::Sound(ALenum format, ALsizei frequency, const string& data):
    format_(format),
    frequency_(frequency)
{

    alGenBuffers(1, &buffer_);

    alBufferData(buffer_, format_, reinterpret_cast<const ALvoid*>(data.data()), data.size(), frequency_);

}



Sound::~Sound() {

    alDeleteBuffers(1, &buffer_);

}



ALuint Sound::getBuffer() const {

    return buffer_;

}



ALsizei Sound::getFrequency() const {

    return frequency_;

}
