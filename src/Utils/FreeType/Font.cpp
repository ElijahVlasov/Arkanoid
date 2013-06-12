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

<<<<<<< HEAD
}



/*void Font::createSymbolVisual(unsigned char ch) {

    Texture* symTexture = new Texture();

    FT_UInt charIndex = FT_Get_Char_Index(face_, ch);

    ASSERT(
        (FT_Load_Glyph(face_, charIndex, FT_LOAD_DEFAULT) == 0),
        runtime_error("Can't get glyph from face")
    );

    FT_Glyph glyph;

    ASSERT(
        (FT_Get_Glyph(face_->glyph, & glyph) == 0),
        runtime_error("Can't get glyph from face")
    );

    FT_Glyph_To_Bitmap( &glyph, ft_render_mode_normal, 0, 1 );
    FT_BitmapGlyph bitmapGlyph = (FT_BitmapGlyph)glyph;

    FT_Bitmap& bitmap = bitmapGlyph->bitmap;

    int width  = next_p2(bitmap.width); // размеры текстуры должны быть
    int height = next_p2(bitmap.rows);  // равны степеням двойки.

    string textureData;

    textureData.resize(4 * width * height);

    // сиволы хранятся в формате RGBA.
    boost::int32_t* data = reinterpret_cast<boost::int32_t*>(const_cast<char*>(textureData.data()));

    for(size_t i = 0; i < static_cast<size_t>(height); i++) {
    
        for(size_t j = 0; j < static_cast<>width; j++) {
        
            size_t dataIndex = j + i * width;

            if((j >= bitmap.width) || (i >= bitmap.rows)) { // если вышли за пределы FT_Bitmap'а
            
                data[dataIndex] = 0;

            } else {
            
                if(bitmap.buffer[j + bitmap.width * i] != 0) {
                
                    data[dataIndex] = ColorToInt32(color_);

                } else { 

                    static const Color transparent = {0.0f, 0.0f, 0.0f, 1.0f};
                
                    data[dataIndex] = ColorToInt32(transparent);

                }

            }

        }

    }

    symTexture->setFormat(GL_RGBA);

    symTexture->setWidth(static_cast<unsigned int>(width));
    symTexture->setHeight(static_cast<unsigned int>(height));

    symTexture->setData(textureData);

    glNewList(listBase_ + ch, GL_COMPILE);    

    glBindTexture(GL_TEXTURE_2D, symTexture->getName());

    glTranslatef(bitmapGlyph->left, 0.0f, 0.0f);

    glPushMatrix();
    glTranslatef(0.0f, bitmapGlyph->top - bitmap.rows, 0.0f);

    float x = static_cast<float>(bitmap.width) / static_cast<float>(width);
    float y = static_cast<float>(bitmap.rows)  / static_cast<float>(height);

    glBegin(GL_QUADS);

    glTexCoord2d(0,0); glVertex2f(0,bitmap.rows);
    glTexCoord2d(0,y); glVertex2f(0,0);
    glTexCoord2d(x,y); glVertex2f(bitmap.width,0);
    glTexCoord2d(x,0); glVertex2f(bitmap.width,bitmap.rows);
    
    glEnd();
  
    glPopMatrix();
    glTranslatef(face_->glyph->advance.x >> 6 ,0,0);

    glEndList();

    symbols_[ch] = boost::shared_ptr<Texture>(symTexture);

}*/



/*void Font::testDraw() {

   // for(unsigned char ch = 0; ch <= UCHAR_MAX; ch++) {
    
        static const Graphics::CoordArray coords = {
        
            boost::geometry::model::d2::point_xy<float>(0.0f, 0.0f),
            boost::geometry::model::d2::point_xy<float>(1.0f, 0.0f),
            boost::geometry::model::d2::point_xy<float>(0.0f, 1.0f),
            boost::geometry::model::d2::point_xy<float>(1.0f, 1.0f)

        };

        if(symbols_[78] != 0) {
            Graphics::DrawTexture(0,0, symbols_[78]->getWidth(), symbols_[78]->getHeight(), coords, *(symbols_[78]));
        }

    //}

}*/
=======
}
>>>>>>> 16b3e3f4ae8cdcad4576442f8db5293f75b68d48
