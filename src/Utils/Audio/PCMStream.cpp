#include <string>

#include <Utils/Audio/Buffer.hpp>
#include <Utils/Audio/PCMStream.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::Audio;



PCMStream::PCMStream(const string& pcmData):
    pcmData_(pcmData)
{}



bool PCMStream::nextBuffer(Buffer& buffer) {

    buffer.setData(pcmData_);

    return true;

}
