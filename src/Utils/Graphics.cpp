#include <Utils/Color.hpp>
#include <Utils/Graphics.hpp>
#include <Utils/Texture.hpp>

#include "geometry_defines.hpp"
#include "gl_includes.h"

using namespace GeometryDefines;

using namespace Utils;



const Color Graphics::defaultClearColor_ = {1.0f, 1.0f, 1.0f, 0.0f};



const Graphics::CoordArray Graphics::UP_COORDS = {

    Point(0.0f, 0.0f),
    Point(1.0f, 0.0f),
    Point(1.0f, 1.0f),
    Point(0.0f, 1.0f)

};



const Graphics::CoordArray Graphics::DOWN_COORDS = {

    Point(1.0f, 0.0f),
    Point(0.0f, 0.0f),
    Point(0.0f, 1.0f),
    Point(1.0f, 1.0f)

};



const Graphics::CoordArray Graphics::LEFT_COORDS = {

    Point(0.0f, 0.0f),
    Point(0.0f, 1.0f),
    Point(1.0f, 1.0f),
    Point(1.0f, 0.0f)

};



const Graphics::CoordArray Graphics::RIGHT_COORDS = {

    Point(0.0f, 1.0f),
    Point(0.0f, 0.0f),
    Point(1.0f, 0.0f),
    Point(1.0f, 1.0f)

};



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



void Graphics::DrawTexture(const Point& point, const Texture& texture, const Graphics::CoordArray& texCoords) {

    Box box(point, Point(point.x() + texture.getWidth(), point.y() + texture.getHeight()));

    DrawTexture(box, texture, texCoords);

}



void Graphics::DrawTexture(const PointI& point, const Texture& texture, const Graphics::CoordArray& texCoords) {

    BoxI box(point, PointI(point.x() + texture.getWidth(), point.y() + texture.getHeight()));

    DrawTexture(box, texture, texCoords);

}



void Graphics::DrawTexture(const Box& box, const Texture& texture, const Graphics::CoordArray& texCoords) {

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, texture.getName());

    glBegin(GL_QUADS);

    glTexCoord2f(texCoords[0].x(), texCoords[0].y());
    glVertex2f(box.min_corner().x(), box.min_corner().y());

    glTexCoord2f(texCoords[1].x(), texCoords[1].y());
    glVertex2f(box.max_corner().x(), box.min_corner().y());

    glTexCoord2f(texCoords[2].x(), texCoords[2].y());
    glVertex2f(box.max_corner().x(), box.max_corner().y());

    glTexCoord2f(texCoords[3].x(), texCoords[3].y());
    glVertex2f(box.min_corner().x(), box.max_corner().y());

    glEnd();

}



void Graphics::DrawTexture(const BoxI& box, const Texture& texture, const Graphics::CoordArray& texCoords) {

    glColor4f(1.0f, 1.0f, 1.0f, 1.0f);

    glBindTexture(GL_TEXTURE_2D, texture.getName());

    glBegin(GL_QUADS);

    glTexCoord2f(texCoords[0].x(), texCoords[0].y());
    glVertex2i(box.min_corner().x(), box.min_corner().y());

    glTexCoord2f(texCoords[1].x(), texCoords[1].y());
    glVertex2i(box.max_corner().x(), box.min_corner().y());

    glTexCoord2f(texCoords[2].x(), texCoords[2].y());
    glVertex2i(box.max_corner().x(), box.max_corner().y());

    glTexCoord2f(texCoords[3].x(), texCoords[3].y());
    glVertex2i(box.min_corner().x(), box.max_corner().y());

    glEnd();

}



void Graphics::DrawTexture(const GeometryDefines::Polygon& polygon, const Texture& texture, const Graphics::CoordArray& texCoords) {

	const GeometryDefines::Polygon::ring_type& polygonOuter = polygon.outer();

	auto pointIter = polygonOuter.begin();

	glBegin(GL_QUADS);

	for(unsigned int i = 0; (i < 4) && (pointIter != polygonOuter.end()); i++, ++pointIter) {

		glTexCoord2f(texCoords[i].x(), texCoords[i].y());
		glVertex2f(pointIter->x(), pointIter->y());

	}

	glEnd();

}



void Graphics::DrawTexture(const GeometryDefines::PolygonI& polygon, const Texture& texture, const Graphics::CoordArray& texCoords) {

	const GeometryDefines::PolygonI::ring_type& polygonOuter = polygon.outer();

	auto pointIter = polygonOuter.begin();

	glBegin(GL_QUADS);

	for(unsigned int i = 0; (i < 4) && (pointIter != polygonOuter.end()); i++, ++pointIter) {

		glTexCoord2f(texCoords[i].x(), texCoords[i].y());
		glVertex2i(pointIter->x(), pointIter->y());

	}

	glEnd();

}



void Graphics::setViewportSize(unsigned int width, unsigned int height) {

    scrWidth_   =  static_cast<float>(width);
    scrHeight_  =  static_cast<float>(height);

    gluOrtho2D(0, width, 0, height);

}



void Graphics::ClearScreen(const Color& clearColor) {

    glClearColor(clearColor[0], clearColor[1], clearColor[2], clearColor[3]);

    glClear(GL_COLOR_BUFFER_BIT);

}
