#include <AL/al.h>
#include <AL/alc.h>

#include <Utils/Audio.hpp>

using namespace Utils;



Audio::Audio():
    device_(alcOpenDevice(0)),
    context_(alcCreateContext(device_, 0))
{

    alcMakeContextCurrent(context_);

    alGenSources(1, &musicSource_);

    

}



Audio::~Audio() {

    alSourceStop(musicSource_);
    alDeleteSources(1, &musicSource_);

    alcMakeContextCurrent(0);
    alcDestroyContext(context_);
    alcCloseDevice(device_);

}



void Audio::playMusic(const Sound& music) {

    ALuint musicBuf = music.getBuffer();

    alSourceQueueBuffers(musicSource_, 1, &musicBuf);

}



void Audio::playSound(const Sound& sound, bool isLoop) {

    ALuint soundSource;

    alGenSources(1, &soundSource);

    

}
