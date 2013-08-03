#include <string>

#include <Utils/OpenAL/Buffer.hpp>
#include <Utils/OpenAL/PCMStream.hpp>

using namespace std;

using namespace Utils;
using namespace Utils::OpenAL;



PCMStream::PCMStream(const string& pcmData):
    pcmData_(pcmData)
{}



bool PCMStream::nextBuffer(Buffer& buffer) {

    buffer.setData(pcmData_);

}
