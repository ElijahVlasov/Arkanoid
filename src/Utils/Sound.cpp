#include <string>

#include <AL/al.h>

#include <Utils/Sound.hpp>

using namespace std;

using namespace Utils;



Sound::Sound() {

    alGenBuffers(1, &buffer_);

}



Sound::Sound(const Sound& sound) {

    setData(sound.getData());

}



Sound::~Sound() {

    alDeleteBuffers(1, &buffer_);

}



std::string Sound::getData() const {

	return binaryBuffer_;

}



void Sound::setData(const string& data) {

	binaryBuffer_ = data;

    alBufferData(buffer_, format_, reinterpret_cast<ALvoid*>(const_cast<char*>(data.data())), data.size(), frequency_);

}



ALuint Sound::getBuffer() const {

    return buffer_;

}



void Sound::setFormat(ALenum format) {

    format_ = format;

}



void Sound::setFrequency(ALsizei frequency) {

    frequency_ = frequency;

}



ALsizei Sound::getFrequency() const {

    return frequency_;

}
