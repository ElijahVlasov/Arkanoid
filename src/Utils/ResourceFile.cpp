#include <string>

#include <Utils/ResourceFile.hpp>

using namespace std;

using namespace Utils;



ResourceFile::ResourceFile() {}



ResourceFile::~ResourceFile() {}



string ResourceFile::getData() const {

    return text_;

}



void ResourceFile::setData(const string& data) {

    text_ = data;

}
