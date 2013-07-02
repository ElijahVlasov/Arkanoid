#ifndef _SALT2D_ENGINE_ISPRITE_HPP
#define _SALT2D_ENGINE_ISPRITE_HPP

#include <Engine/Direction.hpp>

#include "geometry_defines.hpp"

namespace Engine {

    /** Интерфейс для отрисовки объектов.
    */

    class ISprite {

        public:

            virtual ~ISprite() = 0;

            /** Отрисоваться в точке.
            */

            virtual void onRender(const GeometryDefines::Point& point) = 0;

            /** Отрисовать прямоугольник.
            */

            virtual void onRender(const GeometryDefines::Box& box) = 0;

            virtual void onRender(const GeometryDefines::Polygon& polygon) = 0;

    };

}

#endif
