#ifndef _SALT2D_ENGINE_ISPRITE_HPP
#define _SALT2D_ENGINE_ISPRITE_HPP

#include "geometry_defines.hpp"

namespace Engine {

    class ISprite {

        public:

            virtual ~ISprite() = 0;

            virtual void onRender(const GeometryDefines::Point& drawPoint) = 0;

    };

}

#endif
