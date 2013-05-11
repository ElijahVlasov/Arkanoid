#include <cstring>

#include <string>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <Utils/Texture.hpp>

#include <Utils/FreeType/Font.hpp>
#include <Utils/FreeType/Library.hpp>

using namespace std;

using namespace Utils::FreeType;

using Utils::Texture;



Font::Font(const char* filePath):
	lib_(Library::getInstance()),
	facePtr_(lib_->loadFace(filePath, 0, new FT_Face)),
	size_(12)
{}



Font::Font(const string& filePath):
	lib_(Library::getInstance()),
	facePtr_(lib_->loadFace(filePath, 0, new FT_Face)),
	size_(0)
{}



Font::Font(const Font& font):
	lib_(Library::getInstance()),
	facePtr_(font.facePtr_),
	size_(font.size_)
{
}



Font::~Font() {

	if(lib_ != 0) {

		lib_->Free();

	}

}



Font& Font::operator=(const Font& font) {

	facePtr_	=	font.facePtr_;
	size_		=	font.size_;

	return *this;

}



Texture Font::renderText(const char* text) {

	if((text == 0)
		||(strlen(text) == 0)) {
	
			throw(invalid_argument("text"));

	}



}



Texture Font::renderText(const string& text) {

	return renderText(text.c_str());

}



unsigned int Font::getSize() const {

	return size_;

}



void Font::setSize(unsigned int size) {

	if(size == 0) {
	
		throw(invalid_argument("size"));

	}

	size_ = size;

}



Font::Color Font::getColor() const {

	return color_;

}



void Font::setColor(const Font::Color& color) {

	color_ = color;

}