#include "config.h"

#include <fstream>
#include <ios>
#include <string>

#include <Utils.hpp>

using namespace std;



string Utils::readStreamToString(ifstream& is) {

    string streamText;

    if(!is.good()) {

        return streamText;

    }

    char ch;

    while((ch = is.get()) != EOF) { // читаем по символу

        streamText.push_back(ch);

    }

    return streamText;

}



string Utils::readBinaryStream(ifstream& stream) {

    string streamData;

    stream.seekg(0, ios_base::end);
    streamData.resize(stream.tellg());
    stream.seekg(0, ios_base::beg);

    stream.read(const_cast<char*>(streamData.data()), streamData.size());

    return streamData;

}
