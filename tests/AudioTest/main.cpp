#include <cstdlib>

#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <stdexcept>
#include <string>

#include <Utils/assert.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/Audio/AudioManager.hpp>
#include <Utils/Audio/OGGSound.hpp>
#include <Utils/Audio/OGGSoundFactory.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::Audio;



int main(int argc, char* argv[]) {

    try {

        SingletonPointer<AudioManager>      audioManager    =   AudioManager::getInstance();
        SingletonPointer<OGGSoundFactory>   soundFactory    =   OGGSoundFactory::getInstance();

        ifstream soundStream("sound.ogg", ios::binary);
        string soundData;

        ASSERT(
            soundStream.good(),
            runtime_error("Can't load \"sound.ogg\"")
        );

        soundStream.seekg(0, ios_base::end);
        soundData.resize(soundStream.tellg());
        soundStream.seekg(0, ios_base::beg);

        soundStream.read(const_cast<char*>(soundData.data()), soundData.size());

        auto sound = soundFactory->createSound(soundData);

        auto player = audioManager->createSoundPlayer(sound);

        player->setLooping(false);

        player->play();

        while(true) {
            audioManager->update();
        }

    } catch(const std::exception& e) {

        cout << e.what() << endl;

        return EXIT_FAILURE;

    }

    return EXIT_SUCCESS;

}
