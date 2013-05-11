/*****************************************

    Все классы и функции утилитарного
    предназначения.

*****************************************/


#ifndef _SALT2D_UTILS_HPP
#define _SALT2D_UTILS_HPP

#include <fstream>
#include <string>

#include <boost/array.hpp>

#include <boost/geometry/geometries/point_xy.hpp>

#include <Utils/assert.hpp>
#include <Utils/Color.hpp>
#include <Utils/FreeType.hpp>
#include <Utils/Lua.hpp>
#include <Utils/MouseButton.hpp>
#include <Utils/Singleton.hpp>
#include <Utils/Texture.hpp>
#include <Utils/UI.hpp>

namespace Utils {

	typedef boost::array<boost::geometry::model::d2::point_xy<float>, 4> CoordArray; 

	// Отрисовка прямоугольника размером width * height в точке (x; y)
	// с текстурой texture и координатами текстуры texCoords 
	void draw(float x, float y, float width, float height, const CoordArray& texCoords, const Texture& texture);


	// Считать поток stream до символа EOF в std::string
	std::string readStreamToString(std::ifstream& stream);
	
}

#endif