#include "config.h"

#include <fstream>
#include <ios>
#include <string>

#include <boost/array.hpp>
#include <boost/geometry/geometries/point_xy.hpp>

#ifdef MS_WINDOWS
#include <Windows.h>
#endif

#include <GL/gl.h>

#include <Utils.hpp>

using namespace std;



void Utils::draw(float x, float y, float width, float height, const Utils::CoordArray& texCoords, const Utils::Texture& texture) {

		// биндим текстуру
		glBindTexture(GL_TEXTURE_2D, texture.getName());

		// рисуем 2 треугольника
		glBegin(GL_TRIANGLE_STRIP);

		glTexCoord2f(	texCoords[0].x(),	texCoords[0].y()); 
		glVertex2f(x,			y);

		glTexCoord2f(	texCoords[1].x(), texCoords[1].y());
		glVertex2f(x + width,	y);

		glTexCoord2f(	texCoords[2].x(), texCoords[2].y());
		glVertex2f(x,			y + height);

		glTexCoord2f(	texCoords[3].x(), texCoords[3].y());
		glVertex2f(x + width,	y + height);

		glEnd();

}



string Utils::readStreamToString(ifstream& is) {
	
	string streamText("");

	if(!is.good()) {

		return streamText;

	}

	char ch;

	while((ch = is.get()) != EOF) { // читаем по символу

		streamText.push_back(ch);

	}

	return streamText;

}
