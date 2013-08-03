#include <cstdlib>

#include <exception>
#include <fstream>
#include <ios>
#include <iostream>
#include <string>

#include <conio.h>

#include <Utils/SingletonPointer.hpp>

#include <Utils/OpenAL/Audio.hpp>
#include <Utils/OpenAL/OGGSound.hpp>
#include <Utils/OpenAL/OGGSoundBuilder.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::OpenAL;



int main(int argc, char* argv[]) {

    try {

        SingletonPointer<Audio>             audio           =   Audio::getInstance();
        SingletonPointer<OGGSoundBuilder>   soundBuilder    =   OGGSoundBuilder::getInstance();

        fstream soundStream("sound.ogg");
        string soundData;

        soundStream.seekg(0, ios_base::end);
        soundData.resize(soundStream.tellg());
        soundStream.seekg(0, ios_base::beg);

        soundStream.read(const_cast<char*>(soundData.data()), soundData.size());

        auto sound = soundBuilder->createSound(soundData);

        auto player = audio->createSoundPlayer(sound);

        player->play();

        while(true) {
            audio->update();
        }

    } catch(const std::exception& e) {

        cout << e.what() << endl;

        return EXIT_FAILURE;

    }

    return EXIT_SUCCESS;

}
