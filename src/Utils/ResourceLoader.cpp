#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/assert.hpp>

#include <Utils/ResourceLoader.hpp>
#include <Utils/SingletonPointer.hpp>

#include <Utils/Audio/OGGSoundBuilder.hpp>
#include <Utils/Audio/Sound.hpp>

#include <Utils/Graphics/PNGTextureBuilder.hpp>
#include <Utils/Graphics/Texture.hpp>

#include <Utils/FreeType/Font.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::Audio;
using namespace Utils::Graphics;
using namespace Utils::FreeType;



boost::shared_ptr<Texture> ResourceLoader::loadTexture(const char* fileName) throw(invalid_argument, runtime_error) {

    Utils::SingletonPointer<PNGTextureBuilder> textureBuilder = PNGTextureBuilder::getInstance();

    string data = readFile(fileName);

    return textureBuilder->createTexture(data);

}



boost::shared_ptr<Sound> ResourceLoader::loadSound(const char* fileName) throw(invalid_argument, runtime_error) {

    Utils::SingletonPointer<OGGSoundBuilder> soundBuilder = OGGSoundBuilder::getInstance();

    string data = readFile(fileName);

    return soundBuilder->createSound(data);

}



boost::shared_ptr<Font> ResourceLoader::loadFont(const char* fileName) throw(invalid_argument, runtime_error) {

    string data = readFile(fileName);

    return boost::shared_ptr<Font>(new Font(data));

}
