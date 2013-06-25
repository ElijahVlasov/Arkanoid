#ifndef _ENGINE_OBJECT_HPP
#define _ENGINE_OBJECT_HPP

#include <mutex>
#include <stdexcept>
#include <string>

#include <boost/shared_ptr.hpp>

#include <Engine/Direction.hpp>
#include <Engine/ISprite.hpp>
#include <Engine/LocationLayer.hpp>

#include <Utils/ResourceManager.hpp>
#include <Utils/Texture.hpp>

#include "geometry_defines.hpp"

namespace Engine {

    /** Базовый объект игры.
      * @author Elijah Vlasov
    */

    class Object {

        public:

            Object();
            virtual ~Object();

            /** Собитие столкновения с другим объектом.
            */

            virtual void onCollision() = 0;

            /** Отрисовка объекта.
            */

            virtual void onRender();

            /** То, что будет выполняться все время жизни объекта.
            */

            virtual void live() = 0;

            /** Передвинуть объект на xShift и yShift.
            */

            virtual void move(float xShift, float yShift);

            /** Объекты равны если id'ы равны.
            */

            inline bool operator == (const Object& object) { return id_ == object.id_; }

            /** Объекты не равны если id'ы не равны.
            */

            inline bool operator != (const Object& object) { return !(*this == object); }

            void setDirection(Direction dir);
            Direction getDirection() const;

            /** Установить слой локации, в котором находится объект.
            */

            void setParentLayer(const LocationLayerPtr& layer);

            /** Слой локации, в котором находится объект.
            */

            const LocationLayerPtr& getParentLayer() const;

            /** Идентификатор объекта.
            */

            int getId() const;

            /** Установить рендерер объекта.
            */
            void setSprite(const boost::shared_ptr<ISprite>& sprite);

            /** Получить бокс объекта (потоко-небезопасный метод).
            */

            GeometryDefines::Box& box();

        private:

            mutable std::mutex synchroMutex_;

            LocationLayerPtr parentLayer_;

            GeometryDefines::Box box_;

            boost::shared_ptr<ISprite> sprite_;

            Direction dir_;

            int id_;

    };

    typedef boost::shared_ptr<Object> ObjectPtr;

}

#endif

namespace Engine {

    class Object;

    typedef boost::shared_ptr<Object> ObjectPtr;

}
