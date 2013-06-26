#ifndef _SATL2D_ENGINE_DIRECTION_TO_COORDSARRAY_H
#define _SATL2D_ENGINE_DIRECTION_TO_COORDSARRAY_H

#include <Engine/Direction.hpp>

#include <Utils/Graphics.hpp>

namespace Engine {

    /** Преобразовать Direction в соответствующие координаты OpenGL.
    */

    inline Utils::Graphics::CoordArray DirectionToCoordsArray(Direction dir);

}

Utils::Graphics::CoordArray Engine::DirectionToCoordsArray(Engine::Direction dir) {

    using Utils::Graphics;

    switch(dir) {

        case UP: {
            return Graphics::UP_COORDS;
        }
        break;

        case DOWN: {
            return Graphics::DOWN_COORDS;
        }
        break;

        case LEFT: {
            return Graphics::LEFT_COORDS;
        }
        break;

        case RIGHT: {
            return Graphics::RIGHT_COORDS;
        }
        break;

    }

}

#endif
