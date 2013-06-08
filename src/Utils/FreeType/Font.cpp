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
#include FT_GLYPH_H

#include "config.h"

#ifdef MS_WINDOWS
#include <Windows.h>
#endif

#include <GL/gl.h>
#include <GL/glu.h>

#include <Utils/assert.hpp>

#include <Utils/Graphics.hpp>

#include <Utils/Color.hpp>

#include <Utils/Texture.hpp>

#include <Utils/FreeType/Font.hpp>
#include <Utils/FreeType/Library.hpp>

using namespace std;

using namespace Utils;

using namespace Utils::FreeType;



Font::Font():
    isRendered_(false),
    listBase_(glGenLists(UCHAR_MAX + 1)),
    lib_(Library::getInstance()),
    size_(5)
{

    color_[0] = 0.0f;
    color_[1] = 0.0f;
    color_[2] = 0.0f;
    color_[3] = 0.0f;

}



Font::Font(const Font& font):
    isRendered_(false),
    listBase_(glGenLists(UCHAR_MAX + 1)),
    lib_(Library::getInstance()),
    size_(font.size_),
    color_(font.color_)
{

    setData_(font.getData());

}



Font::~Font() {

    if(fontBuffer_.size() != 0) { // если буфер не пуст, значит шрифт загружен
        FT_Done_Face(face_);
    }

    if(lib_ != 0) {
        lib_->Free();
    }

    glDeleteLists(listBase_, UCHAR_MAX + 1);

}



Font& Font::operator=(const Font& font) {

    std::lock_guard<std::mutex> guard(synchroMutex_);
    
    isRendered_ =   false;
    size_       =   font.size_;
    color_      =   font.color_;
    symbols_    =   font.symbols_;

    setData_(font.getData());

    return *this;

}



void Font::renderText(const char* text, float x, float y) throw(invalid_argument, runtime_error) {

    renderText(string(text), x, y);

  /*  Texture renderedText;

    renderedText.setFormat(GL_RGBA);

    string textureData;

    ASSERT(
        (text != 0),
        invalid_argument("text")
    );

    size_t strSize = strlen(text);

    unsigned int width  = strSize * (size_);
    unsigned int height = size_;

    renderedText.setHeight(height);
    renderedText.setWidth(width);

    textureData.resize(4 * (width * height));

    for (int pixI = 0; pixI < height; pixI++) {

        for(size_t i = 0; i < strSize; i++) {
    
            boost::shared_ptr<Texture> symbol = symbols_[i];

            if(symbol == 0) {
                continue;
            }

            string data = symbol->getData();

            copy(data.begin() + pixI * width, data.begin() + pixI * width + width, textureData.begin() + pixI * width);

        }

    }

    renderedText.setData(textureData);

    return renderedText;*/

}



void Font::renderText(const string& text, float x, float y) throw(runtime_error) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    list<string> lines;

    boost::split(lines, text, boost::is_any_of("\n"), boost::token_compress_on);

    glPushAttrib(GL_TRANSFORM_BIT);
    GLint   viewport[4];
    glGetIntegerv(GL_VIEWPORT, viewport);
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(viewport[0], viewport[2], viewport[1], viewport[3]);
    glPopAttrib();

    glPushAttrib(GL_LIST_BIT | GL_CURRENT_BIT  | GL_ENABLE_BIT | GL_TRANSFORM_BIT);
    glMatrixMode(GL_MODELVIEW);
    /*glDisable(GL_LIGHTING);
    glEnable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);     */
 
    glListBase(listBase_);

    float modelViewMatrix[16];

    glGetFloatv(GL_MODELVIEW_MATRIX, modelViewMatrix);

    unsigned int i = 0;

    BOOST_FOREACH(const string& line, lines) {
    
        glPushMatrix();
        glLoadIdentity();
        glTranslatef(x, y - (size_ + 2) * i++, 0);
        glMultMatrixf(modelViewMatrix);

        glCallLists(line.length(), GL_UNSIGNED_BYTE, line.data());

        glPopMatrix();

    }

    glPopAttrib();  

    glPushAttrib(GL_TRANSFORM_BIT);
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glPopAttrib();

}



unsigned int Font::getSize() const {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    return size_;

}



void Font::setSize(unsigned int size) throw(invalid_argument) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    ASSERT(
        (size != 0),
        invalid_argument("size")
    );

    size_ = size;
    
    renderFace();

}



const Color& Font::getColor() const {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    return color_;

}



void Font::setColor(const Color& color) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    color_ = color;

    renderFace();

}



void Font::setData_(const string& data) {

    //std::lock_guard<std::mutex> guard(synchroMutex_);

    if(fontBuffer_.size() != 0) { // если буфер не пуст, значит шрифт загружен
        FT_Done_Face(face_);
    }

    fontBuffer_ = data;

    try {

        face_ = lib_->createFaceFromBuffer(fontBuffer_, 0);

        if(!isRendered_) {
            renderFace();
        }


    } catch(const runtime_error&) {

        fontBuffer_.clear(); // если произошли ошибки очищаем буфер

    }

}



void Font::setData(const string& data) {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    setData_(data);

}



string Font::getData() const {

    std::lock_guard<std::mutex> guard(synchroMutex_);

    return fontBuffer_;

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
