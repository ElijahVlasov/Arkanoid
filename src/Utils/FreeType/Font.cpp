#include <climits>
#include <cmath>
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
    color_(font.color_),
    font_(0)
{

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



Font::FONT_RECT Font::measureText(const char* text) throw(invalid_argument, runtime_error) {

    ASSERT(
        (text != 0),
        invalid_argument("text")
    );

    return measureText(string(text));

}



Font::FONT_RECT Font::measureText(const string& text) throw(runtime_error) {

    return measureText(UTF8_to_UTF16(text));

}



Font::FONT_RECT Font::measureText(const wchar_t* wText) throw(invalid_argument, runtime_error) {

    ASSERT(
        (wText != 0),
        invalid_argument("wText")
    );

    FTBBox bbox = font_->BBox(wText, -1);

    FTPoint low = bbox.Lower();
    FTPoint hi  = bbox.Upper();

    Font::FONT_RECT rect;

    rect.width  = hi.X() - low.X();
    rect.height = hi.Y() - low.Y();

    return rect;

}



Font::FONT_RECT Font::measureText(const wstring& wText) throw(runtime_error) {

    try {

        return measureText(wText.c_str());

    } catch(const invalid_argument&){}

    //return FTBBox();

}



void Font::renderText(const char* text, float x, float y, float width, float height) throw(invalid_argument, runtime_error) {

    ASSERT(
        (text != 0),
        invalid_argument("text")
    );

    renderText(string(text), x, y, width, height);

}



void Font::renderText(const string& text, float x, float y, float width, float height) throw(runtime_error) {

    renderText(UTF8_to_UTF16(text), x, y, width, height);

}



void Font::renderText(const wchar_t* wText, float x, float y, float width, float height) throw(invalid_argument, runtime_error) {

    ASSERT(
        (wText != 0),
        invalid_argument("wText")
    );

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(fontBuffer_.size() == 0) {
        throw(runtime_error("Can't render text! Font buffer empty.\n Check font file."));
    }

    size_t textLen = wcslen(wText);

    if(width >= 0.0f) {

        Font::FONT_RECT rect = measureText(wText);

        if(rect.width > width) {

            float pixPerChar     = rect.width / textLen;

            float excess         = rect.width - width;

            size_t charsForErase = static_cast<size_t>(lround(excess / pixPerChar));

            textLen -= charsForErase;

        }

    }

    glPushMatrix();
    glPushAttrib(GL_COLOR_BUFFER_BIT);

    glColor3fv(color_.c_array());

    font_->Render(wText,
                    textLen,
                    FTPoint(static_cast<FTGL_FLOAT>(x), static_cast<FTGL_FLOAT>(y)),
                    FTPoint(),
                    FTGL::RENDER_ALL);

    glPopAttrib();
    glPopMatrix();

}



void Font::renderText(const wstring& wText, float x, float y, float width, float height) throw(runtime_error) {

    try {

        renderText(wText.c_str(), x, y, width, height);

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
