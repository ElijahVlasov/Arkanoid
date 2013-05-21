#include "config.h"

#ifdef MS_WINDOWS
#include <Windows.h>
#endif 

#include <GL/gl.h>
#include <GL/glu.h>

#include <boost/geometry/geometries/point_xy.hpp>

#include <Utils/Graphics.hpp>
#include <Utils/Texture.hpp>

using namespace boost::geometry::model::d2;

using namespace Utils;


float Graphics::scrWidth_;
float Graphics::scrHeight_;



Graphics::Graphics() {

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glDisable(GL_DEPTH_TEST);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

}



void Graphics::DrawTexture(float x, float y, const Texture& texture) {

    DrawTexture(x, y, texture.getWidth(), texture.getHeight(), texture);

}



void Graphics::DrawTexture(float x, float y, float width, float height, const Texture& texture) {

    static const Graphics::CoordArray texCoords = {

        point_xy<float>(0.0f, 0.0f),
        point_xy<float>(1.0f, 0.0f),
        point_xy<float>(0.0f, 1.0f),
        point_xy<float>(1.0f, 1.0f)

    };

    DrawTexture(x, y, width, height, texCoords, texture);

}



void Graphics::DrawTexture(float x, float y, float width, float height, const CoordArray& texCoords, const Texture& texture) {

    // биндим текстуру
    glBindTexture(GL_TEXTURE_2D, texture.getName());

    // рисуем 2 треугольника
    glBegin(GL_TRIANGLE_STRIP);

    glTexCoord2f(    texCoords[0].x(), (texCoords[0].y())); 
    glVertex2f(x,            y);

    glTexCoord2f(    texCoords[1].x(), texCoords[1].y());
    glVertex2f(x + width,    y);

    glTexCoord2f(    texCoords[2].x(), texCoords[2].y());
    glVertex2f(x,            y + height);

    glTexCoord2f(    texCoords[3].x(), texCoords[3].y());
    glVertex2f(x + width,    y + height);

    glEnd();

}



void Graphics::setViewportSize(unsigned int width, unsigned int height) {

    scrWidth_   =  static_cast<float>(width);
    scrHeight_  =  static_cast<float>(height);

    gluOrtho2D(0, width, 0, height);

}
