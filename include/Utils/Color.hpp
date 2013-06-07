#ifndef _SALT2D_UTILS_COLOR_HPP
#define _SALT2D_UTILS_COLOR_HPP

#include <boost/array.hpp>
#include <boost/cstdint.hpp>

namespace Utils {

    /** Тип для RGBA-цвета.
      * Красный цвет - Color[0]
      * Зеленый цвет - Color[1]
      * Синий цвет - Color[2]
      * Альфа-канал - Color[3]
    */

    typedef boost::array<float, 4> Color;

    /** Перевести цвет в int32.
    */

    inline boost::int32_t ColorToInt32(const Color& color);

}

boost::int32_t Utils::ColorToInt32(const Utils::Color& color) {

    int r = static_cast<int>(color[0] * 255);
    int g = static_cast<int>(color[1] * 255);
    int b = static_cast<int>(color[2] * 255);
    int a = static_cast<int>(color[3] * 255);

    return static_cast<boost::int32_t>( ( (a << 24) | (r << 16) | (g << 8) | b ) );

}

#endif
