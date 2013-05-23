#include <string>

#include <Utils/PlainText.hpp>

using namespace std;

using namespace Utils;



string ResourceFile::getData() const {

    return text_;

}



void ResourceFile::setData(const string& data) {

    text_ = data;

}



ResourceFile::~ResourceFile() {}
