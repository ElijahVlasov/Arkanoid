#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/OpenAL/IStream.hpp>
#include <Utils/OpenAL/PCMSound.hpp>
#include <Utils/OpenAL/PCMStream.hpp>
#include <Utils/OpenAL/Sound.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::OpenAL;



PCMSound::PCMSound(const string& pcmData):
    Sound(),
    stream_(new PCMStream(pcmData))
{}



boost::shared_ptr<IStream> PCMSound::createStream() {

    return stream_;

}
