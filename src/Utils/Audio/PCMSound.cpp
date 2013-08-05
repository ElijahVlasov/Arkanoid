#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/Audio/IStream.hpp>
#include <Utils/Audio/PCMSound.hpp>
#include <Utils/Audio/PCMStream.hpp>
#include <Utils/Audio/Sound.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::Audio;



PCMSound::PCMSound(const string& pcmData):
    Sound(),
    stream_(new PCMStream(pcmData))
{}



boost::shared_ptr<IStream> PCMSound::createStream() {

    return stream_;

}
