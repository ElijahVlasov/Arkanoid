#ifndef _SALT2D_UTILS_SPRITE_HPP
#define _SALT2D_UTILS_SPRITE_HPP

#include "geometry_defines.hpp"

namespace Utils {

    /** Интерфейс для отрисовки объектов.
    */

    class Sprite {

        public:

            virtual ~Sprite();

            /** Отрисоваться в точке.
            */

            virtual void onRender(const GeometryDefines::Point& point) = 0;
            virtual void onRender(const GeometryDefines::PointI& point);

            /** Отрисовать прямоугольник.
            */

            virtual void onRender(const GeometryDefines::Box& box) = 0;
            virtual void onRender(const GeometryDefines::BoxI& box);

            /** Отрисовать многоугольник.
            */

            virtual void onRender(const GeometryDefines::Polygon& polygon) = 0;
            virtual void onRender(const GeometryDefines::PolygonI& polygon);

    };

}

#endif
