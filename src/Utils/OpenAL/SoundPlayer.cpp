#include <mutex>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/OpenAL/Sound.hpp>
#include <Utils/OpenAL/SoundPlayer.hpp>

#include "oal_includes.h"

using namespace std;

using namespace Utils;
using namespace Utils::OpenAL;



const std::size_t SoundPlayer::BUFFERS_COUNT = 10;



SoundPlayer::SoundPlayer(const boost::shared_ptr<Sound>& sound) throw(runtime_error):
    stream_(sound->createStream())
{

    alGenSources(1, &sourceID_);

    alSourcef( sourceID_, AL_PITCH,    1.0f);
    alSourcef( sourceID_, AL_GAIN,     0.0f);
    alSource3f(sourceID_, AL_POSITION, 0.0f, 0.0f, 0.0f);
    alSource3f(sourceID_, AL_VELOCITY, 0.0f, 0.0f, 0.0f);
    alSourcei( sourceID_, AL_LOOPING,  AL_FALSE);

    for(std::size_t i = 0; i < BUFFERS_COUNT; i++) {

        boost::shared_ptr<Buffer> buffer( new Buffer(string(), sound->getFormat(), sound->getFrequency()) );

        ALuint bufferID = buffer->getID();

        buffers_[bufferID] = buffer;

//        alSourceQueueBuffers(sourceID_, 1, &bufferID);

    }

}



SoundPlayer::~SoundPlayer() {

    alDeleteSources(1, &sourceID_);

}



void SoundPlayer::play() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    alSourcePlay(sourceID_);

}



void SoundPlayer::stop() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    alSourceStop(sourceID_);

}



void SoundPlayer::pause() {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    alSourcePause(sourceID_);

}



void SoundPlayer::update() throw(runtime_error) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    int processed;

    ALuint bufferID;

    alGetSourcei(sourceID_, AL_BUFFERS_PROCESSED, &processed);

    while(processed--) {

        alSourceUnqueueBuffers(sourceID_, 1, &bufferID);

        bool isEnded = stream_->nextBuffer(*buffers_[bufferID]);

        alSourceQueueBuffers(sourceID_, 1, &bufferID);

        if(isEnded && !isLooped_) {
            return;
        }

    }

}



void SoundPlayer::setLooping(bool isLooped) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    isLooped_ = isLooped;

}



bool SoundPlayer::isLooped() const {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    return isLooped_;

}
