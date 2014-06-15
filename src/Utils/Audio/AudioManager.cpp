#include <mutex>
#include <stdexcept>

#include <boost/foreach.hpp>
#include <boost/format.hpp>
#include <boost/shared_ptr.hpp>

#include <Utils/assert.hpp>

#include <Utils/Audio/AudioManager.hpp>
#include <Utils/Audio/Sound.hpp>
#include <Utils/Audio/SoundPlayer.hpp>

#include "oal_includes.h"

using namespace std;

using namespace Utils;
using namespace Utils::Audio;



AudioManager::AudioManager() throw(runtime_error):
    device_(alcOpenDevice(0)) // Получаем девайс по-умолчанию.
{

    ASSERT(
        (device_ != 0),
        runtime_error("Can't open audio-device!")
    );

    context_ = alcCreateContext(device_, 0);

    // Тут нельзя вызвать CheckALErrors(), потому что instance_ еще не получил значения.

    ALenum errCode = alcGetError(device_);

    ASSERT(
        (errCode == AL_NO_ERROR),
        runtime_error(static_cast<const char*>(alcGetString(device_, errCode)))
    );


    alcMakeContextCurrent(context_);

    ALfloat listenerPos[] = { 0.0, 0.0, 0.0 };
    ALfloat listenerVel[] = { 0.0, 0.0, 0.0 };
    ALfloat listenerOri[] = { 0.0, 0.0, -1.0,  0.0, 1.0, 0.0 };

    alListenerfv(AL_POSITION,    listenerPos);
    alListenerfv(AL_VELOCITY,    listenerVel);
    alListenerfv(AL_ORIENTATION, listenerOri);

}



AudioManager::~AudioManager() {

    alcMakeContextCurrent(0);
    alcDestroyContext(context_);
    alcCloseDevice(device_);

}



boost::shared_ptr<SoundPlayer> AudioManager::createSoundPlayer(const boost::shared_ptr<Sound>& sound) {

    std::lock_guard<std::mutex> guard(playersMutex_);

    boost::shared_ptr<SoundPlayer> player( new SoundPlayer(sound) );

    players_.push_back(player);

    return player;

}



void AudioManager::update() throw(runtime_error) {

    std::lock_guard<std::mutex> guard(playersMutex_);

    BOOST_FOREACH(boost::shared_ptr< SoundPlayer >& player, players_) {

        player->update();

    }

}



void AudioManager::CheckALErrors() throw(runtime_error) {

    ALenum errCode = alGetError();

    ASSERT(
        (errCode == AL_NO_ERROR),
        runtime_error(static_cast<const char*>(alGetString(errCode)))
    );

}



void AudioManager::CheckALCErrors() throw(runtime_error) {

    ALenum errCode = alcGetError(instance_->device_);

    ASSERT(
        (errCode == AL_NO_ERROR),
        runtime_error(static_cast<const char*>(alcGetString(instance_->device_, errCode)))
    );

}
