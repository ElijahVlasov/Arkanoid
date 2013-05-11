/*****************************************

    ��� ������ � ������� ������������
    ��������������.

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

	// ��������� �������������� �������� width * height � ����� (x; y)
	// � ��������� texture � ������������ �������� texCoords 
	void draw(float x, float y, float width, float height, const CoordArray& texCoords, const Texture& texture);


	// ������� ����� stream �� ������� EOF � std::string
	std::string readStreamToString(std::ifstream& stream);
	
}

#endif