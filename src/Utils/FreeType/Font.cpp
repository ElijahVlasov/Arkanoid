#include <climits>
#include <cstring>

#include <algorithm>
#include <ios>
#include <fstream>
#include <list>
#include <mutex>
#include <string>

#include <boost/cstdint.hpp>
#include <boost/format.hpp>
#include <boost/foreach.hpp>

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

#include <ft2build.h>
#include FT_FREETYPE_H

#include "config.h"

#ifdef MS_WINDOWS
#include <Windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

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

    renderText(string(text), x, y);

}



void Font::renderText(const string& text, float x, float y) throw(runtime_error) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    if(fontBuffer_.size() == 0) {
        throw(runtime_error("Pish pish"));
    }

    wstring wText = stringToWString(text);

    glPushMatrix();
    //glLoadIdentity();                // Âûêëþ÷àåì òåêñòóðû
    //glDisable(GL_TEXTURE_2D);

    glPushAttrib(GL_COLOR_BUFFER_BIT);

    glColor3fv(color_.c_array());

    font_->Render(wText.c_str(),
                    -1,
                    FTPoint(static_cast<FTGL_FLOAT>(x), static_cast<FTGL_FLOAT>(y)),
                    FTPoint(),
                    FTGL::RENDER_ALL);    

    glPopAttrib();

    //glEnable(GL_TEXTURE_2D);
    glPopMatrix();

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

    /*Color color = {

        monochromeFont_->foregroundRed(),
        monochromeFont_->foregroundGreen(),
        monochromeFont_->foregroundBlue(),
        monochromeFont_->foregroundAlpha()

    };*/

    return color_;

}



void Font::setColor(const Color& color) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    /*if(monochromeFont_ != 0) {    
        monochromeFont_->setForegroundColor(color[0], color[1], color[2], color[3]);
    }*/

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