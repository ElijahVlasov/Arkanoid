#ifndef _SALT2D_UTILS_COLOR_HPP
#define _SALT2D_UTILS_COLOR_HPP

#include <boost/array.hpp>

namespace Utils {

    /** Тип для RGBA-цвета.
      * Красный цвет - Color[0]
      * Зеленый цвет - Color[1]
      * Синий цвет - Color[2]
      * Альфа-канал - Color[3]
    */

    typedef boost::array<float, 4> Color;

}

#endif
