#ifndef _ENGINE_OBJECT_HPP
#define _ENGINE_OBJECT_HPP

#include <cmath>

#include <mutex>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

#include <boost/uuid/uuid.hpp>

#include <Engine/Location.hpp>

#include <Utils/ResourceManager.hpp>
#include <Utils/Sprite.hpp>
#include <Utils/Texture.hpp>

#include "geometry_defines.hpp"

namespace Engine {

	class Object;

    typedef boost::shared_ptr<Object> ObjectPtr;

    class Collision;

    /** Базовый объект игры.
      * @author Elijah Vlasov
    */

    class Object: public boost::noncopyable {

        public:

            typedef GeometryDefines::Point DirectionVector;

            Object();
            virtual ~Object();

            /** Собитие столкновения с другим объектом.
            */

            virtual void onCollision(const Collision& collision) = 0;

            /** Отрисовка объекта.
            */

            virtual void onRender();

            /** То, что будет выполняться все время жизни объекта.
            */

            virtual void live() = 0;

            /** Передвинуть объект на step в текущем направлении.
            */

            virtual void move(float step) = 0;

            /** Повернуть объект на step.
              * @param step Единица измерения - 1 / (2 * pi).
            */

            virtual void spin(float step) = 0;

            /** Установить локацию, в которой находится объект.
            */

            void setLocation(const LocationPtr& location);

            /** Локация, в которой находится объект.
            */

            const LocationPtr& getLocation() const;

            /** Идентификатор объекта.
            */

            boost::uuids::uuid getId() const;

            inline void addToDirection(float step);
            void setDirection(float direction);

            float getDirection() const;

            DirectionVector getDirectionVector() const;

            /** Установить рендерер объекта.
            */
            void setSprite(const boost::shared_ptr<Utils::Sprite>& sprite);

            /** Получить полигон объекта.
            */

            GeometryDefines::Polygon getPolygon() const;

            GeometryDefines::Polygon& polygon();

            virtual GeometryDefines::Point getCenter() const;

        private:

            mutable std::mutex synchroMutex_;

            LocationPtr location_;

            GeometryDefines::Polygon polygon_;

            boost::shared_ptr<Utils::Sprite> sprite_;

            float direction_;

            boost::uuids::uuid id_;

    };



    void Object::addToDirection(float step) {

    	direction_ += step;

    	if( (direction_ > 1.0f)
    			|| (direction_ < -1.0f)) {

    		double fractPart, intPart;

    		fractPart = modf(direction_, &intPart);

    		fractPart = copysign(fractPart, intPart);

    		direction_ = static_cast<float>(fractPart);

    	}

    	if(direction_ < 0.0f) {

    		direction_ += 1.0f;

    	}

    }

    inline bool operator == (const Object& obj1, const Object& obj2) { return obj1.getId() == obj2.getId(); }
    inline bool operator != (const Object& obj1, const Object& obj2) { return obj1.getId() != obj2.getId(); }

}

#endif
