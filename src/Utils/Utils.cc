#include "config.h"

#include <fstream>
#include <ios>
#include <string>

#include <Utils.hpp>

using namespace std;



string Utils::readStreamToString(ifstream& is) {
	
    string streamText("");

    if(!is.good()) {

        return streamText;

    }

    char ch;

    while((ch = is.get()) != EOF) { // ������ �� �������

        streamText.push_back(ch);

    }

    return streamText;

}
