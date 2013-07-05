#ifndef _SALT2D_ENGINE_COLLISION_HPP
#define _SALT2D_ENGINE_COLLISION_HPP

#include <Engine/Object.hpp>

namespace Engine {

    class Collision {

        public:

            inline Collision(const ObjectPtr& obj1, const ObjectPtr& obj2):
                obj1_(obj1),
                obj2_(obj2)
            {}



            inline const ObjectPtr& getFirst() const {
                return obj1_;
            }



            inline const ObjectPtr& getSecond() const {
                return obj2_;
            }

        private:

            ObjectPtr obj1_, obj2_;

    };

}

#endif
