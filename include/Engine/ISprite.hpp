#ifndef _SALT2D_ENGINE_ISPRITE_HPP
#define _SALT2D_ENGINE_ISPRITE_HPP

#include <Engine/Direction.hpp>

#include "geometry_defines.hpp"

namespace Engine {

    class ISprite {

        public:

            virtual ~ISprite() = 0;

            virtual void onRender(const GeometryDefines::Point& drawPoint, Direction dir) = 0;
            virtual void onRender(const GeometryDefines::Box& drawBox,     Direction dir) = 0;

    };

}

#endif
