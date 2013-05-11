/****************************************************	

	Базовый класс для всех объектов игры

****************************************************/

#ifndef _ENGINE_OBJECT_HPP
#define _ENGINE_OBJECT_HPP

#include <Engine/Direction.hpp>

#include <Utils/Texture.hpp>

namespace Engine {

	class Object {

		public:

			virtual ~Object();

			virtual void onCollision();

			// обновить состояние объекта
			virtual void onUpdate() = 0;

			virtual void onRender();

			
		/*	void  setAngle(int angle);
			int getAngle()const;*/

			void  setWidth(float width);
			float getWidth()const;

			void  setHeight(float height);
			float getHeight()const;

			void  setX(float x);
			float getX()const;

			void  setY(float y);
			float getY()const;

			int getId()const;

                        Utils

		protected:

			Utils::Texture* texture_;

			float x_, y_;

			float width_, height_;

			DIRECTION dir_;

			int id_;

	};

}


#endif
