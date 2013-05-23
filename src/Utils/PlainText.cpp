#include <string>

#include <Utils/PlainText.hpp>

using namespace std;

using namespace Utils;



const string& PlainText::getData() const {

    return text_;

}



void PlainText::setData(const string& data) {

    text_ = data;

}
