#ifndef _SALT2D_ENGINE_DYNAMICOBJECT_HPP
#define _SALT2D_ENGINE_DYNAMICOBJECT_HPP

#include <mutex>

#include <boost/shared_ptr.hpp>

#include <Engine/Collision.hpp>
#include <Engine/IController.hpp>
#include <Engine/Object.hpp>

namespace Engine {

    class DynamicObject: public Object {

        public:

            DynamicObject();

            virtual void onStartMoving() = 0;
            virtual void onEndMoving()   = 0;

            virtual void onCollision(const Collision& collision);

            virtual void live();

            void move(float step);
            void spin(float step);

            void setController(const boost::shared_ptr<IController>& controller);

        private:

            bool isOnWay(const ObjectPtr& object) const;

            std::mutex synchroMutex_;

            boost::shared_ptr<IController> controller_;

            static const float MIN_MOVE;

            bool isMoving_;


    };

}

#endif
