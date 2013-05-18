/** Классы и функции утилитарного назначения.
  * @author Elijah Vlasov
*/


#ifndef _SALT2D_UTILS_HPP
#define _SALT2D_UTILS_HPP

#include <fstream>
#include <string>

#include <boost/array.hpp>

#include <boost/geometry/geometries/point_xy.hpp>

#include <Utils/assert.hpp>
#include <Utils/Color.hpp>
#include <Utils/FreeType.hpp>
#include <Utils/Graphics.hpp>
#include <Utils/Lua.hpp>
#include <Utils/MouseButton.hpp>
#include <Utils/Singleton.hpp>
#include <Utils/Texture.hpp>
#include <Utils/UI.hpp>

namespace Utils {

    /** Считать поток до символа EOF в std::string.
      * @param stream поток для чтения
    */
    std::string readStreamToString(std::ifstream& stream);
	
}

#endif
