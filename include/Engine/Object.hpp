#ifndef _SALT2D_ENGINE_OBJECT_HPP
#define _SALT2D_ENGINE_OBJECT_HPP

#include <boost/shared_ptr.hpp>

namespace Engine {

    class Object {

        public:

            Object() {}
            virtual ~Object() {}

            virtual void collision(const boost::shared_ptr<Object>& object) = 0;
            virtual void update() = 0;
            virtual void draw() = 0;
      //      virtual void checkCollision()

    };

}

#endif
