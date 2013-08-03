#include <string>

#include <boost/shared_ptr.hpp>

#include <Utils/OpenAL/IStream.hpp>
#include <Utils/OpenAL/OGGSound.hpp>
#include <Utils/OpenAL/OGGStream.hpp>
#include <Utils/OpenAL/Sound.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::OpenAL;



OGGSound::OGGSound(const string& oggData):
    Sound(),
    oggData_(oggData)
{}



boost::shared_ptr<IStream> OGGSound::createStream() {

    return boost::shared_ptr<OGGStream>( new OGGStream(oggData_) );

}
