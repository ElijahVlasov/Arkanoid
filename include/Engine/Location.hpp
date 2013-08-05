#ifndef _SALT2D_ENGINE_LOCATION_HPP
#define _SALT2D_ENGINE_LOCATION_HPP

#include <list>
#include <string>
#include <stdexcept>

#include <boost/shared_ptr.hpp>

#include <Utils/Graphics/Texture.hpp>

#include "World.pb.h"

namespace Engine {

	class Object;

	typedef boost::shared_ptr<Object> ObjectPtr;

	class Location {

		public:

			Location();
			Location(const EngineData::Location& locationData) throw(std::runtime_error);

			~Location();

			void setGroundTexture(const boost::shared_ptr<Utils::Graphics::Texture>& groundTexture);
			boost::shared_ptr<Utils::Graphics::Texture> getGroundTexture() const;

			void addObject(const ObjectPtr& object);

			void deleteObject(const ObjectPtr& object);
			void deleteObject(const Object& object);

			void setWidth(float width);
			float getWidth() const;

			void setHeight(float height);
			float getHeight() const;

			void setName(const char* name);
			void setName(const std::string& name);
			std::string getName() const;

		private:

			float width_, height_;

			std::string name_;

			boost::shared_ptr<Utils::Graphics::Texture> groundTexture_;

			std::list<ObjectPtr> objects_;

	};

	typedef boost::shared_ptr<Location> LocationPtr;

}

#endif
