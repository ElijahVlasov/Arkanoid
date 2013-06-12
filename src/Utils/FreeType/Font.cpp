#include <climits>
#include <cstring>
#include <cwchar>

#include <algorithm>
#include <ios>
#include <fstream>
#include <list>
#include <mutex>
#include <string>

#include <boost/format.hpp>
#include <boost/foreach.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <FTGL/ftgl.h>

#include <Utils/assert.hpp>

#include <Utils/Graphics.hpp>

#include <Utils/Color.hpp>

#include <Utils/Texture.hpp>

#include <Utils.hpp>
#include <Utils/FreeType/Font.hpp>

using namespace std;

using namespace Utils;

using namespace Utils::FreeType;



Font::Font():
    font_(0)
{

    color_[0] = 0.0f;
    color_[1] = 1.0f;
    color_[2] = 0.0f;
    color_[3] = 0.0f;

}



Font::Font(const Font& font):
    font_(0)
{
    
    color_[0] = 0.0f;
    color_[1] = 0.0f;
    color_[2] = 0.0f;
    color_[3] = 0.0f;

    setData_(font.getData());

}



Font::~Font() {

    if(font_ != 0) {
        delete font_;
    }

}



Font& Font::operator=(const Font& font) {

    std::lock_guard<std::mutex> guard(synchroMutex_);
    
    setData_(font.getData());

    return *this;

}



void Font::renderText(const char* text, float x, float y) throw(invalid_argument, runtime_error) {

    ASSERT(
        (text != 0),
        invalid_argument("text")
    );

    renderText(string(text), x, y);

}



void Font::renderText(const string& text, float x, float y) throw(runtime_error) {

    renderText(stringToWString(text), x, y);

}



void Font::renderText(const wchar_t* wText, float x, float y) throw(invalid_argument, runtime_error) {

    ASSERT(
        (wText != 0),
        invalid_argument("wText")
    );

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(fontBuffer_.size() == 0) {
        throw(runtime_error("Can't render text! Font buffer empty.\n Check font file."));
    }

    glPushMatrix();
    glPushAttrib(GL_COLOR_BUFFER_BIT);

    glColor3fv(color_.c_array());

    font_->Render(wText,
                    -1,
                    FTPoint(static_cast<FTGL_FLOAT>(x), static_cast<FTGL_FLOAT>(y)),
                    FTPoint(),
                    FTGL::RENDER_ALL);    

    glPopAttrib();
    glPopMatrix();

}



void Font::renderText(const wstring& wText, float x, float y) throw(runtime_error) {

    try {

        renderText(wText.c_str(), x, y);

    } catch(const invalid_argument&) {}

}



unsigned int Font::getSize() const {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(font_ == 0) {
        return 0;
    }

    return font_->FaceSize();

}



void Font::setSize(unsigned int size) throw(invalid_argument) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    ASSERT(
        (size != 0),
        invalid_argument("size")
    );

    if(font_ == 0) {
        return;
    }

    font_->FaceSize(size);

}



const Color& Font::getColor() const {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    return color_;

}



void Font::setColor(const Color& color) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    color_ = color;

}



void Font::setData_(const string& data) {

    if(font_ != 0) {

        delete font_;
        font_ = 0;

    }

    fontBuffer_ = data;

    font_ = new FTTextureFont((const unsigned char*)fontBuffer_.data(), fontBuffer_.size());

    font_->FaceSize(12);

    if(font_->Error()) {
        fontBuffer_.clear();
    }

    font_->CharMap(ft_encoding_unicode);

}



void Font::setData(const string& data) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    setData_(data);

}



string Font::getData() const {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    return fontBuffer_;

}
