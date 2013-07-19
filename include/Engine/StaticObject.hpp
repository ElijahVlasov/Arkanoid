#ifndef _SALT2D_ENGINE_STATICOBJECT_HPP
#define _SALT2D_ENGINE_STATICOBJECT_HPP

#include <Engine/Object.hpp>

namespace Engine {

    class StaticObject: public Object {

        public:

            void move(float step);
            void spin(float step);

    };

}

#endif
