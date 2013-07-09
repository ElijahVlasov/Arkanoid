#ifndef _ENGINE_OBJECT_HPP
#define _ENGINE_OBJECT_HPP

#include <cmath>

#include <mutex>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>
#include <boost/utility.hpp>

#include <boost/uuid/uuid.hpp>

#include <Engine/Direction.hpp>
#include <Engine/LocationLayer.hpp>

#include <Utils/ResourceManager.hpp>
#include <Utils/ISprite.hpp>
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

            virtual void move(float step);

            /** Повернуть объект на step.
              * @param step Единица измерения - 1 / (2 * pi).
            */

            virtual void spin(float step);

            /** Объекты равны если id'ы равны.
            */

            inline bool operator == (const Object& object) { return id_ == object.id_; }

            /** Объекты не равны если id'ы не равны.
            */

            inline bool operator != (const Object& object) { return !(*this == object); }

            /** Установить слой локации, в котором находится объект.
            */

            void setParentLayer(const LocationLayerPtr& layer);

            /** Слой локации, в котором находится объект.
            */

            const LocationLayerPtr& getParentLayer() const;

            /** Идентификатор объекта.
            */

            boost::uuids::uuid getId() const;

            float getDirection() const;

            DirectionVector getDirectionVector() const;

            /** Установить рендерер объекта.
            */
            void setSprite(const boost::shared_ptr<Utils::ISprite>& sprite);

            /** Получить полигон объекта.
            */

            GeometryDefines::Polygon getPolygon() const;

            virtual GeometryDefines::Point getCenter() const;

        private:

            mutable std::mutex synchroMutex_;

            LocationLayerPtr parentLayer_;

            GeometryDefines::Polygon polygon_;

            boost::shared_ptr<Utils::ISprite> sprite_;

            inline void addToDirection(float step);

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



}

#endif
