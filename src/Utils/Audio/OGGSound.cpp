#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/Audio/IStream.hpp>
#include <Utils/Audio/OGGSound.hpp>
#include <Utils/Audio/OGGStream.hpp>
#include <Utils/Audio/Sound.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::Audio;



OGGSound::OGGSound(const string& oggData):
    Sound(),
    oggData_(oggData)
{}



boost::shared_ptr<IStream> OGGSound::createStream() {

    return boost::shared_ptr<OGGStream>( new OGGStream(oggData_) );

}
