#include <cstring>

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Utils/assert.hpp>

#include <Utils/Color.hpp>

#include <Utils/Texture.hpp>

#include <Utils/FreeType/Font.hpp>
#include <Utils/FreeType/Library.hpp>

using namespace std;

using namespace Utils;

using namespace Utils::FreeType;



Font::Font(const char* filePath) throw(invalid_argument, runtime_error):
    lib_(Library::getInstance()),
    fontBuffer_(lib_->loadFaceFile(filePath)),
    face_(lib_->createFaceFromBuffer(fontBuffer_, 0)),
    size_(12)
{}



Font::Font(const string& filePath) throw(invalid_argument, runtime_error):
    lib_(Library::getInstance()),
    fontBuffer_(lib_->loadFaceFile(filePath)),
    face_(lib_->createFaceFromBuffer(fontBuffer_, 0)),
    size_(12)
{}



Font::Font(const Font& font):
    lib_(Library::getInstance()),
    fontBuffer_(font.fontBuffer_),
    face_(lib_->createFaceFromBuffer(fontBuffer_, 0)),
    size_(font.size_)
{
}



Font::~Font() {

    if(lib_ != 0) {
        lib_->Free();
    }

}



Font& Font::operator=(const Font& font) {

    fontBuffer_  =  font.fontBuffer_;
    size_        =  font.size_;

    face_ = lib_->createFaceFromBuffer(fontBuffer_, 0);

    return *this;

}



Texture Font::renderText(const char* text) throw(invalid_argument, runtime_error) {

    ASSERT(
        (text != 0),
        invalid_argument("text")
    );

    ASSERT(
        (strlen(text) != 0),
        invalid_argument("text")
    );

    return Texture();

}



Texture Font::renderText(const string& text) throw(runtime_error) {

    Texture texture;

    try {
        texture = renderText(text.c_str());
    } catch(const invalid_argument&) {}

    return texture;

}



unsigned int Font::getSize() const {

    return size_;

}



void Font::setSize(unsigned int size) throw(invalid_argument) {

    ASSERT(
        (size != 0),
        invalid_argument("size")
    );

    size_ = size;

}



const Color& Font::getColor() const {

    return color_;

}



void Font::setColor(const Color& color) {

    color_ = color;

}
