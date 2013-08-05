#include <Utils/Audio/Sound.hpp>

#include "oal_includes.h"

using namespace Utils;
using namespace Utils::Audio;



Sound::Sound():
    format_(AL_FORMAT_MONO16)
{}



Sound::~Sound() {}



void Sound::setFormat(ALenum format) {

    format_ = format;

}



ALenum Sound::getFormat() const {

    return format_;

}



void Sound::setFrequency(ALsizei frequency) {

    frequency_ = frequency;

}



ALsizei Sound::getFrequency() const {

    return frequency_;

}
